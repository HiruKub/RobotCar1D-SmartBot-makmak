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

int blackValue = 500;
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

#define leftSpeed 140
#define rightSpeed 120

Cordinate position = { startX, startY, North };

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
  caseDefine();
  // pushBoxforOneCell();
}

void loop() {
  // // ForwardRight(200);
  // // BackwardLeft(200);

  // // Forward(150, 100);
  // if (RobotOnCross() == 1) {
  //   highBreak();
  //   delay(1000);
  //   Forward(leftSpeed, rightSpeed);
  //   delay(500);
  //   Serial.println("onCross");
  // } else {
  //   Forward(leftSpeed, rightSpeed);
  // }

  // Beepbeep(1);

  // readSensor();
  // for (int i = 0; i < 5; i++) {
  //   Serial.print(sensorValues[i]);
  //   Serial.print("\t");
  // }
  // Serial.println("");
  // delay(200);
  // if (RobotOnCross() == 1){
  //   Serial.println("onCross");
  //   Beepbeep(1);
  // }

  // ultraSonic();

  // ForwardRight(100);
  // ForwardLeft(100);
  // delay(500);

  // moveOneCell();
  // turnRight();
  // moveOneCell();
  // turnLeft();
  
  // ultraSonic();
}


// FUNCTIONABLE FUNCTIONNNNNNNN

void caseDefine() {
  switch (caseNum) {
    case 1:  // s r s s s l s s s r s s l s no box
      lowBreak();
      if (ultraSonic() > 2 && ultraSonic() < 30) {
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        turnRight();
        moveOneCell();
      } else {
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
      if (ultraSonic() > 2 && ultraSonic() < 30) {
        turnLeft();
        moveOneCell();
        turnRight();
        moveOneCell();
        lowBreak();
        Beepbeep(2);
        delay(1000);
        caseNum = 11;
        caseDefine();

      } else {
        moveOneCell();
        turnLeft();
        moveOneCell();
        lowBreak();
        Beepbeep(2);
        delay(1000);
        caseNum = 10;
        caseDefine();

      }
      break;
    case 10:  //back to start 1 no box:a s r s s s l push s s s r s s s l s
      turnAround();
      moveOneCell();
      turnRight();
      moveOneCell();
      moveOneCell();
      moveOneCell();
      turnLeft();
      pushOrangebox();
      moveOneCell();
      moveOneCell();
      moveOneCell();
      turnRight();
      moveOneCell();
      moveOneCell();
      turnLeft();
      if (ultraSonic() > 2 && ultraSonic() < 30) {
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        lowBreak();
        Beepbeep(3);
        delay(1000);
        break;
      } else {
        moveOneCell();
        turnRight();
        moveOneCell();
        lowBreak();
        Beepbeep(3);
        delay(1000);
        break;
      }
    case 11:
      turnAround();
      moveOneCell();
      turnLeft();
      moveOneCell();
      turnRight();
      moveOneCell();
      moveOneCell();
      turnLeft();
      pushOrangebox();
      moveOneCell();
      moveOneCell();
      moveOneCell();
      turnRight();
      moveOneCell();
      moveOneCell();
      turnLeft();
      if (ultraSonic() > 2 && ultraSonic() < 30) {
        turnRight();
        moveOneCell();
        turnLeft();
        moveOneCell();
        lowBreak();
        Beepbeep(3);
        delay(1000);
        break;
      } else {
        moveOneCell();
        turnRight();
        moveOneCell();
        lowBreak();
        Beepbeep(3);
        delay(1000);
        break;
      }
      break;
  }
}

void pushOrangebox() {  //s l s / r s s / r s s / r s r / s s r / s l s / l s s / l s r / s r s / r
  pushBoxforOneCell();      //push
  turnLeft();
  moveOneCell();

  turnRight();
  moveOneCell();
  moveOneCell();

  turnRight();
  moveOneCell();
  moveOneCell();

  turnRight();
  moveOneCell();
  turnRight();

  pushBoxforOneCell();  //push
  // moveOneCell();
  turnRight();

  moveOneCell();
  turnLeft();
  moveOneCell();

  turnLeft();
  pushBoxforOneCell();
  pushBoxforOneCell();

  turnLeft();
  moveOneCell();
  turnRight();

  moveOneCell();
  turnRight();
  pushBoxforOneCell();

  turnRight();
}
void pushBoxforOneCell(){
  moveOneCell();
  Forward(200, 180);
  delay(600);
  lowBreak(); 
  delay(60);
  Backward(leftSpeed, rightSpeed);
  delay(500);
  lowBreak();
  delay(60);
}
void moveOneCell() {
  // leave the current node slightly so we don't retrigger immediately
  // while (millis() - t0 < 700) {
  //   Forward(leftSpeed, rightSpeed);
  // }
  while (RobotOnCross() == 0) {
    Forward(leftSpeed, rightSpeed);
  }

  unsigned long t0 = millis();
  while (millis() - t0 < 200) {
    Forward(leftSpeed, rightSpeed);
  }
  changePosition();
  Serial.println("walking 1 cell");
  highBreak();
  delay(120);
}


int ultraSonic() {
  int distance = sonar.ping_cm();
  Serial.println(distance);
  return distance;
}

int RobotOnCross() {
  static unsigned long lastTime = 0;
  unsigned long now = millis();
  if (now - lastTime < 300) return 0;

  readSensor();
  int count = 0;
  for (int i = 0; i < 5; i++) {
    sensorBlack[i] = (sensorValues[i] > blackValue) ? 1 : 0;
    if (sensorBlack[i]){
      count++;
    } 
  }

  if (count >= 3) {
    lastTime = now;
    return 1;
  }
  return 0;
}

void Beepbeep(int Count) {
  for (int i = 0; i < Count; i++) {
    digitalWrite(speakerPin, HIGH);
    delay(400);
    digitalWrite(speakerPin, LOW);
    delay(400);
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
      weight += (i * 1000) - 2000;
    }
    sensorBlack[i] = 0;
  }
  if (weight > 0) {
    ForwardRight(SpeedR);
    ForwardLeft(SpeedL - 50);
    // Serial.println("Turn Right");
  } else if (weight < 0) {
    ForwardRight(SpeedR - 50);
    ForwardLeft(SpeedL);
    // Serial.println("Turn Left");
  } else {
    ForwardRight(SpeedR);
    ForwardLeft(SpeedL);
    // Serial.println("Go Forward");
  }
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
  Forward(150, 150);
  delay(100);
  lowBreak();
}

