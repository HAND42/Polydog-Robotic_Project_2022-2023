##### Polydog_v3 -- May 2023

---

## Angle transmission on Arduino

```lua
function sysCall_actuation()
-- Send the Joint Angles of the robot:
    --if not pluginNotFound then
    ej1=(sim.getJointPosition(elbowj1Handle)*180/math.pi)
    if simROS then
            simROS.publish(jointStatePub,sendJointStates())
    end
    print("port" .. portHandle)
    print("Joint angles: " .. ej1)
    sim.serialSend(portHandle,ej1)
end
```

Here is the main function of the lua code on CoppeliaSim, we send the angles on the Serial port where the Arduino is connected.

for the moment i got this angle wich I want to send to the arduino, moving the hip of the leg B :

port18
Joint angles: 14.531396506384

I sent this joint angle to my servo motor, just to test if it work, with this Arduino code :

```cpp
#include <Servo.h>
Servo myservo;
//#define servoPin 9
void setup() {
  // Start the serial communication
  //myservo.attach(servoPin);
  int _pin = 2;
  Serial.begin(115200);
  delay(100);
}

void loop() {
  //myservo.write(90);
  if (Serial.available()) {
    // Read the incoming data
    // int S1 = Serial.read();
    int H1 = Serial.read();
    // int K1 = Serial.read();
    // set the angle of the servo motor connected to channel 2 to the mapped value of H1
    int hip = map(H1, 0, 180, 500, 2500);
    Serial.print("#");
    Serial.print(2);
    Serial.print("P");
    Serial.print(hip);
    Serial.print("T100\r");
  }
}
```

As I can't listen on the serial port used by the simulation to send data, I have to connect an arduino board to get the data on the RX of the SSC32 board and read it on another serial port :

```c++
Initialize
Received:
#2P1066T100
#2P1100T100
#2P1011T100
#2P1066T100
#2P1044T100
#2P1111T100
#2P1044T100
#2P1122T100
#2P1055T100
#2P1100T100
#2P1066T100
#2P1088T100
#2P1088T100
#2P1088T100

Received:
#2P1066T100
#2P1133T100
#2P1011T100
#2P1100T100
#2P1055T100
#2P1111T100
#2P1044T100
#2P1033T100
#2P1133T100
#2P1122T100
#2P1033T100
#2P1133T100
#2P1100T100
#2P1133T100
#2P1122T100
```

I send data a lot of data at the same time and I can not control or at least I didn't find how to slow down that.

I change the simulation time step to match the actual time. In the serial monitor of coppeliasim, I can see the time flooding correctly, but it still send a lot of data.
