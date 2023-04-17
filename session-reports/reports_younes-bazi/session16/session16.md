# SESSION 16 OUTCOME REPORT
## Date: 21/03/2023
## Main event of the session: Building The Robot in CoppeliaSim V-rep and Optimizing Development Time with Open-Source Simulation Code for The Polydog. 

# Assembly of the Polydog Using Joints  
I started this session by importing all the individual parts of the Polydog from Onshape. The decision to import the parts one by one was made to avoid any complications with the joints, which I planned to add later during the assembly process. This method, although time-consuming, ensured that I had full control over the placement and configuration of each component. After importing all the parts, I began the task of assembling the Polydog using joints. This process was intricate and took a considerable amount of time due to the complexity of the robot's design. I carefully aligned each part and created joints to connect them accurately. As I progressed through the assembly, I made sure to test the functionality and mobility of the joints to ensure smooth operation.  
![Alt text](S16/Capture%20d%E2%80%99%C3%A9cran%202023-04-17%20033843.png)   

# Learning Lua Programming for Controlling the Polydog  
With the Polydog model fully assembled, I shifted my focus to learning how to program the robot. I familiarized myself with the various programming languages and tools that could be used for this purpose. The CoppeliaSim software offers users the flexibility to choose between two programming languages: Lua and Python. After careful consideration, we opted for Lua to control our robot dog. Lua is an ideal choice for controlling the robot dog due to its lightweight nature, ease of embedding, and fast execution speeds. As a high-level, dynamically-typed, and garbage-collected scripting language, Lua is widely used in various domains, such as game development, embedded systems, and web applications. Its simplicity and efficiency make it a popular choice for embedding in software systems where resources are constrained. We decided to use Lua because it provides a robust and efficient solution for controlling our robot dog, while also offering excellent integration with the CoppeliaSim environment. Overall, Lua's features and benefits make it a highly suitable language for our project's requirements.  
I then began learning the syntax and structure of lua, focusing on the commands and functions relevant to controlling the Polydog. I also started to explore different resources, such as online tutorials and documentation, to gain a deeper understanding of programming the robot dog.  

# Utilizing Open-Source Simulation Code for Programming the Polydog  
During my research on programming the Polydog, I stumbled upon a simulation for a similar robot dog created by an experienced robotics developer. After reviewing the simulation and examining the code, I found that it closely matched our project's requirements. Since the simulation was open-source, I decided to use the developer's code as a starting point for our Polydog project. This saved us a considerable amount of time and effort since we didn't have to create the entire codebase from scratch. However, I made sure to carefully review and modify the code to fit our specific needs and ensure that it worked correctly with our robot's unique features and functionality. Using this simulation's code as a foundation, we will be able to significantly speed up our development process and create a more efficient and effective solution for controlling the Polydog.    
Here is a segment of the code:  
`setStepMode=function(stepVelocity,stepAmplitude,stepHeight,movementDirection,rotationMode,movementStrength)`  
    `sim.setScriptSimulationParameter(sim.handle_tree,'stepVelocity',stepVelocity)`  
    `sim.setScriptSimulationParameter(sim.handle_tree,'stepAmplitude',stepAmplitude)`  
    `sim.setScriptSimulationParameter(sim.handle_tree,'stepHeight',stepHeight)`  
    `sim.setScriptSimulationParameter(sim.handle_tree,'movementDirection',movementDirection)`  
    `sim.setScriptSimulationParameter(sim.handle_tree,'rotationMode',rotationMode)`  
    `sim.setScriptSimulationParameter(sim.handle_tree,'movementStrength',movementStrength)`  
`end`  
`moveBody=function(index)`  
    `local p={initialP[1],initialP[2],initialP[3]}`  
    `local o={initialO[1],initialO[2],initialO[3]}`  
    `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
    `if (index==0) then`  
        `-- up/down`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel*2,accel)`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel*2,accel)`  
    `end`  
    `if (index==1) then`  
        `-- 4x twisting`  
        `o[1]=o[1]+5*math.pi/180`  
        `o[2]=o[2]-05*math.pi/180`  
        `o[3]=o[3]-15*math.pi/180`  
        `p[1]=p[1]-0.04*sizeFactor`  
        `p[2]=p[2]+0.02*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[1]=o[1]-10*math.pi/180`  
        `o[3]=o[3]+30*math.pi/180`  
        `p[2]=p[2]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[1]=o[1]+10*math.pi/180`  
        `o[2]=o[2]+10*math.pi/180`  
        `p[2]=p[2]+0.04*sizeFactor`  
        `p[1]=p[1]+0.08*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[1]=o[1]-10*math.pi/180`  
        `o[3]=o[3]-30*math.pi/180`  
        `p[2]=p[2]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
    `end`  
    `if (index==2) then`  
        `-- rolling`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `o[1]=o[1]+23*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[1]=o[1]-46*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[1]=o[1]+23*math.pi/180`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
    `end`  
    `if (index==3) then`  
        `-- pitching`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `o[2]=o[2]+20*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[2]=o[2]-40*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[2]=o[2]+20*math.pi/180`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
    `end`  
    `if (index==4) then`  
        `-- yawing`  
        `p[3]=p[3]+0.04*sizeFactor`  
        `o[3]=o[3]+25*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[3]=o[3]-50*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `o[3]=o[3]+25*math.pi/180`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
        `p[3]=p[3]-0.04*sizeFactor`  
        `sim.moveToPosition(legBase,robotBase,p,o,vel,accel)`  
    `end`  
`end`  
`legBase=sim.getObjectHandle('Base_target')`  
`sizeFactor=sim.getObjectSizeFactor(robotBase)`  
`vel=0.5`  
`accel=0`  
`initialP={0,0,0}`  
`initialO={0,0,0}`  
`initialP[3]=initialP[3]+0.03*sizeFactor`  
`sim.moveToPosition(legBase,robotBase,initialP,initialO,vel,accel)`   
`stepHeight=0.04*sizeFactor`  
`maxWalkingStepSize=0.3*sizeFactor`   
`walkingVel=1`  

This code is a threaded script that controls the robot dog body movement and controls another non-threaded script responsible for generating the walking movement. The setStepMode function is used to set the step mode parameters such as step velocity, step amplitude, step height, movement direction, rotation mode, and movement strength. This function writes the parameters to the simulation using the sim.setScriptSimulationParameter method. The moveBody function generates the body movement of the Polydog. It takes an index parameter that specifies the type of movement to perform, such as up/down, twisting, rolling, pitching, and yawing. It uses sim.moveToPosition to move the robot's leg base and body base to new positions and orientations, controlled by initialP and initialO tables, with velocity vel and acceleration accel. The robotBase and legBase are handles to the robot's body and leg base in the simulation. The sizeFactor is used to adjust the movement based on the size of the Polydog. Finally, There are still some modifications and attributions that need to be made before testing the simulations.


