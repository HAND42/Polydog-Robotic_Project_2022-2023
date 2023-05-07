# SESSION 21 OUTCOME REPORT
## Date: 02/05/2023
## Main event of the session: Establishing ROS Connection and Integrating Esplora Controller with CoppeliaSim Simulation.    

# Establishing a ROS Connection Between Jetson Nano and Computer   
During this session, we worked on establishing a connection between Jetson Nano and the computer using ROS. To do so, we used the remote desktop connection application on Windows to enter the Jetson Nano using its IP address, which is 192.168.55.1. We planned to use the Wi-Fi interfaces to exchange information between Jetson Nano and the computer using ROS.   
To ensure proper communication, we exported ROS_MASTER_URI=http://192.168.55.1:11311/ on the computer. ROS_MASTER_URI is an environment variable that specifies the URI of the ROS master. It works by telling ROS on the computer to send information to the machine with the IP address 192.168.55.1. Additionally, we also needed to specify the ROS_IP of the Jetson Nano using this command: export ROS_IP=192.168.55.1. We did this because initially, ROS has a different IP than the machine.  
After executing the above commands, we successfully established a communication between the computer and Jetson Nano. However, we noticed that on the Jetson Nano, we could see the available topics, such as /JointStates. This topic was created by CoppeliSim on the computer, and it sends the joints values to it. Although we could see the topics on the Jetson Nano, we could not see the messages published on this topic, which was strange. We could not visualize the information on this topic, and we were not sure why this was happening.  

