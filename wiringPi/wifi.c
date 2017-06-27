#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(){
delay(200000);
system("sudo ifup --force wlan0");
system("sudo ifup --force wlan0");
return 0;
}
