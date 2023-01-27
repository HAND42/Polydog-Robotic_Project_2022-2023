 In order to insatll Mysql on our VM, we need to update first the packages with this command:  
sudo apt update  
  ![Alt text](td%20linux/Capture%20d%E2%80%99%C3%A9cran%202022-11-23%20160326.png)
Then we can start the installation of Mysql with this command :    
sudo apt install mysql-server    
![Alt text](td%20linux/Capture%20d%E2%80%99%C3%A9cran%202022-11-23%20160406.png)
To creat a database from the following backup file: https://www.mysqltutorial.org/wp-content/uploads/2018/03/mysqlsampledatabase.zip, we download it first, and then we unzip it using the following command :  
cd ~/Downloads  
unzip mysqlsampledatabase.zip   
![Alt text](td%20linux/Capture%20d%E2%80%99%C3%A9cran%202022-11-23%20160825.png)
and then we enter to mysql using :  
sudo mysql  
And then we declare the new database using this command :  
source /home/younes/Downloads/mysqlsampledatabase.sql  
And finally we can show the database by using this command :  
show databases;
![Alt text](td%20linux/Capture%20d%E2%80%99%C3%A9cran%202022-11-23%20160843.png)




