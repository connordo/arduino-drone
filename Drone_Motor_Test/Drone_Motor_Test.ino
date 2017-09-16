#define MOTOR 10
#define MAX_SPEED 255
#define HIGH_SPEED 200
#define LOW_SPEED 100
#define OFF 0
#define TIME_INTERVAL 5000

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  analogWrite(MOTOR, MAX_SPEED);
  delay(TIME_INTERVAL);
  
  analogWrite(MOTOR, HIGH_SPEED);
  delay(TIME_INTERVAL);
  
  analogWrite(MOTOR, LOW_SPEED);
  delay(TIME_INTERVAL);
  
  analogWrite(MOTOR, OFF);
  delay(TIME_INTERVAL);
}
