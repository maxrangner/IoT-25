#include "rc522.h"
#include "spi.h"

#include <avr/io.h>
#include <util/delay.h>

#define RC522_SS_DDR DDRB
#define RC522_SS_PORT PORTB
#define RC522_SS_PIN PORTB2

#define RC522_RST_DDR DDRB
#define RC522_RST_PORT PORTB
#define RC522_RST_PIN PORTB1

#define RC522_STATUS2_MFCrypto1On 0x08
#define RC522_DIVIRQ_CRCIRq 0x04

static const uint8_t rc522_default_key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

static rc522_tag_t rc522_empty_tag(uint8_t status)
{
    rc522_tag_t tag = {status, {0, 0, 0, 0}};
    return tag;
}

static void rc522_select(void)
{
    RC522_SS_PORT &= ~(1 << RC522_SS_PIN);
}

static void rc522_deselect(void)
{
    RC522_SS_PORT |= (1 << RC522_SS_PIN);
}

static uint8_t rc522_calculate_crc(
    const uint8_t *data,
    uint8_t length,
    uint8_t result[2]
)
{
    uint16_t timeout = 5000;
    uint8_t i;

    rc522_write_reg(CommandReg, cmd_idle);
    rc522_clear_bitmask(DivIrqReg, RC522_DIVIRQ_CRCIRq);
    rc522_set_bitmask(FIFOLevelReg, 0x80);

    for (i = 0; i < length; i++) {
        rc522_write_reg(FIFODataReg, data[i]);
    }

    rc522_write_reg(CommandReg, cmd_calcCRC);

    do {
        if ((rc522_read_reg(DivIrqReg) & RC522_DIVIRQ_CRCIRq) != 0U) {
            result[0] = rc522_read_reg(CRCResultRegL);
            result[1] = rc522_read_reg(CRCResultRegH);
            rc522_write_reg(CommandReg, cmd_idle);
            return RC522_OK;
        }

        timeout--;
    } while (timeout != 0U);

    rc522_write_reg(CommandReg, cmd_idle);
    return RC522_ERR_TIMEOUT;
}

static void rc522_stop_crypto(void)
{
    rc522_clear_bitmask(Status2Reg, RC522_STATUS2_MFCrypto1On);
}

static uint8_t rc522_authenticate(
    uint8_t block_addr,
    const uint8_t key[6],
    const uint8_t uid[4]
)
{
    uint8_t buffer[12];

    buffer[0] = PICC_AUTHENT1A;
    buffer[1] = block_addr;
    buffer[2] = key[0];
    buffer[3] = key[1];
    buffer[4] = key[2];
    buffer[5] = key[3];
    buffer[6] = key[4];
    buffer[7] = key[5];
    buffer[8] = uid[0];
    buffer[9] = uid[1];
    buffer[10] = uid[2];
    buffer[11] = uid[3];

    if (rc522_to_card(cmd_mfAuthent, buffer, 12, 0, 0) != RC522_OK) {
        return RC522_ERR;
    }

    if ((rc522_read_reg(Status2Reg) & RC522_STATUS2_MFCrypto1On) == 0U) {
        return RC522_ERR;
    }

    return RC522_OK;
}

static uint8_t rc522_write_block(uint8_t block_addr, const uint8_t data[16])
{
    uint8_t buffer[18];
    uint8_t response[RC522_MAX_LEN];
    uint8_t response_bits = 0;

    buffer[0] = PICC_WRITE;
    buffer[1] = block_addr;

    if (rc522_calculate_crc(buffer, 2, &buffer[2]) != RC522_OK) {
        return RC522_ERR;
    }

    if (rc522_to_card(cmd_transceive, buffer, 4, response, &response_bits) != RC522_OK) {
        return RC522_ERR;
    }

    if ((response_bits != 4U) || ((response[0] & 0x0FU) != 0x0AU)) {
        return RC522_ERR;
    }

    buffer[0] = data[0];
    buffer[1] = data[1];
    buffer[2] = data[2];
    buffer[3] = data[3];
    buffer[4] = data[4];
    buffer[5] = data[5];
    buffer[6] = data[6];
    buffer[7] = data[7];
    buffer[8] = data[8];
    buffer[9] = data[9];
    buffer[10] = data[10];
    buffer[11] = data[11];
    buffer[12] = data[12];
    buffer[13] = data[13];
    buffer[14] = data[14];
    buffer[15] = data[15];

    if (rc522_calculate_crc(buffer, 16, &buffer[16]) != RC522_OK) {
        return RC522_ERR;
    }

    if (rc522_to_card(cmd_transceive, buffer, 18, response, &response_bits) != RC522_OK) {
        return RC522_ERR;
    }

    if ((response_bits != 4U) || ((response[0] & 0x0FU) != 0x0AU)) {
        return RC522_ERR;
    }

    return RC522_OK;
}

void rc522_write_reg(uint8_t reg, uint8_t value)
{
    rc522_select();
    spi_master_tranceiver((reg << 1) & 0x7E);
    spi_master_tranceiver(value);
    rc522_deselect();
}

uint8_t rc522_read_reg(uint8_t reg)
{
    uint8_t value;

    rc522_select();
    spi_master_tranceiver(((reg << 1) & 0x7E) | 0x80);
    value = spi_master_tranceiver(0x00);
    rc522_deselect();

    return value;
}

void rc522_set_bitmask(uint8_t reg, uint8_t mask)
{
    rc522_write_reg(reg, rc522_read_reg(reg) | mask);
}

void rc522_clear_bitmask(uint8_t reg, uint8_t mask)
{
    rc522_write_reg(reg, rc522_read_reg(reg) & (uint8_t)~mask);
}

