#!/bin/bash
#
# Dpower security proximity arm and disarm
# Part of the Dpower security system by djjeffery73@gmail.com
# The Dpower security system is the most comprehensive web 
# interface for motion currently availiable
# Features include: 
# Edit motion cofig files
# Perform all motion web actions
# Camera viewer
# Event viewer
# Motion sever audio alarms
# Motion server volume control
# Motion server speech tells you which camera had an event
# Email and cellular phone text message
# One click arm and disarm detection on one or all cameras
# proximity arming and disarming (detects your smart phone on
# the local network)

# this file checks if a phones IP is reachable on the network
# if true disarm alarm -- someone is here
# if false arm alarm -- no one is here
# this script needs to be run by crontab every minute.
# a larger time gap may be used but increases the chances of
# you tripping the alarm when you come home.

# IP address of your phone
MYIP="192.168.0.111"

# Results of ping of phone ip
PROXIMITY="$(ping $MYIP -c 1)"

# If the phone was not found, start detection on all cameras, else stop detection
# on all cameras
if [ "$?" -eq 0 ]; then
	echo Host in the vicinity
else
	echo Host not in the vicinity
    sudo cp /home/pi/camera/tmp/snap/snap.jpg /home/pi/tmp.jpg
	sudo date | mail -a /home/pi/tmp.jpg -s Lock dragon9284@me.com
fi

