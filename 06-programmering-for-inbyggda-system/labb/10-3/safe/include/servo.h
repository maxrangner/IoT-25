#ifndef _SERVO_H_
#define _SERVO_H_

#define PORT_SERVO	PORTD
#define PIN_SERVO	PD5
#define DDR_SERVO	DDRD


void init_servo(void);
void servo_set_percentage(signed char percentage);
 
#endif /* _SERVO_H_ */