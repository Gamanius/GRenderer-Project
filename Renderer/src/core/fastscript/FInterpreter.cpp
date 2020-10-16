#include "../GRenderer.h"

/*
 * Syntax:
 *
 * op_plus1: var + literal -> var will be added with the literal
 * op_minus1: var - literal -> var will be subtracted with the literal
 * op_divide1: var / literal -> var will be divided with the literal
 * op_multiply1: var * literal -> var will be multiplied with the literal
 * op_equal: num/char var = value -> declare var with the given value
 * fun_print: data -> will print the thing into the console
 *
 */

void GFScript::Interpreter::op_plus1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)v->data = ((*(double*)v->data) + (*(double*)num->data));
}

void GFScript::Interpreter::op_minus1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)v->data = ((*(double*)v->data) - (*(double*)num->data));
}

void GFScript::Interpreter::op_multiply1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)v->data = ((*(double*)v->data) * (*(double*)num->data));
}

void GFScript::Interpreter::op_divide1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)v->data = ((*(double*)v->data) / (*(double*)num->data));
}

void GFScript::Interpreter::op_equal1(Interpreter* i, Token* type, Token* identifier, Token* data) {
	auto s = (GGeneral::String*)(identifier->data);
	i->variablesNames.push_back(s);

	GFScript::VarType t = GFScript::VarType::INVALID;
	Variable* var = nullptr;
	switch (type->type) {
	case TokenID::NUM_IDENTIFIER:
	{
		t = VarType::NUM;
		break;
	}
	case TokenID::STRING_IDENTIFIER:
	{
		t = VarType::STRING;
		break;
	}
	default:
		THROWF("Internal error: Found unknown vartype");
	}
	var = new Variable(t, data->data);

	i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, var));
}

void GFScript::Interpreter::fun_print(Interpreter* i, Token* data) {
	switch (data->type) {
	case TokenID::NUMBER_LITERAL: LOG(*(double*)data->data);		   break;
	case TokenID::STRING_LITERAL: LOG(*(GGeneral::String*)data->data);   break;
	case TokenID::IDENTIFIER_VAR:
	{
		auto v = i->variableValues[(GGeneral::String*)data->data];
		switch (v->type) {
		case VarType::NUM:
		{
			LOG(*(double*)v->data);
			break;
		}
		case VarType::STRING:
		{
			LOG(*(GGeneral::String*)v->data);
			break;
		}
		}
		break;
	}
	}
}

#define FETCH()\
if (position >= amountTokens) {\
	THROW("Unexpectedly reached end of file");\
	return false;\
} else \
currentToken = &(instance->tokens->operator[](position));\

bool GFScript::Interpreter::Parser::createCode() {
	auto amountTokens = instance->tokens->size();
	for (size_t position = 0; position < amountTokens; position++) {
		auto currentToken = &(instance->tokens->operator[](position));
		switch (currentToken->type) {
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
			instance->functions.push_back((void*)op_equal1);
			instance->functions.push_back((void*)type);
			instance->functions.push_back((void*)identifier);
			instance->functions.push_back((void*)currentToken);
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
			instance->functions.push_back((void*)op_equal1);
			instance->functions.push_back((void*)type);
			instance->functions.push_back((void*)identifier);
			instance->functions.push_back((void*)currentToken);
			break;
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

			switch (op) {
			case TokenID::OP_PLUS:       instance->functions.push_back((void*)op_plus1); break;
			case TokenID::OP_MINUS:		 instance->functions.push_back((void*)op_minus1); break;
			case TokenID::OP_MULTIPLY:	 instance->functions.push_back((void*)op_multiply1); break;
			case TokenID::OP_DIVIDE:	 instance->functions.push_back((void*)op_divide1); break;
			default:
				THROW("[Line: ", currentToken->line, "]: Expected a operator");
				return false;
			}

			instance->functions.push_back((void*)a);
			instance->functions.push_back((void*)data);
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
				instance->functions.push_back((void*)fun_print);
				instance->functions.push_back((void*)data);
				break;
			}
			default:
				THROW("[Line: ", currentToken->line, "]: Cannot use the function with the parameter: ", data->type);
				return false;
			}
		}
		}
	}
	return true;
}

bool GFScript::Interpreter::prepare() {
	Parser parser(this);
	return parser.createCode();
}

void GFScript::Interpreter::execute() {
	for (size_t position = 0; position < functions.size(); position++) {
		auto size = (int)functions[position];
		position++;
		switch (size) {
		case 0:
		{
			auto fun = (void(*)(void*))functions[position];
			fun(this);
			break;
		}
		case 1:
		{
			auto fun = (void(*)(void*, void*))functions[position];
			fun(this, functions[position + 1]);
			position++;
			break;
		}
		case 2:
		{
			auto fun = (void(*)(void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2]);
			position += 2;
			break;
		}
		case 3:
		{
			auto fun = (void(*)(void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3]);
			position += 3;
			break;
		}
		case 4:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4]);
			position += 4;
			break;
		}
		case 5:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4], functions[position + 5]);
			position += 4;
			break;
		}
		case 6:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4], functions[position + 5], functions[position + 6]);
			position += 4;
			break;
		}
		case 7:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4], functions[position + 5], functions[position + 6], functions[position + 7]);
			position += 4;
			break;
		}
		case 8:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4], functions[position + 5], functions[position + 6], functions[position + 7], functions[position + 8]);
			position += 4;
			break;
		}
		case 9:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4], functions[position + 5], functions[position + 6], functions[position + 7], functions[position + 8], functions[position + 9]);
			position += 4;
			break;
		}
		case 10:
		{
			auto fun = (void(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*))functions[position];
			fun(this, functions[position + 1], functions[position + 2], functions[position + 3], functions[position + 4], functions[position + 5], functions[position + 6], functions[position + 7], functions[position + 8], functions[position + 9], functions[position + 10]);
			position += 10;
			break;
		}
		default:
		{
			THROWF("The Interpreter: ", this, " encountered a fatal problem and needs to be terminated");
			return;
		}
		}
	}
}