/*
	MIT License

	Copyright © 2017 by madneon
	http://madneon.com
*/

#include <mdnAnalogButtons.h>

const byte _button_val_none = 255; // full 8 bits

// constructor
mdnAnalogButtons::mdnAnalogButtons(byte pin, byte count, byte values[]) {
	_pin = pin;
	_count = count + 1; // 0 and values

	// alloc memory
	delete []_values;
	_values = new byte[count];

	// assign no button value
	_values[0] = _button_val_none;

	// assign all button values
	for (size_t i = 0; i < _count; i ++){
		_values[i + 1] = values[i];
	}
}

byte mdnAnalogButtons::pop() {
	byte _b = _match_pressed();

	if (_pressed_button != _b) {
		// new button pressed or released
		_pressed_button = _b;
		if (_pressed_button != 0) {
			// its not release
			_pressed_tick = millis();
			_pressed_next = _pressed_tick + time_delay;
		}
	} else {
		// same button
		if (millis() >= _pressed_next) {
			_pressed_next += time_repeat;
		} else {
			return 0; // don't report repeat yet
		}
	}

	return _pressed_button;
}

byte mdnAnalogButtons::_match_pressed() {
	// read value
	int _v = analogRead(_pin) >> 2; // 8 highest bits

	for (size_t i = 0; i < _count; i ++){
		if (abs(_v - _values[i]) <= spread) { // match within spread range
			// return matching button id
			return i;
		}
	}

	// no matching value found
	return 0;
}

void mdnAnalogButtons::hold() {
	// wait until no button is pressed
	int _v = analogRead(_pin) >> 2;
	while (abs(_v - _values[0]) > spread) {
		_v = analogRead(_pin) >> 2;
	}
}
