### BEGIN INIT INFO
# Provides:          motionStartup
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Move motion files at startup.
# Description:       Move motion files at startup.
# X-Start-Before:    motion
### END INIT INFO

#! /bin/sh
# /etc/init.d/motionStartup
#

logger -s "Script motionStartup called"

    logger -s "Script motionStartup started"
    TIMESTAMP=$(date +%d_%m_%Y | sed 's/ //g') # No spaces
    logger -s "Script motionStartup $TIMESTAMP"

if [ -d /home/pi/camera/tmp ]
then
    if [ -d /home/pi/camera/$TIMESTAMP ]
    then
	   if [ -f /home/pi/camera/tmplog.txt ]
	   then
          sudo chmod 777 /home/pi/camera/tmplog.txt
          sudo chmod 777 /home/pi/camera/$TIMESTAMP/log.txt
	      sudo cat /home/pi/camera/tmplog.txt >> /home/pi/camera/$TIMESTAMP/log.txt
	      sudo rm  /home/pi/camera/tmplog.txt
          sudo rm  /home/pi/camera/lock
	   fi
    sudo chmod 777 /home/pi/camera/tmp
    find /home/pi/camera/tmp/. -type f -size 0 -print0 -delete
    find /home/pi/camera/tmp/. -maxdepth 1 -type f | \
        xargs -I '{}' sudo mv {} /home/pi/camera/$TIMESTAMP
    else
    sudo mv -v /home/pi/camera/tmp /home/pi/camera/$TIMESTAMP
    sudo mkdir /home/pi/camera/tmp
    sudo mkdir /home/pi/camera/tmp/snap
    sudo chmod 777 /home/pi/camera/tmp
    sudo chmod 777 /home/pi/camera/tmp/snap
    sudo chmod 777 /home/pi/camera/$TIMESTAMP
    fi
else
    sudo mkdir /home/pi/camera/tmp
    sudo mkdir /home/pi/camera/tmp/snap
    sudo chmod 777 /home/pi/camera/tmp
    sudo chmod 777 /home/pi/camera/tmp/snap
fi

    logger -s "Script motionStartup stopped"


exit 0
