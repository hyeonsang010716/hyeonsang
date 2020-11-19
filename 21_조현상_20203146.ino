// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9
#include <Servo.h>
#define PIN_SERVO 10
#define _SERVO_SPEED 200
#define INTERVAL 20
Servo myservo;
#define _DUTY_MIN 1150
#define _DUTY_MAX 1550
int a, b; // unit: mm
int duty_curr;
float dist_ema;
int duty_chg_per_interval;

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(1000);
  duty_curr = 1000;
  duty_chg_per_interval = (double)((double)_DUTY_MAX - (double)_DUTY_MIN) * ((double)_SERVO_SPEED / 180) * ((double)INTERVAL / 1000);
// initialize serial port
  Serial.begin(57600);

  a = 73;
  b = 357;

  
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  dist_ema = 0.9*dist_ema + 0.1*dist_cali;
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  if(raw_dist > 156 && raw_dist <224) digitalWrite(PIN_LED, 0);
  else digitalWrite(PIN_LED, 255);
  delay(20);
  myservo.writeMicroseconds(duty_curr);

  if(dist_ema >= 255) {
    if(1150 < duty_curr) {
      duty_curr -= duty_chg_per_interval;
      if(duty_curr < 1150) duty_curr = 1150;
    }
  }
  else {
    if(1550 > duty_curr){
      duty_curr += duty_chg_per_interval;
      if(duty_curr > 1550 ) duty_curr = 1550;
    }
  }
}
