#!/bin/bash

   if ifconfig wlan0 | grep -q "inet addr:" ; then
      echo "Network connection active!"
   else
      echo "Network connection down! Attempting reconnection."
      ifup --force wlan0
      sleep 10
   fi