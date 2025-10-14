#include <NewPing.h>

#define MAX_DISTANCE 200
#define echo 12
#define trig 13
NewPing sonar(trig, echo, MAX_DISTANCE);

#define speakerPin 3

#define enA 5
#define in1 8
#define in2 9
#define enB 6
#define in3 10
#define in4 11

#define S1 A4
#define S2 A3
#define S3 A2
#define S4 A1
#define S5 A0

int blackValue = 700;
#define North 0
#define East 1
#define South 2
#define West 3

#define ROWS 6
#define COLS 6

int sensorValues[5];
int sensorBlack[5] = { 0, 0, 0, 0, 0 };

#define startX 0
#define startY 5

int duration, distance;

int grid[ROWS][COLS] = {
  // 0 = CrossLines, 1 = start, 2 = blackBoxs , 3 = Checkpoint , R = Robot, 4 = Orange Box
  { 0, 0, 0, 0, 0, 3 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 2, 4, 0, 0, 0 },
  { 0, 0, 0, 0, 2, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0 },
};

bool onCross = true;

struct Cordinate {
  int x;
  int y;
  int direction;
};

#define leftSpeed 160
#define rightSpeed 160
#define turnSpeed 140

bool haveBeenBlack = false;

Cordinate position = { startX, startY, North };
unsigned long watermelonTime = millis();

// const int DX[4] = { 0, 1, 0, -1 };
// const int DY[4] = { 1, 0, -1, 0 };
// bool visitedDFS[ROWS][COLS];
// int planDirs[ROWS * COLS];  // absolute dir per step (0..3)
// int planLen = 0;
int caseNum = 1;


void setup() {
  lowBreak();
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(echo, INPUT);   //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT);  //สั่งให้ขา trig ใช้งานเป็น output
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
  caseNum = 1;
  // delay(500);
  caseDefine();
}

void loop() {
  // moveOneCell();
  // turnLeft();


  // readSensor();
  // for (int i = 0; i < 5; i++) {
  //   Serial.print(sensorValues[i]);
  //   Serial.print("\t");
  // }
  // if (RobotOnCross() == 1){
  //   Serial.println("onCross");
  //   Beepbeep(1);
  // }
  // Serial.println("");
  // delay(200);
  
}

