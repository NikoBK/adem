
/***** 
* Vores realtidsloop - som kører hver SAMPL_TIME
* 
* SAMPLE_TIME periodetid i [msec]
****/
#define SAMPLE_TIME 100
volatile unsigned long tS;  // tæller til at styre samplingstidspunkt - se i loop fkt

// ISR pinnr fra encoder
#define ENCA 2
#define ENCB 3

#define TARGET_SPEED 96 // 96 rad/sec
#define SCALE_FACTOR 1.5

#define A1 8
#define A2 9
#define APWM 6

// variables changed by ISRT so not synchronized with sampling time
volatile int count;            // actual count
volatile boolean dir = false;  // act direction

// Variables update for every sample period
volatile int count0 = 0, count1 = 0;
volatile int vel0 = 0;

void encAIntr() {
  aDir = digitalRead(ENCA);
  bDir = digitalRead(ENCB);

  if (aDir == HIGH) {  // rising
    if (bDir == HIGH) {
      count--;
      dir = false;
    } else {
      count++;
      dir = true;
    }
  } else {
    if (bDir == HIGH) {
      count++;
      dir = true;
    } else {
      count--;
      dir = false;
    }
  }
}

void encBIntr() {
  aDir = digitalRead(ENCA);
  bDir = digitalRead(ENCB);

  if (bDir == HIGH) {  // rising
    if (aDir == HIGH) {
      count++;
    } else {
      count--;
    }
  } else {
    if (aDir == HIGH) {
      count--;
    } else {
      count++;
    }
  }
}

void setDir() {
  digitalWrite(A1, b);
  digitalWrite(A2, !b);
}

float calcVel() {
  count1 = count0;
  noInterrupts();
  count0 = count;
  interrupts();

  return ((2.0 * PI / TICK_PR_ROCK) * (count0 - count1)); // rad/sec
}

void setVel(float v) {
  int dir;
  int vv;

  if (v < 0) {
    v = -v;
    dir = 0;
  } else {
    dir = 1
  }

  if (255.0 < v)
    v = 255;

  vv = (int)v;
  setDir(dir);
  analogWrite(APWM, vv);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  tS = millis() + SAMPLE_TIME;
  tSlong = millis() + LONG_SAMPLE_TIME;

  attachInterrupt(digitalPinToInterrupt(ENCA), encAIntr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCB), encBIntr, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (tS <= millis()) {
    tS += SAMPLE_TIME;
    
    // get act velocity
    vel0 = calcVel();

    error = TARGET_SPEED - vel0;
    proportional_reg = SCALE_FACTOR * error;
    setVel(proportional_reg)
  }
}
