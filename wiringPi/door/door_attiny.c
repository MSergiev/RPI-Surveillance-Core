#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define SOUND 0
#define RELAY 4
#define SWITCH 5

unsigned int switchTime = 0;
unsigned int mailTime = 0;
unsigned int unlockTime = 0;

unsigned int blinkTime = 0;
int ledOn = 0;

time_t t;
struct tm *tm;

FILE *file;
FILE *lock;

int relayState = 0;
int switchState = 0;
int relayPrevious = 0;
int switchPrevious = 0;

int switchTrigger = 0;
int relayTrigger = 0;

int switchTmp = 0;
int relayTmp = 0;

//int bell = 0;

int main(void){

   time(&t);
   tm = localtime(&t);

   printf("%d-%d-%d %d:%d:%d: Door Monitor Started\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

   wiringPiSetup();
   pinMode(SOUND, OUTPUT);

   pinMode(RELAY, INPUT);
   pinMode(SWITCH, INPUT);

   switchPrevious = digitalRead(SWITCH);
   relayPrevious = digitalRead(RELAY);

   while(1){
      delay(200);
   
      file = fopen("/home/pi/camera/tmplog.txt","a+");
 
      relayState = digitalRead(RELAY);	  
      switchState = digitalRead(SWITCH);

      time(&t);
      tm = localtime(&t);

      if((millis() - blinkTime) > 1000){
      if(ledOn == 0){
      system("sudo /home/pi/scripts/ledOn.sh");
      ledOn = 1;
      blinkTime = millis();
      } else {
      system("sudo /home/pi/scripts/ledOff.sh");
      ledOn = 0;
      blinkTime = millis();
      }
      }

      /*if(switchState != switchPrevious){
	      switchTmp = switchState;
          delay(1000);
		  switchState = digitalRead(SWITCH);
		  if(switchTmp == switchState){
		  switchTrigger = 1;}
	  }

      if(relayState != relayPrevious){
	      relayTmp = relayState;
          delay(200);
		  relayState = digitalRead(RELAY);
		  if(relayTmp == relayState){
		  relayTrigger = 1;}
	  }*/

	  if(switchState == 1){
	  lock = fopen("/home/pi/camera/lock","a+");
      fclose(lock);
	  }
	  
	  
      if(relayState == 1){
      printf("%d-%d-%d %d:%d:%d - Doorbell Alert!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
      fprintf(file, "%d-%d-%d %d:%d:%d - Doorbell Alert!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec); 
	  if((millis() - mailTime) > 5000){
         system("/home/pi/scripts/mail.sh");
         printf("%d-%d-%d %d:%d:%d - Doorbell Mail sent\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
         fprintf(file, "%d-%d-%d %d:%d:%d - Doorbell Mail sent\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
         mailTime = millis();
      }
	  }

      if(switchState == 1 && switchPrevious == 0){
      printf("%d-%d-%d %d:%d:%d - Door has been locked!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec); 
      fprintf(file, "%d-%d-%d %d:%d:%d - Door has been locked!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec); 
	  digitalWrite(SOUND, 1);
      delay(50);
      digitalWrite(SOUND, 0);
      delay(50);
	  digitalWrite(SOUND, 1);
      delay(50);
      digitalWrite(SOUND, 0);
      delay(50);
	  digitalWrite(SOUND, 1);
      delay(50);
      digitalWrite(SOUND, 0);
      delay(50);
	  digitalWrite(SOUND, 1);
      delay(50);
      digitalWrite(SOUND, 0);
      delay(50);
	  switchTrigger = 0;
      }

      if(switchState == 0 && switchPrevious == 1){
      printf("%d-%d-%d %d:%d:%d - Door has been unlocked!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
      fprintf(file, "%d-%d-%d %d:%d:%d - Door has been unlocked!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
      if((millis() - unlockTime) > 10000){
         system("/home/pi/scripts/mailUnlock.sh");
         printf("%d-%d-%d %d:%d:%d - Unlock mail sent\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
         fprintf(file, "%d-%d-%d %d:%d:%d - Unlock mail sent\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
         unlockTime = millis();
      }
	  switchTrigger = 0;
      }


 /*     if(bell == 1){
      if(switchState == 0){
        if(switchPrevious == 1 || switchTrigger == 1){
         if(switchTrigger == 0){
           switchTime = millis();
         }
         switchTrigger = 1;
         if((millis() - switchTime) >= 30000){
          printf("%d-%d-%d %d:%d:%d - Sound Alert Invoked\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
          fprintf(file, "%d-%d-%d %d:%d:%d - Sound Alert Invoked\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
          softToneWrite(SOUND, beep);
          delay(period);
          softToneWrite(SOUND, 0);
          delay(period);
          softToneWrite(SOUND, beep);
          delay(period);
          softToneWrite(SOUND, 0);
          delay(period);
          softToneWrite(SOUND, beep);
          delay(period);
          softToneWrite(SOUND, 0);
          delay(period);

          switchTrigger = 0;
          bell = 0;
         }
        }
      }
      } */
		  	  
      relayPrevious = relayState;
      switchPrevious = switchState;
	  
      fclose(file);
   }

   printf("%d-%d-%d %d:%d:%d - PROGRAM ERROR!\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

   return 1;
}