void turnLeft() {
  position.direction = (position.direction + 3) % 4;
  BackwardLeft(140);
  ForwardRight(120);
  delay(120);

  unsigned long t0 = millis();
  while (millis() - t0 < 800) {
    readSensor();
    if (sensorValues[2] < blackValue) break;  // go away from line
  }

  bool seenOn = false;
  t0 = millis();
  while (millis() - t0 < 1200) {
    readSensor();
    bool centerOn = (sensorValues[2] > blackValue);// find the line
    if (centerOn) {
      seenOn = true;
      break;
    }
  }
  lowBreak();
  snapToLine();
  Serial.println("TurnLeft");
}

void turnRight() {
  position.direction = (position.direction + 1) % 4;
  ForwardLeft(140);
  BackwardRight(120);
  delay(120);

  unsigned long t0 = millis();
  while (millis() - t0 < 800) {
    readSensor();
    if (sensorValues[2] < blackValue) break;  // go away from line
  }

  bool seenOn = false;
  t0 = millis();
  while (millis() - t0 < 1200) {
    readSensor();
    bool centerOn = (sensorValues[2] > blackValue); // find the line
    if (centerOn) {
      seenOn = true;
      break;
    }
  }
  lowBreak();
  snapToLine();
  Serial.println("TurnRight");
}

void turnAround() {
  position.direction = (position.direction + 2) % 4;
  ForwardLeft(180);
  BackwardRight(160);
  delay(120);
  unsigned long t0 = millis();
  while (millis() - t0 < 800) {
    readSensor();
    if (sensorValues[2] < blackValue) break;  // center off the old line
  }

  // 2) Count two center-on crossings (≈90° and ≈180°)
  int crossings = 0;
  bool prevOn = false;
  t0 = millis();
  while (millis() - t0 < 2200) {  // safety timeout
    readSensor();
    bool centerOn = (sensorValues[2] > blackValue);
    if (centerOn && !prevOn) {  // rising edge
      crossings++;
      if (crossings >= 2) {  // reached ~180°
        delay(70);           // small extra to center
        break;
      }
    }
    prevOn = centerOn;
  }

  lowBreak();
  snapToLine();  // fine-align on the corridor
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
      weight += (i * 1000) - 2000;
    }
    sensorBlack[i] = 0;
  }
  if (weight > 0) {
    BackwardRight(SpeedR);
    BackwardLeft(SpeedL - 50);
    Serial.println("Turn Right");
  } else if (weight < 0) {
    BackwardRight(SpeedR - 50);
    BackwardLeft(SpeedL);
    Serial.println("Turn Left");
  } else {
    BackwardRight(SpeedR);
    BackwardLeft(SpeedL);
    Serial.println("Go Forward");
  }
}

