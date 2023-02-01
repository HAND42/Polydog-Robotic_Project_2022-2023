In the database_backup.sh file, I echo the following sentence :

mysqldump -u kenai classicmodels >> $DESTINATION.sql 2>>/var/log/dump-mysql.log

echo "A sql backup created on $DATE" >> /var/log/dump-mysql.log
echo "The sql backup $FILE_TODELETE was deleted" >> /var/log/dump-mysql.log

I keep the 100 first lines in the log-file.

echo "$(tail -100 /var/log/dump-mysql.log)" > /var/log/dump-mysql.log

