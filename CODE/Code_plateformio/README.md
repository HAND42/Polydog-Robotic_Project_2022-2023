# Code PlateformIO

The code part of our project was implemented on a PlateformIO workspace. It allows to create a single source code for multiple environments easily (Arduino Uno, Mega 2560, etc) with a single code base, and provides an easy-to-use interface for managing dependencies, libraries, and building and uploading code to the board. It is particularly useful for developing complex IoT projects that involve multiple microcontrollers and devices.


<h4>In the src folder, we have 3 classes :</h4> 

## CustomServos:

The CustomServo class has a constructor which takes as input the pin to which the servo is connected.

The write(int angle) method allows to move the servo to the desired angle by using the map() function to convert the angle into a value between 500 and 2500 corresponding to the protocol of the SSC32 card.

The method move(int position, int time) manages the serial communication to move the servo motor. It sends commands in the format "#pin Pposition Ttime" to the SSC32 board to indicate the position and the time that the servo must take to reach the target position.

## Leg :

The Leg class has a constructor that takes as input the leg number to use. Based on this number, it assigns the appropriate values for the member variables _knee_servo, _hip_servo, _shoulder_servo, _knee_offset, _hip_offset, _ANGLE_MIN_SHOULDER and _ANGLE_MAX_SHOULDER.

The method move_knee(int angle, int offset) moves the knee of the servo to the desired angle using the write() function of the CustomServo class. It also uses an offset variable to align the servo angles. There is also a move_knee(int angle) method that uses the offset of the class.

The move_hip(int angle, int offset) method moves the servo hip to the desired angle in the same way as the move_knee method.

The move_shoulder(int angle) method moves the servo shoulder to the desired angle using the write() function of the CustomServo class. It also ensures that the angle does not exceed the predefined limits for this joint.


## PolyDog :

The PolyDog class is used to control the overall robot and includes methods for making the robot stand up, move, and orient itself based on input from an accelerometer and joystick.

The angles of each servo motors are chosen after numerous tests to optimize the movement of the of the leg.

Through the Arduino board, we send commands to the Serial commands to the Serial of the ssc-32. The message sent is of the form " #{pin_number} P {position between 500 and 2500} T {time} We do not use the time parameter in the move function. This allows us to have the freedom to to vary the time in the methods coding the robot movements of the robot. The write function returns the move function by
converting the 500-2500 microseconds amplitude into 0-180°. This facilitates the physical understanding of the robot.


## Accelerometer :

This class allows the use of the ADXL345 accelerometer with an Arduino microcontroller. It uses the Wire library to communicate with the accelerometer via the I2C bus.

The Accelerometer class has two methods: start() and display_rolls_pitch().

The start() method configures the accelerometer to start measuring accelerations and performs an offset calibration for the X, Y and Z axes.

The display_rolls_pitch() method reads the acceleration data from the accelerometer on the X, Y and Z axes, calculates the rotation around the X axis (roll) and around the Y axis (pitch) using the trigonometric functions atan() and sqrt(), and then uses a low-pass filter to smooth the resulting values. The roll and pitch values are then displayed on the serial link.

## Remote esplora

It is a class that allows to control Polydog with an Esplora card. It uses the "SoftwareSerial" library to communicate with the Esplora card via the serial link.

The RemoteEsplora class has two constructors, a default constructor and a constructor that takes as input the RX and TX pins for the serial link. It also uses the libraries RemoteEsplora.h and Esplora.h

The begin(long speed) method configures the serial link for a specified speed in bauds.

The method RemoteInstruction(PolyDog dog) reads the data from the Esplora card (acceleration on the X and Y axes, trigger position, button status, etc.) and displays them on the serial link for debugging.

This method does not work yet. We still have to modify it to add it in the main() and thus lighten the code in the loop() function