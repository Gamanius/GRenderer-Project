#include "../GRenderer.h"
#include <gl/glew.h>

GRenderer::ShaderProgram::ShaderProgram(std::initializer_list<Primitives::Shader*> shaders) {
	for (auto s : shaders)
		shaderIDs.push_back(&s->ID);
}

GRenderer::ShaderProgram::~ShaderProgram() {
	glDeleteProgram(ID);
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

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::mat2<float>& mat) {
	glUniformMatrix2fv(getUniformLocation(name), 1, true, mat.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::mat3<float>& mat) {
	glUniformMatrix3fv(getUniformLocation(name), 1, true, mat.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::mat4<float>& mat) {
	glUniformMatrix4fv(getUniformLocation(name), 1, true, mat.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, float ui) {
	glUniform1f(getUniformLocation(name), ui);
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec2<float>& ui) {
	glUniform2fv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec3<float>& ui) {
	glUniform3fv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec4<float>& ui) {
	glUniform4fv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, int ui) {
	glUniform1i(getUniformLocation(name), ui);
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec2<int>& ui) {
	glUniform2iv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec3<int>& ui) {
	glUniform3iv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec4<int>& ui) {
	glUniform4iv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, unsigned int ui) {
	glUniform1ui(getUniformLocation(name), ui);
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec2<unsigned int>& ui) {
	glUniform2uiv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec3<unsigned int>& ui) {
	glUniform3uiv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::set(const GGeneral::String& name, GMath::vec4<unsigned int>& ui) {
	glUniform4uiv(getUniformLocation(name), 1, ui.mem());
}

void GRenderer::ShaderProgram::bind() {
	glUseProgram(ID);
}

void GRenderer::ShaderProgram::unbind() {
	glUseProgram(0);
}

GGeneral::String GRenderer::ShaderProgram::getInfoMessage() {
	int length;
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length);
	if (length == 0)
		return "";
	char* infolog = new char[length];//static_cast<char*>(MALLOC(sizeof(char) * length));
	glGetProgramInfoLog(ID, length, NULL, infolog);
	return GGeneral::String(infolog);
}

const unsigned int GRenderer::ShaderProgram::getUniformLocation(const GGeneral::String& name) const {
	return glGetUniformLocation(ID, name.cStr());
}