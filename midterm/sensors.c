// IR Sensors
// Example 1
// React if object detected on Right/Left/Both or No sides

#include <stdio.h>
#include <wiringPi.h>


#define LEFT_TRACER_PIN 10
#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26
#define RIGHT_TRACER_PIN 11

void initIR();
void initLineTacer();

int leftIR;
int mLeftIR;
int mRightIR; 
int rightIR;
// int sensors[4];

int main(void){
    
    if(wiringPiSetup() == -1)
	    return 0;
  
    initIR();


    while (1) {
        leftIR = !digitalRead(LEFT_TRACER_PIN); // 1 will be white
        mLeftIR = !digitalRead(LEFT_IR_PIN);
        mRightIR = !digitalRead(RIGHT_IR_PIN);
        rightIR = !digitalRead(RIGHT_TRACER_PIN);
        printf("\r%d %d %d %d\n", leftIR, mLeftIR, mRightIR, rightIR);

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
//gcc 6-ir_sensor_ex.c -o irex -lwiringPi
// ./irex