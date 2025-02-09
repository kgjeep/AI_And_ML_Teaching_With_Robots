// Programma gia na elegxei to braxiona me efarmogh toy teachable machine
#include <Servo.h>
Servo gripper;
Servo LiftServo;
Servo Base;
int k1 = 80, k2 = 120, k3 = 90;  // Αρχικοποίηση των τιμών των σερβοκινητήρων

void setup() 
{ 
 Serial.begin(9600);
  gripper.attach(11);
  LiftServo.attach(10);
  Base.attach(9);
  gripper.write(k1);
  delay(1000);
  LiftServo.write(k2);
  delay(1000);
  Base.write(k3);
  delay(1000);
    
}

void loop() {
  // CHeck to see if Serial data is being received
  if (Serial.available() > 0) {
    
    // Create a new string variable to receive Serial data
    String receivedString = "";
    
    // Loop through received data and append to the receivedString variable
    while (Serial.available() > 0) {
      receivedString += char(Serial.read ());
    }
    
    // Print received Serial data
    Serial.println(receivedString);
    
    // Change LED status based on received data
    if(receivedString == "1"){// go to center
    gripper.write(k1);
    delay(500);
    LiftServo.write(k2);
    delay(500);
    Base.write(k3);
    delay(500);
    }
    else if (receivedString == "2"){// Move to the LEFT because the person oposite is looking to the RIGHT
     Base.write(180);
     delay(500); 
     LiftServo.write(10);
     delay(500);
     gripper.write(20);
     delay(500);
    }
    else if (receivedString == "3"){//Move to the RIGHT because the person oposite is looking to the LEFT
     Base.write(0);
     delay(500); 
     LiftServo.write(10);
     delay(500);
     gripper.write(20);
     delay(500);
    }
    else{
     delay(2);
    }
  }
} 