void caseDefine() {
  switch (caseNum) {
    case 1:  // s r s s s l s s s r s s l s no box
      lowBreak();
      delay(500);
      if (ultraSonic() > 2 && ultraSonic() < 25) {
        Beepbeep(1);
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        turnRight();
      } else {
        Beepbeep(1);
        moveOneCell();
        turnRight();
        moveOneCell();
      }
      moveOneCell();
      moveOneCell();
      turnLeft();
      moveOneCell();
      moveOneCell();
      moveOneCell();
      turnRight();
      moveOneCell();
      if (ultraSonic() > 2 && ultraSonic() < 25) {
        delay(500);
        turnLeft();
        moveOneCell();
        turnRight();
        moveOneCell();
        lowBreak();
        Beepbeep(2);
        delay(1000);
        //caseNum = 11;
        // caseNum = 3;
        caseNum = 5;
        caseDefine();

      } else {
        delay(500);
        moveOneCell();
        turnLeft();
        moveOneCell();
        lowBreak();
        Beepbeep(2);
        delay(1000);
        //caseNum = 10;
        // caseNum = 2;
        caseNum = 6;
        caseDefine();
      }
      break;

      case 5:
        turnAround();
        moveOneCell();
        turnLeft();
        moveOneCell();
        moveOneCell();
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        moveOneCell();
        turnRight();
        moveOneCell();
        moveOneCell();
      if (ultraSonic() > 2 && ultraSonic() < 25) {
        delay(500);
        turnLeft();
        moveOneCell();
        turnRight();
        moveOneCell();
        Beepbeep(3);
      }else {
        delay(500);
        moveOneCell();
        turnLeft();
        moveOneCell();
        Beepbeep(3);
      }
      break;

      case 6:
        turnAround();
        moveOneCell();
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        moveOneCell();
        turnRight();
        moveOneCell();
        moveOneCell();
        if (ultraSonic() > 2 && ultraSonic() < 25) {
        delay(500);
        turnLeft();
        moveOneCell();
        turnRight();
        moveOneCell();
        Beepbeep(3);
      }else {
        delay(500);
        moveOneCell();
        turnLeft();
        moveOneCell();
        Beepbeep(3);
      }
      break;




    // case 2:  // a s r s s l s s s r s s (if found l s r s) (else s l s) not found box
    //   turnAround();
    //   moveOneCell();
    //   turnRight();
    //   moveOneCell();
    //   moveOneCell();
    //   turnLeft();
    //   moveOneCell();
    //   moveOneCell();
    //   moveOneCell();
    //   turnRight();
    //   moveOneCell();
    //   moveOneCell();

    //   // Now check if something (box) is detected by ultrasonic
    //   if (ultraSonic() > 2 && ultraSonic() < 25) {
    //     // if found box → l s r s
    //     turnLeft();
    //     moveOneCell();
    //     turnRight();
    //     moveOneCell();
    //   } else {
    //     // else → s l s
    //     moveOneCell();
    //     turnLeft();
    //     moveOneCell();
    //   }

    //   lowBreak();
    //   delay(60);
    //   Beepbeep(3);
    //   delay(1000);
    //   break;

    // case 3://found box at check point
    // case 3:           //found box at check point
    //   turnAround();   // a
    //   moveOneCell();  // s
    //   turnLeft();     // l
    //   moveOneCell();  // s
    //   turnRight();    // r
    //   moveOneCell();  // s
    //   turnLeft();     // l
    //   moveOneCell();  // s
    //   moveOneCell();  // s
    //   moveOneCell();  // s
    //   turnRight();    // r
    //   moveOneCell();  // s
    //   moveOneCell();  // s

    //   // 🔍 Check for box using ultrasonic
    //   if (ultraSonic() > 2 && ultraSonic() < 25) {
    //     // Box found → l s r s
    //     turnLeft();
    //     moveOneCell();
    //     turnRight();
    //     moveOneCell();
    //     Serial.println("Box detected - performed l s r s");
    //   } else {
    //     // No box → s l s
    //     moveOneCell();
    //     turnLeft();
    //     moveOneCell();
    //     Serial.println("No box - performed s l s");
    //   }

    //   lowBreak();
    //   delay(100);
    //   Beepbeep(3);
    //   delay(1000);
    //   break;
    // case 10:  //back to start 1 no box:a s r s s s l push s s s r s s s l s
    //   turnAround();
    //   moveOneCell();
    //   turnRight();
    //   moveOneCell();
    //   moveOneCell();
    //   moveOneCell();
    //   turnLeft();
    //   pushOrangebox();
    //   moveOneCell();
    //   moveOneCell();
    //   moveOneCell();
    //   turnRight();
    //   moveOneCell();
    //   moveOneCell();
    //   turnLeft();
    //   if (ultraSonic() > 2 && ultraSonic() < 25) {
    //     turnRight();
    //     moveOneCell();
    //     turnLeft();
    //     moveOneCell();
    //     lowBreak();
    //     delay(60);
    //     Beepbeep(3);
    //     delay(1000);
    //   } else {
    //     moveOneCell();
    //     turnRight();
    //     moveOneCell();
    //     lowBreak();
    //     delay(60);
    //     Beepbeep(3);
    //     delay(1000);
    //   }
    //   break;
    // case 11:
    //   turnAround();
    //   moveOneCell();
    //   turnLeft();
    //   moveOneCell();
    //   turnRight();
    //   moveOneCell();
    //   moveOneCell();
    //   turnLeft();
    //   pushOrangebox();
    //   moveOneCell();
    //   moveOneCell();
    //   moveOneCell();
    //   turnRight();
    //   moveOneCell();
    //   moveOneCell();
    //   turnLeft();
    //   if (ultraSonic() > 2 && ultraSonic() < 25) {
    //     turnRight();
    //     moveOneCell();
    //     turnLeft();
    //     moveOneCell();
    //     lowBreak();
    //     Beepbeep(3);
    //     delay(1000);
    //     break;
    //   } else {
    //     moveOneCell();
    //     turnRight();
    //     moveOneCell();
    //     lowBreak();
    //     Beepbeep(3);
    //     delay(1000);
    //     break;
    //   }
    //   break;
  }
}

void Forward(int SpeedL, int SpeedR) {
  readSensor();
  Serial.println("This worked naja");
  int weight = 0;
  for (int i = 0; i < 5; i++) {
    sensorBlack[i] = (sensorValues[i] > blackValue) ? 1 : 0;
  }
  for (int i = 0; i < 5; i++) {
    if (sensorBlack[i] > 0) {
      weight += (i * 10) - 20;
    }
    sensorBlack[i] = 0;
  }
  if (weight > 0) {
    // ForwardRight(SpeedR - (abs(weight) * 2.2));
    ForwardRight(SpeedR - 50);
    ForwardLeft(SpeedL);
    Serial.println("Turn Right");
  } else if (weight < 0) {
    ForwardRight(SpeedR);
    // ForwardLeft(SpeedL - (abs(weight) * 2.2));
    ForwardLeft(SpeedL - 50);
    Serial.println("Turn Left");
  } else {
    ForwardRight(SpeedR);
    ForwardLeft(SpeedL);
    Serial.println("Go Forward");
  }
}