# Integrating the Esplora Controller with the CoppeliaSim Simulation using Serial Communication.  
During the second part of this session, I worked on integrating the Esplora controller that I programmed during the first semester (you can see [here](https://github.com/HAND42/Polydog-Robotic_Project_2022-2023/blob/main/session-reports/reports_younes-bazi/session8/session8.md) how i programmed it and how it communicates with the arduino mega via the bluetooth modules) to the CoppeliaSim simulation. The aim was to use the Esplora controller to control the Polydog on the simulation (and by doing that we can control the real physical polydog after establishing connection between the simulation and the jetson nano). To achieve this, we needed to establish communication between the Esplora controller and the simulation.  
The type of communication between the Esplora controller and the simulation was serial. The Esplora controller was connected to the Arduino Mega using Bluetooth modules. The HC05 Bluetooth module, which was the master, was connected to the Esplora. The HC05 sent the values of the joysticks, switches, and accelerometer of the controller to the HC06 Bluetooth module, which was connected to the Arduino Mega. The Arduino Mega read the values from HC06 and sent them to the computer through the port COM6.  
here is the code that read the values from the HC06 module connected to the arduino mega via the TX03 and RX03 pins and write them to the port that coppeliaSim will read from it  after:  
`#include <Esplora.h>`  
`int AccX;`  
`int AccY;`  
`int JoyX;`  
`int JoyY;`  
`int Switch1;`  
`int Switch2;`  
`int Switch3;`  
`int Switch4;`  
`int Joybutton;`  
`void setup(){`  
`Serial.begin(38400);`   
`delay(100);`  
`Serial3.begin(38400);`  
`delay(100);}`   
`void loop(){`  
  `if (Serial3.available()>= 9) {`  
    `AccX = Serial3.read(); // read the first value`  
    `AccY = Serial3.read(); // read the second value`  
    `JoyX = Serial3.read();// read the third value`  
    `JoyY = Serial3.read();`   
    `Switch1 = Serial3.read();`   
    `Switch2 = Serial3.read();`  
    `Switch3 = Serial3.read();`  
    `Switch4 = Serial3.read();`  
    `Joybutton = Serial3.read();`  
    `Serial.write(AccX);`  
    `Serial.write(AccY);`  
    `Serial.write(JoyX);`  
    `Serial.write(JoyY);`  
    `Serial.write(Switch1);`  
    `Serial.write(Switch2);`  
    `Serial.write(Switch3);`  
    `Serial.write(Switch4);`  
    `Serial.write(Joybutton);`  
    `delay(100);`  
`}`  
`}`    

Here is the code responsible for reading the values from the port on coppeliaSim:    

`function sysCall_init()`  
    `portHandle=sim.serialOpen("COM6",38400)`    
`end`  
`function sysCall_actuation()`  
`if sim.serialCheck(portHandle) > 0 then -- check if data is available`  
       `data = sim.serialRead(portHandle, 9, true) -- read 9 bytes of data`  
        `if data then`  
            `accX = string.byte(data, 1) -- extract the first value`  
            `accY = string.byte(data, 2) -- extract the second value`  
            `JoyX = string.byte(data, 3) -- extract the third value`  
            `sim.setScriptSimulationParameter(sim.handle_chain,'JoyX',JoyX)`  
            `JoyY = string.byte(data, 4) -- extract the fourth value`  
            `sim.setScriptSimulationParameter(sim.handle_chain,'JoyY',JoyY)`  
            `switch1 = string.byte(data, 5) -- extract the fifth value`  
            `sim.setScriptSimulationParameter(sim.handle_tree,'switch1',switch1)`  
            `switch2 = string.byte(data, 6) -- extract the sixth value`  
            `sim.setScriptSimulationParameter(sim.handle_tree,'switch2',switch2)`  
            `switch3 = string.byte(data, 7) -- extract the seventh value`  
            `sim.setScriptSimulationParameter(sim.handle_tree,'switch3',switch3)`  
            `switch4 = string.byte(data, 8) -- extract the eighth value`  
            `sim.setScriptSimulationParameter(sim.handle_tree,'switch4',switch4)`  
            `joyButton = string.byte(data, 9) -- extract the ninth value`  
            `sim.setScriptSimulationParameter(sim.handle_tree,'joyButton',joyButton)`  
            `sim.addStatusbarMessage("AccX = " .. accX .. ", AccY = " .. accY .. ", JoyX = " .. JoyX .. ", JoyY = " .. JoyY .. ", Switch1 = " .. switch1 .. ", Switch2 = " .. switch2 .. ", Switch3 = " .. switch3 .. ", Switch4 = " .. switch4 .. ", Joybutton = " .. joyButton)`      
        `end`  
    `end`  
`end`  
`function sysCall_cleanup()`  
    `sim.serialClose(portHandle)`  
`end`  

Here's the code that allows the Polydog in CoppeliaSim to respond to any variations in the values of the joysticks on the Esplora controller and move accordingly: 

`controller = function()`  
    `JoyX=sim.getScriptSimulationParameter(sim.handle_self,'JoyX')`  
    `JoyY=sim.getScriptSimulationParameter(sim.handle_self,'JoyY')`  
    `if JoyY == 0 then`  
        `-- Move robot forward`  
        `setStepMode(walkingVel,maxWalkingStepSize,stepHeight,0,0,0.4)`  
    `elseif JoyY == 253 then`  
        `-- Move robot backward`
        `setStepMode(walkingVel,maxWalkingStepSize,stepHeight,180,0,0.6)`  
    `else`  
        `setStepMode(walkingVel,maxWalkingStepSize,stepHeight,0,0,0)`  
    `end`      
    `if JoyX == 0 then`  
        `-- Move robot sideways left`  
        `setStepMode(walkingVel,maxWalkingStepSize,stepHeight,-90,0,0.4)`  
    `elseif JoyX == 253 then`  
        `-- Move robot sideways right`  
        `setStepMode(walkingVel,maxWalkingStepSize,stepHeight,90,0,0.4)`  
    `end`  
`end`   
If you want to understand how the setStepMode() function works , you must see the previous reports. Here is the video that shows that the polydog on coppeliaSim respond to the Esplora controller : 
![Alt text](S21/controlling_robot.gif)  