#! /bin/sh

# check that motion is running every 5 minutes

# result is zero if we find it running

ps -F | grep "\./door"
if [ $? -ne 0 ]
 then
 echo "Monitor not running, re-starting it"
 sudo /home/pi/wiringPi/door/./door
 else
 echo "Monitor is running."
fi

exit 0
