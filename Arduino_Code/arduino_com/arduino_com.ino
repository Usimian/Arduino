#include <Servo.h>
#include <math.h>


#define MAX_GAMMA 50
// Servo variables
#define MAX_SERVOS 12
#define MAX_PULSE 2500
#define MIN_PULSE 560

Servo Servos[MAX_SERVOS];


// Loop time variables
unsigned long previousMillis = 0;
const long interval = 20;
unsigned long loopTime;
unsigned long previousLooptime;
double t;

struct angles {
  double tetta;
  double alpha;
  double gamma;
};
struct angles anglesFR;
struct angles anglesFL;
struct angles anglesBR;
struct angles anglesBL;
// Receive buffer variables
const byte numChars = 32;
char receivedChars[numChars];
int spaceCounter = 0;

boolean newData = false;

int pulse0, pulse1, pulse2, pulse3, pulse4, pulse5, pulse6, pulse7, pulse8, pulse9, pulse10, pulse11;

char a;
int pulse;

int batteryLevel = 0; // Last averaged battery level
int batterySum = 0;
int batteryPollCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  IMUSetup();
  connectServos();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    t = float(currentMillis) / 1000;
    loopTime = currentMillis - previousLooptime;  // The time it takes for one loop
    Serial.print("<");
    Serial.print(loopTime);
    Serial.print("#");
    getBatteryLevel();
    Serial.print(batteryLevel);
    Serial.print("#");
    previousLooptime = currentMillis;

    readAngles();

    recvWithStartEndMarkers();

    newData = false;
    moveServos(pulse0, pulse1, pulse2, pulse3, pulse4, pulse5, pulse6, pulse7, pulse8, pulse9, pulse10, pulse11);
  }
}

void getBatteryLevel() {
  batterySum += analogRead(A8);
  batteryPollCount += 1;
  if (batteryPollCount >= 20)
  {
    batteryLevel = batterySum / 20; // Average the battery readings
    batterySum = 0;
    batteryPollCount = 0;
  }
}

void connectServos() {
  //FR
  Servos[0].attach(40);//coxa
  Servos[1].attach(38);//femur
  Servos[2].attach(36);//tibia

  Servos[3].attach(42);//FL
  Servos[4].attach(44);//0=550
  Servos[5].attach(46);

  Servos[6].attach(34);//BR
  Servos[7].attach(32);//0=2500
  Servos[8].attach(30);

  Servos[9].attach(48);//BL
  Servos[10].attach(50);//0=550
  Servos[11].attach(52);
}



void moveServos(int pulse0, int pulse1, int pulse2, int pulse3, int pulse4, int pulse5, int pulse6, int pulse7, int pulse8, int pulse9, int pulse10, int pulse11) {

  Servos[0].writeMicroseconds(pulse0);
  Servos[1].writeMicroseconds(pulse1);
  Servos[2].writeMicroseconds(pulse2);

  Servos[3].writeMicroseconds(pulse3);
  Servos[4].writeMicroseconds(pulse4);
  Servos[5].writeMicroseconds(pulse5);

  Servos[6].writeMicroseconds(pulse6);
  Servos[7].writeMicroseconds(pulse7);
  Servos[8].writeMicroseconds(pulse8);

  Servos[9].writeMicroseconds(pulse9);
  Servos[10].writeMicroseconds(pulse10);
  Servos[11].writeMicroseconds(pulse11);
}


void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char spaceMarker = '#';

  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    //        Serial.print("serial In");
    if (recvInProgress == true) {
      if (rc != endMarker && rc != spaceMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else if (rc == spaceMarker ) {
        receivedChars[ndx] = '\0';
        if (spaceCounter == 0) {
          //Serial.println(receivedChars);
          pulse0 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 1) {
          //Serial.println(receivedChars);
          pulse1 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 2) {
          //Serial.println(receivedChars);
          pulse2 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 3) {
          //Serial.println(receivedChars);
          pulse3 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 4) {
          //Serial.println(receivedChars);
          pulse4 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 5) {
          //Serial.println(receivedChars);
          pulse5 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 6) {
          //Seral.println(receivedChars);
          pulse6 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 7) {
          //Serial.println(receivedChars);
          pulse7 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 8) {
          //Serial.println(receivedChars);
          pulse8 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 9) {
          //Serial.println(receivedChars);
          pulse9 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 10) {
          //Serial.println(receivedChars);
          pulse10 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
        else if (spaceCounter == 11) {
          //Serial.println(receivedChars);
          pulse11 = atoi(receivedChars);
          spaceCounter++;
          ndx = 0;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        //Serial.println(receivedChars);
        pulse11 = atoi(receivedChars);
        recvInProgress = false;
        ndx = 0;
        spaceCounter = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}
