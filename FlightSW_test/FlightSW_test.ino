#define DBG 1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (DBG) Serial.println("DBG is set to one. Debug Statements will print");

  int checkval = 5;
  if (sensors_init() == 0) {
    if (DBG) Serial.println("All sensors online");
  }
  else {
    if (DBG) Serial.println("Error with sensors");
  }
}

void loop() {
}
