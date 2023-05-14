// Copyright (c) 2022-2022. ANJOU Raphaël & DURAND Hugo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Arduino.h>
#include "CustomServo/CustomServo.h"
#include "Accelerometer/Accelerometer.h"
#include "PolyDog/PolyDog.h"
#include "Leg/Leg.h"

/**
 * This method is the {@code PolyDog} initializer.
 * It is just creating the {@code Leg} instances.
 *
 * @author ANJOU Raphael
 */
PolyDog::PolyDog() : legA(1), legB(2), legC(3), legD(4)
{
    // HOLDER
}

/**
 * This method start the robot standing up on its feet. The position allows the rear leg to be raised while keeping the robot stable.
 * The algorithm consists in placing the hip and the knee motors in a stable position.
 *
 * @author ANJOU Raphael
 */
void PolyDog::stand_up()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(115);
        leg_list[i].move_knee(65);
    }

    this->hold_shoulders();
}
/**
 * This method start the robot standing up on its feet.
 * The position allows the front leg to be raised while keeping the robot stable.
 * @author DURAND Hugo
 */
void PolyDog::stand_up2()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(100);
        leg_list[i].move_knee(90);
    }

    this->hold_shoulders();
}
void PolyDog::stand_up3()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(110);
        leg_list[i].move_knee(73);
    }

    this->hold_shoulders();
}

/**
 * This method start the robot standing up on its feet. We have recovered two positions in which the robot is at the same height.
 * We have drawn a linear function on excel to implement here.
 * @author DURAND Hugo
 */
void PolyDog::stand_up4()
{
    int hip = 90;
    for (int i = 0; i < 15; i++)
    {
        hip = 115 - i;
        legA.move_hip(hip);
        legB.move_hip(hip);
        legC.move_hip(hip);
        legD.move_hip(hip);
        legA.move_knee((int)(-hip * 1.6667 + 256.67));
        legB.move_knee((int)(-hip * 1.6667 + 256.67));
        legC.move_knee((int)(-hip * 1.6667 + 256.67));
        legD.move_knee((int)(-hip * 1.6667 + 256.67));

        delay(30);
    }

    for (int i = 0; i < 15; i++)
    {
        hip = 100 + i;
        legA.move_hip(hip);
        legB.move_hip(hip);
        legC.move_hip(hip);
        legD.move_hip(hip);
        legA.move_knee((int)(-hip * 1.6667 + 256.67));
        legB.move_knee((int)(-hip * 1.6667 + 256.67));
        legC.move_knee((int)(-hip * 1.6667 + 256.67));
        legD.move_knee((int)(-hip * 1.6667 + 256.67));

        delay(30);
    }

    this->hold_shoulders();
}

void PolyDog::stand_up5()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(120);
        leg_list[i].move_knee(57);
    }

    this->hold_shoulders();
}

void PolyDog::horizontal_pos(Accelerometer dof)
{
    String acc = dof.display_rolls_pitch();
    Serial.println(acc);
}

void PolyDog::stand_up6()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(140);
        leg_list[i].move_knee(40);
    }
    delay(1000);

    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(100);
        leg_list[i].move_knee(78);
    }

    this->hold_shoulders();
    delay(1000);
}
void PolyDog::stand_up7(double AG, double EG)
{
    double ha, ka;
    Coord coord;
    coord.x = 0;
    coord.y = EG;
    coord.z = AG;
    get_angle_simplified(coord, ha, ka);
    get_coordonate_E_simplified(ha, ka, coord);
    Serial.println(ka);
    Serial.println(ha);
    Serial.println(coord.y);
    Serial.println(coord.z);

    // for (int i = 0; i < 4; i++)
    // {
    //     leg_list[i].move_hip(ha);
    //     leg_list[i].move_knee(ka);
    // }

    // this->hold_shoulders();
}

