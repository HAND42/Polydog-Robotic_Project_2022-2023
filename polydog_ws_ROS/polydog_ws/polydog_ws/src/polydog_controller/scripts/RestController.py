#!/usr/bin/env python3

import rospy
import numpy as np
from Transformations import rotxyz
from PIDControllerX import PID_controllerX
from PIDControllerY import PID_controllerY
class RestController(object):
    def __init__(self, default_stance):
        self.def_stance = default_stance

        # TODO: tune kp, ki and kd
        #                                     kp     ki    kd
        #self.pid_controller = PID_controller(0.02,0.00,0.000)
        self.pid_controllerx = PID_controllerX(0.025,0.000,0.0015)
        self.pid_controllery = PID_controllerY(0.015,0.000,0.0015)
        self.use_imu = True
        self.use_button = True
        self.pid_controllerx.reset()
        self.pid_controllery.reset()
        
    def updateStateCommand(self, msg, state, command):
        # local body position
        #state.body_local_position[0] = msg.linear.z * 0.04
        state.body_local_position[0] = msg.axes[0]  * 0.04
        if msg.axes[1]  < 0: 
            state.body_local_position[2] = msg.axes[1]  * 0.09
        if msg.axes[1] > 0: 
            state.body_local_position[2] = msg.axes[1]  * 0.04
        if msg.axes[1]  == 0: 
            state.body_local_position[2] = msg.axes[1] 
        # local body orientation
        state.body_local_orientation[0] = msg.axes[4]  * 0.4
        state.body_local_orientation[1] = msg.axes[3]  * 0.5
        state.body_local_orientation[2] = msg.axes[7]  * 0.08
        #compensationz = self.pid_controllerz.run(state.imu_roll)
        #print(compensationz[0])
        #state.body_local_orientation[0] = compensationz[0]



    @property
    def default_stance(self):
        return self.def_stance
        
    def stabilize(self, msg4, state, command):
        #compensationz = self.pid_controllerz.run(msg4.data[0])
        #state.body_local_orientation[1] = 0.2
        pass
        
        
    def follow(self, msg2,command):
        pass
        
    def navigate(self, msg3, command):
        pass        

    def step(self, state, command):
        temp = self.default_stance
        temp[2] = [command.robot_height] * 4

        # roll and pitch compensation
        # if self.use_imu == True, the robot tries to keep its body horizontal
        # using a PID controller
        if self.use_imu:
            compensationy = self.pid_controllery.run(state.imu_pitch)
            compensationx = self.pid_controllerx.run(state.imu_roll)
            print(state.imu_roll-4)
            #print(state.imu_pitch-5)
            #print(state.imu_yaw)
            roll_compensation = compensationx[0]
            pitch_compensation = compensationy[0]

            rot = rotxyz(roll_compensation,-pitch_compensation,0)
            temp = np.matmul(rot,temp)

        return temp

    def run(self, state, command):
        state.foot_locations = self.step(state, command)
        return state.foot_locations
