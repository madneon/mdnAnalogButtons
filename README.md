# repository moved to:
https://git.madneon.com/Arduino/mdnAnalogButtons/

# mdnAnalogButtons
Arduino library for multiple buttons on single analog pin

# Usage
4 buttons example using 1x10k and 4x1k resistors on A0 pin:

```
#include <mdnAnalogButtons.h>

mdnAnalogButtons buttons(A0, 4, (byte[4]){22, 42, 58, 72});

void setup() {
	Serial.begin(9600);
}

void loop() {
	byte b = buttons.pop();
	if (b != 0) {
		Serial.println(b);
	}
}
```
