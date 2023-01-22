#include <Esplora.h>
void setup()
{
Serial.begin(38400);
Serial1.begin(38400);
}
void loop()
{
//Read the Values from the esplora controller.
int a=Esplora.readButton(1);
int b=Esplora.readButton(2);
int c=Esplora.readButton(4);
int d=Esplora.readButton(3);
int e=Esplora.readJoystickButton();
int f=Esplora.readJoystickX();
int g=Esplora.readJoystickY();
int x_axis = Esplora.readAccelerometer(X_AXIS);
int y_axis = Esplora.readAccelerometer(Y_AXIS);
int X_axis=map(x_axis,-180,180,0,254);
X_axis=constrain(X_axis,0,254);
int Y_axis=map(y_axis,-180,180,0,254);
Y_axis=constrain(Y_axis,0,254);
int h=map(f,-512,+512,0,+254);
h=constrain(h,0,254);
int i=map(g,-512,+512,0,+254);
i=constrain(i,0,254);
//print the values in the serial monitor
Serial.print("AccX= ");
Serial.print(X_axis);
Serial.print("\tAccY= ");
Serial.print(Y_axis);
Serial.print("\tJoyX= ");
Serial.print(h);
Serial.print("\tJoyY= ");
Serial.print(i);
Serial.print("\tSwitch1= ");
Serial.print(a);
Serial.print("\tSwitch2= ");
Serial.print(b);
Serial.print("\tSwitch3= ");
Serial.print(d);
Serial.print("\tSwitch4= ");
Serial.print(c);
Serial.print("\tJoybutton= ");
Serial.println(e);
delay(100);
//Send the information to the Bluetooth module hc05 via serial pin 1.
Serial1.write(X_axis);
Serial1.write(Y_axis);
Serial1.write(h);
Serial1.write(i);
Serial1.write(a);
Serial1.write(b);
Serial1.write(d);
Serial1.write(c);
Serial1.write(e);
delay(100);
} 