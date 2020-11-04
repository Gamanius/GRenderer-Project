#include "../GRenderer.h"

#define FETCH()\
if (position >= amountTokens) {\
	THROW("Unexpectedly reached end of file");\
	return false;\
} else \
currentToken = &(instance->tokens->operator[](position));\

bool GFScript::Interpreter::Parser::createCode(bool debug) {
	auto amountTokens = instance->tokens->size();
	for (size_t position = 0; position < amountTokens; position++) {
		auto currentToken = &(instance->tokens->operator[](position));
		switch (currentToken->type) {
			//num identifier = value
		case GFScript::TokenID::NUM_IDENTIFIER:
		{
			auto type = currentToken;

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}
			auto identifier = currentToken;

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::EQUALS) {
				THROW("[Line: ", currentToken->line, "]: Expected a equals symbol");
				return false;
			}

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::NUMBER_LITERAL) {
				THROW("[Line: ", currentToken->line, "]: Expected a number");
				return false;
			}

			instance->functions.push_back((void*)3);
			if (debug)
				instance->functions.push_back((void*)d_op_equalnum);
			else
				instance->functions.push_back((void*)op_equalnum);
			instance->functions.push_back((void*)type);
			instance->functions.push_back((void*)identifier);
			instance->functions.push_back((void*)currentToken);

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Expected a new line");
				return false;
			}

			break;
		}
		case GFScript::TokenID::STRING_IDENTIFIER:
		{
			auto type = currentToken;
			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}
			auto identifier = currentToken;

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::EQUALS) {
				THROW("[Line: ", currentToken->line, "]: Expected a equals symbol");
				return false;
			}

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::STRING_LITERAL) {
				THROW("[Line: ", currentToken->line, "]: Expected a string");
				return false;
			}

			instance->functions.push_back((void*)3);
			if (debug)
				instance->functions.push_back((void*)op_equalstr);
			else
				instance->functions.push_back((void*)d_op_equalstr);
			instance->functions.push_back((void*)type);
			instance->functions.push_back((void*)identifier);
			instance->functions.push_back((void*)currentToken);

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Expected a new line");
				return false;
			}

			break;
		}
		case GFScript::TokenID::NUMARRAY_IDENTIFIER:
		{
			auto type = currentToken;
			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}
			auto identifier = currentToken;

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::EQUALS) {
				THROW("[Line: ", currentToken->line, "]: Expected a equals symbol");
				return false;
			}

			std::vector<double*>* numbers = new std::vector<double*>;

			position++;
			for (; position < amountTokens; position++) {
				FETCH();
				if (currentToken->type != GFScript::TokenID::NUMBER_LITERAL) {
					break;
				}
				numbers->push_back((double*)currentToken->data);
			}

			if (currentToken->type != GFScript::TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Expected a new line");
				return false;
			}

			instance->functions.push_back((void*)4);
			if (debug)
				instance->functions.push_back((void*)d_op_equalnumarray);
			else
				instance->functions.push_back((void*)op_equalnumarray);
			instance->functions.push_back((void*)type);
			instance->functions.push_back((void*)identifier);
			instance->functions.push_back((void*)numbers->size());
			instance->functions.push_back((void*)numbers);
			break;
		}
		case GFScript::TokenID::STRINGARRAY_IDENTIFIER:
		{
			auto type = currentToken;
			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}
			auto identifier = currentToken;

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::EQUALS) {
				THROW("[Line: ", currentToken->line, "]: Expected a equals symbol");
				return false;
			}

			std::vector<GGeneral::String*>* numbers = new std::vector<GGeneral::String*>;

			position++;
			for (; position < amountTokens; position++) {
				FETCH();
				if (currentToken->type != GFScript::TokenID::STRING_LITERAL) {
					break;
				}
				numbers->push_back((GGeneral::String*)currentToken->data);
			}

			if (currentToken->type != GFScript::TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Expected a new line");
				return false;
			}

			instance->functions.push_back((void*)4);
			if (debug)
				instance->functions.push_back((void*)d_op_equalstrarray);
			else
				instance->functions.push_back((void*)op_equalstrarray);
			instance->functions.push_back((void*)type);
			instance->functions.push_back((void*)identifier);
			instance->functions.push_back((void*)numbers->size());
			instance->functions.push_back((void*)numbers);
			break;
		}
		case GFScript::TokenID::IDENTIFIER_VAR:
		{
			auto a = currentToken;
			position++;
			FETCH();

			auto op = currentToken->type;
			position++;
			FETCH();

			auto data = currentToken;

			instance->functions.push_back((void*)2);

			if (debug)
				switch (op) {
				case TokenID::OP_PLUS:       instance->functions.push_back((void*)d_op_plus1); break;
				case TokenID::OP_MINUS:		 instance->functions.push_back((void*)d_op_minus1); break;
				case TokenID::OP_MULTIPLY:	 instance->functions.push_back((void*)d_op_multiply1); break;
				case TokenID::OP_DIVIDE:	 instance->functions.push_back((void*)d_op_divide1); break;
				case TokenID::EQUALS:        instance->functions.push_back((void*)d_op_equalset); break;
				default:
					THROW("[Line: ", currentToken->line, "]: Expected a operator");
					return false;
				}
			else
				switch (op) {
				case TokenID::OP_PLUS:       instance->functions.push_back((void*)op_plus1); break;
				case TokenID::OP_MINUS:		 instance->functions.push_back((void*)op_minus1); break;
				case TokenID::OP_MULTIPLY:	 instance->functions.push_back((void*)op_multiply1); break;
				case TokenID::OP_DIVIDE:	 instance->functions.push_back((void*)op_divide1); break;
				case TokenID::EQUALS:        instance->functions.push_back((void*)op_equalset); break;
				default:
					THROW("[Line: ", currentToken->line, "]: Expected a operator");
					return false;
				}

			instance->functions.push_back((void*)a);
			instance->functions.push_back((void*)data);

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Expected a new line");
				return false;
			}

			break;
		}
		case GFScript::TokenID::FUNCTION_PRINT:
		{
			position++;
			FETCH();
			auto data = currentToken;

			switch (data->type) {
			case TokenID::NUMBER_LITERAL:
			case TokenID::STRING_LITERAL:
			case TokenID::IDENTIFIER_VAR:
			{
				instance->functions.push_back((void*)1);
				if (debug)
					instance->functions.push_back((void*)d_fun_print);
				else
					instance->functions.push_back((void*)fun_print);
				instance->functions.push_back((void*)data);
				break;
			}
			default:
				THROW("[Line: ", currentToken->line, "]: Cannot use the function with the parameter: ", data->type);
				return false;
			}

			position++;
			FETCH();
			if (currentToken->type != GFScript::TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Expected a new line");
				return false;
			}

			break;
		}
		case GFScript::TokenID::FUNCTION_ADDARRAY:
		{
			position++;
			FETCH();
			auto var = currentToken;
			if (var->type != TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}

			position++;
			FETCH();
			auto data = currentToken;
			if (data->type != TokenID::IDENTIFIER_VAR && data->type != TokenID::NUMBER_LITERAL && data->type != TokenID::STRING_LITERAL) {
				THROW("[Line: ", currentToken->line, "]: Expected a valid element to push into the array");
				return false;
			}

			instance->functions.push_back((void*)2);
			if (debug)
				instance->functions.push_back((void*)d_fun_add_a);
			else
				instance->functions.push_back((void*)fun_add_a);
			instance->functions.push_back((void*)var);
			instance->functions.push_back((void*)data);

			break;
		}
		case GFScript::TokenID::FUNCTION_SIZEARRAY:
		{
			position++;
			FETCH();
			auto var = currentToken;
			if (var->type != TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}

			position++;
			FETCH();
			auto var2 = currentToken;
			if (var2->type != TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}

			instance->functions.push_back((void*)2);
			if (debug)
				instance->functions.push_back((void*)d_fun_size_a);
			else
				instance->functions.push_back((void*)fun_size_a);
			instance->functions.push_back((void*)var);
			instance->functions.push_back((void*)var2);

			break;
		}
		case GFScript::TokenID::FUNCTION_SETARRAY:
		{
			position++;
			FETCH();
			auto var = currentToken;
			if (var->type != TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}

			position++;
			FETCH();
			auto index = currentToken;

			position++;
			FETCH();
			auto data = currentToken;

			instance->functions.push_back((void*)3);
			if (debug)
				instance->functions.push_back((void*)d_fun_set_a);
			else
				instance->functions.push_back((void*)fun_set_a);
			instance->functions.push_back((void*)var);
			instance->functions.push_back((void*)index);
			instance->functions.push_back((void*)data);
			break;
		}
		case GFScript::TokenID::FUNCTION_GETARRAY:
		{
			position++;
			FETCH();
			auto var = currentToken;
			if (var->type != TokenID::IDENTIFIER_VAR) {
				THROW("[Line: ", currentToken->line, "]: Expected an identifier");
				return false;
			}

			position++;
			FETCH();
			auto index = currentToken;
			if (index->type != TokenID::IDENTIFIER_VAR && index->type != TokenID::NUMBER_LITERAL) {
				THROW("[Line: ", currentToken->line, "]: Expected a valid index");
				return false;
			}

			position++;
			FETCH();
			auto var2 = currentToken;
			if (var2->type != TokenID::IDENTIFIER_VAR && var2->type != TokenID::NUMBER_LITERAL) {
				THROW("[Line: ", currentToken->line, "]: Expected a valid index");
				return false;
			}

			instance->functions.push_back((void*)3);
			if (debug)
				instance->functions.push_back((void*)d_fun_get_a);
			else
				instance->functions.push_back((void*)fun_get_a);
			instance->functions.push_back((void*)var);
			instance->functions.push_back((void*)index);
			instance->functions.push_back((void*)var2);
			break;
		}
		default:
		{
			if (currentToken->type != TokenID::BREAK) {
				THROW("[Line: ", currentToken->line, "]: Found unexpected token: ", currentToken->type);
				return false;
			}
		}
		}
	}
	return true;
}