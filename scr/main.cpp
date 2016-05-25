#include <iostream>
#include <stdio.h>
#include <time.h>

extern "C" int init(int d_level);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor, int value);
extern "C" int read_analog(int ch_adc);
void turnLeft();
void turnRight();


using namespace std;

const int speed = 110;

//Not sure which motor is which...
//follows left wall.
//when next to a wall, the sensor reading is large. Closer you are, the larger the reading


int main()
{
//change numbers based on which inputs sensors are connected to. 1 is the left most sensor, 2 is the middle, 3 is the right
    int sen1 = read_analog(0);//left
    int sen2 = read_analog(1);//middle
    int sen3 = read_analog(2);//right

    while (1){
    while (sen2<30 && sen1>30){
    sen1 = read_analog(0);//change 0,1,2 numbers based on which inputs sensors are connected into. 
    sen2 = read_analog(1);
    sen3 = read_analog(2);

    int dif = sen1-200;//200 is a base number ideally this number is the distance from the left wall that we want to maintain.
    dif=dif*0.5;//how much correction is caused by dif.
    set_motor(1,speed+dif);//change +-
    set_motor(2,speed-dif);//possibly going to swing

    printf("The difference is "+dif);
     }
     if(sen1>30 && sen2>30 && sen3>30){//turns 180 when in corner
     turnLeft1();
     turnLeft1();
     }
    else if(sen1<30){//turns left when no left wall detected
    turnLeft1();
    Sleep(1,0);
    }
    else if (sen2>30 && sen1>30){//turns right when front direction is blocked
    turnRight1();
    Sleep(1,0);
    }
    else {//goes backwards if it broke out of while loop for no reason
    set_motor(1,-100);
    set_motor(2,-100);
    }
    }
    return 0;
}

void turnLeft1(){
    set_motor(1,speed);
    set_motor(2,-speed);//possible 0 instead of -speed
    Sleep(1,0);//turns for 1 second, posibly too long/ too short
    set_motor(1,speed);
    set_motor(2,speed);//resets motor to straight once turned
    }

void turnRight1(){
    set_motor(1,-speed);//possibly 0 instead of -speed
    set_motor(2,speed);
    Sleep(1,0);//turns for 1 second
    set_motor(1,speed);
    set_motor(2,speed);//resets motor to straight once turned
    }