#define MOTOR_1 10
#define MOTOR_2 9
#define MOTOR_3 6
#define MOTOR_4 11

#define ACCEL 255
#define STABL 0
#define DECEL 10

#define TIME 500
void setup() {

}

void loop() {
  analogWrite(MOTOR_1, ACCEL);
  delay(TIME);
  analogWrite(MOTOR_1, STABL);
  delay(TIME);

  analogWrite(MOTOR_2, ACCEL);
  delay(TIME);
  analogWrite(MOTOR_2, STABL);
  delay(TIME);

  analogWrite(MOTOR_3, ACCEL);
  delay(TIME);
  analogWrite(MOTOR_3, STABL);
  delay(TIME);

  analogWrite(MOTOR_4, ACCEL);
  delay(TIME);
  analogWrite(MOTOR_4, STABL);
  delay(TIME);

  //----------------

  analogWrite(MOTOR_1, DECEL);
  delay(TIME);
  analogWrite(MOTOR_1, STABL);
  delay(TIME);

  analogWrite(MOTOR_2, DECEL);
  delay(TIME);
  analogWrite(MOTOR_2, STABL);
  delay(TIME);

  analogWrite(MOTOR_3, DECEL);
  delay(TIME);
  analogWrite(MOTOR_3, STABL);
  delay(TIME);

  analogWrite(MOTOR_4, DECEL);
  delay(TIME);
  analogWrite(MOTOR_4, STABL);
  delay(TIME);

  analogWrite(MOTOR_1, ACCEL);
  analogWrite(MOTOR_2, ACCEL);
  analogWrite(MOTOR_3, ACCEL);
  analogWrite(MOTOR_4, ACCEL);
  delay(2000);
  analogWrite(MOTOR_1, DECEL);
  analogWrite(MOTOR_2, DECEL);
  analogWrite(MOTOR_3, DECEL);
  analogWrite(MOTOR_4, DECEL);
  delay(2000);
}
