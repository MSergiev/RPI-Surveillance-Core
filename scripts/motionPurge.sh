find /home/pi/camera -mindepth 1 -maxdepth 1 -type d -ctime +100 | xargs rm -rf
find /home/pi/routerDrive -mindepth 1 -maxdepth 1 -type d -ctime +10 | xargs rm -rf
sudo ntpd -q
