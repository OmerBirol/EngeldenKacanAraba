#include <picobricks.h>

#define TRIG_PIN 26
#define ECHO_PIN 27
#define SLOW     120
#define FAST     255

long duration;
float cm;
int stage = 0;   

motorDriver motor;

void distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  cm = (duration / 2) / 29.1;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  distance();
  delay(150);

  if (stage == 0) {
    
    if (cm < 8.0) {
      backward();
      delay(300);
      stop();

      right();
      delay(350);
      stop();
      delay(200);

      stage = 1; 
    } else {
      forward();
    }
  } 
  else if (stage == 1) {
    
    if (cm < 8.0) {
      backward();
      delay(300);
      stop();

      left();
      delay(350);
      stop();
      delay(200);

      stage = 2; 
    } else {
      forward();
    }
  } 
  else if (stage == 2) {
    
    if (cm < 8.0) {
      backward();
      delay(300);
      stop();
      
      right();
      delay(350);
      stop();
      delay(200);

      stage = 0; 
    } else {
      forward();
    }
  }
}

void forward() {
  motor.dc(1, SLOW, 0);
  motor.dc(2, SLOW, 0);
}

void right() {
  motor.dc(1, SLOW, 1);
  motor.dc(2, SLOW, 0);
}

void left() {
  motor.dc(1, SLOW, 0);
  motor.dc(2, SLOW, 1);
}

void stop() {
  motor.dc(1, 0, 0);
  motor.dc(2, 0, 0);
}

void backward() {
  motor.dc(1, SLOW, 1);
  motor.dc(2, SLOW, 1);
}
