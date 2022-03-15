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
int sensors[4];

int main(void){
    
    if(wiringPiSetup() == -1)
	    return 0;
  
    initIR();


    while (1) {
        leftIR = !digitalRead(LEFT_TRACER_PIN); // 1 will be white
        mLeftIR = !digitalRead(LEFT_IR_PIN);
        mRightIR = !digitalRead(RIGHT_IR_PIN);
        rightIR = !digitalRead(RIGHT_TRACER_PIN);
        sensors = {leftIR, mLeftIR, mRightIR, rightIR};
        // printf("%d %d %d %d\n", leftIR, mLeftIR, mRightIR, rightIR);
        printf("%d %d %d %d\n", sensors[0], sensors[1], sensors[2], sensors[3]);
        // Forward
        if (!leftIR && !mLeftIR && !mRightIR && !rightIR) {
            printf("Go Forward")
        }
        else if (!leftIR && mLeftIR && mRightIR && !rightIR) {
            printf("Go Forward 2")
        }
        // Stop
        else if (leftIR && !mLeftIR && !mRightIR && rightIR) {
            printf("Stop")
        }
        else if (leftIR && mLeftIR && mRightIR && rightIR) {
            printf("Stop 2")
        }

        // if(mLeftIR == 1 && mRightIR == 0 ) {
        //     printf("Right\n");
           
        // }else if (mLeftIR == 0 && mRightIR == 1) { 
        //     printf("Left\n");

        // }else if(mLeftIR == 0 && mRightIR == 0){
        //     printf("Both\n");

        // }else if(mLeftIR == 1 && mRightIR == 1){
        //     printf("No\n");
        // }
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