/**
 * By retrieving the value of the accelerometer of the Esplora remote control,
 * The robot is oriented according to the inclination of the joystick.
 *
 * @author DURAND Hugo
 */
void PolyDog::orientation(int AccX, int AccY)
{

    int angle_accx = (((AccX - 130) + 5) / 10) * 2;
    int angle_accy = (AccY - 125) / 5;
    legA.move_shoulder(90 - angle_accx);
    legB.move_shoulder(90 + angle_accx);
    legC.move_shoulder(90 + angle_accx);
    legD.move_shoulder(90 - angle_accx);

    legA.move_knee(73 - angle_accy);
    legB.move_knee(73 - angle_accy);

    legC.move_knee(73 + angle_accy);
    legD.move_knee(73 + angle_accy);
}

/**
 * This method place the shoulder in a position where all legs are perpendicular to the ground.
 * The algorithm consists in placing all shoulder motors at a 90 degrees angle.
 * Otherwise when we place the legs, there will be legs inverted with the others.
 *
 * @author ANJOU Raphael
 */
void PolyDog::hold_shoulders()
{
    /*
    100 : he spreads his legs
    80 : he brings his legs together
    */

    legA.move_shoulder(100);
    legB.move_shoulder(100);
    legC.move_shoulder(100);
    legD.move_shoulder(100);
}

/**
 * Execution of this method when placing the legs on the servo motor heads.
 * <p>
 * The placement is arbitrary. However, we have positioned the legs to optimize the servo's range of motion.
 * <p>
 * The algorithm consists in placing all hip and knee motors at a 90 degrees angle. It is useful while we screw the legs to the body.
 *
 * @author DURAND Hugo
 */
void PolyDog::placing_legs()
{
    for (int i = 0; i < 4; i++)
    {
        leg_list[i].move_hip(90);
        leg_list[i].move_knee(90);
    }
    this->hold_shoulders();
}

/**
 * This method moves the robot body from up to down using only his hip.
 * <p>
 * This method takes a minimum of 2400ms to execute due to 80 delays of 30ms.
 * <p>
 * The algorithm consists of two loops, each one of 40 steps. They allow a smooth movement between two desired positions
 * of the robot. One of the loop moves the robot down, and the next one up.
 *
 * @author DURAND Hugo
 */
void PolyDog::range_motion_hip()
{
    legA.move_hip(95);
    legB.move_hip(95);
    legC.move_hip(95);
    legD.move_hip(95);
    delay(100);
    for (int i = 0; i < 40; i++)
    {

        legA.move_hip(95 + i);
        legB.move_hip(95 + i);
        legC.move_hip(95 + i);
        legD.move_hip(95 + i);

        delay(30);
    }

    for (int i = 0; i < 40; i++)
    {
        legA.move_hip(135 - i);
        legB.move_hip(135 - i);
        legC.move_hip(135 - i);
        legD.move_hip(135 - i);
        delay(30);
    }
}

/**
 * This method moves the robot body from up to down using only his knee.
 * <p>
 * This method takes a minimum of 2400ms to execute due to 80 delays of 30ms.
 * <p>
 * The algorithm consists of two loops, each one of 40 steps. They allow a smooth movement between two desired positions
 * of the robot. One of the loop moves the robot down, and the next one up.
 *
 * @author DURAND Hugo
 */
void PolyDog::range_motion_knee()
{
    for (int i = 0; i < 40; i++)
    {
        legA.move_knee(70 + i);
        legB.move_knee(70 + i);
        legC.move_knee(70 + i);
        legD.move_knee(70 + i);
        legA.move_hip(115);
        legB.move_hip(115);
        legC.move_hip(115);
        legD.move_hip(115);

        delay(30);
    }

    for (int i = 0; i < 40; i++)
    {
        legA.move_knee(110 - i);
        legB.move_knee(110 - i);
        legC.move_knee(110 - i);
        legD.move_knee(110 - i);
        legA.move_hip(115);
        legB.move_hip(115);
        legC.move_hip(115);
        legD.move_hip(115);

        delay(30);
    }
}

