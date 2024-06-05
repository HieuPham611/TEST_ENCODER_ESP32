#include <Arduino.h>
#include <ESP32Encoder.h>

const int ledPin1 = 25;  //chân xung pwm 1
const int ledPin2 = 13;  //chân xung pwm 2
// configuration of PWM channels
const int freq = 5000;      // tần số xung
const int ledChannel1 = 0;  // kênh PWM
const int ledChannel2 = 1;  // kênh PWM
const int resolution = 8;   // độ phân giải 8bit
/*-------------------------------MOTOR DIRECTION--------------------------*/
#define DIR1_1 27
#define DIR1_2 26
#define DIR2_1 12
#define DIR2_2 14

#define ENC_2A 32
#define ENC_2B 33
#define ENC_1A 17
#define ENC_1B 16

ESP32Encoder encoder_left;
ESP32Encoder encoder_right;

void setup_pwm() {
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcAttachPin(ledPin1, ledChannel1);
  ledcAttachPin(ledPin2, ledChannel2);

  pinMode(DIR1_1, OUTPUT);
  pinMode(DIR1_2, OUTPUT);
  pinMode(DIR2_1, OUTPUT);
  pinMode(DIR2_2, OUTPUT);
}

void Right_Motor_PWM(float PWM_) {
  if (PWM_ >= 0) {
    ledcWrite(ledChannel1, PWM_);
    digitalWrite(DIR1_1, LOW);
    digitalWrite(DIR1_2, HIGH);
  } else {
    ledcWrite(ledChannel1, abs(PWM_));
    digitalWrite(DIR1_1, HIGH);
    digitalWrite(DIR1_2, LOW);
  }
}
void Left_Motor_PWM(float PWM_) {
  if (PWM_ >= 0) {
    ledcWrite(ledChannel2, PWM_);
    digitalWrite(DIR2_1, LOW);
    digitalWrite(DIR2_2, HIGH);
  } else {
    ledcWrite(ledChannel2, abs(PWM_));
    digitalWrite(DIR2_1, HIGH);
    digitalWrite(DIR2_2, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  setup_pwm();
  // Gắn các chân GPIO cho encoder
  // encoder.attachSingleEdge(32, 33); 
  encoder_right.attachSingleEdge(ENC_1A, ENC_1B);
  encoder_right.clearCount();

  encoder_left.attachSingleEdge(ENC_2A, ENC_2B);
  encoder_left.clearCount();

  Serial.println("Ví dụ về encoder");
}

void loop() {
  int64_t count_left = encoder_left.getCount();
  Serial.print("Giá trị encoder: ");
  Serial.print(count_left);

  Serial.print('\t');

  int64_t count_right = encoder_right.getCount();
  Serial.print("Giá trị encoder: ");
  Serial.println(count_right);





  // Right_Motor_PWM(255);
  // Left_Motor_PWM(255);
  // delay(100);
}
