#include "../GRenderer.h"

GScript::Interpreter::Interpreter(GFile::File gprojFile) {
	this->source = GGeneral::String(gprojFile.data);
}

GScript::Interpreter::Interpreter(GGeneral::String source) {
	this->source = GGeneral::String(source);
}

bool GScript::Interpreter::prepare() {
	Lexer l;
	l.setSource(&source);
	if (!l.createTokens()) {
		THROW("An error occurred while trying to parse the given source");
		return false;
	}
	Parser p;
	p.setTokens(&l.tokens);
	if (!p.createAbstractSyntaxTree()) {
		THROW("An error occurred while trying to parse the given source");
		return false;
	}

	return true;
}