/**
 * This method moves the robot body from left to right using only his shoulders.
 * <p>
 * This method takes a minimum of 2400ms to execute due to 80 delays of 30ms.
 * <p>
 * The algorithm consists of two loops, each one of 40 steps. They allow a smooth movement between two desired positions
 * of the robot. One of the loop moves it to the right, and the next one to the left.
 *
 * @author DURAND Hugo
 */
void PolyDog::range_motion_shoulder()
{

    for (int i = 0; i < 40; i++)
    {
        legA.move_shoulder(70 + i);
        legB.move_shoulder(110 - i);
        legC.move_shoulder(110 - i);
        legD.move_shoulder(70 + i);

        delay(30);
    }

    for (int i = 0; i < 40; i++)
    {
        legA.move_shoulder(110 - i);
        legB.move_shoulder(70 + i);
        legC.move_shoulder(70 + i);
        legD.move_shoulder(110 - i);
        delay(30);
    }
}

void PolyDog::trot_walk()
{
    int time = 300;

    leg_list[0].move_knee(80);
    leg_list[0].move_hip(90);
    leg_list[2].move_knee(80);
    leg_list[2].move_hip(90);
    delay(time);
    leg_list[1].move_knee(125);
    leg_list[1].move_hip(115);
    leg_list[3].move_knee(125);
    leg_list[3].move_hip(115);
    delay(time);
    leg_list[0].move_hip(130);
    leg_list[0].move_knee(40);
    leg_list[2].move_hip(130);
    leg_list[2].move_knee(40);
    delay(time);

    leg_list[1].move_knee(80);
    leg_list[1].move_hip(90);
    leg_list[3].move_knee(80);
    leg_list[3].move_hip(90);
    delay(time);
    leg_list[0].move_knee(125);
    leg_list[0].move_hip(115);
    leg_list[2].move_knee(125);
    leg_list[2].move_hip(115);
    delay(time);

    leg_list[1].move_hip(130);
    leg_list[1].move_knee(40);
    leg_list[3].move_hip(130);
    leg_list[3].move_knee(40);
    delay(time);
}

void PolyDog::stand_up8()
{

    leg_list[0].move_hip(110);
    leg_list[0].move_knee(100);
    leg_list[2].move_hip(110);
    leg_list[2].move_knee(100);

    leg_list[1].move_hip(138);
    leg_list[1].move_knee(30);
    leg_list[3].move_hip(138);
    leg_list[3].move_knee(30);
}

void PolyDog::trot_walk2()
{
    int time = 500;

    leg_list[0].move_hip(110);
    leg_list[0].move_knee(63);
    leg_list[2].move_hip(110);
    leg_list[2].move_knee(63);
    delay(time);
    leg_list[1].move_knee(80);
    leg_list[1].move_hip(138);
    leg_list[3].move_knee(80);
    leg_list[3].move_hip(138);
    delay(time);
    leg_list[0].move_hip(138);
    leg_list[0].move_knee(30);
    leg_list[2].move_hip(138);
    leg_list[2].move_knee(30);
    delay(time);

    leg_list[1].move_hip(110);
    leg_list[1].move_knee(63);
    leg_list[3].move_hip(110);
    leg_list[3].move_knee(63);
    delay(time);
    leg_list[0].move_knee(80);
    leg_list[0].move_hip(138);
    leg_list[2].move_knee(80);
    leg_list[2].move_hip(138);
    delay(time);

    leg_list[1].move_hip(138);
    leg_list[1].move_knee(30);
    leg_list[3].move_hip(138);
    leg_list[3].move_knee(30);
    delay(time);
}

void PolyDog::move_2leg(int i, int j)
{
    leg_list[i].move_knee(115);
    leg_list[i].move_hip(115);
    leg_list[j].move_knee(115);
    leg_list[j].move_hip(115);
    delay(2000);
    leg_list[i].move_hip(120);
    leg_list[i].move_knee(57);
    leg_list[j].move_hip(120);
    leg_list[j].move_knee(57);
    delay(2000);
}

