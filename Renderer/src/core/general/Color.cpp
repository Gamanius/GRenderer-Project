#include "../GRenderer.h"

GGeneral::Color::Color(byte r, byte g, byte b) : red(r), green(g), blue(b) {
}

byte GGeneral::Color::operator[](byte i) {
	switch (i)
	{
	case 0: return red;
	case 1: return green;
	case 2: return blue;
	default: return 0;
	}
}