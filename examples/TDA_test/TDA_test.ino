// TDA test sketch
#include <TDA7468D.h>
#include <Wire.h>

TDA7468D tda;

void audio();

void setup() {
  tda.reset(); //reset state
  
  tda.setInput(IN1); // IN1 IN2 IN3 IN4
  //tda.setAutoInc(true) //  Incremental Bus (read datasheet)
  tda.setMic(0); // set gain for mic 0 .. 4 -> 0 6 10 14 dB
  tda.turnMic(false); // enable or disable mic
  audio();
}

void audio() {
  tda.setGain(0); // 0 .. 7 -> 0 .. 14 dB step 2 dB   set input Gain
  tda.setSurround(true,0,3,0);
  tda.setVol_R(40);
  tda.setVol_L(40);
  tda.setBass(7);
  tda.setTreble(7);
  tda.mute(false);
  tda.balance(0);
  tda.setAlc(false,false,false,0,0,false);
}

void loop() {
  // put your main code here, to run repeatedly:

}