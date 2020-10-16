#include "../GRenderer.h"
#include <string>

#define CLEANRETURN()\
for (size_t i = 0; i < tokens->size(); i++) {\
for (size_t j = 0; j < allVarNames.size(); j++) {\
	if (tokens->operator[](i).type == TokenID::IDENTIFIER_VAR)\
		if ((*(GGeneral::String*)tokens->operator[](i).data).compare(*allVarNames[j])) {\
			tokens->operator[](i).data = nullptr; \
			break;\
		}\
}\
}\
delete tokens; \
return nullptr; \

std::vector<GFScript::Token>* GFScript::Tokenizer::createTokens() {
	auto amountChar = source.getSize() + 1;
	std::vector<Token>* tokens = new std::vector<Token>;
	std::vector<GGeneral::String*> allVarNames;
	unsigned int line = 1;

	for (size_t position = 0; position < amountChar; position++) {
		char currentChar = source[position];
		switch (currentChar) {
		case '/':  tokens->push_back(GFScript::Token(GFScript::TokenID::OP_DIVIDE, line));  goto DONE;
		case '-':  tokens->push_back(GFScript::Token(GFScript::TokenID::OP_MINUS, line));	goto DONE;
		case '+':  tokens->push_back(GFScript::Token(GFScript::TokenID::OP_PLUS, line));	goto DONE;
		case '*':  tokens->push_back(GFScript::Token(GFScript::TokenID::OP_MULTIPLY, line)); goto DONE;
		case '(':  tokens->push_back(GFScript::Token(GFScript::TokenID::LPARAN, line));		goto DONE;
		case ')':  tokens->push_back(GFScript::Token(GFScript::TokenID::RPARAN, line));		goto DONE;
		case '=':  tokens->push_back(GFScript::Token(GFScript::TokenID::EQUALS, line));		goto DONE;
		case '\n':  tokens->push_back(GFScript::Token(GFScript::TokenID::BREAK, line));		line++;  goto DONE;
		case '"':
		{
			GGeneral::String* string = new GGeneral::String();
			position++;
			currentChar = source[position];
			while (currentChar != '"' && currentChar != '\0') {
				string->operator<<(currentChar);
				position++;
				currentChar = source[position];
			}
			if (currentChar == '\0') {
				THROW("Unexpectedly reached end of file while trying to parse String \"", *string, "\"");
				delete string;
				CLEANRETURN();
			}
			tokens->push_back(GFScript::Token(GFScript::TokenID::STRING_LITERAL, line, string));
			goto DONE;
		}
		case '#':
		{
			while (currentChar != '\n') {
				position++;
				currentChar = source[position];
			}
		}
		[[fallthrough]];
		case '\r':
		case '\0':
		case ' ': goto DONE;
		}

		if ((currentChar >= 48 && currentChar <= 57) || currentChar == '.') {
			//Do number routine
			GFScript::Token tok;
			GGeneral::String number;
			byte dots = 0;
			for (; position < amountChar; position++) {
				char c = source[position];
				if ((c >= 48 && c <= 57) || c == '.') {
					number << c;
					if (c == '.')
						dots++;
				}
				else {
					break;
				}
			}
			position--;
			if (dots > 1) {
				THROW("[Line:", line, "] Error while trying to parse number: '", number, "'. To many '.'");
				CLEANRETURN();
			}
			else if (dots) {
				if (number.getSize() == 1) {
					THROW("[Line:", line, "] Error while trying to parse number: '", number, "' Expected number but didn't get one :(");
					CLEANRETURN();
				}
			}
			tok.type = GFScript::TokenID::NUMBER_LITERAL;
			auto d = new double;
			*d = std::stod(number.cStr());
			tok.data = d;

			tok.line = line;
			tokens->push_back(GFScript::Token(tok.type, tok.line, tok.data));
			tok.data = nullptr;
			goto DONE;
		}
		else if ((currentChar >= 97 && currentChar <= 122) || (currentChar >= 65 && currentChar <= 90)) {
			//Do functions and vars
			GGeneral::String stringliteral;
			while ((currentChar >= 97 && currentChar <= 122) || (currentChar >= 65 && currentChar <= 90) || (currentChar >= 48 && currentChar <= 57)) {
				stringliteral << source.operator[](position);
				position++;
				currentChar = source.operator[](position);
			}
			position--;
			if (stringliteral.compare("print"))
				tokens->push_back(GFScript::Token(GFScript::TokenID::FUNCTION_PRINT, line, nullptr));
			else if (stringliteral.compare("num"))
				tokens->push_back(GFScript::Token(GFScript::TokenID::NUM_IDENTIFIER, line, nullptr));
			else if (stringliteral.compare("string"))
				tokens->push_back(GFScript::Token(GFScript::TokenID::STRING_IDENTIFIER, line, nullptr));
			else {
				GGeneral::String* s = nullptr;
				for (size_t i = 0; i < allVarNames.size(); i++) {
					auto string = allVarNames[i];
					if (string->compare(stringliteral)) {
						tokens->push_back(GFScript::Token(GFScript::TokenID::IDENTIFIER_VAR, line, string));
						goto LOOP_STOP;
					}
				}
				s = new GGeneral::String(stringliteral);
				tokens->push_back(GFScript::Token(GFScript::TokenID::IDENTIFIER_VAR, line, s));
				allVarNames.push_back(s);
			LOOP_STOP:;
			}
			goto DONE;
		}
		else {
			GGeneral::String error;
			while (currentChar != ' ' && currentChar != '\r' && currentChar != '\n' && position < amountChar) {
				error << currentChar;
				position++;
				currentChar = source[position];
			}
			THROW("[Line:", line, "] Error while trying to parse token: '", error, "'");
			CLEANRETURN();
		}
	DONE:;
	}
	for (size_t i = 0; i < allVarNames.size(); i++) {
		allVarNames[i] = nullptr;
	}
	return tokens;
}