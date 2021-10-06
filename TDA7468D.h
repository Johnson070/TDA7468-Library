/**
 * @brief TDA7468D arduino library
 * @author Johnson070 <v.veberm@gmail.com>
 * @version 1.0
 *
 * @section license_sec License
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 *
 * @section other_sec Others notes and compatibility warning
 * Compatible with arduino 1.0.x and >=0023\n
 * Retro-compatible with the previous library version
 */
#pragma once

#include <Wire.h>		// обычная Wire
#include <Arduino.h>

//#define DEBUG_TDA

#define TDA7468_addr 0x88

#define TDA7468_RESET 0b1111110

enum _inputs {
	IN1,
	IN2,
	IN3,
	IN4
};

class TDA7468D {
	public:
		TDA7468D();
		//TDA7468D(uint8_t addr = TDA7468_addr);
		//TDA7468D(uint8_t sda, uint8_t scl, uint8_t addr = TDA7468_addr);

		void setInput(_inputs input);
		void reset();

		void setAutoInc(bool enable);

		/*
			micVol - 0 .. 4 -> gain 0 .. 14 dB (0 6 10 14)
		*/
		void setMic(uint8_t micVol);
		void turnMic(bool enable);

		/*
			0 - 0dB
			1 - 2dB
			2 - 4dB
			3 - 6dB
			4 - 8dB
			5 - 10dB
			6 - 12dB
			7 - 14dB
		*/
		void setGain(uint8_t val); //0-7 

		/*
			enable - 0 .. 1 off / on
			gain - 0 .. 4 -> 0 .. 12 dB(0 6 9 12)   =default 0dB
			mix - 0 .. 7 -> inv 0 .. 2 (100 50 25 %) | 0% | non inv 4 .. 6 (100 75 50) | 7 mute
			buffGain - 0 .. 1 (0 6 dB)
		*/
		void setSurround(bool enable,uint8_t gain, uint8_t mix , bool buffGain);

		/*
			vol - 0 .. 87 -> 0 .. -87 dB
		*/
		void setVol_L(uint8_t vol);
		void setVol_R(uint8_t vol);

		/*
			bass - 
					0 .. 6 - -14 .. -2 dB
					7 - 0 db
					8 .. 14 - 2 .. 14 dB
		*/
		void setBass(uint8_t bass);

		/*
			treble - 
					0 .. 6 - -14 .. -2 dB
					7 - 0 db
					8 .. 14 - 2 .. 14 dB
		*/
		void setTreble(uint8_t treble);

		void mute(bool enable);

		/*
			0 .. 100 -> balance left
			0 .. -100 -> balance right
		*/
		void balance(int8_t balance);

		//TDA7468_BASS_ALC I don't know how this thing work(sorry:( )
		void setAlc(bool enable, bool detector, bool circ, uint8_t attack, uint8_t threshold, bool attackMode);

		_inputs selectedInput = IN1;
	private:
		uint8_t TDA7468_INPUT_SELECT = 0b0;
		uint8_t TDA7468_INPUT_GAIN = 0b1;
		uint8_t TDA7468_SURROUND = 0b10;
		uint8_t TDA7468_VOLUME_LEFT = 0b11;
		uint8_t TDA7468_VOLUME_RIGHT = 0b100;
		uint8_t TDA7468_TREBLE_BASS = 0b101;
		uint8_t TDA7468_OUTPUT = 0b110;
		uint8_t TDA7468_BASS_ALC = 0b111;

		uint8_t _address = TDA7468_addr;

		bool _autoInc = false;

		// TDA7468_INPUT_SELECT mode
		bool _mute = false;
		uint8_t _mic_set = 0b11;

		//TDA7468_TREBLE_BASS
		uint8_t _treble = 0b111; // 0 dB
		uint8_t _bass = 0b111; // 0 dB

		int16_t	_balance = 0;

		void sendData(uint8_t sub_addr, uint8_t data);
};
