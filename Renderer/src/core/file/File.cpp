#include "../GRenderer.h"
#undef UNICODE
#include <Windows.h>
#include <iostream>
#include <fstream>

unsigned long long int GIO::getFileSize(GGeneral::String& relativeFilepath) {
	File returnValue = {};
	std::fstream file(relativeFilepath, std::ios_base::binary);
	if (file.fail())
		return 0;
	file.seekg(0, std::ios_base::end);
	auto size = file.tellg();
	file.close();
	return size;
}

GIO::File* GIO::loadFile(GGeneral::String relativeFilepath) {
	File* returnValue = new File();
	std::fstream file(relativeFilepath, std::ios_base::binary | std::ios_base::in);
	if (file.fail())
		return returnValue;
	file.seekg(0, std::ios_base::end);
	auto size = file.tellg();
	file.seekg(0, 0);

	char* buffer = static_cast<char*>(MALLOC(size));// new char[static_cast<unsigned int>(size)];
	file.read(buffer, size);
	file.close();
	returnValue->size = size;
	returnValue->data = reinterpret_cast<byte*>(buffer);
	return returnValue;
}

GGeneral::String GIO::getWorkingDirectionary() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return GGeneral::String(buffer);
}

bool GIO::Graphics::isParseble(GGeneral::String& filepath) {
	auto file = loadFile(filepath);
	return isParseble(file->data);
}

static byte BMPSig[] = { 0x42, 0x4d };
bool GIO::Graphics::isParseble(byte* data) {
	if (data[0] == BMPSig[0] && data[1] == BMPSig[1])
		return true;
	return false;
}

GIO::Graphics::Image* doBMP(GIO::File* f) {
	using namespace GIO::Graphics;
	Image* returnValue = new Image;
	//Check for header
	//only support for 32 and 24 bit BMP's
	int height = reinterpret_cast<int*>(&f->data[0x16])[0];
	returnValue->dim.height = height;
	int width = reinterpret_cast<int*>(&f->data[0x12])[0];
	returnValue->dim.width = width;
	unsigned short bpp = reinterpret_cast<unsigned short*>(&f->data[0x1c])[0];
	//ONLY 32bit and 24bit support for now
	if (bpp != 24 && bpp != 32)
		return nullptr;
	//Unused
	//unsigned int compression = reinterpret_cast<unsigned int*>(&f->data[0x1e])[0];

	unsigned int pixelStart = reinterpret_cast<unsigned int*>(&f->data[0xa])[0];
	unsigned long readBytes = height * width * (bpp == 24 ? 3 : 4);
	returnValue->data = static_cast<byte*>(MALLOC(readBytes));
	memcpy(returnValue->data, &f->data[pixelStart], readBytes);
	returnValue->size = readBytes;
	returnValue->hasAlpha = bpp == 32;

	delete f;
	return returnValue;
}

GIO::Graphics::Image* GIO::Graphics::loadImage(GGeneral::String filepath) {
	auto file = loadFile(filepath);
	if (file->data == nullptr) {
		delete file;
		return nullptr;
	}	if (!isParseble(file->data)) {
		delete file;
		return nullptr;
	}
	if (file->operator[](0) == BMPSig[0] && file->operator[](1) == BMPSig[1]) {
		return doBMP(file);
	}
	delete file;
	return nullptr;
}