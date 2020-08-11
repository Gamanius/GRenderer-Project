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

GGamepad::Gamepad GGamepad::getGamepad(short num) {
	if (getAmountOfConnectedGPad() > num)
		return Gamepad();
	return Gamepad(num - 1);
}

bool GGamepad::Gamepad::vibrate(float amount, bool leftMotor) {
	XINPUT_VIBRATION vib;
#pragma warning(suppress : 4244)
	unsigned short m = 65535 * amount;
	vib.wLeftMotorSpeed = leftMotor * m;
	vib.wRightMotorSpeed = !leftMotor * m;
	return XInputSetState(num, &vib);
}

bool GGamepad::Gamepad::stopvibrate() {
	return false;
}

#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

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