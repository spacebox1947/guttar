/***********************************************************************
 ************************************
 * GUTTAR :: An algorithmic piece of junk
 * //
 * Composed by Andrew Israelsen
 ************************************
 ************************************************************************/
//
//analog list
int piezoPin[] = {
  3, 5, 6, 9, 10, 11};
//pinTone list
int pinTones[6];
//Analog Read various Sensors
int analRead[6];
int analScl128[6];
int analScl256[6];
int analScl1024[6];
int analScl2048[6];
int analScl8192[6];
int analScl16384[6];
//
//timers and constants and rand oh my!
//
const int timeConst = 30; //min add for cloudRand
const int timeConst2 = 10000; //cloudWait delay long
const int timeConst3 = 10; //min add for pinTone1 + pinTone2
const int timeConst4 = 2500; //cloudWait delay short, pinTone1 + pinTone2 timer constant
const int timeConst5 = 1250;
//
//random ints
//
int getRandPin = 0;
int randPinEvents = 0;
//
//read ints
//
int getReadShort = 0;
int getReadLong = 0;
//
//timer ints for delays (various)
//
int totalWait = 0;
int timeCloud = 0;
int toneGen = 0;
//
//other constants for FOR and aWrite
const int f = 255; //aWrite on
const int e = 0; //aWrite off
int x = 0; //var for random pin selectors
int y = 0; //var when calling two separate random pins in same function
//
//
/***********************************************************************
 ************************************
 * SETUP
 ************************************
 ************************************************************************/
void setup() {
  randomSeed(analogRead(6));
  Serial.begin(57600);
  for (int i = 0; i<5; i++) {
    pinMode(piezoPin[i], OUTPUT);
    Serial.print("Pin Assigned: ");
    Serial.println(i);
  }
}


/***********************************************************************
 ************************************
 * MAIN LOOP
 ************************************
 ************************************************************************/
void loop() {
  //Get analog values and write them to variables
  analogReader();
  //pick sound generating function
  int selector = random(1, 100);
  //Serial.println(selector);
  if (selector >= 1 && selector < 20) {
    cloudRand();
  }
  else if (selector >=20 && selector < 36 ) {
    pinTone1();
  }
  else if (selector >= 36 && selector < 52) {
    pinTone2();
  }
  else if (selector >= 52 && selector < 68) {
    pinTone3();//melody 1
  }
  else if (selector >= 68 && selector < 84) {
    pinTone4();
  }
  else {
    pinTone5();//melody 2 long
  }
  //pick delay length
  int selector2 = random(2);
  //Serial.println(selector2);
  if (selector2 = 0) {
    cloudWait1();
  }
  else {
    cloudWait2();
  }
}


//Get analog values of PhotoSensors and Scale them to varios 2^X values
void analogReader(){
  for (int i = 0; i<5; i++) {
    analRead[i] = analogRead(i);
  }
  //map sensor values for analSclShort and analSclPwm and analSclLong
  for (int i = 0; i<5; i++) {
    analScl128[i] = map(analRead[i], 0, 1023, 0, 127);
    analScl256[i] = map(analRead[i], 0, 1023, 0, 255);
    analScl1024[i] = analRead[i];
    analScl2048[i] = map(analRead[i], 0, 1023, 0, 2047);
    analScl8192[i] = map(analRead[i], 0, 1023, 0, 8191);
    analScl16384[i] = map(analRead[i], 0, 1023, 0, 16383);
  }
}


//CloudWait Timer (long)
void cloudWait1() {
  //get delay length
  x = random(5);
  getReadLong = analScl16384[x];
  getReadLong = getReadLong - 5000;
  totalWait = getReadLong + timeConst2;
  totalWait = totalWait * 2;
  //Serial.println(totalWait);
  delay(totalWait);
}

//cloudWait timer 2 (short)
void cloudWait2() {
  //get delay length
  x = random(5);
  getReadLong = analScl2048[x];
  getReadLong = getReadLong - 2500;
  totalWait = getReadLong + timeConst4;
  totalWait = totalWait * 2;
  //Serial.println(totalWait);
  delay(totalWait);
}

//Random Drip Cloud
void cloudRand() {
  //get delay legnth
  x = random(5);
  getReadShort = analScl128[x];
  timeCloud = getReadShort + timeConst;
  //Serial.print("Cloud Delay: ");
  //Serial.println(timeCloud);
  //generate number of random on/off events
  randPinEvents = random(0, 25);
  //step through random pins over randPinEvents
  for (int i = 0; i < randPinEvents; i++) {
    //pick a random pin
    x = random(5);
    //Serial.print("Selected Pin : ");
    //Serial.println(piezoPin[x]);
    analogWrite(piezoPin[x], f);
    analogWrite(piezoPin[x], e);
    delay(timeCloud);
  }
}

void pinTone1() {
  //assign variable delays to pinTones
  for (int i = 0; i < 6; i++) {
    //assign delayMicro values to pinTones[]
    x = random(5);
    toneGen = analScl256[x];
    toneGen = toneGen + timeConst3;
    pinTones[i] = toneGen;
    //Serial.println(pinTones[i]);
  }
  //get random number of events
  randPinEvents = random(1, 15);
  //step through 6 pins with pinTones values
  for (int p = 0; p < randPinEvents; p++) {
    //generate for loop length
    x = random(5);
    getReadLong = analScl8192[x];
    getReadLong = getReadLong - 2500;
    totalWait = getReadLong + timeConst4;
    if (totalWait < 0) {
      totalWait = timeConst4;
    }
    for (int i = 0; i < totalWait; i ++) {
      x = random(0, 5);
      //Serial.println("Random pin selected :: ");
      //Serial.println(x);
      analogWrite(piezoPin[x], f);
      delayMicroseconds(pinTones[p]);
      analogWrite(piezoPin[x], e);
      delayMicroseconds(pinTones[p]);
    }
  }
}

