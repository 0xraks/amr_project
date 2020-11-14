#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Float64
print('ROS Twist to Arduino PWM running')
left_pwm=0
right_pwm=0
left_pub=rospy.Publisher('/left_publish',Float64,queue_size=10)
right_pub=rospy.Publisher('/right_publish',Float64,queue_size=10)


class Driver:
    def __init__(self):
        rospy.init_node('driver')

        self._last_received = rospy.get_time()
        self._timeout = rospy.get_param('~timeout', 2)
        self._rate = rospy.get_param('~rate', 10)
        self._max_speed = rospy.get_param('~max_speed', 0.5)
        self._wheel_base = rospy.get_param('~wheel_base', 0.091)

        # Setup subscriber for velocity twist message
        rospy.Subscriber('cmd_vel', Twist, self._velocity_received_callback)

    def convert(self,val):
        self.new_val=val*25.5
        if self.new_val > 255:
            return 255
        else:
            return int(self.new_val)

    def _velocity_received_callback(self, message):
        """Handle new velocity command message."""

        self._last_received = rospy.get_time()
        linear = message.linear.x
        angular = message.angular.z


        # Calculate wheel speeds in m/s
        left_speed = linear - angular*self._wheel_base/2
        right_speed = linear + angular*self._wheel_base/2
        print("Left Motor Speed " , left_speed , " m/s")
        print("Right Motor Speed " ,right_speed ," m/s")
        left_pwm=left_speed*25.5
        right_pwm=right_speed*25.5
        if  left_pwm > 255:
            left_pwm=255
        if right_pwm > 255:
            right_pwm=255
        if  left_pwm < -255:
            left_pwm=-255
        if right_pwm < -255:
            right_pwm=-255
        left_pub.publish(left_pwm)
        right_pub.publish(right_pwm)


    def run(self):
        """The control loop of the driver."""

        rate = rospy.Rate(self._rate)

        while not rospy.is_shutdown():

            rate.sleep()

def main():
    driver = Driver()

    # Run driver. This will block
    driver.run()
    


if __name__ == '__main__':
    main()
