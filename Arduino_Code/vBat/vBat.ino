// Arduino Example Code snippet

#define VBATPIN A6

float measuredvbat;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
measuredvbat = analogRead(VBATPIN);

measuredvbat *= 2;    // we divided by 2, so multiply back
measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
measuredvbat /= 1024; // convert to voltage
Serial.print("VBat: " ); Serial.println(measuredvbat);
}
