#!/bin/sh  
username "$younes"  
database="$classicmodels"
day="$(date +'%d_%m_%Y_%H_%M_%S')"
logfile="/home/var/log/dump-mysql.log"  
echo "$now : starting database backup" >> $logfile
file="data_backup_$now".bz2
backupfolder="/home/databasebackup"
pathfile="$backupfolder/$file"
sudo mysql --user=$username $database > $pathfile
echo "$now : backup complete" >> $logfile

nbfile="$(ls -F $backupfolder | wc -l)"
if [ $nbfile -gt 5 ]
then
	echo "$now : The oldest one will be delete" >> $logfile
	rm $backupfolder/"$(ls -t $backupfolder | tail-l)";
	echo "$now : The oldest backup has been delete" >> $logfile
fi