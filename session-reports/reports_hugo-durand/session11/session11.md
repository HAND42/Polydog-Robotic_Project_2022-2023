# Session 11 - Week 6

##### Polydog_v3 -- February 2022

-----

## Placing metal servo horns

In grey pro resin, the screw thread that links the servo motor head to the servo horn is damaged and the shoulder of the leg does not follow the movement ordered by the electronic board.

For the umpteenth and last time, I disassembled the legs to place metal servo horns by cutting the upper part of the single blade propeller to fit it in the old handspinner servo horn location.

![](placing-servo-horn.gif)

On the picture, we can see that the cut top part does not fill the exact location. There is a small gap. By adding extra strong glue, the servo horn does not move anymore, and it will never move again. 

The reassembly also takes a lot of time. So part of the session was devoted to that, and also an extra 3 hours for the complete reassembly of the robot, which is still an inert object.

## Research of a stable position

From the beginning, I started from the principle that the balance of a robot dog can never be obtained. The objective was to make it lose its balance momentarily by raising a paw, or two in an optimal way to put it back a few feet away, thus restoring its balance. 

I was greatly inspired by this video showing the gait of a robot very similar to mine, we can see that the movement of the legs is done by small steps but very fast: 

<figure align="center"><img src="diy-quadruped-robot.png"><figcaption><a href=https://www.youtube.com/watch?v=Y6QYdh4bs70&ab_channel=YunusZenichowski>Youtube-link --> Low Cost Walking Quadruped Robot DIY</a></figcaption></figure>

I'm pretty sure that by lifting a leg the balance of the robot is compromised.

However, I have not yet succeeded in obtaining an adequate result for the robot to move forward using this method : the robot is too unbalanced to move forward correctly. 

Going back to the base, I added functions that place the legs of the robot in different positions.

The inclination of the line formed by the foot and the center of rotation of the hip can lead to either unbalance or balance of the body.

Here is the test with the robot in a stable position with the lines vertical: 

![](the-leg-is-straight.gif)

By raising the leg, it fall immediatly.

Here is the test with the robot in a stable position with the lines this way :

 /'''\

![](the-legs-are-spread-out.gif)

The result is not convincing, there is still a long way to go.

