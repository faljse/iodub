/*
 AnalogButtons.cpp - Multiple buttons on one pin library
 Copyright (c) 2014 Roberto Lo Giacco.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as 
 published by the Free Software Foundation, either version 3 of the 
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "AnalogButtons.h"
#include <Arduino.h>

Button::Button(uint16_t value, void (*clickFunction)(void), void (*holdFunction)(void), uint16_t holdDuration, uint16_t holdInterval) {
	this->value = value;
	this->duration = holdDuration;
	this->interval = holdInterval;
	this->clickFunction = clickFunction;
	this->holdFunction = holdFunction;
}

AnalogButtons::AnalogButtons(uint8_t pin, uint8_t mode, uint16_t debounce, uint8_t margin) {
	this->pin = pin;
	this->debounce = debounce;
	this->counter = 0;
	this->margin = margin;
	pinMode(pin, mode);
}

void AnalogButtons::add(Button button) {
	if (buttonsCount < ANALOGBUTTONS_MAX_SIZE) {
    	buttons[buttonsCount++] = button;
  	}
}

void AnalogButtons::check() {
	// In case this function gets called very frequently avoid sampling the analog pin too often
	if (millis() - time > ANALOGBUTTONS_SAMPLING_INTERVAL) {
		time = millis();
		uint16_t reading = analogRead(pin);
		for (uint8_t i = 0; i < buttonsCount; i++) {
			if ((int16_t)reading >= (int16_t)buttons[i].value - margin && reading <= buttons[i].value + margin) {
				
				if (lastButtonPressed != &buttons[i]) {
					buttons[i].isHeldDown = false;
					if (debounceButton != &buttons[i]) {
                    	counter = 0;
                    	debounceButton = &buttons[i];
                  	}
					if (++counter >= debounce) {
						// button properly debounced
						lastButtonPressed = &buttons[i];
						previousMillis = millis();
					}
				} else {
					if (!buttons[i].isHeldDown && ((millis() - previousMillis) > buttons[i].duration)) {
						// button has been hold down long enough
						buttons[i].isHeldDown = true;
						buttons[i].held();
						previousMillis = millis();
					} else if (buttons[i].isHeldDown && ((millis() - previousMillis) > buttons[i].interval)) {
						// button was already held, it's time to fire again
						buttons[i].held();
						previousMillis = millis();
					}
				}
				// The first matching button is the only one that gets triggered
				return;
			}
		}
		// If execution reaches this point then no button has been pressed during this check
		if (lastButtonPressed != 0x00 && !lastButtonPressed->isHeldDown) {
			lastButtonPressed->pressed();
		}
		debounceButton = lastButtonPressed = 0x00;
	}
}
