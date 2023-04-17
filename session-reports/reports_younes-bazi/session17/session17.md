# SESSION 17 OUTCOME REPORT
## Date: 28/03/2023
## Main event of the session: Successfully Achieving Our Goal: Making Our Robot Walk in Simulation.   

During this session, we achieved a significant milestone in our project by successfully adapting and modifying the code we had previously obtained from an open-source project. As discussed in our previous meeting, our goal was to make our robot walk in the simulation, and we are delighted to report that we have successfully achieved this objective. We worked diligently to understand the code and implement the necessary changes to make our robot walk seamlessly. We faced some challenges along the way, but we were able to overcome them and achieve our goal.
# Walking Forward  
![Alt text](S17/Walking%20Forward.gif)  
# Walking Backwards  
![Alt text](S17/Walking%20Backwards.gif)  
# Walking Sideways  
![Alt text](S17/Walking%20sideways.gif)  
# Turning  
![Alt text](S17/Turning.gif)  

# The code  
The code responsible for controlling the walking behavior of the Polydog is this:  
`function __setObjectPosition__(a,b,c)`  
    `-- compatibility routine, wrong results could be returned in some situations, in CoppeliaSim <4.0.1`  
    `if b==sim.handle_parent then`  
        `b=sim.getObjectParent(a)`  
    `end`  
    `if (b~=-1) and (sim.getObjectType(b)==sim.object_joint_type) and (sim.getInt32Param(sim.intparam_program_version)>=40001) then`  
        `a=a+sim.handleflag_reljointbaseframe`  
    `end`  
    `return sim.setObjectPosition(a,b,c)`  
`end`  
`function __getObjectPosition__(a,b)`  
    `-- compatibility routine, wrong results could be returned in some situations, in CoppeliaSim <4.0.1`  
    `if b==sim.handle_parent then`  
        `b=sim.getObjectParent(a)`  
    `end`  
    `if (b~=-1) and (sim.getObjectType(b)==sim.object_joint_type) and (sim.getInt32Param(sim.intparam_program_version)>=40001) then`  
        `a=a+sim.handleflag_reljointbaseframe`  
    `end`  
    `return sim.getObjectPosition(a,b)`  
`end`  
`function sysCall_init()`  
    `robotBase=sim.getObjectHandle('Base_target')`  
    `legTips={-1,-1,-1,-1}`  
    `legTargets={-1,-1,-1,-1}`  
    `for i=1,4,1 do`  
        `legTips[i]=sim.getObjectHandle('tip'..i)`
        `legTargets[i]=sim.getObjectHandle('target'..i)`  
    `end`  
    `initialPos={nil,nil,nil,nil}`  
    `for i=1,4,1 do`  
        `initialPos[i]=__getObjectPosition__(legTips[i],robotBase)`  
    `end`  
    `legMovementIndex={1,3,1,3}`  
    `stepProgression=0`  
    `stepVelocity=0.1`  
    `stepAmplitude=0.16`  
    `stepHeight=0.04`  
    `movementStrength=1`  
    `realMovementStrength=0`  
    `movementDirection=0*math.pi/180`  
    `rotation=0`     
`end`  
`function sysCall_cleanup()`  
`end`  
`function sysCall_actuation()`   
    `dt=sim.getSimulationTimeStep()`  
    `stepVelocity=sim.getScriptSimulationParameter(sim.handle_self,'stepVelocity')`  
    `stepAmplitude=sim.getScriptSimulationParameter(sim.handle_self,'stepAmplitude')`  
    `stepHeight=sim.getScriptSimulationParameter(sim.handle_self,'stepHeight')`  
    `movementDirection=math.pi*sim.getScriptSimulationParameter(sim.handle_self,'movementDirection')/180`  
    `rotation=sim.getScriptSimulationParameter(sim.handle_self,'rotationMode')`  
    `movementStrength=sim.getScriptSimulationParameter(sim.handle_self,'movementStrength')`  
    `dx=movementStrength-realMovementStrength`  
    `if (math.abs(dx)>dt*0.1) then`  
        `dx=math.abs(dx)*dt*0.5/dx`  
    `end`  
    `realMovementStrength=realMovementStrength+dx`  
    `for leg=1,4,1 do`  
        `sp=(stepProgression+(legMovementIndex[leg]-1)/4) % 1`  
        `offset={0,0,0}`  
        `if (sp<(1/3)) then`  
            `offset[1]=sp*3*stepAmplitude/2`  
        `else`  
            `if (sp<(1/3+1/6)) then`  
                `s=sp-1/3`  
                `offset[1]=stepAmplitude/2-stepAmplitude*s*6/2`  
                `offset[3]=s*6*stepHeight`  
            `else`  
                `if (sp<(2/3)) then`  
                    `s=sp-1/3-1/6`  
                    `offset[1]=-stepAmplitude*s*6/2`  
                    `offset[3]=(1-s*6)*stepHeight`  
                `else`  
                    `s=sp-2/3`  
                    `offset[1]=-stepAmplitude*(1-s*3)/2`  
                `end`  
            `end`  
        `end`  
        `md=movementDirection+math.abs(rotation)*math.atan2(initialPos[leg][1]*rotation,-initialPos[leg][2]*rotation)`  
        `offset2={offset[1]*math.cos(md)*realMovementStrength,offset[1]*math.sin(md)*realMovementStrength,offset[3]*realMovementStrength}`  
        `p={initialPos[leg][1]+offset2[1],initialPos[leg][2]+offset2[2],initialPos[leg][3]+offset2[3]}`  
        `__setObjectPosition__(legTargets[leg],robotBase,p) -- We simply set the desired foot position. IK is implicitely handled after that (in the default main script). You could also explicitely handle IK for this foot with sim.handleIkGroup()`
    `end`
    `stepProgression=stepProgression+dt*stepVelocity`
    `sim.addStatusbarMessage(stepProgression)`
`end`  

The script focuses on controlling the leg movements of the Polydog to enable walking. It starts by defining compatibility routines, __setObjectPosition__ and __getObjectPosition__, to ensure correct results are produced in certain situations. In the sysCall_init function, the script initializes essential variables, such as leg tips, leg targets, initial positions, and movement parameters. The primary actuation logic is present in the sysCall_actuation function, where the step progression, amplitude, height, movement direction, and rotation are updated based on the simulation parameters. The script calculates the desired foot positions for each leg by factoring in the movement strength and direction. Notably, the code does not involve any explicit math operations for handling inverse kinematics, as the simulator implicitly takes care of these calculations when setting the desired foot position. The script adjusts the target positions and lets the simulation handle the underlying inverse kinematic operations, allowing the robot dog to walk smoothly. Now that we have succeeded simulating the robot, our next step is to let CoppeliaSim control our robot with ROS, which will allow us to integrate our simulation with the real world.

