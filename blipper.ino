// declare the switch pins
const int AS_SENSOR = 12;
const int SOLENOID = 11;
const int WARMUP_SW = 9;
const int CLUTCH_SENSOR = 10;

const int WARMUP_TIME = 300; // duration seconds
const int WARMUP_BLIP_ONTIME = 100; // duration ms
const int AS_BLIP_ONTIME = 200; // duration ms

void setup() {
  // initialize pins
  pinMode(AS_SENSOR, INPUT);
  digitalWrite(AS_SENSOR, HIGH);
  pinMode(CLUTCH_SENSOR, INPUT);
  digitalWrite(CLUTCH_SENSOR, HIGH);
  pinMode(WARMUP_SW, INPUT);
  digitalWrite(WARMUP_SW, HIGH);
  pinMode(SOLENOID, OUTPUT);
}

void loop() {
  warmup();
  ab();
}

void ab() {
  int ab_read = digitalRead(AS_SENSOR);
  int ab_fire = 0;
  while (doAb()) {
    if (ab_fire == 0) {
      ab_fire += 1;
      digitalWrite(SOLENOID, HIGH);
      delay(AS_BLIP_ONTIME);
      digitalWrite(SOLENOID, LOW);
      delay(100);
    }
    delay(1);
  }
}

bool doAb() {
  return (digitalRead(AS_SENSOR) == LOW and digitalRead(CLUTCH_SENSOR) == HIGH);
}

void warmup() {
  long warmup_time = WARMUP_TIME * 1000L;
  while (doWarmup()) {
    if (warmup_time > 0) {
      digitalWrite(SOLENOID, HIGH);
      delay(WARMUP_BLIP_ONTIME);
      digitalWrite(SOLENOID, LOW);
      delay(3000-WARMUP_BLIP_ONTIME);
      warmup_time -= 3000L;
    } else {
      delay(1);
    }
  }
}

bool doWarmup() {
  return (digitalRead(WARMUP_SW) == LOW);
}
