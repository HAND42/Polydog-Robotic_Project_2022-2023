#!/usr/bin/env python3

import rospy
import time
import serial
from sensor_msgs.msg import Joy,Imu
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64MultiArray
from geometry_msgs.msg import Twist
import RobotController
import robot_IK
from std_msgs.msg import Float64



USE_IMU = True
RATE = 300

rospy.init_node("Robot_Controller")
pub = rospy.Publisher('/joint_states', JointState, queue_size=10)
joint_state = JointState()
joint_angles1=[0]*12
joint_names = ["RL1_joint", "FL1_joint", "FR1_joint", "RR1_joint", "RR2_joint", "FR2_joint", "FL2_joint", "RL2_joint", "RL3_joint", "FL3_joint", "FR3_joint", "RR3_joint"]
# Robot geometry
body = [0.286, 0.205]
legs = [0.0, 0.30, 0.1295, 0.125] 
serial_port = serial.Serial(
    port="/dev/ttyUSB0",
    baudrate=9600,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
)
# Wait a second to let the port initialize
time.sleep(1)
polydog_robot = RobotController.Robot(body, legs, USE_IMU)
inverseKinematics = robot_IK.InverseKinematics(body, legs)

#command_topics = ["/polydog_controller/FR1_joint/command",
                 # "/polydog_controller/FR2_joint/command",
                 # "/polydog_controller/FR3_joint/command",
                #  "/polydog_controller/FL1_joint/command",
                #  "/polydog_controller/FL2_joint/command",
                #  "/polydog_controller/FL3_joint/command",
                #  "/polydog_controller/RR1_joint/command",
                #  "/polydog_controller/RR2_joint/command",
                 # "/polydog_controller/RR3_joint/command",
                #  "/polydog_controller/RL1_joint/command",
                #  "/polydog_controller/RL2_joint/command",
                #  "/polydog_controller/RL3_joint/command"]

#publishers = []
#for i in range(len(command_topics)):
    #publishers.append(rospy.Publisher(command_topics[i], Float64, queue_size = 10))
    
rospy.Subscriber("/cmd_vel",Twist,polydog_robot.navigate2)
rospy.Subscriber("/euler_angles",Float64MultiArray,polydog_robot.imu_orientation)
rospy.Subscriber("/human_distance",Float64MultiArray,polydog_robot.follow)
rospy.Subscriber("polydog_joy/joy_ramped",Joy,polydog_robot.joystick_command)


rate = rospy.Rate(RATE)

del body
del legs
#del command_topics
del USE_IMU
del RATE

while not rospy.is_shutdown():
    leg_positions = polydog_robot.run()
    polydog_robot.change_controller()
    def map1(value):
        return int((value+1.57)/(1.57+1.57)*(2500-500)+500)
    dx = polydog_robot.state.body_local_position[0]
    dy = polydog_robot.state.body_local_position[1]
    dz = polydog_robot.state.body_local_position[2]
    
    roll = polydog_robot.state.body_local_orientation[0]
    pitch = polydog_robot.state.body_local_orientation[1]
    yaw = polydog_robot.state.body_local_orientation[2]

    try:
        joint_angles = inverseKinematics.inverse_kinematics(leg_positions,
                               dx, dy, dz, roll, pitch, yaw)
        #joint_angles1=[0]*12
        for i in range(len(joint_angles)):
            #if i == 2 or i == 3 or i == 4 or i == 5 or i == 8 or i == 9 or i == 10 or i == 11:
                #publishers[i].publish(-joint_angles[i])
            #if i == 0 or i == 1 or i == 6 or i == 7 :
               # publishers[i].publish(joint_angles[i])
            if i == 0 :
                command = "#4P%d\r\n" % map1(-joint_angles[i]-3*0.07535)
                serial_port.write(command.encode())
                joint_angles1[2]=joint_angles[i]
                #print(command)
            if i == 1 :
                command = "#6P%d\r\n" % map1(joint_angles[i]-5*0.157)
                serial_port.write(command.encode())
                joint_angles1[5]=joint_angles[i]
                #print(command)
            if i == 2 :
                command = "#5P%d\r\n" % map1(-joint_angles[i]-joint_angles[i-1])
                serial_port.write(command.encode())
                joint_angles1[10]=-joint_angles[i]
              #  print(command)
            if i == 3 :
                command = "#20P%d\r\n" % map1(-joint_angles[i]-1*0.07535-0.025)
                serial_port.write(command.encode())
                joint_angles1[1]=-joint_angles[i]
              # print(command)
            if i == 4 :
                command = "#22P%d\r\n" % map1(-joint_angles[i]-2*0.05)
                serial_port.write(command.encode())
                joint_angles1[6]=-joint_angles[i]
               # print(command)
            if i == 5 :
                command = "#21P%d\r\n" % map1(joint_angles[i]+joint_angles[i-1]+1.57+3*0.05)
                serial_port.write(command.encode())
                joint_angles1[9]=-joint_angles[i]
              #  print(command)
            if i == 6 :
                command = "#0P%d\r\n" % map1(joint_angles[i]+0.157-0.05)
                serial_port.write(command.encode())
                joint_angles1[3]=joint_angles[i]
              #  print(command)
            if i == 7 :
                command = "#2P%d\r\n" % map1(joint_angles[i]-2*0.157)
                serial_port.write(command.encode())
                joint_angles1[4]=joint_angles[i]
              #  print(command)
            if i == 8 :
                command = "#1P%d\r\n" % map1(-joint_angles[i]-joint_angles[i-1]-1.57+2*0.157+0.07535)
                serial_port.write(command.encode())
                joint_angles1[11]=-joint_angles[i]
              #  print(command)
            if i == 9 :
                command = "#16P%d\r\n" % map1(joint_angles[i]+0.05)
                serial_port.write(command.encode())
                joint_angles1[0]=-joint_angles[i]
              #  print(command)
            if i == 10 :
                command = "#17P%d\r\n" % map1(-joint_angles[i]+2*0.157+0.0100+1*0.05)
                serial_port.write(command.encode())
                joint_angles1[7]=-joint_angles[i]
              #  print(command)
            if i == 11 :
                command = "#18P%d\r\n" % map1(joint_angles[i]+joint_angles[i-1]+1.57-2*0.157-2*0.0785)
                serial_port.write(command.encode())
                joint_angles1[8]=-joint_angles[i]
              #  print(command)
        joint_state.name = joint_names
        joint_state.position = joint_angles1
        joint_state.header.stamp = rospy.Time.now()
        pub.publish(joint_state)
        rate.sleep()
    except:
        pass

    rate.sleep()
