#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <softTone.h>

#define SOUND 0
#define RELAY 4
#define SWITCH 5

int main(){

wiringPiSetup();

softToneCreate(SOUND);

pinMode(SWITCH, INPUT);
pinMode(RELAY, INPUT);

for(;;){

if(digitalRead(SWITCH) == 1){
printf("SWITCH is ON");
softToneWrite(SOUND, 3000);
delay(100);
softToneWrite(SOUND, 0);
delay(100);
}

if(digitalRead(RELAY) == 1){
printf("RELAY is OFF");
softToneWrite(SOUND, 1000);
delay(1000);
softToneWrite(SOUND, 0);
}

}

return 0;

}
