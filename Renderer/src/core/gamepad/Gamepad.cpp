#include "../GRenderer.h"
#include <Windows.h>
#include <Xinput.h>
#pragma warning(disable : 4995)

short GGamepad::getAmountOfConnectedGPad() {
	XINPUT_STATE state;
	for (short i = 0; i < 4; i++) {
		auto error = XInputGetState(i, &state);
		if (error == ERROR_DEVICE_NOT_CONNECTED)
			return i;
	}
	return 4;
}

void GGamepad::enable(bool enable) {
	XInputEnable(enable);
}

GGamepad::Gamepad::Gamepad(byte num) { listen(num); }

void GGamepad::Gamepad::listen(byte num) {
	if (num > 3 || num < 0)
		THROWW("The parameter is not a valid controller number. All functions in the Gamepad class will throw an error");
	this->num = num;
}

bool GGamepad::Gamepad::vibrate(unsigned short amount, byte leftMotor) {
	XINPUT_VIBRATION vib;
	vib.wLeftMotorSpeed = (leftMotor & 0b1) * amount;
	vib.wRightMotorSpeed = (leftMotor & 0b10) * amount;
	return XInputSetState(num, &vib);
}

bool GGamepad::Gamepad::stopvibrate() {
	XINPUT_VIBRATION vib;
	vib.wLeftMotorSpeed = 0;
	vib.wRightMotorSpeed = 0;
	return XInputSetState(num, &vib);
}

GGamepad::GamepadState GGamepad::Gamepad::getState() {
	XINPUT_STATE  pad;
	XInputGetState(num, &pad);
	GamepadState state;

	state.dpad_up = pad.Gamepad.wButtons & 0x0001;
	state.dpad_down = pad.Gamepad.wButtons & 0x0002;
	state.dpad_left = pad.Gamepad.wButtons & 0x0004;
	state.dpad_right = pad.Gamepad.wButtons & 0x0008;

	state.start = pad.Gamepad.wButtons & 0x0010;
	state.back = pad.Gamepad.wButtons & 0x0020;

	state.left_thumbstick = pad.Gamepad.wButtons & 0x0040;
	state.right_thumbstick = pad.Gamepad.wButtons & 0x0080;

	state.button_left_shoulder = pad.Gamepad.wButtons & 0x0100;
	state.button_right_shoulder = pad.Gamepad.wButtons & 0x0200;

	state.button_a = pad.Gamepad.wButtons & 0x1000;
	state.button_b = pad.Gamepad.wButtons & 0x2000;
	state.button_x = pad.Gamepad.wButtons & 0x4000;
	state.button_y = pad.Gamepad.wButtons & 0x8000;

	state.left_trigger = pad.Gamepad.bLeftTrigger;
	state.right_trigger = pad.Gamepad.bRightTrigger;

	state.left_thumbstick.x = pad.Gamepad.sThumbLX;
	state.left_thumbstick.y = pad.Gamepad.sThumbLY;

	state.right_thumbstick.x = pad.Gamepad.sThumbRX;
	state.right_thumbstick.y = pad.Gamepad.sThumbRY;

	return state;
}