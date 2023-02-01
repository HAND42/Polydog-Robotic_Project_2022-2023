#!/bin/bash

#I save in a variable the current date 
DATE=$(date +%Y-%m-%d-%H-%M-%S)

#The name of my file
DESTINATION=mysqlsampledata_$DATE

#The path where I create my backup
cd /home/kenai/Desktop/database-backup

#To back up MySQL database
mysqldump -u kenai classicmodels >> $DESTINATION.sql 2>>/var/log/dump-mysql.log


#Convert the file.sql in .bz2
bzip2 $DESTINATION.sql

echo "A sql backup created on $DATE" >> /var/log/dump-mysql.log

#It give me the number of backup file registred in the directory
NUMBER_BACKUP=$(find /home/kenai/Desktop/database-backup/mysqlsampledata*.sql.bz2 | wc -l);


while [ $NUMBER_BACKUP -gt 5 ]
do 

	FILE_TODELETE=$(find /home/kenai/Desktop/database-backup/mysqlsampledata*.sql.bz2 | head -n 1);
	rm -f $FILE_TODELETE;
	NUMBER_BACKUP=$((NUMBER_BACKUP-1));
	echo "The sql backup $FILE_TODELETE was deleted" >> /var/log/dump-mysql.log
done

echo "$(tail -100 /var/log/dump-mysql.log)" > /var/log/dump-mysql.log
