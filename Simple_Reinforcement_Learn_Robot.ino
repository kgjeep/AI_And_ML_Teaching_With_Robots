#include <Servo.h>

Servo servo1,servo2;

#ifdef __arm__

extern "C" char* sbrk(int incr);

#else // __ARM__

extern char *__brkval;

#endif // __arm__

int freeMemory() { // this routine reports on free ram space

char top;

#ifdef __arm__

return &top - reinterpret_cast(sbrk(0));

#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)

return &top - __brkval;

#else // __arm__

return __brkval ? &top - __brkval : &top - __malloc_heap_start;

#endif // __arm__

}

float distance;

float sonarTime;

int TRIGGER=7,ECHO=8; // sonar pins

//int state=0;

//int numberSuccesses = 0;

int episodes = 0;

int spos1 = 0; // servo1 position

int spos2 = 0; // servo2 position

int spos3 = 0; // servo1 position

int spos4 =0; // servo2 position

int spos1High =0; // servo1 highest position

int spos2High =0;

int spos3High =0;

int spos4High =0;

float distanceHigh=2.,distanceHigh1=2.; 

float distDifference=0,distPrevious=0,distCurrent=0;

/////  setup  /////////////////////

void setup (){

randomSeed(analogRead(0));
Serial.begin(9600);

servo1.attach( 9, 600, 2400 );
servo2.attach( 6, 600, 2400 );


myServo(servo1,180,1,8,1); // set servos to zero position  

delay(1000);

myServo(servo2,180,1,8,1);

delay(1000);

pinMode(TRIGGER, OUTPUT); // setup sonar

pinMode(ECHO, INPUT);


distPrevious = getDistance(); //get initial distance

Serial.println(distPrevious);

delay(1000);



} 
//////  getDistance  ///////////////

float getDistance() { // routine to measure distance = call and average it 5 times

int numberTriggers = 5;

int average = 0;

for(int i=0;i<=numberTriggers; i++){

digitalWrite(TRIGGER, LOW);

delayMicroseconds(5);

digitalWrite(TRIGGER, HIGH);

delayMicroseconds(10);

digitalWrite(TRIGGER, LOW);

sonarTime = pulseIn(ECHO, HIGH);

distance = sonarTime / 58.00;

average = average + distance;

// Serial.print(sonarTime);Serial.print(" ");Serial.print(distance);Serial.println("cm");

delay(100);

} // end for i

average = average / numberTriggers;

Serial.println(average);

return average;

}// end get ultrasonic distance routine


///////  doTraining  ///////////////
void doTraining() {

Serial.println("Do doTraining...");

episodes = 40;

for (int episode=0;episode<=episodes; episode++)

{
spos1 = random(50,120);
spos2 = random(5,140);
spos3 = random(50,120);
spos4 = random(5,140);

myServo(servo1,spos1,1,7,1); //(Servo servo,int newAngle,int angleInc,int incDelay,int servoNum)

myServo(servo2,spos2,1,7,1);

myServo(servo1,spos3,1,7,1);

myServo(servo2,spos4,1,7,1);

distCurrent = getDistance(); // get distance - note this is not always accurate so sometimes robot will just claw the air

distDifference = distCurrent - distPrevious;

distPrevious = distCurrent;

Serial.print(" episode = ");Serial.print(episode);

// Serial.print(" state = ");Serial.print(state);

Serial.print(" spos1 = ");Serial.print(spos1);

Serial.print(" spos2 = ");Serial.print(spos2);

Serial.print(" spos3 = ");Serial.print(spos3);

Serial.print(" spos4 = ");Serial.print(spos4);

Serial.print(" distance Difference = ");Serial.println(distDifference);

if ( distDifference > distanceHigh) { // if current distancee is greater than highest then replace postions

spos1High = spos1; // servo position 1

spos2High = spos2; // servo position 2

spos3High = spos3; // servo position 3

spos4High = spos4; // servo position 4

distanceHigh = distDifference;

// distPrevious = distCurrent;

}
else if ( distanceHigh <= distanceHigh1 and episode >= 40)
{
  episode =0;
  Serial.print("New episodes distancsHigh = ");Serial.println(distanceHigh);

  Serial.println(" ");
}
} // end each episode

Serial.print("spos1High = ");Serial.println(spos1High);

Serial.println(" ");

} // end doTraining

/////// doLearnedBehavior ///////////
void doLearnedBehavior() {

Serial.println("Do Learned behavior... ");

myServo(servo1,180,1,8,1);

myServo(servo2,180,1,8,1);

delay(2000);

for (int i=0;i<10;i++) { //Ten repeats of the learned behavior

Serial.print(" spos1High= "); Serial.print(spos1High);

Serial.print(" spos2High = ");Serial.print(spos2High);

Serial.print(" spos3High = ");Serial.print(spos3High);

Serial.print(" spos4High = ");Serial.println(spos4High);

myServo(servo1,spos1High,1,7,1);

myServo(servo2,spos2High,1,7,1);

myServo(servo1,spos3High,1,7,1);

myServo(servo2,spos4High,1,7,1);

} 

} 

/////////  void loop  /////

void loop(){ 

int freespace = freeMemory(); Serial.print("free memory= "); Serial.println(freespace);

doTraining(); 

//freespace = freeMemory(); Serial.print("free memory= "); Serial.println(freespace);

doLearnedBehavior(); 

myServo(servo1,90,1,8,1);

myServo(servo2,90,1,8,1);

Serial.print("end program ");

delay(2000);

exit(0); // quit program

} // end main loop


///////  myServo  ////////////////////////////////////////////////////////////////////////////////////////////

void myServo(Servo servo,int newAngle,int angleInc,int incDelay,int servoNum) {

int curAngle = 0;

curAngle = servo.read();

if (curAngle < newAngle) {

for(int angle=curAngle;angle < newAngle;angle += angleInc) {

servo.write(angle);

delay(incDelay); }

}

else if (curAngle > newAngle) {

for(int angle=curAngle;angle > newAngle;angle -= angleInc) {

servo.write(angle);

delay(incDelay); }

}

} 
