#include "../GRenderer.h"
#include <string>

GScript::Interpreter::Lexer::Lexer(const GGeneral::String* source) {
	this->source = source;
	if (!createTokens())
		THROW("Couldn't create tokens from the source");
}

void GScript::Interpreter::Lexer::setSource(const GGeneral::String* source) {
	tokens.clear();
	position = 0;
	this->source = source;
}

bool GScript::Interpreter::Lexer::createTokens() {
	unsigned int line = 1;
	for (position = 0; position < source->getSize(); position++) {
		char c = source->operator[](position);
		if ((c >= 48 && c <= 57) || c == '.') {
			//Do number routine
			GScript::Token tok;
			GGeneral::String number;
			number << c;
			byte dots = 0;
			if (c == '.')
				dots++;
			position++;
			for (; position < source->getSize(); position++) {
				c = source->operator[](position);
				if ((c >= 48 && c <= 57) || c == '.') {
					number << c;
					if (c == '.')
						dots++;
				}
				else {
					break;
				}
			}
			if (dots > 1) {
				THROW("[Line:", line, "] Error while trying to parse number: '", number, "'. To many '.'");
				return false;
			}
			else if (dots) {
				tok.token = GScript::TokenID::DOUBLE_LITERAL;
				tok.dvalue = std::stod(number.cStr());
			}
			else {
				tok.token = GScript::TokenID::INTEGER_LITERAL;
				tok.ivalue = std::stoi(number.cStr());
			}
			tok.svalue = std::move(number);
			tok.line = line;
			tokens.push_back(tok);
		}
		switch (c) {
		case '/':  tokens.push_back(GScript::Token(GScript::TokenID::OP_DIVIDE, 0, line, "/"));    break;
		case '-':  tokens.push_back(GScript::Token(GScript::TokenID::OP_MINUS, 0, line, "-"));		break;
		case '+':  tokens.push_back(GScript::Token(GScript::TokenID::OP_PLUS, 0, line, "+"));		break;
		case '*':  tokens.push_back(GScript::Token(GScript::TokenID::OP_MULTIPLY, 0, line, "*"));	break;
		case ';':  tokens.push_back(GScript::Token(GScript::TokenID::BREAK, 0, line, ";"));		break;
		case '(':  tokens.push_back(GScript::Token(GScript::TokenID::LPARAN, 0, line, "("));		break;
		case ')':  tokens.push_back(GScript::Token(GScript::TokenID::RPARAN, 0, line, ")"));		break;
		case '\n': line++; break;
		}
	}
	return true;
}