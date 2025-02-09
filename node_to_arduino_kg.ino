/*
 * This file receives a Serial value of "1" or "0" and changes the light based on
 * that value. 
 */  

// Define the port for the LED
int lightPin1 = 2;
int lightPin2 = 3;
int lightPin3 = 4;
void setup() 
{ 
  
  // Initialize the light pin
  pinMode(lightPin1, OUTPUT);
  pinMode(lightPin2, OUTPUT);
  pinMode(lightPin3, OUTPUT);
  // Initialize the Serial
  Serial.begin(9600);
  
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
    if(receivedString == "1"){
      digitalWrite(lightPin1,HIGH);
      digitalWrite(lightPin2,LOW);
      digitalWrite(lightPin3,LOW);  
    }
    else if (receivedString == "2"){
      digitalWrite(lightPin2,HIGH);
      digitalWrite(lightPin1,LOW);
      digitalWrite(lightPin3,LOW); 
    }
    else if (receivedString == "3"){
      digitalWrite(lightPin3,HIGH);
      digitalWrite(lightPin1,LOW);
      digitalWrite(lightPin2,LOW);
    }
    else{
      digitalWrite(lightPin2,LOW);
      digitalWrite(lightPin1,LOW);
      digitalWrite(lightPin3,LOW);  
    }
  }
}   
