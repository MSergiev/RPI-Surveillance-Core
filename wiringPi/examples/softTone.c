#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <softTone.h>

#define	PIN 0

//int scale [8] = { 262, 294, 330, 349, 392, 440, 494, 525 } ;
int beep = 1800;

int main ()
{
 // int i ;

  wiringPiSetup () ;

  softToneCreate (PIN) ;

  piHiPri(99);

  for (;;)
  {
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(100);
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(1000);

  softToneWrite(PIN, beep);
  delay(50);
  softToneWrite(PIN, 0);
  delay(100);
  softToneWrite(PIN, beep);
  delay(50);
  softToneWrite(PIN, 0);
  delay(1000);

/*  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(500);
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(500);
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(500);
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(500);
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(500);
  softToneWrite(PIN, beep);
  delay(100);
  softToneWrite(PIN, 0);
  delay(500);
*/


  //  for (i = 0 ; i < 8 ; ++i)
  //  {
  //    printf ("%3d\n", i) ;
  //    softToneWrite (PIN, scale [i]) ;
  //    delay (500) ;
  //  }
  }
}
