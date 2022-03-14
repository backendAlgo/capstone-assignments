#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define TRIG_PIN		28
#define ECHO_PIN		29

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define MAX_SPEED 63
#define MIN_SPEED 0

void initDCMotor();
void initUltrasonic();
void smoothForward();
void smoothRight();
void smoothLeft();
int getDistance();
void stopDCMotor();

int dist;

int c;

int main(void)
{
	if(wiringPiSetup() == -1)
		return 0;
	
	initUltrasonic();
	initDCMotor();
	while(1)
	{
		dist = getDistance();

        if(dist <= 25){
			if (c == 0){
				smoothRight();
				delay(900);
				smoothForward();
				delay(900);
				smoothLeft();
				delay(900);
			}
            else if (c == 1){
				smoothRight();
				delay(850);
				smoothForward();
				delay(200);
				smoothLeft();
				delay(900);
				smoothForward();
				delay(1700);
				smoothLeft();
				delay(900); //850
			}
			else if (c == 2){
				smoothRight();
				delay(900);
				smoothForward();
				delay(250);
				smoothLeft();
				delay(950);
				smoothForward();
				delay(1900);
				smoothLeft();
				delay(900);
			}
			else if (c == 3){
				smoothRight();
				delay(900);
				smoothForward();
				delay(250);
				smoothLeft();
				delay(850);
				smoothForward();
				delay(1700);
				smoothLeft();
				delay(850);
			}
			else if (c == 4){
				smoothRight();
				delay(900);
				smoothForward();
				delay(320);
				smoothLeft();
				delay(900);
				smoothForward();
				delay(250);
				smoothRight();
				delay(1000);
				smoothForward();
				delay(1000);
				stopDCMotor();
				delay(5000);
				break;
			}
            if (c == 5) {
				stopDCMotor();
				delay(5000);
				break;
			}
            c++;
            continue;
        } 
        else{
			smoothForward();
		}
	}
	return 0;
}

void initUltrasonic(){
    pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
}

int getDistance()
{
	int start_time=0, end_time=0;
	float distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(100);
    digitalWrite(TRIG_PIN, HIGH) ;
    delayMicroseconds(10) ;
    digitalWrite(TRIG_PIN, LOW) ;
    
    while (digitalRead(ECHO_PIN) == 0) ;
    start_time = micros() ;
    
    while (digitalRead(ECHO_PIN) == 1) ;
    end_time = micros() ;
    
    distance = (end_time - start_time) / 29. / 2. ;
	
	return (int)distance;
}

void initDCMotor()
{
pinMode(IN1_PIN,SOFT_PWM_OUTPUT);
pinMode(IN2_PIN,SOFT_PWM_OUTPUT);
pinMode(IN3_PIN,SOFT_PWM_OUTPUT);
pinMode(IN4_PIN,SOFT_PWM_OUTPUT);
 
softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}

void smoothForward()
{
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void smoothRight()
{
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED/8);
}

void smoothLeft()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED/8);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void stopDCMotor()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);		
//printf("Stop\n");
}	
