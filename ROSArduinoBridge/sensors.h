/* Functions for various sensor types */

#ifdef SENSOR_SONAR

#define TRIG_PIN 3
#define ECHO_PIN 2

#endif

void initSonar() {

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}
float microsecondsToCm(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per cm.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

long Ping() {
  Serial.println("sonar hi");
  long duration, range;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH); // convert the time into meters
  range = microsecondsToCm(duration);

  return (range);
}