void PolyDog::move_leg(int i)
{
    int k = (i + 2) % 4;
    leg_list[k].move_knee(105);
    for (int j = 0; j < 4; j++)
    {
        if (j != i)
        {
            leg_list[j].move_shoulder(90);
        }
    }
    leg_list[i].move_knee(115);
    leg_list[i].move_hip(115);
    delay(2000);
    this->hold_shoulders();
    leg_list[i].move_hip(100);
    leg_list[i].move_knee(90);
    leg_list[k].move_knee(90);
    delay(2000);
}

void PolyDog::move_leg2(int i)
{
    int time = 1000;
    leg_list[i].move_knee(115);
    delay(time);
}

void PolyDog::avance()
{
    int time = 200;
    leg_list[1].move_hip(130);
    leg_list[1].move_knee(40);
    leg_list[3].move_hip(130);
    leg_list[3].move_knee(40);
    delay(time);
    leg_list[0].move_knee(75);
    leg_list[2].move_knee(75);
    delay(time);
    leg_list[0].move_hip(120);
    leg_list[0].move_knee(57);
    leg_list[2].move_hip(120);
    leg_list[2].move_knee(57);
    delay(time);
    leg_list[1].move_knee(75);
    leg_list[3].move_knee(75);
    delay(time);
    leg_list[0].move_hip(130);
    leg_list[0].move_knee(40);
    leg_list[2].move_hip(130);
    leg_list[2].move_knee(40);
    delay(time);
    leg_list[1].move_hip(120);
    leg_list[1].move_knee(57);
    leg_list[3].move_hip(120);
    leg_list[3].move_knee(57);
    delay(time);
}

void PolyDog::avance2()
{
    int time = 200;
    leg_list[1].move_hip(130);
    leg_list[1].move_knee(40);
    leg_list[3].move_hip(130);
    leg_list[3].move_knee(40);
    delay(time);
    leg_list[0].move_knee(80);
    leg_list[2].move_knee(80);
    delay(time);
    leg_list[0].move_hip(120);
    leg_list[0].move_knee(57);
    leg_list[2].move_hip(120);
    leg_list[2].move_knee(57);
    delay(time);
    leg_list[1].move_knee(80);
    leg_list[3].move_knee(80);
    delay(time);
    leg_list[0].move_hip(130);
    leg_list[0].move_knee(40);
    leg_list[2].move_hip(130);
    leg_list[2].move_knee(40);
    delay(time);
    leg_list[1].move_hip(120);
    leg_list[1].move_knee(57);
    leg_list[3].move_hip(120);
    leg_list[3].move_knee(57);
    delay(time);
}

void PolyDog::moving_shoulders()
{
    leg_list[1].move_shoulder(85);
    leg_list[2].move_shoulder(85);

    leg_list[0].move_knee(115);
    leg_list[0].move_hip(115);
    leg_list[3].move_knee(115);
    leg_list[3].move_hip(115);

    leg_list[0].move_shoulder(110);
    leg_list[3].move_shoulder(110);

    leg_list[0].move_knee(90);
    leg_list[0].move_hip(100);
    leg_list[3].move_knee(90);
    leg_list[3].move_hip(100);
}
/**
 * This methods moves the robot one step to the right.
 * WARNING : It is still not working properly. The robot needs to be lifted a little bit to walk properly.
 * If placed in a loop, the robot appears to be walking sideways.
 * <p>
 * This method takes a minimum of 1400ms due to 12 delays of 100ms and 10 delays of 20ms
 * <p>
 * The algorithm consists of 3 main steps. First, we are moving leg B and leg C to the left one after the other. The
 * second step consists in moving shoulders B and C so that they are above their respective foot and moving shoulders A
 * and D to follow the body (all of the shoulders move simultaneously). Final step consists in bringing back the feet of
 * the legs B and C.
 *
 * @author ANJOU Raphael
 */