int RobotOnCross() {
  readSensor();
  // delay(100);
  int count = 0;
  for (int i = 0; i < 5; i++) {
    sensorBlack[i] = (sensorValues[i] > blackValue) ? 1 : 0;
    if (sensorBlack[i]) {
      count++;
    }
  }

  if (count > 3) {
    if (haveBeenBlack == true) {
      // haveBeenBlack = false;watermelonTie = millis();
      return 0;
    } else {
      watermelonTime = millis();
      haveBeenBlack = true;
      return 1;
    }
  }
  watermelonTime = millis();
  haveBeenBlack = false;
  return 0;
}

void moveOneCell() {
  // leave the current node slightly so we don't retrigger immediately
  // while (millis() - t0 < 700) {
  //   Forward(leftSpeed, rightSpeed);
  // }


  while (RobotOnCross() == 0) {
    Forward(leftSpeed, rightSpeed);
  }

  Forward(leftSpeed, rightSpeed);
  delay(400);
  //changePosition();
  lowBreak();
  delay(500);
  //Beepbeep(1);
  Serial.println("walking 1 cell");
  // delay(120);
}

// void changePosition() {
//   if (position.direction == North) position.y++;
//   else if (position.direction == South) position.y--;
//   else if (position.direction == East) position.x++;
//   else if (position.direction == West) position.x--;
// }

void readSensor() {
  sensorValues[0] = analogRead(S1);
  sensorValues[1] = analogRead(S2);
  sensorValues[2] = analogRead(S3);
  sensorValues[3] = analogRead(S4);
  sensorValues[4] = analogRead(S5);
}

int ultraSonic() {
  int distance = sonar.ping_cm();
  Serial.println(distance);
  return distance;
}

void Beepbeep(int Count) {
  lowBreak();
  for (int i = 0; i < Count; i++) {
    digitalWrite(speakerPin, HIGH);
    delay(400);
    digitalWrite(speakerPin, LOW);
    delay(400);
  }
}

void turnRight() {
  //position.direction = (position.direction + 1) % 4;
  ForwardLeft(turnSpeed);
  BackwardRight(turnSpeed);
  delay(360);

  while (true) {
    readSensor();
    if (sensorValues[2] > blackValue) break;
  }
  lowBreak();
  // snapToLine();
  Serial.println("TurnRight");
}

void turnLeft() {
  //position.direction = (position.direction + 3) % 4;
  BackwardLeft(turnSpeed);
  ForwardRight(turnSpeed);
  delay(400);

  while (true) {
    readSensor();
    if (sensorValues[2] > blackValue) break;
  }

  // snapToLine();
  lowBreak();
  delay(250);
  Serial.println("TurnLeft");
}

void snapToLine() {  //ใส่หลังจาก Turn
  unsigned long t0 = millis();
  while (millis() - t0 < 500) {
    readSensor();
    int b0 = (sensorValues[0] > blackValue);
    int b1 = (sensorValues[1] > blackValue);
    int b2 = (sensorValues[2] > blackValue);
    int b3 = (sensorValues[3] > blackValue);
    int b4 = (sensorValues[4] > blackValue);
    if (b2 && (b1 == b3)) break;
    Forward(140, 140);
  }
  Forward(leftSpeed, rightSpeed);
  delay(100);
  lowBreak();
}

void lowBreak() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void highBreak() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void Backward(int SpeedL, int SpeedR) {
  readSensor();
  Serial.println("This worked naja");
  int weight = 0;
  for (int i = 0; i < 5; i++) {
    sensorBlack[i] = (sensorValues[i] > blackValue) ? 1 : 0;
  }
  for (int i = 0; i < 5; i++) {
    if (sensorBlack[i] > 0) {
      weight += (i * 10) - 20;
    }
    sensorBlack[i] = 0;
  }
  if (weight > 0) {
    BackwardRight(SpeedR);
    BackwardLeft(SpeedL - (abs(weight * 2.2)));
    //BackwardLeft(SpeedL - 50);
    // Serial.println("Turn Right");
  } else if (weight < 0) {
    BackwardRight(SpeedR - (abs(weight * 2.2)));
    //BackwardRight(SpeedR - 50);
    BackwardLeft(SpeedL);
    // Serial.println("Turn Left");
  } else {
    BackwardRight(SpeedR);
    BackwardLeft(SpeedL);
    // Serial.println("Go Forward");
  }
}

void ForwardLeft(int Speed) {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, Speed);
}

void ForwardRight(int Speed) {
  //motor 1
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, Speed);
}

void BackwardRight(int Speed) {
  //motor 1
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, Speed);
}

void BackwardLeft(int Speed) {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, Speed);
}

void turnAround() {
  position.direction = (position.direction + 2) % 4;
  ForwardLeft(turnSpeed);
  BackwardRight(turnSpeed);
  delay(400);

  while (true) {
    readSensor();
    if (sensorValues[2] > blackValue) break;
  }

  delay(400);

  while (true) {
    readSensor();
    if (sensorValues[2] > blackValue) break;
  }
  highBreak();
}