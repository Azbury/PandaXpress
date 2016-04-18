/** MoveForwad
* This program tells the robot to move forward
* Later, we will add code to make it follow a straight line
* Then we will have it capable of going through multiple corrdinates
*/
#include <SoftwareSerial.h>
#include "enes100.h"

SoftwareSerial mySerial(8, 9); //RX is pin 8, TX is pin 9
enes100::RfClient<SoftwareSerial> rf(&mySerial); 
enes100::Marker marker;

int markerNumber=3; //update this with whatever black and white marker you receive
int rf_Rx = 3;
int rf_Tx = 4;
int ena = 5; //pwm
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int enb = 10; //pwm

void setup() {
  Serial.begin(9600);
  rfSetup();
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
motorStraight();
}


void motorStraight(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena,255);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb,255);
}

void rfSetup() {
  mySerial.begin(9600); //this establishes serial communication with
                      //something other than serial monitor, in this
                      //case RF communication with mission control

  pinMode(rf_Rx, INPUT); //since pin 8 is RX, it receives as an input
  pinMode(rf_Tx, OUTPUT); //since pin 9 is TX, it transmits as an output
  rf.resetServer();
  rf.sendMessage("\nTeam PandaXpress is Connected\n"); //sent to mission control
  Serial.println("Team PandaXpress is Connected"); //sent to student's serial monitor
}

void rfRead() {
    if(rf.receiveMarker(&marker, markerNumber)) {
    rf.sendMessage("\nMarker is successfully being read\n");
  }
  else
  {
    rf.sendMessage("\nMarker is not registering\n");
    Serial.println("Marker is not registering");
  }
}

