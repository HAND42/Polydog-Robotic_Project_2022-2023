#include <Esplora.h>
int AccX;
int AccY;
int JoyX;
int JoyY;
int Switch1;
int Switch2;
int Switch3;
int Switch4;
int Joybutton;
void setup(){
Serial.begin(38400);
delay(100);
Serial.println("Bonjour -Pret pour les commandes AT");
Serial3.begin(38400);
delay(100);}
void loop(){
  if (Serial3.available()>= 9) { // This code is checking if there are 9 bytes available in the Serial3 buffer, if there are, it's reading the first value and assigns it to the variable AccX, then it's reading the second value and assigns it to the variable AccY, and so on
    AccX = Serial3.read(); // read the first value
    AccY = Serial3.read(); // read the second value
    JoyX = Serial3.read();// read the third value
    JoyY = Serial3.read();
    Switch1 = Serial3.read();
    Switch2 = Serial3.read();
    Switch3 = Serial3.read();
    Switch4 = Serial3.read();
    Joybutton = Serial3.read();
    //print the values in the serial monitor
    Serial.print("AccX= ");
    Serial.println(AccX);
    Serial.print("AccY= ");
    Serial.println(AccY);
    Serial.print("JoyX= ");
    Serial.println(JoyX);
    Serial.print("JoyY= ");
    Serial.println(JoyY);
    Serial.print("Switch1= ");
    Serial.println(Switch1);
    Serial.print("Switch2= ");
    Serial.println(Switch2);
    Serial.print("Switch3= ");
    Serial.println(Switch3);
    Serial.print("Switch4= ");
    Serial.println(Switch4);
    Serial.print("Joybutton= ");
    Serial.println(Joybutton);
    delay(100);


}
}