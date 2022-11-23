In order to modify the size of the logfile of the script we use this command :  
truncate -s 500 MB /var/log/yourlogfile  
if we assume that we delete the data from the file when it reaches 500 MB with this command :  
if [ "$logfile" -gt 500 MB ]   
then   
    truncate -s 0 $logfile  
    
fi  
Then we can choose a size limit that only dumps the logs when the file has done a number of repetitions we determined.
