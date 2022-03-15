// IR Sensors
// Example 1
// React if object detected on Right/Left/Both or No sides

#include <stdio.h>
#include <wiringPi.h>


#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26
#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

void initIR();
void initLineTacer();

int leftTracer;
int rightTracer;

int main(void){
    
    if(wiringPiSetup() == -1)
	    return 0;
  
    int LValue, RValue; 
    initIR();


    while (1) {
        leftTracer = digitalRead(LEFT_TRACER_PIN); // 0 is white
        rightTracer = digitalRead(RIGHT_TRACER_PIN);
        
        LValue = digitalRead(LEFT_IR_PIN);
        RValue = digitalRead(RIGHT_IR_PIN);
        printf("%d %d %d %d", leftTracer, LValue, RValue, rightTracer);

        // if(LValue == 1 && RValue == 0 ) {
        //     printf("Right\n");
           
        // }else if (LValue == 0 && RValue == 1) { 
        //     printf("Left\n");

        // }else if(LValue == 0 && RValue == 0){
        //     printf("Both\n");

        // }else if(LValue == 1 && RValue == 1){
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