void pinTone2() {
  //assign variable delays to pinTones
  for (int i = 0; i < 6; i++) {
    x = random(5);
    toneGen = analScl128[x];
    toneGen = toneGen + timeConst3;
    pinTones[i] = toneGen;
    //Serial.println(pinTones[i]);
  }
  //step through 6 pins with pinTones values
  for (int p = 0; p < 6; p++) {
    //get for loop length
    x = random(5);
    getReadLong = analScl2048[x];
    getReadLong = getReadLong - 2500;
    totalWait = getReadLong + timeConst4;
    //
    for (int i = 0; i < totalWait; i ++) {
      x = random(0, 5);
      analogWrite(piezoPin[x], f);
      delayMicroseconds(pinTones[p]);
      analogWrite(piezoPin[x], e);
      delayMicroseconds(pinTones[p]);
    }
  }
}

void pinTone3() {
  //assign variable delays to pinTones
  for (int i = 0; i < 6; i++) {
    //assign delayMicro values to pinTones[]
    x = random(5);
    y = random(5);
    if (x == y) {
      if (y == 0) {
        y = y + 1;
      }
      else {
        y = y - 1;
      }
    }
    toneGen = analScl128[x] + analScl256[y];
    toneGen = toneGen + timeConst3;
    pinTones[i] = toneGen;
    //Serial.println(pinTones[i]);
  }
  //get random number of events
  randPinEvents = random(1, 8);
  //step through 6 pins with pinTones values
  for (int p = 0; p < randPinEvents; p++) {
    //generate for loop length
    x = random(5);
    getReadLong = analScl16384[x];
    getReadLong = getReadLong - 5000;
    totalWait = getReadLong + timeConst2;
    for (int i = 0; i < totalWait; i ++) {
      //Serial.println("Random pin selected :: ");
      //Serial.println(x);
      analogWrite(piezoPin[p], f);
      delayMicroseconds(pinTones[p]);
      analogWrite(piezoPin[p], e);
      delayMicroseconds(pinTones[p]);
    }
  }
}

void pinTone4() {
  //assign variable delays to pinTones
  for (int i = 0; i < 6; i++) {
    //assign delayMicro values to pinTones[]
    x = random(5);
    y = random(5);
    if (x == y) {
      if (y == 0) {
        y = y + 1;
      }
      else {
        y = y - 1;
      }
    }
    toneGen = analScl1024[x] - analScl256[y];
    if (toneGen < 0) {
      toneGen = toneGen * -1;
    }
    toneGen = toneGen + timeConst3;
    pinTones[i] = toneGen;
    //Serial.println(pinTones[i]);
  }
  //get random number of events
  randPinEvents = random(1, 20);
  //step through 6 pins with pinTones values
  for (int p = 0; p < randPinEvents; p++) {
    //generate for loop length
    x = random(5);
    y = random(5);
    if (x == y) {
      if (y == 0) {
        y = y + 1;
      }
      else {
        y = y - 1;
      }
    }
    getReadLong = analScl1024[x] + analScl256[y];
    getReadLong = getReadLong - 2500;
    totalWait = getReadLong + timeConst5;
    for (int i = 0; i < totalWait; i ++) {
      x = random(0, 5);
      //Serial.println("Random pin selected :: ");
      //Serial.println(x);
      analogWrite(piezoPin[x], f);
      delayMicroseconds(pinTones[p]);
      analogWrite(piezoPin[x], e);
      delayMicroseconds(pinTones[p]);
    }
  }
}

void pinTone5() {
  //assign variable delays to pinTones
  for (int i = 0; i < 6; i++) {
    x = random(5);
    toneGen = analScl128[x];
    toneGen = toneGen + timeConst3;
    pinTones[i] = toneGen;
    //Serial.println(pinTones[i]);
  }
  //step through 6 pins with pinTones values
  for (int p = 0; p < 6; p++) {
    //get for loop length
    x = random(5);
    getReadLong = analScl8192[x];
    getReadLong = getReadLong - 2500;
    totalWait = getReadLong + timeConst4;
    //
    for (int i = 0; i < totalWait; i ++) {
      x = random(0, 5);
      analogWrite(piezoPin[x], f);
      delayMicroseconds(pinTones[p]);
      analogWrite(piezoPin[x], e);
      delayMicroseconds(pinTones[p]);
    }
  }
  for (int p = 0; p < 6; p++) {
    //get for loop length
    getReadLong = random(7500);
    getReadLong = getReadLong - 2500;
    totalWait = getReadLong + timeConst4;
    //
    for (int i = 0; i < totalWait; i ++) {
      x = random(0, 5);
      analogWrite(piezoPin[x], f);
      delayMicroseconds(pinTones[p]);
      analogWrite(piezoPin[x], e);
      delayMicroseconds(pinTones[p]);
    }
  }
}

