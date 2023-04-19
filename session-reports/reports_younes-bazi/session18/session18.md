# SESSION 18 OUTCOME REPORT
## Date: 04/04/2023
## Main event of the session: Successfully Achieving Our Goal: Making Our Robot Walk in Simulation.    
During this session, my main focus was on improving the 3D model of the Polydog in CoppeliaSim to closely resemble our physical robot dog, in order to achieve a simulation that closely mimics reality. This is crucial as CoppeliaSim will eventually control our robot using ROS, and having a simulation that closely matches our real robot will ensure smooth movement and walking in the simulation and the reality. I spent time redesigning the robot in CoppeliaSim until it looked similar to our real robot.  
Old Version :  
![Alt text](S18/Capture%20d%E2%80%99%C3%A9cran%202023-04-19%20034605.png)  
![Alt text](S18/Capture%20d%E2%80%99%C3%A9cran%202023-04-19%20034731.png)  
New Version :  
![Alt text](S18/Capture%20d%E2%80%99%C3%A9cran%202023-04-19%20025309.png)  
![Alt text](S18/Capture%20d%E2%80%99%C3%A9cran%202023-04-19%20025356.png)  
In Gifs below, you can observe the walking movements of the Polydog. As you can see, the movements of the new version of the dog are significantly more dynamic and smooth compared to the previous version. The reason behind the improved dynamic and smooth movements of the new version of the Polydog is due to the additional development I carried out on the code. By refining the code and making necessary adjustments, I was able to enhance the performance of the robot's walking movements, resulting in a more realistic and dynamic simulation.
![Alt text](S18/Walking%20forward%20V2.gif)    
![Alt text](S18/Walking%20Backwards%20V2.gif)  
![Alt text](S18/Walking%20sideways%20V2.gif)  
![Alt text](S18/Turning%20V2.gif)  
# In-Place Maneuvers  
I also managed to program the robot to perform new in-place maneuvers using the code below. Through careful coding and implementation, I was able to enable the robot to perform yawing, rolling, and pitching movements while remaining in place. These maneuvers added a new level of versatility and flexibility to the robot's movements, allowing it to exhibit more dynamic and realistic behaviors.  
`moveBody=function(index)`  
    `local p={initialP[1],initialP[2],initialP[3]}`  
    `local o={initialO[1],initialO[2],initialO[3]}`  
    `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
    `if (index==0) then`  
        `-- up/down`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel*2,accel)`  
        `sim.wait(3)`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel*2,accel)`  
        `sim.wait(3)`  
    `end`  
    `if (index==1) then`  
        `-- 4x twisting`  
        `o[1]=o[1]+5*math.pi/180`  
        `o[2]=o[2]-05*math.pi/180`  
        `o[3]=o[3]-15*math.pi/180`  
        `p[1]=p[1]-0.04*sizeFactor`  
        `p[2]=p[2]+0.02*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[1]=o[1]-10*math.pi/180`  
        `o[3]=o[3]+30*math.pi/180`  
        `p[2]=p[2]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[1]=o[1]+10*math.pi/180`  
        `o[2]=o[2]+10*math.pi/180`  
        `p[2]=p[2]+0.04*sizeFactor`  
        `p[1]=p[1]+0.08*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[1]=o[1]-10*math.pi/180`  
        `o[3]=o[3]-30*math.pi/180`  
        `p[2]=p[2]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
    `end`  
    `if (index==2) then`  
        `-- rolling`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `o[1]=o[1]+23*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[1]=o[1]-46*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[1]=o[1]+23*math.pi/180`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
    `end`  
    `if (index==3) then`  
        `-- pitching`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `o[2]=o[2]+20*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[2]=o[2]-40*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[2]=o[2]+20*math.pi/180`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
    `end`  
    `if (index==4) then`  
        `-- yawing`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `o[3]=o[3]+25*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`   
        `sim.wait(3)`  
        `o[3]=o[3]-50*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `o[3]=o[3]+25*math.pi/180`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`  
        `sim.wait(3)`  
    `end`  
`end`   
The moveBody function generates in-place maneuvers for the robot dog in CoppeliaSim by adjusting its position and orientation, and then using the sim.moveToPosition function to move the robot to the desired position and orientation with specified velocity and acceleration parameters.     
Here are the results:  
UP AND DOWN  
![Alt text](S18/Up%20and%20Down.gif)    
ROLLING (Rotational motion around the robot's longitudinal axis (X-axis))    
![Alt text](S18/Rolling.gif    
PITCHING (Rotational motion around the robot's lateral axis (Y-axis))     
![Alt text](S18/Pitching.gif)    
YAWING  (rotational motion around the robot's vertical axis (Z-axis))  
![Alt text](S18/Yawing.gif)    
4x TWISTING    
![Alt text](S18/Twisting.gif)  