void changePosition() {
  if (position.direction == North) position.y++;
  else if (position.direction == South) position.y--;
  else if (position.direction == East) position.x++;
  else if (position.direction == West) position.x--;
}


void readSensor() {
  sensorValues[0] = analogRead(S1);
  sensorValues[1] = analogRead(S2);
  sensorValues[2] = analogRead(S3);
  sensorValues[3] = analogRead(S4);
  sensorValues[4] = analogRead(S5);
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

void ForwardLeft(int Speed) {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, Speed);
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
// void showGridInt(const int grid[ROWS][COLS]) {
//   for (int y = 0; y < ROWS; y++) {
//     for (int x = 0; x < COLS; x++) {
//       Serial.print(grid[y][x]);
//       Serial.print('\t');
//     }
//     Serial.println();
//   }
// }

// bool inBounds(int x, int y) {
//   return x >= 0 && x < COLS && y >= 0 && y < ROWS;
// }

// // Return true when goal reached; push dirs while unwinding
// bool dfsPlan(int x, int y) {
//   if (grid[y][x] == 3) return true;  // at goal

//   visitedDFS[y][x] = true;

//   for (int dir = 0; dir < 4; dir++) {
//     int nx = x + DX[dir];
//     int ny = y + DY[dir];

//     if (!inBounds(nx, ny)) continue;
//     if (visitedDFS[ny][nx]) continue;
//     // walkable: 1 or 3 (goal). Skip 2 (blocked) and 0 (empty).
//     int cell = grid[ny][nx];
//     if (!(cell == 1 || cell == 3)) continue;

//     if (dfsPlan(nx, ny)) {
//       planDirs[planLen++] = dir;  // record absolute direction used to go x,y -> nx,ny
//       return true;
//     }
//   }
//   return false;  // dead end
// }

// bool buildDFSPlan(int sx, int sy) {
//   for (int y = 0; y < ROWS; y++)
//     for (int x = 0; x < COLS; x++) visitedDFS[y][x] = false;
//   planLen = 0;

//   // Find goal (first '3')
//   int gx = -1, gy = -1;
//   for (int y = 0; y < ROWS; y++)
//     for (int x = 0; x < COLS; x++)
//       if (grid[y][x] == 3) {
//         gx = x;
//         gy = y;
//       }

//   if (gx == -1) {
//     Serial.println("No checkpoint (3) in grid");
//     return false;
//   }

//   // Run DFS from start; directions will be pushed in reverse
//   if (!dfsPlan(sx, sy)) {
//     Serial.println("DFS: no path");
//     return false;
//   }

//   // Reverse to make it start->goal order
//   for (int i = 0; i < planLen / 2; i++) {
//     int t = planDirs[i];
//     planDirs[i] = planDirs[planLen - 1 - i];
//     planDirs[planLen - 1 - i] = t;
//   }

//   Serial.print("DFS plan len=");
//   Serial.println(planLen);
//   Serial.print("Dirs (0=N,1=E,2=S,3=W): ");
//   for (int i = 0; i < planLen; i++) {
//     Serial.print(planDirs[i]);
//     Serial.print(' ');
//   }
//   Serial.println();
//   return true;
// }

// void executePlan() {
//   for (int i = 0; i < planLen; i++) {
//     int desired = planDirs[i];                          // absolute dir for next step
//     int diff = (desired - position.direction + 4) % 4;  // 0=fwd,1=right,2=U,3=left
//     if (diff == 1) turnRight();
//     else if (diff == 3) turnLeft();
//     else if (diff == 2) turnAround();

//     moveOneCell();
//   }
//   Serial.println("Yippee");
//   lowBreak();
// }
