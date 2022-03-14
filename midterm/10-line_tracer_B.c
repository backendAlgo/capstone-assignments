
//Motor + Ultrasonic + Line Tracer

#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <softPwm.h>
#include <signal.h>

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6
// 8v
// #define MAX_SPEED 40
// #define MID_SPEED 25
// #define MIN_SPEED 0
// 7.5v

#define turnDelay 30

#define TRIG_PIN		28
#define ECHO_PIN		29

void initLineTacer();
void initDCMotor();
void initDCPWMMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void smoothForward();
void smoothRight();
void smoothLeft();
void stopDCMotor();
void stopDCPWMMotor();

void initUltrasonic();
void lineTracerDetect();
int getDistance();

int dist;
int leftTracer;
int rightTracer;
bool test1 = false;

int const MAX_SPEED = 100;
int NORM_SPEED = MAX_SPEED/3;
int MID_SPEED = MAX_SPEED/4;
int const MIN_SPEED = 0;

void signal_callback_handler(int signum) {
   printf("Caught Signal: %d", signum);
   stopDCPWMMotor();
   exit(signum);
}
int main(void) {
	signal(SIGINT, signal_callback_handler);
    if (wiringPiSetup() == -1)
        return 0;

    initLineTacer();
    initUltrasonic();
    initDCPWMMotor();
	int count = 0;
    
    while (1) {

	dist = getDistance();
	printf("Distance: %d\n", dist);

        if(dist <= 15){
			count++;
			printf("Count: %d\n", count);
			if (count == 3) {
				// do manevour
			} else {				
				dist = getDistance();
				while (dist <= 15)
				{
					stopDCPWMMotor();
					printf("STOP: distance is less than 15cm\n");
					delay(1500);
					dist = getDistance();
				}				
			}  
        } else{
		lineTracerDetect();
		
		if(test1==true){
			
			break;}
		}
	
		
	}

    return 0;
}

void initLineTacer() {
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}


void initUltrasonic(){
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

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


void goForward()
{
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, LOW);
	digitalWrite(IN3_PIN, HIGH);
	digitalWrite(IN4_PIN, LOW);
	
}


void goBackward()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, HIGH);
	
}


void goLeft()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, HIGH);
	digitalWrite(IN4_PIN, LOW);
	
}

void goRight()
{
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, LOW);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, HIGH);
	
}

void smoothForward()
{
softPwmWrite(IN1_PIN, NORM_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, NORM_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}
void smoothRight()
{
softPwmWrite(IN1_PIN, NORM_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MID_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void smoothLeft()
{
softPwmWrite(IN1_PIN, MID_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, NORM_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void stopDCMotor()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, LOW);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, LOW);
	
}
void stopDCPWMMotor()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);		
//printf("Stop\n");
}	




int getDistance()
{
	int 		start_time=0, end_time=0;
	float 	distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(30) ;
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



void lineTracerDetect(){
	
 leftTracer = digitalRead(LEFT_TRACER_PIN);
 rightTracer = digitalRead(RIGHT_TRACER_PIN);
	
	
	if (leftTracer == 0 && rightTracer == 1) {
            printf("Right\n");
			smoothRight();
			delay(turnDelay);


        }
        else if (rightTracer == 0 && leftTracer == 1) {
            printf("Left\n");
			smoothLeft();
			delay(turnDelay);


        }
        else if (rightTracer == 0 && leftTracer == 0) {
            printf("Stop\n");
			stopDCPWMMotor();
			delay(turnDelay);
			// test1 = true;
			

        }
        else if (rightTracer == 1 && leftTracer == 1) {
            printf("Forward\n");
			smoothForward();
			delay(turnDelay);

        }
	
	}

//gcc 10-line_tracer_B.c -o lineb -lwiringPi
// ./lineb
