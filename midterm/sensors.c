// IR Sensors
// Example 1
// React if object detected on Right/Left/Both or No sides

#include <stdio.h>
#include <wiringPi.h>


#define LEFT_TRACER_PIN 10
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26
#define RIGHT_TRACER_PIN 11

#define LEFT_OBS		28
#define FRONT_OBS		29

#define TRIG_PIN		28
#define ECHO_PIN		29
int dist;

void initIR();
void initLineTacer();
void initUltrasonic();
int getDistance();
void initIROBS();

int leftIR;
int mLeftIR;
int mRightIR; 
int rightIR;

int leftOBS;
int frontOBS;
// int sensors[4];

int main(void){
    
    if(wiringPiSetup() == -1)
	    return 0;
  
    initIR();
    // initUltrasonic();
    initIROBS();

    while (1) {
        // dist = getDistance();
		// printf("Distance: %d\n", dist);
        leftOBS = !digitalRead(LEFT_IR_PIN);
        frontOBS = !digitalRead(RIGHT_IR_PIN);

        leftIR = !digitalRead(LEFT_TRACER_PIN); // 1 will be white
        mLeftIR = !digitalRead(LEFT_IR_PIN);
        mRightIR = !digitalRead(RIGHT_IR_PIN);
        rightIR = !digitalRead(RIGHT_TRACER_PIN);
        delay(30);
        printf("%d %d %d %d\n", leftIR, mLeftIR, mRightIR, rightIR);
        printf("LeftOBS: %d", leftOBS);
        printf("FrontOBS: %d", frontOBS);
        // Left
        if (leftIR && !mLeftIR && !mRightIR && !rightIR) {
            // printf("Go Slight Right\n");
        }
        else if (!leftIR && mLeftIR && !mRightIR && !rightIR) {
            // printf("Go More Right\n");
        }
        else if (leftIR && mLeftIR && !mRightIR && !rightIR) {
            // printf("Go More More Right\n");
        }
        else if ((leftIR && mLeftIR && mRightIR && !rightIR) ||
                 (leftIR && !mLeftIR && mRightIR && !rightIR) ||
                 (leftIR && mLeftIR && !mRightIR && rightIR)) {
            // printf("Go Sharp Right\n");
        }
        // Forward
        else if (!leftIR && !mLeftIR && !mRightIR && !rightIR) {
            // printf("Go Forward\n");
        }
        else if (!leftIR && mLeftIR && mRightIR && !rightIR) {
            // printf("Go Forward 2\n");
        }
        // Stop
        else if (leftIR && !mLeftIR && !mRightIR && rightIR) {
            // printf("Stop\n");
        }
        else if (leftIR && mLeftIR && mRightIR && rightIR) {
            // printf("Stop 2\n");
        }
        // Right
        else if (!leftIR && !mLeftIR && !mRightIR && rightIR) {
            // printf("Go Slight Left\n");
        }
        else if (!leftIR && !mLeftIR && mRightIR && !rightIR) {
            // printf("Go More Left\n");
        }
        else if (!leftIR && !mLeftIR && mRightIR && rightIR) {
            // printf("Go More More Left\n");
        }
        else if ((!leftIR && mLeftIR && mRightIR && rightIR) ||
                 (!leftIR && mLeftIR && !mRightIR && rightIR) ||
                 (leftIR && !mLeftIR && mRightIR && rightIR)) {
            // printf("Go Sharp Left\n");
        }
    }
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

void initUltrasonic(){
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void initIROBS(){
    pinMode(LEFT_OBS, INPUT);
    pinMode(FRONT_OBS, INPUT);
}
//gcc 6-ir_sensor_ex.c -o irex -lwiringPi
// ./irex