# Session 8 - Week 50 & Christmas vacations

##### Polydog_v3 -- December 2022

-----

## Offset & stable position

Just after reassembling the legs, I realized that I had positioned the legs on the head of the motor servos with this code: 

```c++
void PolyDog::stand_up()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(115); 
        leg_list[i].move_knee(65);
    }

    this->hold_shoulders();
}
```

I had him lift his paw to observe the stability of the rest of the body when he lost a fulcrum. Here is the result in picture : 

![](raising-leg.gif)

However, when I tested a trotting code, some motors were in opposition with other motors breaking the symmetry of the movement. Two legs went in the opposite direction of the other two. By putting back the leg again, I lost the stability of the robot that I had previously : 

![](raising-leg-actual_configuration.gif)

I drew 4 crosses on a table in my room to place the 4 feet exactly in the right place. This allowed me to be quite precise on the offset of the hips and knees.

If the leg is too far back, it is sufficient to increase the angular value of the hip offset and vice versa. Then, when the robot leans on one leg, the angular value of the knee offset must be increased.

 After a few attempts, I have a dog that stands straight, can be better with a spirit level. Waiting for being in class.

## Trot walk

I wrote this function to test à little walk just to see : 
```c++
void trot_walk();
```
Result : 

![](trotwalk.gif)

It doesn't looks so bad taking into account the fact that it is not stable when it lifts a leg. The goal for the next session will be to get him to move one paw without falling and two why not.

## Range of Motion mouvement of the knee and hip

I wrote some functions that shows the range of motion I can use to raise a leg and put it backward or forward.

void PolyDog::range_motion_hip();
void PolyDog::range_motion_knee();
void PolyDog::range_motion_shoulder();

![](motionknee.gif)

Then I needed to know what angles to choose so that the leg would land further away but at the same distance from the ground as the other legs.

So I made a table from two points and drew the linear curve on excel. Then, I implemented it in a stand up3 function, to illustrate the result.

```c++
void PolyDog::stand_up3()
{
    int hip=90;
    for (int i = 0; i < 15; i++)
    {
        hip=115-i;
        legA.move_hip(hip);
        legB.move_hip(hip);
        legC.move_hip(hip);
        legD.move_hip(hip);
        legA.move_knee( (int)(-hip*1.6667 +256.67));
        legB.move_knee( (int)(-hip*1.6667 +256.67));
        legC.move_knee( (int)(-hip*1.6667 +256.67));
        legD.move_knee( (int)(-hip*1.6667 +256.67));
        
        delay(30);
    }

    for (int i = 0; i < 15; i++)
    {
        hip=100+i;
        legA.move_hip(hip);
        legB.move_hip(hip);
        legC.move_hip(hip);
        legD.move_hip(hip);
        legA.move_knee( (int)(-hip*1.6667 +256.67));
        legB.move_knee( (int)(-hip*1.6667 +256.67));
        legC.move_knee( (int)(-hip*1.6667 +256.67));
        legD.move_knee( (int)(-hip*1.6667 +256.67));

        delay(30);
    }

     this->hold_shoulders(); 

}
```

Unfortunately you can't put video in an .md report, not to my knowledge anyway, but if you listen to the sound of the mp4s in this session's file, you can hear a squeak. I need to put some oil before I can continue. Or maybe even better, add some ball bearings at the places where two plastic parts slide together. I should have done this long before, but it wasn't the concern before. 

