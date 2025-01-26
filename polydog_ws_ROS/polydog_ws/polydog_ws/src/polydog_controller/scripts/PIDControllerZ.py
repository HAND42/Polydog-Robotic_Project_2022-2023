#!/usr/bin/env python3

import rospy
import numpy as np

class PID_controllerZ(object):
    def __init__(self, kp, ki, kd):
        self.kp = kp
        self.ki = ki
        self.kd = kd

        # desired yaw angles
        self.desired_rpy = np.array([310])
        self.I_term = np.array([0.0])
        self.D_term = np.array([0.0])

        # TODO: Tune max_I
        self.max_I = 5
        self.last_error = np.array([0.0])
        

    def run(self, yaw):
        # determine error
        error = self.desired_rpy - np.array([yaw])
        
        if abs(error) <= 30 :
            return np.array([0.0])

        # determine time step
        t_now = rospy.Time.now()
        step = (t_now - self.last_time).to_sec()

        # Check if step is zero or close to zero
        if abs(step) < 1e-6:
            return np.array([0.0, 0.0])

        # I term update
        self.I_term = self.I_term + error * step

        # anti-windup
        for i in range(1):
            if self.I_term[i] < -self.max_I:
                self.I_term[i] = -self.max_I
            elif self.I_term[i] > self.max_I:
                self.I_term[i] = self.max_I

        # approximate first derivative
        self.D_term = (error - self.last_error) / step

        # update last values
        self.last_time = t_now
        self.last_error = error

        # compute return values
        P_ret = self.kp * error
        I_ret = self.I_term * self.ki
        D_ret = self.D_term * self.kd

        return P_ret + I_ret + D_ret

    def reset(self):
        self.last_time = rospy.Time.now()
        self.I_term = np.array([0.0])
        self.D_term = np.array([0.0])
        self.last_error = np.array([0.0])

    def desired_RPY_angles(self, des_yaw):
        # set desired roll, pitch, and yaw angles
        self.desired_rpy = np.array([des_yaw])
        
