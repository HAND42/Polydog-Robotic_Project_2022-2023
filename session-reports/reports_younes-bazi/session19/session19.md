# SESSION 19 OUTCOME REPORT
## Date: 11/04/2023
## Main event of the session: ROS Integration with CoppeliaSim for controlling the physical Polydog and  Implementing a PID Controller for Smooth and Precise Motion.   
# Implementing PID Controller for the Polydog in Coppeliasim    
During today's session, I worked on implementing a PID(Proportional-Integral-Derivative) controller code for the Polydog in CoppeliaSim simulation. The goal of this session was to develop a PID controller code for the robot dog in CoppeliaSim simulation that would ensure the robot dog remains stable on a table even when it is rotated, maintaining angles of 0 on the x and y axes.  
To begin, I reviewed the principles of the PID controller, which involves calculating an error term based on the difference between the desired setpoint and the actual measured value, and then adjusting the control signal accordingly. The PID controller consists of three components: the proportional (P), integral (I), and derivative (D) terms, each of which contributes to the overall control action.  
Next, I implemented the PID controller code in Lua language, which is the scripting language used in CoppeliaSim simulation. I defined the gains for the P, I, and D terms, and initialized variables to store previous error and integral error values for calculating the derivative term. I also set the desired setpoint for the robot dog's position, which determines the target position that the Polydog should reach.  
I then integrated the PID controller code into the existing simulation environment of the robot dog in CoppeliaSim. I added the necessary API calls to retrieve the current position of the Polydog and calculate the error term based on the desired setpoint. I also implemented the control action by adjusting the velocity of the robot dog based on the calculated control signal from the PID controller.  
After the initial implementation, I performed several iterations of testing and fine-tuning to optimize the performance of the PID controller. I adjusted the gains for the P, I, and D terms to achieve a smooth and stable control action.  
Here is the code :   
`stabilizeRobotDog = function()`  
    `Polydog = sim.getObjectHandle('Body')`  
    `body_visual = sim.getObjectHandle('Reference')`  
    `orientation = sim.getObjectOrientation(Polydog, body_visual)`  
    `-- Convert orientation to degrees`  
    `angle = {`  
        `(orientation[1] * 180) / math.pi,`  
        `(orientation[2] * 180) / math.pi,`  
        `(orientation[3] * 180) / math.pi`  
    `}`  
    `x, y, z = angle[1], angle[2], angle[3]`  
    `targetOrientation = {0, 0, 0} -- The desired orientation (in degrees) when the robot is steady`    
    `-- Calculate the orientation error (difference between target and current orientation)`    
    `errorX, errorY, errorZ = targetOrientation[1] - x, targetOrientation[2] - y, targetOrientation[3] - z`    
    `-- PID control gains for each axis (you may need to adjust these values)`  
    `kPy = 0.015`    
    `kIy = 0.2`    
    `kDy = 0.1`    
    `-- Initialize the integral and derivative errors if not already done`  
    `if integralErrorX == nil then`  
        `integralErrorX, integralErrorY, integralErrorZ = 0, 0, 0`  
        `prevErrorX, prevErrorY, prevErrorZ = errorX, errorY, errorZ`  
    `end`  
    `-- Calculate the integral and derivative errors`  
    `integralErrorX = integralErrorX + errorX * dt`  
    `integralErrorY = integralErrorY + errorY * dt`  
    `integralErrorZ = integralErrorZ + errorZ * dt`  
    `derivativeErrorX = (errorX - prevErrorX) / dt`  
    `derivativeErrorY = (errorY - prevErrorY) / dt`  
    `derivativeErrorZ = (errorZ - prevErrorZ) / dt`  
    `-- Calculate the required orientation adjustments based on the error and control gains`  
    `adjustmentX = kPx * errorX + kIx * integralErrorX + kDx * derivativeErrorX`  
    `adjustmentY = kPy * errorY + kIy * integralErrorY + kDy * derivativeErrorY`  
    `adjustmentZ = kPz * errorZ + kIz * integralErrorZ + kDz * derivativeErrorZ`  
    `-- Update the previous errors`  
    `prevErrorX, prevErrorY, prevErrorZ = errorX, errorY, errorZ`  
    `-- Adjust the robot dog's leg positions and orientations based on the calculated adjustments`  
    `p = {initialP[1], initialP[2], initialP[3]}`  
    `o = {initialO[1], initialO[2], initialO[3]}`  
    `if  y~=0  then`  
        `o[2]=o[2]+adjustmentY`  
        `sim.moveToPosition(legBase,PolydogBase,p,o,vel,accel)`     
    `end`  
