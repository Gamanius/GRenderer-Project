#pragma once

#include "../../GRenderer.h"
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <string>

GRenderer::Primitives::ShaderTypes getTypeFromComment(std::string s) {
	using namespace GRenderer::Primitives;
	if (s.find("frag") != std::string::npos || s.find("Frag") != std::string::npos)
		return ShaderTypes::FRAGMENT_SHADER;
	if (s.find("comp") != std::string::npos || s.find("Comp") != std::string::npos)
		return ShaderTypes::COMPUTE_SHADER;
	if (s.find("vert") != std::string::npos || s.find("Vert") != std::string::npos)
		return ShaderTypes::VERTEX_SHADER;
	if (s.find("geo") != std::string::npos || s.find("Geo") != std::string::npos)
		return ShaderTypes::GEOMETRY_SHADER;
	if (s.find("cont") != std::string::npos || s.find("Cont") != std::string::npos)
		return ShaderTypes::TESS_CONTROL_SHADER;
	if (s.find("eval") != std::string::npos || s.find("Eval") != std::string::npos)
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

GRenderer::Primitives::Shader::Shader(std::string filepath) {
	if (!loadShader(filepath))
		return;

	if (type == GRenderer::Primitives::ShaderTypes::UNKOWN_SHADER)
		return;

	if (!compileShader())
		return;

	fail = false;
}

GRenderer::Primitives::Shader::Shader(std::string filepath, ShaderTypes type) : type(type) {
	if (!loadShader(filepath))
		return;

	if (!compileShader())
		return;

	fail = false;
}

GRenderer::Primitives::Shader::~Shader() {
	glDeleteShader(ID);
}

bool GRenderer::Primitives::Shader::loadShader(std::string filepath) {
	std::ifstream fileIn(filepath);
	if (fileIn.fail()) {
		fail = true;
		return false;
	}

	std::string stringIn;
	while (getline(fileIn, stringIn)) {
		if (stringIn.find("#shader") != std::string::npos) {
			type = getTypeFromComment(stringIn);
		}
		else
			sourceCode += stringIn + "\n";
	}
	return true;
}

bool GRenderer::Primitives::Shader::compileShader() {
	if (type == ShaderTypes::UNKOWN_SHADER)
		return false;
	ID = glCreateShader(ShaderTypeToGLenum(type));
	const char* shaderSourceCopy = sourceCode.c_str();
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

std::string GRenderer::Primitives::Shader::getInfoMessage() {
	int length;
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
	if (length == 0)
		return "";
	char* infolog = static_cast<char*>(MALLOC(sizeof(char) * length));
	glGetShaderInfoLog(ID, length, NULL, infolog);
	return std::string(infolog);
}

bool GRenderer::Primitives::Shader::failed() const {
	return fail;
}