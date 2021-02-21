#include "GRenderer.h"

GGeneral::RGBColor::RGBColor(byte r, byte g, byte b) : red(r), green(g), blue(b) {}

byte GGeneral::RGBColor::operator[](byte i) {
	switch (i) {
	case 0: return red;
	case 1: return green;
	case 2: return blue;
	default: return 0;
	}
}

GGeneral::RGBColor GGeneral::RGBColor::HSVtoRGB(HSVColor color) {
	return color.HSVtoRGB();
}

GGeneral::RGBColor GGeneral::HSVColor::HSVtoRGB() {
	//taken from https://www.rapidtables.com/convert/color/hsv-to-rgb.html
	float c = v * s;
	float x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
	float m = v - c;

	RGBColor rgb;
	if(0 <= h && h < 60) {
		rgb.red = (c + m) * 255;
		rgb.green = (x + m) * 255;
		rgb.blue = m * 255;
	}
	else if (60 <= h && h < 120) {
		rgb.red = (x + m) * 255;
		rgb.green = (c + m) * 255;
		rgb.blue = m * 255;
	}
	else if (120 <= h && h < 180) {
		rgb.red = m * 255;
		rgb.green = (c + m) * 255;
		rgb.blue = (x + m) * 255;
	}
	else if (180 <= h && h < 240) {
		rgb.red = m * 255;
		rgb.green = (x + m) * 255;
		rgb.blue = (c + m) * 255;
	}
	else if (240 <= h && h < 300) {
		rgb.red = (x + m) * 255;
		rgb.green = m * 255;
		rgb.blue = (c + m) * 255;
	}
	else if (300 <= h && h < 360) {
		rgb.red = (c + m) * 255;
		rgb.green = m * 255;
		rgb.blue = (x + m) * 255;
	}

	return rgb;
}

GGeneral::aRGBColor::aRGBColor(byte red, byte green, byte blue, byte alpha) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

byte GGeneral::aRGBColor::operator[](byte i) {
	switch (i) {
	case 0: return red;
	case 1: return green;
	case 2: return blue;
	case 3: return alpha;
	default: return 0;
	}
}

GGeneral::HSVColor::HSVColor(int hue, float saturation, float value) {
	this->h = hue;
	this->s = saturation;
	this->v = value;
}