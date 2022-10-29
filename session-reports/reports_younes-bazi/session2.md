# SESSION 2 OUTCOME REPORT
## Date: 18/10/2022
## Main event of the session: Fixing the IMU drift problem. 
During the last session, i encountered a major problem which is the instability of the 10 DOF IMU sensor, but i finally found a solution for this issue after Mr.Masson gave me a course (that you can find in the file reports_younes-bazi) to read called "how to use an IMU for a self-balancing robot".This problem is common and it is called the IMU drift.  
To understand the cause of an IMU drift we need to understand first how an IMU detects position. IMUs work by detecting rotational movement of the three-axis, commonly known as Pitch, Roll, and YAW. To achieve such, it relies on the functionality of Accelerometers, Gyroscopes, and Magnetometer.The IMU orientation is usually obtained by integrating the angular velocity measured
 with the gyroscope, This allows for an immediate detection of orientation changes but leads to a DRIFT of the estimated orientation over time. BUT WHY IT LEADS TO A DRIFT? well the answer is simple : In order to get rotation (angle) from a gyroscope, which senses angular velocity, you need to perform a single integration.  
f ≡ frequency  
∫cos(2π×ft)) = (1/(2π×f)) × sin(2π×ft)  
But be aware that integration turns noise into drift. As we see above, the integration gets a 1/f outside, meaning that high frequency (f) noise disappears with integration, i.e. a noise of frequency will drop by a factor of a 100, but a very low frequency will be amplified, meaning the gyroscope will drift over time.  
To avoid this problem, we can use the accelerometre instead of the gyroscope both present in the same IMU, so we should read only the accelerometer data from the 10 DOF IMU sensor using arduino.  
I used this code to display the roll and pitch values:  
  
![](arduino%20code%201.png)
![](arduino%20code%202.png)  
And as you can see the roll and pitch values are more stable than it was in the first time using the gyroscope.  
![](roll%20and%20pitch%20values.png)  
During this session, i also managed to do a 3D visualization of the accelerometer (Accelerometer orientation tracking ) using a software called processing 4 by sending the roll and pitch values through the serial port and recieving them in the processing development environment in order to rotate the 3D object that we will create. Here's the complete Processing code:  
![](processing%201.png)  
![](processing%202.png)  
And you can see the final result in the video inside the reports_younes-bazi file.  
Now that we can display and know the exact roll pitch and yaw values without any noises, we need to start to think of the right control loop mechanism (PI,PD,PID).
