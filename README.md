# TDA7468D
 Library for TDA7468D I2C control!<br>
 [Datasheet TDA7468D](https://pdf1.alldatasheet.com/datasheet-pdf/view/92058/STMICROELECTRONICS/TDA7468D13TR.html)

## Start
 1) Create object ```TDA7468D tda;```
 2) Select input ```tda.setInput(IN1);``` or ```IN2```,```IN2```,```IN3```

## Set volume
 Input volume between `0` and `87` => `0 .. -87 dB`.

## Set bass and treble
 Input value between `0` and `14`
 1) `0 .. 6` -> `-14 .. -2 dB` (step 2 dB)
 2) `7` -> `0 dB`
 3) `8 .. 14` -> `2 .. 14 dB` (step 2 dB)

## Mute
 `tda.mute(bool state);` - enable or disable music output.
 
## Balance
 `tda.balance(int8_t balance);` balance between `-100` and `100`
 1) `-100 .. 0` -> balance right channel
 2) `0 .. 100` -> balancу left channel

## Input gain
 `setGain(uint8_t val);` gain between `0` and `7` -> `0 .. 14 dB` (step 2 dB)

## More
 1) `setAlc(bool enable, bool detector, bool circ, uint8_t attack, uint8_t threshold, bool attackMode);`
 2) `void setSurround(bool enable,uint8_t gain, uint8_t mix , bool buffGain);`<br><br>
    `gain` -> `0 .. 4` - `0 .. 12 dB` (0 6 9 12 dB)<br>
    `mix` -> `0 .. 2` - inv mix(100 50 25%) | `3` - 0% | `4 .. 6` mix(100 75 50) | `7` - mute<br>
    `buffGain` -> `0 .. 1` - `0 or 6 dB`
 3) `setMic(uint8_t micVol);`<br><br>
    `micVol` -> `0 .. 4` - `0 .. 14 dB` (0 6 10 14 dB) mic GAIN
 4) `turnMic(bool enable);`
