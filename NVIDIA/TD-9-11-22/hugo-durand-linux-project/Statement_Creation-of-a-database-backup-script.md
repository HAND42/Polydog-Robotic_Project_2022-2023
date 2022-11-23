## Creation of a database backup script

Statement :

* Install MySQL on your VM
* Create the database from the following backup file: https://www.mysqltutorial.org/wp-content/uploads/2018/03/mysqlsampledatabase.zip
* Write a script to backup the classicmodels database. Please note the following:
    * The database backup must be contained in a single file
    * This file must be compressed in .bz2 format
    * The file must be time-stamped (year-month-day-hour-minutes-seconds)
    * If the backup is successful, the script will keep only the 5 most recent backup files
    * This script must run every 10 minutes, the logs must be sent in /var/log/dump-mysql.log
    * Find a tool to control the size of the log file /var/log/dump-mysql.log. Propose a configuration that seems reasonable to you


Expected result:

The results should be available on your git repository, in a NVIDIA/TD-9-11-22/<student name> directory.

You must provide:
 * setup-mysql:
    * A readme or script explaining how to:
      * install MySQL
      * Import the database
      NB: If you make a readme, you must indicate the commands used
  * dump-database.sh:
    * A database backup script
  * dump-database.service & dump-database.timer: 
    * The files to set up the backup as a service
  * setup-dump-database-service: 
    * A readme or script explaining how to set up the service. NB: If you make a readme, you must indicate the commands used
  * setup-dump-database-logs-cleanup:
    * A readme or a script explaining how to configure the log control