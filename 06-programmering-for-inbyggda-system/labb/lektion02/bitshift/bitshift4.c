#include <stdio.h> 
#include <stdbool.h>

void printBits(size_t const size, void const* const ptr)
{
    unsigned char* b = (unsigned char*)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}




#define BIT_SET(tal, bitNo) ((tal) |= (1ULL << (bitNo)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

//#define MINI_INT char

//    kan du gå igenom MSB & LSB eller missade jag det ?

int main(){
    //unsigned char PORTB = 255; // 11111111
    //unsigned char PORTC = 15; // 00001111
    unsigned char PORTD = 214; // 
    //unsigned char PORTAAA = 'A'; // printf("%c")

    printBits(sizeof(PORTD), &PORTD);

    unsigned char PORTE = 0b00000110; //6
                //        0b00001000
                //        0b00001110 

    // sätt bit 4 till 1 UTANM ATT ÄNDRA DOM ANDRA BITARNA
    PORTE = PORTE | 0b00001000;
    PORTE = PORTE | 0b00100000; // BIT 6
    PORTE = PORTE | ( 1 << 6);
    BIT_SET(PORTE,6);

    // CLEAR BIT nr 6 - släcka led-lampan
    // AND
    // 0b00110010
    // 0b00100000 - 6 biten
    // 0b11011111
    // 0b00010010
    // Skapa tal med aktuell bit satt!
    // invertera det talet 
    // använder inverterat tal som AND
    
    //PORTE = PORTE & ~0b00100000;
    //PORTE = PORTE & ~( 1 << 6);
    BIT_CLEAR(PORTE,6);

    // Vi vill kolla om bit 6 är satt
    //
    if(BIT_CHECK(PORTE,6)){

    }  
    // if(PORTE & 0b00100000){

    // }

    // efter

    // & bitwise and
    // bitwise or
    // bitwise not
    // SÄTTA EN VISS BIT ("göra sp en specifik LED lyser - tex nr 3")        
    // digitalWrite(3, HIGH);


    //int n;
    //scanf -> n
    // 65, 98
    // 010000001
    //char x = 'A'; // 65

    // unsigned char PORTD = 0; // 8 bitar
    // //Lets set bit 3 så ledLED på tredje börjar lysa
    // //PORTD |= (1 << 3) | (1 << 5);
    // // BITTARNAS NUMMER STARTAR PÅ 0
    // BIT_SET(PORTD,3);
    // BIT_SET(PORTD,5);

    // printBits(sizeof(PORTD),&PORTD);

    // // CLEARA EN BIT
    // //PORTD &= ~(1 << 5);
    // // a &= ~(1ULL<<b)
    // BIT_CLEAR(PORTD,5);
    // printBits(sizeof(PORTD),&PORTD);


    // // (!!((a) & (1ULL<<(b)))) 

    // if(BIT_CHECK(PORTD,5)){

    // }


    //  while(true){
    //     printf("1. Mata in ett tal\n");        
    //     printf("2. Skriv ut bittarna\n");        
    //     printf("3. Set a bit\n");        
    //     printf("4. Clear a bit\n");        
    //     printf("Action:");
    //     int action;
    //     scanf(" %d",&action);
    //     if(action == 1){
    //         printf("Ange ett tal:");
    //         scanf(" %c", &PORTD);
    //     }
    //     if(action == 2){
    //         printf("TALET in BINARY\n");
    //         printBits(sizeof(PORTD), &PORTD);
    //     }
    //     if(action == 3){
    //         // skapa 0x00000001
    //         //                 0x01101100
    //         // talet = talet | 0x0001001 -< SIUSTA BITENM ÄR satt
    //         //                 0x01101101  

    //         // 0b000010100
    //         //talet |= (1 << 3) | (1 << 5);
    //         //BIT_SET(talet,3);
    //         //BIT_SET(talet,5);

    //         printf("Enter bitnumber to set\n");
    //         //
    //         int bitNo;
    //         scanf(" %d",&bitNo);
    //         BIT_SET(PORTD,bitNo);
    //         //((talet) |= (1ULL << (bitNo)));
            
    //     }


    // }

    // // unsigned int v = 0b10010000;
    // // printf("%d\n",v);
    // // printBits(sizeof(v),&v);

    // //unsigned int v = 12;
    // return 0;
}