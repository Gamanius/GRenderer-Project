#include "GRenderer.h"

#define throw_debug_error(interpreter, tok, error) { interpreter->d_error = true;\
THROW("[Line: ", tok->line, "]: ", error);\
return;}\

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
		case VarType::NUMARRAY:
		{
			std::vector<double*>* a = (std::vector<double*>*)v->data;
			GGeneral::String s;
			for (size_t i = 0; i < a->size() - 1; i++) {
				s << *a->operator[](i) << ", ";
			}
			s << *a->operator[](a->size() - 1);
			LOG(s);
			break;
		}
		case VarType::STRINGARRAY:
		{
			std::vector<GGeneral::String*>* a = (std::vector<GGeneral::String*>*)v->data;
			GGeneral::String s;
			for (size_t i = 0; i < a->size() - 1; i++) {
				s << *a->operator[](i) << ", ";
			}
			s << *a->operator[](a->size() - 1);
			LOG(s);
			break;
		}
		}
		break;
	}
	}
}

void GFScript::Interpreter::d_fun_print(Interpreter* i, Token* data) {
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
		case VarType::NUMARRAY:
		{
			std::vector<double*>* a = (std::vector<double*>*)v->data;
			GGeneral::String s;
			for (size_t i = 0; i < a->size() - 1; i++) {
				s << *a->operator[](i) << ", ";
			}
			s << *a->operator[](a->size() - 1);
			LOG(s);
			break;
		}
		case VarType::STRINGARRAY:
		{
			std::vector<GGeneral::String*>* a = (std::vector<GGeneral::String*>*)v->data;
			GGeneral::String s;
			for (size_t i = 0; i < a->size() - 1; i++) {
				s << *a->operator[](i) << ", ";
			}
			s << *a->operator[](a->size() - 1);
			LOG(s);
			break;
		}
		}
		break;
	}
	default:
		throw_debug_error(i, data, "Couldn't print given symbol");
	}
}