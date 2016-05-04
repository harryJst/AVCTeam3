#include <stdio.h>
#include <time.h>

extern "C" int init(int d_level);
extern "C" int sleep(int sec, int usec);
extern "C" int set_motor(int motor, int value);
extern "C" int take_picture();
extern "C" int get_pixel(int row, int col, int colour);
extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
using namespace std;

int main()
{
  init(0);
        open_screen_stream();
        int[] pixels = new int[320];;
        while (true) {
            take_picture();
            update_screen();
            //getting the halfway pixel (120) possibly change to top pixel?
            for (int i = 0;i<320;i++) {
                int whiteness = get_pixel(i, 120, 3);//need to check that the first pixel of the picture is gotten when i=0
                if (whiteness>150) { //is this the correct number?  150 is light grey. possibly INCREASE this.
                    whiteness = 1;
                }
                else {
                    whiteness = 0;
                }
                pixels[i] = whiteness;
            }
            int num = -160;
            for (int i=0; i<320;i++){        //this loop goes through the pixel array and multiplies each value by num, num starts at -160 and increases by 1 each loop       
                if(num==0){num++;}//addded an "if" to skip 0 so that it goes ....-2,-1,1,2....
                pixels[i]=pixels[i]*num;
                num++;
            }
            int sum = 0;
            for (int i=0; i<320;i++){     //this loop simply adds up the array          
                sum = sum + pixels[i];
            }
            /*if there are lots of white pixels on the left, sum should be very negative, lots on the right and sum should be very positive, 
              when relativly even, the sum should be very small. The sum is proportional to how uneven the white pixels are. Maximum sum is about 12200*/
              
            double turnRate = 0.001;//needs to be tested
            UI.printf("\nThe sum is %d, motor speed is ",sum);
            set_motor(1 , 20+turnRate*sum);//20 is the base speed which is the speed when the white line is perfectly centred
            set_motor(2 , 20-turnRate*sum);
        }
  }
  
     return 0;
}