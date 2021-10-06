/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * 
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * 
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

/* Dependencies */
#include <Wire.h>
#include "TDA7468D.h"

TDA7468D::TDA7468D() {
	Wire.begin();
}

void TDA7468D::reset() {
	sendData(TDA7468_RESET,0x0);
}

void TDA7468D::setInput(_inputs input) {
	selectedInput = input;
	uint8_t data = input | (0 << 2) | (_mic_set << 3) | (_mute << 5);
	sendData(TDA7468_INPUT_SELECT, data);
}

void TDA7468D::setAutoInc(bool enable) {
	_autoInc = enable;
}

void TDA7468D::turnMic(bool enable) {
	_mute = enable;
	uint8_t data = selectedInput | (0 << 2) | (_mic_set << 3) | (_mute << 5);
	sendData(TDA7468_INPUT_SELECT, data);
}

void TDA7468D::setMic(uint8_t micVol) {
	if (micVol > 4) return;

	_mic_set = 0b11 - micVol;
	
	uint8_t data = selectedInput | (0 << 2) | (_mic_set << 3) | (_mute << 5);
	sendData(TDA7468_INPUT_SELECT, data);
}

void TDA7468D::setGain(uint8_t val){
	if (val > 7) return;
	sendData(TDA7468_INPUT_GAIN, val);
}

void TDA7468D::setSurround(bool enable,uint8_t gain, uint8_t mix, bool buffGain) {
	if (gain > 4 || mix > 7) return;
	uint8_t data = enable | (gain << 1) | (mix << 3) || (buffGain << 6);
	sendData(TDA7468_SURROUND, data);
}

void TDA7468D::setVol_L(uint8_t vol) {
	if (vol > 87) return;
	vol *= constrain(100 - _balance,0,100);
	Serial.println(vol);
	if (vol > 63) {
		vol = (((vol-56)/8)<<6) | 0b111000 | (~vol & 0b00000111);
	}
	
	sendData(TDA7468_VOLUME_LEFT,vol);
}

void TDA7468D::setVol_R(uint8_t vol) {
	if (vol > 87) return;
	vol *= constrain(100 + _balance,0,100);
	if (vol > 63) {
		vol = (((vol-56)/8)<<6) | 0b111000 | (vol & 0b00000111);
	}
	
	sendData(TDA7468_VOLUME_RIGHT,vol);
}

void TDA7468D::setBass(uint8_t bass) {
	if (bass > 15) return;

	uint8_t data;
	if (bass > 7) {
		_bass = (0b1000 | (0b111 - (bass & 0b0111) - 0b0001));
		data = (_bass << 4) | _treble;
	}
	else {
		_bass = bass;
		data = (_bass << 4) | _treble;
	}
	sendData(TDA7468_TREBLE_BASS, data);
}

void TDA7468D::setTreble(uint8_t treble) {
	if (treble > 15) return;

	uint8_t data;
	if (treble > 7) {
		_treble = (0b1000 | (0b111 - (treble & 0b0111) - 0b0001));
		data = (_bass << 4) | _treble;
	}
	else {
		_treble = treble;
		data = (_bass << 4) | _treble;
	}
	sendData(TDA7468_TREBLE_BASS, data);
}

void TDA7468D::mute(bool enable){
	sendData(TDA7468_OUTPUT, enable);
}

void TDA7468D::setAlc(bool enable, bool detector, bool circ, uint8_t attack, uint8_t threshold, bool attackMode) {
	if (attack > 3 || threshold > 3) return;

	uint8_t out = (attackMode << 7) | (threshold << 5) | (attackMode << 3) | (circ << 2) | (detector << 1) | enable;
	sendData(TDA7468_BASS_ALC, out);	
} 

void TDA7468D::balance(int8_t balance) {
	_balance = balance;
}


/////////////////////////////////////////////////////////////

void TDA7468D::sendData(uint8_t sub_addr, uint8_t data){
	#ifdef DEBUG_TDA
	Serial.print(sub_addr | (_autoInc << 4),BIN);
	Serial.print(" ");
	Serial.println(data,BIN);
	#else
	Wire.beginTransmission(_address);
	Wire.write(sub_addr | (_autoInc << 4));
	Wire.write(data);
	Wire.endTransmission();
	#endif
}
