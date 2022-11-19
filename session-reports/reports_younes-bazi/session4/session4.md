# SESSION 4 OUTCOME REPORT
## Date: 15/11/2022
## Main event of the session: Inverse Kinematics.
As i was searching for more informations about the stabilization of the robot, I found that the study of inverse Kinematics are essential for the balance of the Polydog, because Inverse kinematics is the use of kinematic equations to determine the motion of a robot to reach a desired position, it is used to compute an appropriate state in a robot's configuration space, given a target position in task space, in the other hand PID control applies responsive correction signals to a robot's actuators, allowing it to reach its target accurately. A reliable inverse kinematic solution is NECESSARY for programming a robot to perform tasks, this why I decided to do an inverse kinematics study of our robot before we go on with the PID tuning .  
First thing first , our robot has 4 legs and each one has 3 movable parts (3DOF) which makes it a total of 12 joint angles that we should determine. But in order to make things more easier, we are going to implement Kinematics of the PolyDog on Python. And to verify all the calculations happening here, it is helpful to have some kind of visual output ,so we are going to use Matplotlib.   
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20231915.png)  
We then start with solving the Leg's Inverse Kinematics and calculate (theta1,theta2,theta3) our output angles for a given Foot-Position (x,y,z) in Leg-Space. The Leg's origin (the shoulder) is at (0,0,0). l1,l2,l3 and l4 are the length of the Leg's Segments.  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20232825.png)  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20232921.png)  
Here is the result :  
![Alt text](Figure%202022-11-18%20233309.png)  
And now the code works , we can test some different Target-Positions.  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20234336.png)  
![Alt text](Figure%202022-11-18%20234242.png)  
To be able to calculate a Leg's Pose, we need to know where it starts when the Body has a specific Pose. The Pose is defined by omega,phi and psi (Remember, these are the Euler angles that the 10 DOF sensor will provide us with) and xm,ym and zm are the Center of the Body.  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20235415.png)  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20235441.png)  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-18%20235506.png)  
Here is the result for the body Part :  
![Alt text](Figure%202022-11-18%20235512.png)  
Now we need to combine the Body's Kinematics with the four Legs. Input will be the Body-Pose (omega,phi,psi,xm,ym,zm) that will be given by the 10 DOF sensor and Positions for all four Legs in World-Space (Lp).  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-19%20000535.png)  
![Alt text](Figure%202022-11-19%20000702.png)  
We can now apply some random poses on the Robot's Body to verify the correctness of all Legs.  
![Alt text](Capture%20d%E2%80%99%C3%A9cran%202022-11-19%20001154.png)  
![Alt text](Figure%202022-11-19%20001131.png)  
Now the calculations work, i will try next week to implement kinemactis on the arduino board , and try to do some poses on the real Polydog to see if it really works in real life.