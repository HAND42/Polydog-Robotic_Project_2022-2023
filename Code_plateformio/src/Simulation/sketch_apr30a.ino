#include <Servo.h>
Servo myservo;
#define servoPin 9
void setup() {
  // Start the serial communication
  myservo.attach(servoPin);
  int _pin= 2;
  Serial.begin(9600);
  delay(100);



}

void loop() {
//myservo.write(90);
  if (Serial.available()) {
    // Read the incoming data
    //int S1 = Serial.read();
    int H1 = Serial.read();
    //int K1 = Serial.read();
    // set the angle of the servo motor connected to channel 0 to 90 degrees
    
  //Serial.write("#1P",fu,"\r");
  //Serial.write("#2P500\r");
  //Serial.write("#3P500\r");

  //delay(1000); // wait for 1 second

  // set the angle of the servo motor connected to channel 0 to 0 degrees
  //Serial.write("#2P500\r");

  //delay(1000); // wait for 1 second


    // Print the received data to the serial monitor
    //Serial.print("Received value: ");
    //Serial.println(S1);
    //int hip = map(H1, 0, 180, 500, 2500);
    String command = "#2P" + String(map(H1, 0, 180, 500, 2500)) + "T100";
    Serial.write(command.c_str());
    //Serial.print("#");
    //Serial.print(14);
    //Serial.print(" P");
    //Serial.print(2500);
    //Serial.print(" T");
    //Serial.println(1000);
    delay(100);
  }
}
