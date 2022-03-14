// Stopper

#include <stdio.h>
#include <wiringPi.h>

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define MAX_SPEED 100
#define NORM_SPEED MAX_SPEED/4
#define MID_SPEED MID_SPEED/8
#define MIN_SPEED 0


void initDCMotor();
void initDCPWMMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();
void stopDCPWMMotor();

int main(void)
{
	if(wiringPiSetup() == -1)
		return 0;
	initDCPWMMotor();
	goForward();
	delay(100);
	stopDCPWMMotor();
	return 0;
}

void initDCMotor()
{
    	
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
	
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, HIGH);
	digitalWrite(IN4_PIN, HIGH);						
}

void goForward()
{
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);		
		printf("Forward\n");
}	

void goBackward()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);		
		printf("Backwrad\n");
}	
	
	
void goLeft()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);		
		printf("Left\n");
}	

void goRight()
{
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);		
		printf("Right\n");
}	

void stopDCMotor()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, LOW);		
		printf("Stop\n");
}		
void stopDCPWMMotor()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);		
//printf("Stop\n");
}	
void initDCPWMMotor() {
pinMode(IN1_PIN,SOFT_PWM_OUTPUT);
pinMode(IN2_PIN,SOFT_PWM_OUTPUT);
pinMode(IN3_PIN,SOFT_PWM_OUTPUT);
pinMode(IN4_PIN,SOFT_PWM_OUTPUT);
 
softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}