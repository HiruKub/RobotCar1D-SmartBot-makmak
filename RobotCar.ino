#define echo 12
#define trig 13

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

int sensorValues[5];
int sensorBlack[5] = {0,0,0,0,0};

#define startX 0
#define startY 5

int duration, distance;

int grid[6][6] = {// 0 = CrossLines, 1 = paths, 2 = blackBoxs , 3 = Checkpoint , R = Robot
  {0,0,0,0,0,3}, 
  {0,0,0,0,0,0},
  {0,2,0,0,0,0},
  {0,0,0,0,2,0},
  {0,0,0,0,0,0}, 
  {'R',0,0,0,0,0},
};

bool onCross = true;

struct Cordinate {
  int xNow;
  int yNow;
  int direction;
};

#define leftSpeed 180
#define rightSpeed 160

Cordinate position = {startX,startY,North};

void setup() {
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
  pinMode(echo, INPUT); //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT); //สั่งให้ขา trig ใช้งานเป็น output
  Serial.begin(9600);

}

void loop() {
  // // ForwardRight(200);
  // // BackwardLeft(200);

  readSensor();
  for(int i = 0; i < 5 ;i++){
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println("");
  // delay(200);

  // Forward(150, 100);
  if(RobotOnCross() == 1){
    highBreak();
    delay(1000);
    Forward(leftSpeed, rightSpeed);
    delay(500);
    Serial.println("onCross");
  }
  else
  {
    Forward(leftSpeed,rightSpeed);
  }


}

// FUNCTIONABLE FUNCTION
void ultraSonic(){
  digitalWrite(trig, LOW); 
  delayMicroseconds(5); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(5); 
  digitalWrite(trig, LOW); //ใช้งานขา trig
  
  duration = pulseIn(echo, HIGH); //อ่านค่าของ echo เป็น microseconds แล้วนำมาหารให้เป็น centimeters
  distance = duration / 48.25; //คำนวณหาค่า centimeters
  Serial.print(distance); //แสดงค่าระยะเป็น centimeters
  Serial.print(" cm\n");
}

int RobotOnCross(){
  static unsigned long lastTime = 0;
  unsigned long now = millis();
  if (now - lastTime < 300) return 0; //FIX THIS

  readSensor();
  int count = 0;
  for(int i = 0 ; i < 5 ;i++){
    if(sensorValues[i] > blackValue)
    {
      sensorBlack[i] = 1;
    }
    else {
      sensorBlack[i] = 0;
    }
    if(sensorBlack[i] == 1)
    {
      count++;
    }
  }
  if(count >= 3){
    return 1;
  }
  else return 0;
}



void Forward(int SpeedL , int SpeedR){
  readSensor();
  Serial.println("This worked naja");
  int weight = 0;
  for (int i=0;i<5;i++) {
    sensorBlack[i] = (sensorValues[i] > blackValue) ? 1 : 0;
  }
  for(int i = 0; i < 5 ; i++)
  {
    if(sensorBlack[i] > 0)
    {
      weight += (i * 1000) - 2000;
    }
    sensorBlack[i] = 0;
  }
  if (weight > 0){
    ForwardRight(SpeedR);
    ForwardLeft(SpeedL - 50);
    Serial.println("Turn Right");
  }
  else if(weight < 0){
    ForwardRight(SpeedR - 50);
    ForwardLeft(SpeedL);
    Serial.println("Turn Left");
  }
  else{
    ForwardRight(SpeedR);
    ForwardLeft(SpeedL);
    Serial.println("Go Forward");
  }
}

void snapToLine() { //ใส่หลังจาก Turn
  unsigned long t0 = millis();
  while (millis() - t0 < 500) {
    readSensor();
    int b0 = (sensorValues[0] > blackValue);
    int b1 = (sensorValues[1] > blackValue);
    int b2 = (sensorValues[2] > blackValue);
    int b3 = (sensorValues[3] > blackValue);
    int b4 = (sensorValues[4] > blackValue);
    if (b2 && (b1 == b3)) break;
    Forward(110,110);
  }
  Forward(120,120);
  delay(100);
  lowBreak();
}

void turnLeft()  
{ 
  position.direction = (position.direction + 3) % 4;
  BackwardLeft(150);
  ForwardRight(130);
  delay(300);
}

void turnRight() 
{ 
  position.direction = (position.direction + 1) % 4; 
  ForwardLeft(150);
  BackwardRight(130);  
  delay(300);
}

void turnAround()
{ 
  position.direction = (position.direction + 2) % 4; 
  ForwardLeft(150);
  BackwardRight(130);  
  delay(600);
}

void changePosition() {
  if (position.direction == North) position.yNow++;
  else if (position.direction == South) position.yNow--;
  else if (position.direction == East)  position.xNow++;
  else if (position.direction == West)  position.xNow--;
}

void Backward(int SpeedL , int SpeedR){
  BackwardLeft(SpeedL);
  BackwardRight(SpeedR);
}
void readSensor()
{
  sensorValues[0] = analogRead(S1);
  sensorValues[1] = analogRead(S2);
  sensorValues[2] = analogRead(S3);
  sensorValues[3] = analogRead(S4);
  sensorValues[4] = analogRead(S5);
}

void ForwardRight(int Speed){
  //motor 1
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, Speed);
}

void BackwardRight(int Speed){
  //motor 1
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, Speed);
}

void BackwardLeft(int Speed){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, Speed);
}

void ForwardLeft(int Speed){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, Speed);
}

void lowBreak()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void highBreak()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

