/*
	MIT License

	Copyright © 2017 by madneon
	http://madneon.com
*/

#ifndef mdnAnalogButtons_h
#define mdnAnalogButtons_h

#include <Arduino.h>

class mdnAnalogButtons {
	public:
		mdnAnalogButtons(byte pin, byte count, byte values[]); // constructor

		unsigned long time_delay = 250; // button repeat delay
		unsigned long time_repeat = 50; // button repeat after delay
		byte spread = 4; // +/- on matching

		byte pop();
		void hold();
	private:
		byte _pin = 0; // analog pin to read

		byte _count = 0; // number of buttons
		byte *_values = 0; // values of buttons, 8 highest bits of analogRead(), min. distance = spread*2!

		byte _pressed_button = 0; // currently pressed button
		unsigned long _pressed_tick = 0; // tick of first press
		unsigned long _pressed_next = 0; // tick of next repeated press

		byte _match_pressed();
};

#endif
