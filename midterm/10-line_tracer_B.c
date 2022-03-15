
//Motor + Ultrasonic + Line Tracer

#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <softPwm.h>
#include <signal.h>

#define LEFT_TRACER_PIN 10
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26
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


#define TRIG_PIN		28
#define ECHO_PIN		29

void initIR();
void initLineTacer();
int leftIR;
int mLeftIR;
int mRightIR; 
int rightIR;
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
// int NORM_SPEED = 60; // Good for <7v
int NORM_SPEED = 50; // Good for >7v
int MID_SPEED = 5;
int const MIN_SPEED = 0;

// int turnDelay = 60; // Good for <7v
int turnDelay = 90; // Good for >7v
int turner = 0;
int lastTurn = 0;

void signal_callback_handler(int signum) {
   printf("Caught Signal: %d", signum);
   stopDCPWMMotor();
   exit(signum);
}
int main(void) {
	stopDCPWMMotor();
	signal(SIGINT, signal_callback_handler);
	stopDCPWMMotor();
    if (wiringPiSetup() == -1)
        return 0;

    initIR();
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
			if (count == 2 && NORM_SPEED == 60) {
				printf("C obstacle detected...\n");
				smoothRight(-1);
				printf("turning right\n");
				delay(500);
				smoothForward();
				printf("moving forward\n");
				delay(900);
				smoothLeft(-1);
				printf("turning left\n");
				delay(500);
				smoothForward();
				printf("moving forward\n");
				delay(1300);
				smoothLeft(-1);
				printf("turning left\n");
				delay(500);
				smoothForward();
				printf("moving forward\n");
				delay(1200);
				smoothRight(-1);
				printf("turning right\n");
				delay(500);
				smoothForward();
				printf("moving forward\n");
				delay(1000);
				printf("C obstacle end...\n");
			} 
			else if (count == 2 && NORM_SPEED == 50) {
				int inc = 200;
				printf("C obstacle detected...\n");
				smoothRight(-1);
				printf("turning right\n");
				delay(500 + inc);
				smoothForward();
				printf("moving forward\n");
				delay(900 + inc-50);
				smoothLeft(-1);
				printf("turning left\n");
				delay(500 + inc);
				smoothForward();
				printf("moving forward\n");
				delay(1300 + inc);
				smoothLeft(-1);
				printf("turning left\n");
				delay(500 + inc);
				smoothForward();
				printf("moving forward\n");
				delay(1200 + inc -50);
				smoothRight(-1);
				printf("turning right\n");
				delay(500 + inc + 100);
				smoothForward();
				printf("moving forward\n");
				delay(800 + inc);
				printf("C obstacle end...\n");
			}
			else if (count == 3) {
				printf("D obstacle need stop...\n");
				stopDCPWMMotor();
				delay(1000);
				test1 = true;
			} 
			else {				
				printf("A obstacle wait till removing...\n");
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

void initIR()
{
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
		
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
softPwmWrite(IN1_PIN, NORM_SPEED-15);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, NORM_SPEED-15);
softPwmWrite(IN4_PIN, MIN_SPEED);
}
void smoothRight(int add)
{
	if (add == 2) {
		softPwmWrite(IN1_PIN, MAX_SPEED -20);
		softPwmWrite(IN2_PIN, MIN_SPEED);
		softPwmWrite(IN3_PIN, MID_SPEED);
		softPwmWrite(IN4_PIN, MIN_SPEED);
	}
	else if (add == 1) {
		softPwmWrite(IN1_PIN, NORM_SPEED);
		softPwmWrite(IN2_PIN, MIN_SPEED);
		softPwmWrite(IN3_PIN, MIN_SPEED);
		softPwmWrite(IN4_PIN, MIN_SPEED);
	}
	else if (add == 0) {
		softPwmWrite(IN1_PIN, NORM_SPEED);
		softPwmWrite(IN2_PIN, MIN_SPEED);
		softPwmWrite(IN3_PIN, MIN_SPEED);
		softPwmWrite(IN4_PIN, MID_SPEED);
	}
	else if (add == -1) {
		softPwmWrite(IN1_PIN, NORM_SPEED);
		softPwmWrite(IN2_PIN, MIN_SPEED);
		softPwmWrite(IN3_PIN, MIN_SPEED);
		softPwmWrite(IN4_PIN, NORM_SPEED);
	}
}

void smoothLeft(int add)
{
if (add == 2) {
		softPwmWrite(IN1_PIN, MID_SPEED);
		softPwmWrite(IN2_PIN, MIN_SPEED);
		softPwmWrite(IN3_PIN, MAX_SPEED -20);
		softPwmWrite(IN4_PIN, MIN_SPEED);
	}
	else if (add == 1) {
		softPwmWrite(IN1_PIN, MIN_SPEED);
		softPwmWrite(IN2_PIN, MIN_SPEED);
		softPwmWrite(IN3_PIN, NORM_SPEED);
		softPwmWrite(IN4_PIN, MIN_SPEED);
	}
	else if (add == 0) {
		softPwmWrite(IN1_PIN, MIN_SPEED);
		softPwmWrite(IN2_PIN, MID_SPEED);
		softPwmWrite(IN3_PIN, NORM_SPEED);
		softPwmWrite(IN4_PIN, MIN_SPEED);
	}
	else if (add == -1) {
		softPwmWrite(IN1_PIN, MIN_SPEED);
		softPwmWrite(IN2_PIN, NORM_SPEED);
		softPwmWrite(IN3_PIN, NORM_SPEED);
		softPwmWrite(IN4_PIN, MIN_SPEED);
	}
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
    delay(10) ;
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
	leftIR = !digitalRead(LEFT_TRACER_PIN); // 1 will be white
        mLeftIR = !digitalRead(LEFT_IR_PIN);
        mRightIR = !digitalRead(RIGHT_IR_PIN);
        rightIR = !digitalRead(RIGHT_TRACER_PIN);
        printf("%d %d %d %d\n", leftIR, mLeftIR, mRightIR, rightIR);

        // Left
        if (leftIR && !mLeftIR && !mRightIR && !rightIR) {
            printf("Go Slight Right\n");
			smoothRight(2);
			lastTurn = 1;
			delay(turnDelay);
        }
        else if (!leftIR && mLeftIR && !mRightIR && !rightIR) {
            printf("Go More Right\n");
			if (lastTurn == -1) {
            	printf("Calibrate: Go More Left\n");
				smoothLeft(-1);
				delay(turnDelay + 20);
			}
			else {
            	printf("Go More Right\n");
				smoothRight(-1);
				delay(turnDelay *5);
			}
				lastTurn = 1;
		}
        else if (leftIR && mLeftIR && !mRightIR && !rightIR) {
            printf("Go More More Right\n");
			smoothRight(-1);
			lastTurn = 1;
			// // delay(turnDelay);
        }
        else if ((leftIR && mLeftIR && mRightIR && !rightIR) ||
                 (leftIR && !mLeftIR && mRightIR && !rightIR) ||
                 (leftIR && mLeftIR && !mRightIR && rightIR)) {
            printf("Go Sharp Right\n");
			smoothRight(-1);
			lastTurn = 1;
			// // delay(turnDelay);
        }
        // Forward
        else if (!leftIR && !mLeftIR && !mRightIR && !rightIR) {
            printf("Go Forward\n");
			smoothForward();
			lastTurn = 0;
			// delay(50);
        }
        else if (!leftIR && mLeftIR && mRightIR && !rightIR) {
            printf("Go Forward 2\n");
			if (lastTurn < 0) {
				smoothLeft(-1);
				delay(turnDelay);
			}
			else if (lastTurn > 0) {
				smoothRight(-1);
				delay(turnDelay);
			}
			else {
				smoothForward();
			}
			lastTurn = 0;
			// delay(50);
        }
        // Stop
        else if (leftIR && !mLeftIR && !mRightIR && rightIR) {
            printf("Stop\n");
			stopDCPWMMotor();
			lastTurn = 0;
			// // delay(turnDelay);
        }
        else if (leftIR && mLeftIR && mRightIR && rightIR) {
            printf("Stop 2\n");
			stopDCPWMMotor();
			lastTurn = 0;
			// // delay(turnDelay);
        }
        // Right
        else if (!leftIR && !mLeftIR && !mRightIR && rightIR) {
            printf("Go Slight Left\n");
			smoothLeft(2);
			lastTurn = -1;
			delay(turnDelay);
        }
        else if (!leftIR && !mLeftIR && mRightIR && !rightIR) {
			if (lastTurn == 1) {
            	printf("Calibrate: Go More Right\n");
				smoothRight(-1);
				delay(turnDelay + 20);
			}
			else {
            	printf("Go More Left\n");
				smoothLeft(-1);
				delay(turnDelay *5);
			}
				lastTurn = -1;
        }
        else if (!leftIR && !mLeftIR && mRightIR && rightIR) {
            printf("Go More More Left\n");
			smoothLeft(-1);
			lastTurn = -1;
			// // delay(turnDelay);
        }
        else if ((!leftIR && mLeftIR && mRightIR && rightIR) ||
                 (!leftIR && mLeftIR && !mRightIR && rightIR) ||
                 (leftIR && !mLeftIR && mRightIR && rightIR)) {
            printf("Go Sharp Left\n");
			smoothLeft(-1);
			lastTurn = -1;
			// // delay(turnDelay);
        }


	// if (leftTracer == 0 && rightTracer == 1) {
	// 	if (lastTurn == 1) {
	// 		turner++;
	// 	}
	// 	else if (lastTurn == -1) {
	// 		turner == 0;
	// 	}
	// 	else {
	// 		turner == 0;
	// 	}
    //         printf("Right\n");
	// 		smoothRight(turner *1);
	// 		turner++;
			// delay(turnDelay + (turner *50));
	// 		lastTurn = 1;

    //     }
    //     else if (rightTracer == 0 && leftTracer == 1) {
	// 	if (lastTurn == -1) {
	// 		turner++;
	// 	}
	// 	else if (lastTurn == 1) {
	// 		turner == 0;
	// 	}
	// 	else {
	// 		turner == 0;
	// 	}
    //         printf("Left\n");
	// 		smoothLeft(turner *1);
			// delay(turnDelay + (turner *50));
	// 		lastTurn = -1;
    //     }
    //     else if (rightTracer == 0 && leftTracer == 0) {
    //         printf("Stop\n");
	// 		stopDCPWMMotor();
			// delay(turnDelay);
	// 		// test1 = true;
	// 		lastTurn = 0;
			


    //     }
    //     else if (rightTracer == 1 && leftTracer == 1) {
    //         printf("Forward\n");
	// 		smoothForward();
			// delay(50);
	// 		lastTurn = 0;

    //     }
	
	}

//gcc 10-line_tracer_B.c -o lineb -lwiringPi
// ./lineb
