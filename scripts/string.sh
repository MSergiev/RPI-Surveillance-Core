#!/bin/sh
#

if [ -f /home/pi/camera/tmplog.txt ]
then
if [ -f /home/pi/camera/lock ]
then
sudo /usr/bin/wget --delete-after "http://192.168.0.66:8080/0/config/set?text_left=ON/LOCKED"
else
sudo /usr/bin/wget --delete-after "http://192.168.0.66:8080/0/config/set?text_left=ON/UNLOCKED"
fi
else
sudo /usr/bin/wget --delete-after "http://192.168.0.66:8080/0/config/set?text_left=Monitor is OFF"
sudo pkill door
sudo /home/pi/wiringPi/door/./door
fi