`end`  
Here is gif showing the robot staying steady (y angle always equal 0) on a rotating table:  
![Alt text](S19/Stabilization.gif)  
# Integrating CoppeliaSim with ROS  
I also worked on integrating CoppeliaSim with ROS (Robot Operating System) to establish communication between the simulation environment and real physical robots. I successfully wrote a code that allowed me to send joint values from CoppeliaSim to ROS, enabling me to control the physical robots in real-time. The code I developed utilized the ROS interface provided by CoppeliaSim, which allows communication between the simulation environment and ROS nodes. I first created a ROS node in CoppeliaSim using the Lua scripting language. This ROS node acted as a bridge, enabling communication between CoppeliaSim and ROS. Next, I implemented the code to retrieve joint values from the simulated Polydog model in CoppeliaSim. I accessed the joint positions and velocities using the CoppeliaSim API, which provides functions for interacting with the simulation environment. I then packaged these joint values into a ROS message, specifically a JointState message, which is a standard ROS message type used to represent joint states of a robot. Once the JointState message was created, I published it to a ROS topic using the ROS interface provided by CoppeliaSim. ROS topics are communication channels used by ROS nodes to send and receive messages. In this case, I published the JointState message to a specific topic, which was subscribed to by the ROS node that will be run on the physical robot. The integration of CoppeliaSim with ROS opens up exciting possibilities for testing and validating robot control algorithms in a simulated environment before deploying them on real physical robots. This enables safer and more efficient development of robotic systems, as it reduces the risks associated with testing on real robots directly.  
Here is the code :  
`function sysCall_init()`         
    `robotHandle=sim.getObjectHandle(sim.handle_self)`  
     `sholderj1Handle = sim.getObjectHandle('sholderj1')`  
     `elbowj1Handle = sim.getObjectHandle('elbowj1')`  
     `legj1Handle = sim.getObjectHandle('legj1')`  
     `sholderj2Handle = sim.getObjectHandle('sholderj2')`  
     `elbowj2Handle = sim.getObjectHandle('elbowj2')`  
     `legj2Handle = sim.getObjectHandle('legj2')`  
     `sholderj3Handle = sim.getObjectHandle('sholderj3')`  
     `elbowj3Handle = sim.getObjectHandle('elbowj3')`  
     `legj3Handle = sim.getObjectHandle('legj3')`  
     `sholderj4Handle = sim.getObjectHandle('sholderj4')`  
     `elbowj4Handle = sim.getObjectHandle('elbowj4')`  
     `legj4Handle = sim.getObjectHandle('legj4')`  
`-- Check if the required ROS plugin is there:`   
    `moduleName=0`  
    `moduleVersion=0`  
    `index=0`  
    `pluginNotFound=true`  
    `while moduleName do`  
        `moduleName,moduleVersion=sim.getModuleName(index)`  
        `if (moduleName=='RosInterface') then`  
            `pluginNotFound=false`  
        `end`  
        `index=index+1`  
    `end`  
    `-- Add a banner:`  
    `if (pluginNotFound) then`  
        `bannerText="ROS Not Connected"`  
    `else`  
        `bannerText="ROS Connected"`  
    `end`  
    `black={0,0,0,0,0,0,0,0,0,0,0,0}`  
    `red={0,0,0,0,0,0,0,0,0,1,0.2,0.2}`  
    `sim.addBanner(bannerText,0,sim.banner_bitmapfont+sim.banner_overlay,nil,sim.getObjectHandle(sim.handle_self),black,red)`    
    `-- Ok now launch the ROS client application:`  
    `if (not pluginNotFound) then`  
        `local sysTime=sim.getSystemTimeInMs(-1)`   
        `local JointsTopicName = 'JointIK'..sysTime`  
        `local simulationTimeTopicName='simTime'..sysTime -- we add a random component so that we can have several instances of this robot running`       
    `-- Prepare the sensor publisher and the motor speed subscribers:`  
       `jointStatePub = simExtRosInterface_advertise('/JointStates','sensor_msgs/JointState')`   
       `--jointStatePub = simROS.advertise('/JointStates','sensor_msgs/JointState')`  
        `--publisher=simROS.advertise('/simulationTime','std_msgs/Float32')`  
        `--simTimePub=simROS.advertise('/'..simulationTimeTopicName,'std_msgs/Float32')`  
        `-- Now we start the client application:`  
        `--result=sim.launchExecutable('rosRobotIK',JointsTopicName.." "..simulationTimeTopicName,0)`  
    `end`   
