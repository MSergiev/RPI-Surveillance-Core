sleep 3
sudo cp /home/pi/camera/tmp/snap/snap.jpg /home/pi/tmp.jpg
sudo date | mail -a /home/pi/tmp.jpg -s Doorbell irdoorcam@gmail.com
