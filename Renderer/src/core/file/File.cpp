#include "../GRenderer.h"
#undef UNICODE
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <lodepng.h>
#include <algorithm>

#define FORMAT_THROW(msg, error)\
{LPVOID lpMsgBuf = nullptr;\
\
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |	FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, 0, (LPTSTR)&lpMsgBuf, 0, NULL);\
THROWW(msg, (char*)lpMsgBuf);\
LocalFree(lpMsgBuf);}

unsigned long long int GFile::getFileSize(GGeneral::String& relativeFilepath) {
	File returnValue = {};
	std::fstream file(relativeFilepath, std::ios_base::binary);
	if (file.fail())
		return 0;
	file.seekg(0, std::ios_base::end);
	auto size = file.tellg();
	file.close();
	return size;
}

GFile::File* GFile::loadFile(GGeneral::String relativeFilepath) {
	File* returnValue = new File();
	std::fstream file(relativeFilepath, std::ios_base::binary | std::ios_base::in);
	if (file.fail()) {
		THROW("Error while trying to load from relative path ", relativeFilepath, ". Maybe the Path is wrong?");
		return returnValue;
	}
	file.seekg(0, std::ios_base::end);
	unsigned int size = static_cast<unsigned int>(file.tellg());
	file.seekg(0, 0);

	char* buffer = new char[size];//MALLOC new char[static_cast<unsigned int>(size)];
	file.read(buffer, size);
	file.close();
	returnValue->size = size;
	returnValue->data = reinterpret_cast<byte*>(buffer);
	returnValue->filepath = GGeneral::String(relativeFilepath);
	return returnValue;
}

GGeneral::String GFile::loadFileS(GGeneral::String filepath) {
	GGeneral::String s;
	auto file = loadFile(filepath);
	if (file == nullptr)
		return s;

	file->data[file->size] = '\0';
	s.take(file->data, file->size + 1);
	//Don delete the actual data!
	file->data = 0;
	delete file;
	return s;
}

GGeneral::String GFile::getWorkingDirectionary() {
	char buffer[MAX_PATH];
	auto error = GetModuleFileName(NULL, buffer, MAX_PATH);
	if (error == 0) {
		FORMAT_THROW("Error while trying to get the path of the executable. Code: ", GetLastError());
	}
	return GGeneral::String(buffer);
}

GFile::Graphics::ImageType GFile::Graphics::isParseble(GGeneral::String& filepath) {
	auto file = loadFile(filepath);
	return isParseble(file->data);
}

constexpr byte BMPSig[] = { 0x42, 0x4d };
constexpr byte PNGSig[] = { 137, 80, 78, 71, 13, 10, 26, 10 };
GFile::Graphics::ImageType GFile::Graphics::isParseble(byte* data) {
	bool is = true;
	for (size_t i = 0; i < 2; i++) {
		is = is && data[i] == BMPSig[i];
	}
	if (is)
		return GFile::Graphics::ImageType::BITMAP;
	is = true;
	for (size_t i = 0; i < 8; i++) {
		is = is && data[i] == PNGSig[i];
	}
	if (is)
		return GFile::Graphics::ImageType::PORTABLE_NETWORK_GRAPHICS;
	return GFile::Graphics::ImageType::UNKNOWN;
}

GFile::Graphics::Image* doBMP(GFile::File* f) {
	using namespace GFile::Graphics;
	Image* returnValue = new Image;
	returnValue->type = ImageType::BITMAP;
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
	returnValue->data = new byte[readBytes];// static_cast<byte*>(MALLOC(readBytes));
	memcpy(returnValue->data, &f->data[pixelStart], readBytes);
	returnValue->size = readBytes;
	returnValue->hasAlpha = bpp == 32;

	delete f;
	return returnValue;
}

GFile::Graphics::Image* doPNG(GFile::File* f) {
	using namespace GFile::Graphics;
	Image* returnValue = new Image;
	returnValue->type = ImageType::PORTABLE_NETWORK_GRAPHICS;

	unsigned int error;
	LodePNGState state = {};
	error = lodepng_inspect(&returnValue->dim.width, &returnValue->dim.height, &state, f->data, f->size);
	if (error != 0) {
		THROW("An error occurred while parsing a PNG image: '", lodepng_error_text(error), "'");
	}

	//error = lodepng_decode_memory(&returnValue->data, &returnValue->dim.width, &returnValue->dim.height, f->data, f->size, (LodePNGColorType)color, depth);
	error = lodepng_decode(&returnValue->data, &returnValue->dim.width, &returnValue->dim.height, &state, f->data, f->size);

	if (state.info_png.color.colortype == LodePNGColorType::LCT_RGBA || state.info_png.color.colortype == LodePNGColorType::LCT_GREY_ALPHA) {
		returnValue->size = returnValue->dim.width * returnValue->dim.height * 4;
		returnValue->hasAlpha = true;
	}
	else
		returnValue->size = returnValue->dim.width * returnValue->dim.height * 3;

	if (error != 0) {
		THROW("An error occurred while parsing a PNG image: '", lodepng_error_text(error), "'");
	}

	return returnValue;
}

GFile::Graphics::Image* GFile::Graphics::loadImage(GGeneral::String filepath) {
	auto file = loadFile(filepath);
	if (file->data == nullptr) {
		delete file;
		return nullptr;
	}
	auto type = isParseble(file->data);
	switch (type) {
	case GFile::Graphics::ImageType::UNKNOWN:
	{
		delete file;
		THROWW("File is possibly corrupt or not supported");
		return nullptr;
	}
	case GFile::Graphics::ImageType::BITMAP:
	{
		return doBMP(file);
	}
	case GFile::Graphics::ImageType::PORTABLE_NETWORK_GRAPHICS:
	{
		return doPNG(file);
	}
	}
	delete file;
	THROWW("File is possibly corrupt or not supported");
	return nullptr;
}

GFile::Graphics::Cursor* GFile::Graphics::loadCursor(GGeneral::String filepath) {
	auto c = new Cursor;
	c->type = GFile::Graphics::ImageType::CURSOR;
	auto file = LoadCursorFromFile(filepath);
	if (file == nullptr) {
		FORMAT_THROW("An error occurred: ", GetLastError());
		return c;
	}
	c->instance = file;

	return c;
}

GFile::Graphics::Cursor::~Cursor() {
	DestroyIcon((HICON)instance);
}

void GFile::Graphics::Image::flip() { std::reverse(this->data, this->data + this->size); }