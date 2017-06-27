sleep 2
sudo cp /home/pi/camera/tmp/snap/snap.jpg /home/pi/tmp.jpg
sudo date | mail -a /home/pi/tmp.jpg -s Unlock irdoorcam@gmail.com
