#include "mbed.h"
#include "glibr.h"
#include "SDFileSystem.h"
#include "wave_player.h"

glibr GSensor(p9,p10);
SDFileSystem sd(p5, p6, p7, p8, "sd"); //SD card
AnalogOut DACout(p18);
wave_player waver(&DACout);
int isr_flag = 0;
DigitalOut myled(LED1);
//InterruptIn interrupt(p11);
Serial pc(USBTX, USBRX);
bool ret;
int val;

int main()
{
    myled = 0;
    ret = 0;
    val = 0;
    if ( GSensor.ginit() ) {
        pc.printf("APDS-9960 initialization complete\n\r");
    } else {
        pc.printf("Something went wrong during APDS-9960 init\n\r");
    }

    // Start running the APDS-9960 gesture sensor engine
    if ( GSensor.enableGestureSensor(true) ) {
        pc.printf("Gesture sensor is now running\n\r");
    } else {
        pc.printf("Something went wrong during gesture sensor init!\n\r");
    }

    FILE *Up;
    FILE *Down;
    FILE *Left;
    FILE *Right;
    FILE *Far;
    FILE *Near;

    //   waver.play(wave_file);
    while(1) {
        /* ret = GSensor.isGestureAvailable();
         pc.printf("Is Gesture Available?: %d\n", ret);
         myled = ret;
         val = GSensor.readGesture();
         */
        if ( GSensor.isGestureAvailable() ) {
            switch ( GSensor.readGesture() ) {
                case DIR_UP:
                    pc.printf("UP\n");
                    Up=fopen("/sd/up.wav","r");
                    if(Up!=NULL){
                    waver.play(Up);
                    }else{ pc.printf("Up not open");} 
                    fclose(Up);   
                    break;
                case DIR_DOWN:
                    pc.printf("DOWN\n");
                    Down=fopen("/sd/down.wav","r");
                    if(Down!=NULL){
                    waver.play(Down);
                    }else{ pc.printf("Down not open");}
                    fclose(Down);
                    break;
                case DIR_LEFT:
                    pc.printf("LEFT\n");
                    Left=fopen("/sd/left.wav","r");
                    if(Left!=NULL){
                    waver.play(Left);
                    }else{pc.printf("Left not open");}
                    fclose(Left);
                    break;
                case DIR_RIGHT:
                    pc.printf("RIGHT\n");
                     Right=fopen("/sd/right.wav","r");
                    if(Right!=NULL){
                    waver.play(Right);
                    }else{pc.printf("Right not open");}
                    fclose(Right);
                case DIR_NEAR:
                    pc.printf("NEAR\n");
                    Near=fopen("/sd/near.wav","r");
                    if(Near!=NULL){
                    waver.play(Near);
                    }else{pc.printf("Near not open");}
                    fclose(Near);
                    break;
                case DIR_FAR:
                    pc.printf("FAR\n");
                    Far=fopen("/sd/far.wav","r");
                    if(Far!=NULL){
                    waver.play(Far);
                    }else{pc.printf("Far not open");}
                    fclose(Far);
                    break;
                default:
                    pc.printf("NONE\n");
            }
        }


        //   wait(1);

    }



}