void rc522_reset(void)
{
    rc522_write_reg(CommandReg, cmd_softReset);
    _delay_ms(50);
}

void rc522_antenna_on(void)
{
    if ((rc522_read_reg(TxControlReg) & 0x03) != 0x03) {
        rc522_set_bitmask(TxControlReg, 0x03);
    }
}

void rc522_init(void)
{
    RC522_SS_DDR |= (1 << DDB2);
    RC522_RST_DDR |= (1 << DDB1);

    rc522_deselect();
    RC522_RST_PORT |= (1 << RC522_RST_PIN);

    rc522_reset();

    rc522_write_reg(TModeReg, 0x8D);
    rc522_write_reg(TPrescalerReg, 0x3E);
    rc522_write_reg(TReloadRegL, 30);
    rc522_write_reg(TReloadRegH, 0);
    rc522_write_reg(TxASKReg, 0x40);
    rc522_write_reg(ModeReg, 0x3D);

    rc522_antenna_on();
}

uint8_t rc522_to_card(
    uint8_t command,
    const uint8_t *send_data,
    uint8_t send_len,
    uint8_t *back_data,
    uint8_t *back_len
)
{
    uint8_t irq_en = 0x00;
    uint8_t wait_irq = 0x00;
    uint8_t last_bits;
    uint8_t n;
    uint16_t timeout;
    uint8_t i;

    if (command == cmd_mfAuthent) {
        irq_en = 0x12;
        wait_irq = 0x10;
    } else if (command == cmd_transceive) {
        irq_en = 0x77;
        wait_irq = 0x30;
    }

    rc522_write_reg(ComIEnReg, irq_en | 0x80);
    rc522_clear_bitmask(ComIrqReg, 0x80);
    rc522_set_bitmask(FIFOLevelReg, 0x80);
    rc522_write_reg(CommandReg, cmd_idle);

    for (i = 0; i < send_len; i++) {
        rc522_write_reg(FIFODataReg, send_data[i]);
    }

    rc522_write_reg(CommandReg, command);

    if (command == cmd_transceive) {
        rc522_set_bitmask(BitFramingReg, 0x80);
    }

    timeout = 2000;
    do {
        n = rc522_read_reg(ComIrqReg);
        timeout--;
    } while ((timeout != 0U) && ((n & 0x01) == 0U) && ((n & wait_irq) == 0U));

    rc522_clear_bitmask(BitFramingReg, 0x80);

    if (timeout == 0U) {
        return RC522_ERR_TIMEOUT;
    }

    if ((rc522_read_reg(ErrorReg) & 0x1B) != 0U) {
        return RC522_ERR;
    }

    if (back_data != 0 && back_len != 0) {
        n = rc522_read_reg(FIFOLevelReg);
        last_bits = rc522_read_reg(ControlReg) & 0x07;

        if (last_bits != 0U) {
            *back_len = (uint8_t)((n - 1U) * 8U + last_bits);
        } else {
            *back_len = (uint8_t)(n * 8U);
        }

        if (n == 0U) {
            n = 1U;
        }

        if (n > RC522_MAX_LEN) {
            n = RC522_MAX_LEN;
        }

        for (i = 0; i < n; i++) {
            back_data[i] = rc522_read_reg(FIFODataReg);
        }
    }

    return RC522_OK;
}

uint8_t rc522_request(uint8_t req_mode, uint8_t *tag_type)
{
    uint8_t back_bits = 0;
    uint8_t buffer[2];
    uint8_t status;

    rc522_write_reg(BitFramingReg, 0x07);

    buffer[0] = req_mode;
    status = rc522_to_card(cmd_transceive, buffer, 1, tag_type, &back_bits);

    if ((status != RC522_OK) || (back_bits != 0x10)) {
        return RC522_ERR;
    }

    return RC522_OK;
}

uint8_t rc522_anticoll(uint8_t *ser_num)
{
    uint8_t i;
    uint8_t ser_num_check = 0;
    uint8_t back_len = 0;
    uint8_t buffer[2];
    uint8_t status;

    rc522_write_reg(BitFramingReg, 0x00);

    buffer[0] = PICC_ANTICOLL;
    buffer[1] = 0x20;

    status = rc522_to_card(cmd_transceive, buffer, 2, ser_num, &back_len);
    if (status != RC522_OK) {
        return status;
    }

    if (back_len != 40U) {
        return RC522_ERR;
    }

    for (i = 0; i < 4; i++) {
        ser_num_check ^= ser_num[i];
    }

    if (ser_num_check != ser_num[4]) {
        return RC522_ERR;
    }

    return RC522_OK;
}

rc522_tag_t rc522_read_tag(void)
{
    uint8_t tag_type[2];
    uint8_t raw_uid[5];
    rc522_tag_t tag = rc522_empty_tag(RC522_ERR);

    if (rc522_request(PICC_REQIDL, tag_type) != RC522_OK) {
        return tag;
    }

    tag.status = rc522_anticoll(raw_uid);
    if (tag.status != RC522_OK) {
        return tag;
    }

    tag.uid[0] = raw_uid[0];
    tag.uid[1] = raw_uid[1];
    tag.uid[2] = raw_uid[2];
    tag.uid[3] = raw_uid[3];

    return tag;
}

uint8_t rc522_write_tag(uint8_t block_addr, const uint8_t data[16])
{
    rc522_tag_t tag = rc522_read_tag();
    uint8_t status;

    if (tag.status != RC522_OK) {
        return tag.status;
    }

    status = rc522_authenticate(block_addr, rc522_default_key, tag.uid);
    if (status != RC522_OK) {
        rc522_stop_crypto();
        return status;
    }

    status = rc522_write_block(block_addr, data);
    rc522_stop_crypto();

    return status;
}
