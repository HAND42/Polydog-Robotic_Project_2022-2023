# SESSION 3 OUTCOME REPORT
## Date: 28/10/2022
## Main event of the session: PID controller for self-balancing.
Now we know the exact inclinations of the robot, we need to correct them if they ever exceeded a limit that we will determine, and in order to do that we are going to use a PID controller. But first, what is a PID controller ? to be honest, i had some difficulties to understand what it is and how it works, but after many hours of reading, the only website that satisfied me was [wikipedia](https://en.wikipedia.org/wiki/PID_controller). So basiclly the P stands for Proportional, meaning that the output is proportional to the error. I.e. the bigger the current error is, the bigger the output is.
I stands for integral, and is the sum of the instantaneous error over time. I.e. the I-part is proportional to both the magnitude and the duration of the error. That means that even if the error is static, the I-part will continue to grow. This will eliminate small errors that accumulate over time.
The D stands for derivative, and reflects the rate of change of the error. I.e. for a static error, the D-part will be 0. For a error that is rapidly increasing, the D-part will be large.
Each part is multiplied by a constant, Kp, Ki and Kd, deciding the gain of each part of the PID, the proportional gain, integral gain and derivative gain. The basic idea behind a PID controller is to read a sensor (in our case ,the sensor is the accelerometer), then compute the desired actuator output by calculating proportional, integral, and derivative responses and summing those three components to compute the output. But Why use PID and not other controllers like P,PI,PD? the answer is more precise control of the variable under control, and fast response to changes.So now,  you have basically a measured value from the accelerometer, which can be interpreted as the error value. This error is the input of any PID calculation. There are tons of math functions you could use but the PID inventor genius selected only 3! Luckily all these function can be ultra easily implemented using programming on any language. We are going to implement on an arduino sketch, and in order to do that,  five parameters must be known: proportional, integral and derivative constants, input value and set point value. PID computation must be inside a looping function. The first part of the function should be determining the time elapsed. In Arduino, the current time can be determined by millis() and the elapsed time is just:  
currentTime = millis();  
elapsedTime = currentTime - previousTime;  
Next, the error must be determined:  
error = setPoint - input;  
Recall that the integral of the error is the cumulative error over time. To calculate an integral using Arduino, we simply do:  
cumError += error * elapsedTime;  
The derivative of the error is the rate of change of the error:  
rateError = (error - lastError)/elapsedTime;  
Finally, the computed output is:  
output = Kp * error + Ki * cumError + Kd * rateError;  
Here, the Kp, Ki and Kd are the predetermined constants.  
Finally, the variables must be noted for the next iteration:  
lastError = error;  
previousTime = currentTime;  
The main question here is how to calculate these constants: Kp, Ki, Kd . well, the answer is simple, they are not calculated. They are experimentally determined, and that is what we are going to do next session.  
Finally, i still have some thoughts about whether should we use a kalman filter alongside the PID controller or it is not necessary, because Kalman filter has a good performance in filtering noise, on the other hand, PID control will work well if there is no noise ,and the combination of PID control and Kalman filter is expected to overcome the decline in the control system performance.
