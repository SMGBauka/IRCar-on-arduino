#include "IRremote.h"
#include "Wire.h"

#define IR_PIN        2
#define BUZZER_PIN    9
#define LED_PIN       11

#define MTR_IN1_PIN   7
#define MTR_IN2_PIN   6
#define MTR_IN3_PIN   5
#define MTR_IN4_PIN   4
#define FORWARD_IR_CODE 3877175040
#define BACKWARD_IR_CODE 2907897600
#define LEFT_IR_CODE 4144561920
#define RIGHT_IR_CODE 2774204160
#define BUZZER_IR_CODE 3810328320

#define BUZ_ON  digitalWrite(BUZZER_PIN, 1)
#define BUZ_OFF digitalWrite(BUZZER_PIN, 0)

IRrecv irrecv(IR_PIN);

#define IR_CMD_NONE     0
#define IR_CMD_FORWARD  1
#define IR_CMD_BACKWARD 2
#define IR_CMD_LEFT     3
#define IR_CMD_RIGHT    4
#define IR_CMD_BUZZER   5


uint32_t ir_cmd = 0;
uint32_t timer_cmd_dur = 0;

void setup()
{
  pinMode(MTR_IN1_PIN, 1);
  pinMode(MTR_IN2_PIN, 1);
  pinMode(MTR_IN3_PIN, 1);
  pinMode(MTR_IN4_PIN, 1);
  pinMode(BUZZER_PIN, 1);
  pinMode(LED_PIN, 1);
  
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  BUZ_ON;
  delay(1000);
  BUZ_OFF;
}

void loop()
{
 if(IrReceiver.decode()) 
 {
  uint32_t ir_res = IrReceiver.decodedIRData.decodedRawData;
  Serial.println(ir_res);
  if(ir_res == FORWARD_IR_CODE)
  {
    ir_cmd = IR_CMD_FORWARD;
    timer_cmd_dur = millis();
  }
  else if(ir_res == BACKWARD_IR_CODE)
  {
    ir_cmd = IR_CMD_BACKWARD;
    timer_cmd_dur = millis();
  }
  else if(ir_res == RIGHT_IR_CODE)
  {
    ir_cmd = IR_CMD_RIGHT;
    timer_cmd_dur = millis();
  }
  else if(ir_res == BUZZER_IR_CODE)
  {
    ir_cmd = IR_CMD_BUZZER;
    timer_cmd_dur = millis();
  }
  else if(ir_res == LEFT_IR_CODE)
  {
    ir_cmd = IR_CMD_LEFT;
    timer_cmd_dur = millis();
  }
  else if(ir_res == 0)
  {
    timer_cmd_dur = millis();
  }
 }
 IrReceiver.resume();

 if((millis() - timer_cmd_dur) >= 250) ir_cmd = IR_CMD_NONE;
 
 if(ir_cmd == IR_CMD_FORWARD)
    mtr_f(); 
 else if(ir_cmd == IR_CMD_BACKWARD)
    mtr_b();
 else if(ir_cmd == IR_CMD_LEFT)
    mtr_l();
 else if(ir_cmd == IR_CMD_RIGHT)
    mtr_r();
 else if(ir_cmd == IR_CMD_BUZZER)
    BUZ_ON;
 else{
    mtr_s();
    BUZ_OFF;
 }
 delay(1);
}

void mtr_f() 
{
  digitalWrite(MTR_IN1_PIN, 1);
  digitalWrite(MTR_IN2_PIN, 0);
  digitalWrite(MTR_IN3_PIN, 1);
  digitalWrite(MTR_IN4_PIN, 0);
}

void mtr_b()
{
  digitalWrite(MTR_IN1_PIN, 0);
  digitalWrite(MTR_IN2_PIN, 1);
  digitalWrite(MTR_IN3_PIN, 0);
  digitalWrite(MTR_IN4_PIN, 1);
}
void mtr_l()
{
  digitalWrite(MTR_IN1_PIN, 0);
  digitalWrite(MTR_IN2_PIN, 1);
  digitalWrite(MTR_IN3_PIN, 1);
  digitalWrite(MTR_IN4_PIN, 0);
}

void mtr_r(){
  digitalWrite(MTR_IN1_PIN, 1);
  digitalWrite(MTR_IN2_PIN, 0);
  digitalWrite(MTR_IN3_PIN, 0);
  digitalWrite(MTR_IN4_PIN, 1);
}

void mtr_s() 
{
  digitalWrite(MTR_IN1_PIN, 0);
  digitalWrite(MTR_IN2_PIN, 0);
  digitalWrite(MTR_IN3_PIN, 0);
  digitalWrite(MTR_IN4_PIN, 0);
}