`end`  
`function sendJointStates()`  
     `sj1=(sim.getJointPosition(sholderj1Handle)*180/math.pi)`  
     `ej1=(sim.getJointPosition(elbowj1Handle)*180/math.pi)`  
     `lj1=(sim.getJointPosition(legj1Handle)*180/math.pi)`  
     `sj2=(sim.getJointPosition(sholderj2Handle)*180/math.pi)`  
     `ej2=(sim.getJointPosition(elbowj2Handle)*180/math.pi)`  
     `lj2=(sim.getJointPosition(legj2Handle)*180/math.pi)`  
     `sj3=(sim.getJointPosition(sholderj3Handle)*180/math.pi)`  
     `ej3=(sim.getJointPosition(elbowj3Handle)*180/math.pi)`  
     `lj3=(sim.getJointPosition(legj3Handle)*180/math.pi)`  
     `sj4=(sim.getJointPosition(sholderj4Handle)*180/math.pi)`  
     `ej4=(sim.getJointPosition(elbowj4Handle)*180/math.pi)`  
     `lj4=(sim.getJointPosition(legj4Handle)*180/math.pi)`  
     `sj1m = angle_map(sj1,-78,102,0,180)`  
     `ej1m = angle_map(ej1,-75,105,0,180)`  
     `lj1m = angle_map(lj1,-79,101,180,0) `  
`return`  
 `{`  
    `header = {seq=0,stamp=simExtRosInterface_getTime(),frame_id=Realname},`  
    `name = {},`  
    `position = {sj1,ej1,lj1, sj2,ej2,lj2, sj3,ej3,lj3, sj4,ej4,lj4},`  
    `velocity = {},`  
    `effort = {}      `     
 `}`  
`end `  
`--Maping function`  
`function angle_map(Value, Xmin, Xmax, Ymin, Ymax)`  
    `xmin = Xmin`  
    `xmax = Xmax`  
    `ymin = Ymin`  
    `ymax = Ymax`  
    `out = ( ((Value-xmin)*(ymax-ymin))/(xmax-xmin) )+ymin`  
  `return {out}`  
`end`  
`function sysCall_actuation()`  
`-- Send the Joint Angles of the robot:` 
    `--if not pluginNotFound then`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(sholderj1Handle,'sholderj1'))`    
            `simExtRosInterface_publish(jointStatePub,sendJointStates(elbowj1Handle,'elbowj1'))`   
            `simExtRosInterface_publish(jointStatePub,sendJointStates(legj1Handle,'legj1'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(sholderj2Handle,'sholderj2'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(elbowj2Handle,'elbowj2'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(legj2Handle,'legj2'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(sholderj3Handle,'sholderj3'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(elbowj3Handle,'elbowj3'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(legj3Handle,'legj3'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(sholderj4Handle,'sholderj4'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(elbowj4Handle,'elbowj4'))`  
            `simExtRosInterface_publish(jointStatePub,sendJointStates(legj4Handle,'legj4'))`  
    `--end`  
`end`  
`function sysCall_cleanup()`  
    `if not pluginNotFound then`  
        `-- Following not really needed in a simulation script (i.e. automatically shut down at simulation end):`  
        `--simRExt(jointStatePub)`  
    `end`  
`end`  