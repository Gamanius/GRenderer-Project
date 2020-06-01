#include "../GRenderer.h"
#include <gl/glew.h>

GRenderer::ShaderProgram::ShaderProgram(std::initializer_list<Primitives::Shader*> shaders) {
	for (auto s : shaders)
		shaderIDs.push_back(&s->ID);
}

bool GRenderer::ShaderProgram::link() {
	ID = glCreateProgram();
	bind();
	for (auto s : shaderIDs) {
		glAttachShader(ID, *s);
	}

	glLinkProgram(ID);

	int isLinked;
	glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);
	return isLinked;
}

void GRenderer::ShaderProgram::bind() {
	glUseProgram(ID);
}

void GRenderer::ShaderProgram::unbind() {
	glUseProgram(0);
}

std::string GRenderer::ShaderProgram::getInfoMessage() {
	int length;
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length);
	if (length == 0)
		return "";
	char* infolog = (char*)malloc(sizeof(char) * length);
	glGetProgramInfoLog(ID, length, NULL, infolog);
	return std::string(infolog);
}