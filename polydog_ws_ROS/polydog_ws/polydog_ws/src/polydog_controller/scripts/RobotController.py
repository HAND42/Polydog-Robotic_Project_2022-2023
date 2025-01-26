#!/usr/bin/evn python3

import numpy as np
import tf
from StateCommand import State, Command, BehaviorState
from RestController import RestController
from TrotGaitController import TrotGaitController
from CrawlGaitController import CrawlGaitController
from StandController import StandController
from Follower import Follower
from Navigation import Navigation

class Robot(object):
    def __init__(self, body, legs, imu):
        self.body = body
        self.legs = legs

        self.delta_x = self.body[0] * 0.5
        self.delta_y = self.body[1] * 0.5 + self.legs[1]
        self.x_shift_front = 0.02 #0.006
        self.x_shift_back = -0.02 #-0.03
        self.default_height = 0.20

        self.trotGaitController = TrotGaitController(self.default_stance,
            stance_time = 0.18, swing_time = 0.24, time_step = 0.065,
            use_imu = imu)

        self.crawlGaitController = CrawlGaitController(self.default_stance,
            stance_time = 0.55, swing_time = 0.45, time_step = 0.02)
            
        self.standController = StandController(self.default_stance)

        self.restController = RestController(self.default_stance)
        
        self.follower = Follower(self.default_stance,
            stance_time = 0.18, swing_time = 0.24, time_step = 0.065,
            use_imu = imu)
            
        self.navigation = Navigation(self.default_stance,
            stance_time = 0.18, swing_time = 0.24, time_step = 0.065,
            use_imu = imu)

        self.currentController = self.restController
        self.state = State(self.default_height)
        self.state.foot_locations = self.default_stance
        self.command = Command(self.default_height)

    def change_controller(self):
        
        if self.command.trot_event:
            if self.state.behavior_state == BehaviorState.REST:
                self.state.behavior_state = BehaviorState.TROT
                self.currentController = self.trotGaitController
                self.currentController.pid_controller.reset()
                self.currentController.pid_controllerZ.reset()
                self.state.ticks = 0
            self.command.trot_event = False

        elif self.command.crawl_event:
            if self.state.behavior_state == BehaviorState.REST:
                self.state.behavior_state = BehaviorState.CRAWL
                self.currentController = self.crawlGaitController
                self.currentController.first_cycle = True;
                self.state.ticks = 0
            self.command.crawl_event = False

        elif self.command.stand_event:
            if self.state.behavior_state == BehaviorState.REST:
                self.state.behavior_state = BehaviorState.STAND
                self.currentController = self.standController
            self.command.stand_event = False

        elif self.command.rest_event:
            self.state.behavior_state = BehaviorState.REST
            self.currentController = self.restController
            self.currentController.pid_controllerx.reset()
            self.currentController.pid_controllery.reset()
            self.command.rest_event = False
            
        elif self.command.follow_event:
            if self.state.behavior_state == BehaviorState.REST:
                self.state.behavior_state = BehaviorState.FOLLOW
                self.currentController = self.follower
                self.currentController.pid_controller.reset()
                self.currentController.pid_controllerZ.reset()
                self.state.ticks = 0
            self.command.follow_event = False
            
        elif self.command.navigate_event:
            if self.state.behavior_state == BehaviorState.REST:
                self.state.behavior_state = BehaviorState.NAVIGATE
                self.currentController = self.navigation
                self.currentController.pid_controller.reset()
                self.currentController.pid_controllerZ.reset()
                self.state.ticks = 0
            self.command.navigate_event = False

    def joystick_command(self,msg):
    
        if msg.buttons[0]: # rest
            self.command.trot_event = False
            self.command.crawl_event = False
            self.command.stand_event = False
            self.command.rest_event = True
            self.command.follow_event = False
            self.command.navigate_event = False
            
        elif msg.buttons[1]: # trot
            self.command.trot_event = True
            self.command.crawl_event = False
            self.command.stand_event = False
            self.command.rest_event = False
            self.command.follow_event = False
            self.command.navigate_event = False
            
        #elif msg.buttons[2]: # crawl
            #self.command.trot_event = False
            #self.command.crawl_event = True
           # self.command.stand_event = False
           # self.command.rest_event = False
           # self.command.follow_event = False
            #self.command.navigate_event = False
                        
        elif msg.buttons[3]: # follow
            self.command.trot_event = False
            self.command.crawl_event = False
            self.command.stand_event = False
            self.command.rest_event = False
            self.command.follow_event = True
            self.command.navigate_event = False
                   
        elif msg.buttons[2]: # navigate
            self.command.trot_event = False
            self.command.crawl_event = False
            self.command.stand_event = False
            self.command.rest_event = False
            self.command.navigate_event = True
            
        self.currentController.updateStateCommand(msg, self.state, self.command)


    def imu_orientation(self,msg4):
        #q = msg.orientation
        #rpy_angles = tf.transformations.euler_from_quaternion([q.x,q.y,q.z,q.w])
        self.state.imu_roll = msg4.data[1] #rpy_angles[0]
        self.state.imu_pitch = msg4.data[2] #rpy_angles[1]
        #print(msg4.data[1])
        self.state.imu_yaw = msg4.data[0] #rpy_angles[2]
        self.currentController.stabilize(msg4,self.state,self.command)

    def follow(self,msg2):
        self.state.distance = msg2.data[0]
        self.state.x = msg2.data[1]
        self.state.y = msg2.data[2]
        self.currentController.follow(msg2,self.command)
        #print(msg.data[0])
        #print(msg.data[1])
        #print(msg.data[2])
        
    def navigate2(self,msg3):
        self.currentController.navigate(msg3,self.command)
        #print(msg3.linear.x)
        #print(msg3.angular.z)

    def run(self):
        return self.currentController.run(self.state, self.command)

    @property
    def default_stance(self):
        # FR, FL, RR, RL
        return np.array([[self.delta_x + self.x_shift_front,self.delta_x + self.x_shift_front,-self.delta_x + self.x_shift_back,-self.delta_x + self.x_shift_back],
                         [-self.delta_y                    ,self.delta_y                     ,-self.delta_y                    , self.delta_y                    ],
                         [0                                ,0                                ,0                                ,0                                ]])
