#pragma once

#include "../../GRenderer.h"
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <string>

GRenderer::Primitives::ShaderTypes getTypeFromComment(GGeneral::String s) {
	using namespace GRenderer::Primitives;
	if (s.find("frag") != GGeneral::String::npos || s.find("Frag") != GGeneral::String::npos)
		return ShaderTypes::FRAGMENT_SHADER;
	if (s.find("comp") != GGeneral::String::npos || s.find("Comp") != GGeneral::String::npos)
		return ShaderTypes::COMPUTE_SHADER;
	if (s.find("vert") != GGeneral::String::npos || s.find("Vert") != GGeneral::String::npos)
		return ShaderTypes::VERTEX_SHADER;
	if (s.find("geo") != GGeneral::String::npos || s.find("Geo") != GGeneral::String::npos)
		return ShaderTypes::GEOMETRY_SHADER;
	if (s.find("cont") != GGeneral::String::npos || s.find("Cont") != GGeneral::String::npos)
		return ShaderTypes::TESS_CONTROL_SHADER;
	if (s.find("eval") != GGeneral::String::npos || s.find("Eval") != GGeneral::String::npos)
		return ShaderTypes::TESS_EVALUATION_SHADER;
	return ShaderTypes::UNKOWN_SHADER;
}

GLenum ShaderTypeToGLenum(GRenderer::Primitives::ShaderTypes s) {
	using namespace GRenderer::Primitives;
	switch (s) {
	case ShaderTypes::COMPUTE_SHADER:         return GL_COMPUTE_SHADER;
	case ShaderTypes::VERTEX_SHADER:          return GL_VERTEX_SHADER;
	case ShaderTypes::TESS_CONTROL_SHADER:    return GL_TESS_CONTROL_SHADER;
	case ShaderTypes::TESS_EVALUATION_SHADER: return GL_TESS_EVALUATION_SHADER;
	case ShaderTypes::GEOMETRY_SHADER:        return GL_GEOMETRY_SHADER;
	case ShaderTypes::FRAGMENT_SHADER:        return GL_FRAGMENT_SHADER;
	}
	return -1;
}

GRenderer::Primitives::Shader::Shader(GGeneral::String filepath) {
	if (!loadShader(filepath))
		return;

	if (type == GRenderer::Primitives::ShaderTypes::UNKOWN_SHADER)
		return;

	if (!compileShader())
		return;

	fail = false;
}

GRenderer::Primitives::Shader::Shader(GGeneral::String filepath, ShaderTypes type) : type(type) {
	if (!loadShader(filepath))
		return;

	if (!compileShader())
		return;

	fail = false;
}

GRenderer::Primitives::Shader::~Shader() {
	glDeleteShader(ID);
}

bool GRenderer::Primitives::Shader::loadShader(GGeneral::String filepath) {
	std::ifstream fileIn(filepath);
	if (fileIn.fail()) {
		fail = true;
		return false;
	}
	//TODO FIX THIS...MIGHT BE PERFOMANCE HEAVY
	std::string stringIn;
	while (getline(fileIn, stringIn)) {
		if (stringIn.find("#shader") != std::string::npos) {
			type = getTypeFromComment(stringIn.c_str());
		}
		else {
			sourceCode += stringIn.c_str();
			sourceCode += "\n";
		}
	}
	return true;
}

bool GRenderer::Primitives::Shader::compileShader() {
	if (type == ShaderTypes::UNKOWN_SHADER)
		return false;
	ID = glCreateShader(ShaderTypeToGLenum(type));
	const char* shaderSourceCopy = sourceCode.cStr();
	glShaderSource(ID, 1, &shaderSourceCopy, NULL);
	glCompileShader(ID);

	int isCompiled;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled != 1) {
		fail = true;
		return false;
	}
	return true;
}

GGeneral::String GRenderer::Primitives::Shader::getInfoMessage() {
	int length;
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
	if (length == 0)
		return "";
	char* infolog = new char[length];//static_cast<char*>(MALLOC(sizeof(char) * length));
	glGetShaderInfoLog(ID, length, NULL, infolog);
	return GGeneral::String(infolog);
}

bool GRenderer::Primitives::Shader::failed() const {
	return fail;
}