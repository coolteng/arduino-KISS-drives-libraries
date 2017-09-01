// 作者：鄧崇林
#include <CltTimer1CTC.h>
#include <CltTimer2PWM.h>
#define LENGTH 256 // 波數值表長度
int speakerPin = 11; // Can be either 3 or 11, two PWM outputs connected to Timer 2

unsigned char wave[LENGTH] = { // 波長儲存數值表
  127,130,133,136,139,142,145,148,151,154,157,160,164,166,169,172,
  175,178,181,184,187,189,192,195,197,200,202,205,207,210,212,214,
  217,219,221,223,225,227,229,231,232,234,236,237,239,240,242,243,
  244,245,246,247,248,249,250,251,251,252,252,253,253,253,253,253,
  254,253,253,253,253,252,252,251,251,250,249,249,248,247,246,245,
  243,242,241,239,238,236,235,233,231,230,228,226,224,222,220,218,
  215,213,211,209,206,204,201,199,196,193,191,188,185,182,180,177,
  174,171,168,165,162,159,156,153,150,147,144,141,137,134,131,128,
  125,122,119,116,112,109,106,103,100, 97, 94, 91, 88, 85, 82, 79,
   76, 73, 71, 68, 65, 62, 60, 57, 54, 52, 49, 47, 44, 42, 40, 38,
   35, 33, 31, 29, 27, 25, 23, 22, 20, 18, 17, 15, 14, 12, 11, 10,
    8,  7,  6,  5,  4,  4,  3,  2,  2,  1,  1,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  1,  1,  2,  2,  3,  4,  5,  6,  7,  8,  9,
   10, 11, 13, 14, 16, 17, 19, 21, 22, 24, 26, 28, 30, 32, 34, 36,
   39, 41, 43, 46, 48, 51, 53, 56, 58, 61, 64, 66, 69, 72, 75, 78,
   81, 84, 87, 89, 93, 96, 99,102,105,108,111,114,117,120,123,127};

//ISR(TIMER1_COMPA_vect) {
void tickSineWaveISR(void) {
  static byte index=0; // 指向每一個數值表的起頭索引位址
  Timer2PWM.putByte2Sound(speakerPin, wave[index++]);
} 

void setup() {
  pinMode(speakerPin, OUTPUT); // 將Timer2計時器的PWM針腳設為輸出
  Timer2PWM.initMode3(speakerPin);
  // Set up Timer 1 to send a sample every interrupt.
  // sampling rate = 1/16us = 1/0.0000016s = 62.5KHz
  Timer1CTC.initTOP(16); // us, microSeconds(微秒)，取樣率=62.5KHz
  Timer1CTC.attachInterrupt(tickSineWaveISR);
  interrupts();
}

void loop() { 
  // 什麼事也沒做，但還是持續不間斷地發出音效！
}