void PolyDog::move_right()
{
    // LEG A
    legA.move_hip(50);
    delay(100);
    legA.move_shoulder(70);
    delay(100);
    legA.move_hip(70);
    legA.move_knee(80);
    delay(100);

    // LEG D
    legD.move_hip(50);
    delay(100);
    legD.move_shoulder(70);
    delay(100);
    legD.move_hip(70);
    legD.move_knee(80);
    delay(100);

    // --- ALL LEGS SIMULTANEOUSLY ---
    for (int i = 1; i <= 10; i++)
    {
        legC.move_knee(70 + i);         // GOAL = 80
        legC.move_shoulder(90 - i * 2); // GOAL = 70

        legB.move_knee(70 + i);         // GOAL = 80
        legB.move_shoulder(90 - i * 2); // GOAL = 70

        legA.move_shoulder(70 + i * 2); // GOAL = 90
        legA.move_knee(80 - i);         // GOAL = 70

        legD.move_shoulder(70 + i * 2); // GOAL = 90
        legD.move_knee(80 - i);         // GOAL = 70

        delay(20);
    }

    // LEG C
    legC.move_hip(50);
    delay(100);
    legC.move_shoulder(90);
    delay(100);
    legC.move_hip(70);
    legC.move_knee(80);
    delay(100);

    // LEG B
    legB.move_hip(50);
    delay(100);
    legB.move_shoulder(90);
    delay(100);
    legB.move_hip(70);
    legB.move_knee(80);
    delay(100);
}

// ------------------------------------------------

/**
 * This methods moves the robot one step to the left.
 * WARNING : It is still not working properly. The robot needs to be lifted a little bit to walk properly.
 * If placed in a loop, the robot appears to be walking sideways.
 * <p>
 * This method takes a minimum of 1400ms due to 12 delays of 100ms and 10 delays of 20ms
 * <p>
 * The algorithm consists of 3 main steps. First, we are moving leg C and leg B to the left one after the other. The
 * second step consists in moving shoulders A and D so that they are above their respective foot and moving shoulders B
 * and C to follow the body (all of the shoulders move simultaneously). Final step consists in bringing back the feet of
 * the legs A and D.
 *
 * @author ANJOU Raphael
 */
void PolyDog::move_left()
{
    // LEG C
    legC.move_hip(50);
    delay(100);
    legC.move_shoulder(70);
    delay(100);
    legC.move_hip(70);
    legC.move_knee(80);
    delay(100);

    // LEG B
    legB.move_hip(50);
    delay(100);
    legB.move_shoulder(70);
    delay(100);
    legB.move_hip(70);
    legB.move_knee(80);
    delay(100);

    // --- ALL LEGS SIMULTANEOUSLY ---
    for (int i = 1; i <= 10; i++)
    {
        legA.move_knee(70 + i);         // GOAL = 80
        legA.move_shoulder(90 - i * 2); // GOAL = 70

        legD.move_knee(70 + i);         // GOAL = 80
        legD.move_shoulder(90 - i * 2); // GOAL = 70

        legC.move_shoulder(70 + i * 2); // GOAL = 90
        legC.move_knee(80 - i);         // GOAL = 70

        legB.move_shoulder(70 + i * 2); // GOAL = 90
        legB.move_knee(80 - i);         // GOAL = 70

        delay(20);
    }

    // LEG A
    legA.move_hip(50);
    delay(100);
    legA.move_shoulder(90);
    delay(100);
    legA.move_hip(70);
    legA.move_knee(80);
    delay(100);

    // LEG D
    legD.move_hip(50);
    delay(100);
    legD.move_shoulder(90);
    delay(100);
    legD.move_hip(70);
    legD.move_knee(80);
    delay(100);
}
