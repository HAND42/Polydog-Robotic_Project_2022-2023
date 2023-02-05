# Session 9 - Week 3

##### Polydog_v3 -- January 2022

-----

## Esplora remote

I integrated the code of younes and adapted it so that the dog robot responds to some commands of the controller. The Esplora remote control sends the values of its joysticks and buttons via bluetooth to the Arduino board. 

I made a class EsploraRemote that allows to control Polydog.

The RemoteEsplora class has two constructors, a default constructor and a constructor that takes as input the RX and TX pins for the serial link.

The begin(long speed) method configures the serial link for a specified speed in bauds.

The method RemoteInstruction(PolyDog dog) reads the data from the Esplora card (acceleration on the X and Y axes, trigger position, button status, etc.) and displays them on the serial link for debugging.

This method does not work yet. We still have to modify it to add it in the main() and thus lighten the code in the loop() function

For now, the fonctionnality works in the main() but I'm stilling working on how to make it work in the class, with nearly the same code, except that I have to create SoftwareSerial Serial3 in main or as a private variable and use in the function EsploraRemote.

Here is an example of the code execution when the switch1 button is pressed, it starts to follow the movements of the remote control thanks to the accelerometer fixed on the card :

![](orientation.gif)


## Oral presentation


For the oral on Monday January 16th, we have prepared a list of features to present. If we press the front joystick, it makes the robot move forward. Two buttons allow to visualize the balance of the robot on 3 legs, by raising either a front leg or a back leg by adapting the position of the legs.



Here is the code in the main, in charge of managing the button pressing and joysticks : 

```c++
 if (JoyY <= 100){
     dog.trot_walk();
    }
     if (JoyY >= 150){
        dog.trot_walk();
    }
    if (Switch1 != 1){
        orientation=1-orientation;
        dog.stand_up3();
    }
    if (Switch2 != 1){
        dog.stand_up2();
        dog.move_leg(0);
    }
    if (Switch3 != 1){
        dog.stand_up();
        dog.move_leg(3);
    }
    if (Switch4 != 1){
        dog.stand_up3();
    }
}
if (orientation){
    dog.orientation(AccX,AccY);
    }
```

We have explained a little bit during the short time (5 min) how we envisage the next step in the learning of the robot to walk for good. We are currently developing a simulation of the robot's gait using reverse kinematics to learn to balance itself. 

Towards the very end of the demo, the servo horns that I had tended to build and develop gave up the ghost by splitting into pieces. I had new parts printed in stronger resins hoping that this kind of incident will not happen again if I really want to progress in the code part.

I rebuilt it again on Friday, with 2 new servo horns keeping two of the old ones to see the difference between the two. I took the risk to leave them to see if they hold or not.

