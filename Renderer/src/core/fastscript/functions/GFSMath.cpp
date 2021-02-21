#include "GRenderer.h"

#define throw_debug_error(interpreter, tok, error) { interpreter->d_error = true;\
THROW("[Line: ", tok->line, "]: ", error);\
return;}\

void GFScript::Interpreter::op_plus1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		*(double*)v->data = ((*(double*)v->data) + (*(double*)b->data));
	}
	else
		*(double*)v->data = ((*(double*)v->data) + (*(double*)num->data));
}

void GFScript::Interpreter::d_op_plus1(Interpreter* i, Token* var, Token* num) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		if (b->type != VarType::NUM) {
			throw_debug_error(i, num, "The given Identifier is not a number");
		}
		*(double*)v->data = ((*(double*)v->data) + (*(double*)b->data));
	}
	else if (num->type == TokenID::NUMBER_LITERAL) {
		*(double*)v->data = ((*(double*)v->data) + (*(double*)num->data));
	}
	else {
		throw_debug_error(i, num, "Found a invalid symbol");
	}
}

void GFScript::Interpreter::op_minus1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		*(double*)v->data = ((*(double*)v->data) - (*(double*)b->data));
	}
	else
		*(double*)v->data = ((*(double*)v->data) - (*(double*)num->data));
}

void GFScript::Interpreter::d_op_minus1(Interpreter* i, Token* var, Token* num) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		if (b->type != VarType::NUM) {
			throw_debug_error(i, num, "The given Identifier is not a number");
		}
		*(double*)v->data = ((*(double*)v->data) - (*(double*)b->data));
	}
	else if (num->type == TokenID::NUMBER_LITERAL) {
		*(double*)v->data = ((*(double*)v->data) - (*(double*)num->data));
	}
	else {
		throw_debug_error(i, num, "Found a invalid symbol");
	}
}

void GFScript::Interpreter::op_multiply1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		*(double*)v->data = ((*(double*)v->data) * (*(double*)b->data));
	}
	else
		*(double*)v->data = ((*(double*)v->data) * (*(double*)num->data));
}

void GFScript::Interpreter::d_op_multiply1(Interpreter* i, Token* var, Token* num) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		if (b->type != VarType::NUM) {
			throw_debug_error(i, num, "The given Identifier is not a number");
		}
		*(double*)v->data = ((*(double*)v->data) * (*(double*)b->data));
	}
	else if (num->type == TokenID::NUMBER_LITERAL) {
		*(double*)v->data = ((*(double*)v->data) * (*(double*)num->data));
	}
	else {
		throw_debug_error(i, num, "Found a invalid symbol");
	}
}

void GFScript::Interpreter::op_divide1(Interpreter* i, Token* var, Token* num) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		*(double*)v->data = ((*(double*)v->data) / (*(double*)b->data));
	}
	else
		*(double*)v->data = ((*(double*)v->data) / (*(double*)num->data));
}

void GFScript::Interpreter::d_op_divide1(Interpreter* i, Token* var, Token* num) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	if (num->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)num->data];
		if (b->type != VarType::NUM) {
			throw_debug_error(i, num, "The given Identifier is not a number");
		}
		*(double*)v->data = ((*(double*)v->data) / (*(double*)b->data));
	}
	else if (num->type == TokenID::NUMBER_LITERAL) {
		*(double*)v->data = ((*(double*)v->data) / (*(double*)num->data));
	}
	else {
		throw_debug_error(i, num, "Found a invalid symbol");
	}
}

void GFScript::Interpreter::op_equalnum(Interpreter* i, Token* type, Token* identifier, Token* data) {
	//Get name of the identifier
	auto s = (GGeneral::String*)(identifier->data);
	i->variablesNames.push_back(s);

	//Create variable
	auto v = new Variable(VarType::NUM, data->data);

	//and save it somewhere
	i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
}

void GFScript::Interpreter::d_op_equalnum(Interpreter* i, Token* type, Token* identifier, Token* data) {
	//Check if var already exist
	auto s = (GGeneral::String*)(identifier->data);
	if (i->variableValues.find(s) == i->variableValues.end()) {
		i->variablesNames.push_back(s);

		//Create variable
		auto v = new Variable(VarType::NUM, data->data);

		//and save it somewhere
		i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
	}
	else {
		throw_debug_error(i, identifier, "Identifier already exists!");
	}
}

void GFScript::Interpreter::op_equalstr(Interpreter* i, Token* type, Token* identifier, Token* data) {
	//Get name of the identifier
	auto s = (GGeneral::String*)(identifier->data);
	i->variablesNames.push_back(s);

	//Create variable
	auto v = new Variable(VarType::STRING, data->data);

	//and save it somewhere
	i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
}

void GFScript::Interpreter::d_op_equalstr(Interpreter* i, Token* type, Token* identifier, Token* data) {
	//Check if var already exist
	auto s = (GGeneral::String*)(identifier->data);
	if (i->variableValues.find(s) == i->variableValues.end()) {
		i->variablesNames.push_back(s);

		//Create variable
		auto v = new Variable(VarType::STRING, data->data);

		//and save it somewhere
		i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
	}
	else {
		throw_debug_error(i, identifier, "Identifier already exists!");
	}
}

void GFScript::Interpreter::op_equalset(Interpreter* i, Token* identifier, Token* data) {
	auto v = i->variableValues[(GGeneral::String*)identifier->data];
	if (data->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)data->data];
		switch (b->type) {
		case VarType::NUM:		(*(double*)v->data) = *(double*)b->data; break;
		case VarType::NUMARRAY:
		{
			delete v->data;
			v->data = new std::vector<double*>(*(std::vector<double*>*)b->data);
			break;
		}
		case VarType::STRING:
		{
			delete v->data;
			(*(GGeneral::String*)v->data) = GGeneral::String(*(GGeneral::String*)b->data);
			break;
		}
		case VarType::STRINGARRAY:
		{
			delete v->data;
			v->data = new  std::vector<GGeneral::String*>(*(std::vector<GGeneral::String*>*)b->data);
			break;
		}
		default:
			THROWW("[Line:", identifier->line, "]: Couldn't set value because of wrong type: ", data->type);
		}
	}
	else {
		switch (data->type) {
		case TokenID::NUMBER_LITERAL: (*(double*)v->data) = *(double*)data->data; break;
		case TokenID::STRING_LITERAL: /*Need to delete the previous string before copying the other one*/ delete v->data;  (*(GGeneral::String*)v->data) = GGeneral::String(*(GGeneral::String*)data->data); break;
		default:
			THROWW("[Line:", identifier->line, "]: Couldn't set value because of wrong type: ", data->type);
		}
	}
}

void GFScript::Interpreter::d_op_equalset(Interpreter* i, Token* identifier, Token* data) {
	auto v = i->variableValues[(GGeneral::String*)identifier->data];
	if (data->type == TokenID::IDENTIFIER_VAR) {
		auto b = i->variableValues[(GGeneral::String*)data->data];
		if (b->type != v->type) {
			throw_debug_error(i, identifier, "The Identifiers do not have the same type.");
			return;
		}
		switch (v->type) {
		case VarType::NUM:
		{
			(*(double*)v->data) = *(double*)b->data; break;
		}
		case VarType::NUMARRAY:
		{
			delete v->data;
			v->data = new std::vector<double*>(*(std::vector<double*>*)b->data);
			break;
		}
		case VarType::STRING:
		{
			delete v->data;
			(*(GGeneral::String*)v->data) = GGeneral::String(*(GGeneral::String*)b->data);
			break;
		}
		case VarType::STRINGARRAY:
		{
			delete v->data;
			v->data = new  std::vector<GGeneral::String*>(*(std::vector<GGeneral::String*>*)b->data);
			break;
		}
		default:
			THROWW("[Line:", identifier->line, "]: Couldn't set value because of wrong type: ", data->type);
		}
	}
	else {
		switch (data->type) {
		case TokenID::NUMBER_LITERAL: (*(double*)v->data) = *(double*)data->data; break;
		case TokenID::STRING_LITERAL: /*Need to delete the previous string before copying the other one*/ delete v->data;  (*(GGeneral::String*)v->data) = GGeneral::String(*(GGeneral::String*)data->data); break;
		default:
			THROWW("[Line:", identifier->line, "]: Couldn't set value because of wrong type: ", data->type);
		}
	}
}

void GFScript::Interpreter::fun_abs(Interpreter* i, Token* var) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)(v->data) = std::abs(*(double*)(v->data));
}

void GFScript::Interpreter::d_fun_abs(Interpreter* i, Token* var) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	//Check if number
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	*(double*)(v->data) = std::abs(*(double*)(v->data));
}

void GFScript::Interpreter::fun_ceil(Interpreter* i, Token* var) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)(v->data) = std::ceil(*(double*)(v->data));
}

void GFScript::Interpreter::d_fun_ceil(Interpreter* i, Token* var) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	//Check if number
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	*(double*)(v->data) = std::ceil(*(double*)(v->data));
}

void GFScript::Interpreter::fun_floor(Interpreter* i, Token* var) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)(v->data) = std::floor(*(double*)(v->data));
}

void GFScript::Interpreter::d_fun_floor(Interpreter* i, Token* var) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	//Check if number
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	*(double*)(v->data) = std::floor(*(double*)(v->data));
}

void GFScript::Interpreter::fun_round(Interpreter* i, Token* var) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	*(double*)(v->data) = std::round(*(double*)(v->data));
}

void GFScript::Interpreter::d_fun_round(Interpreter* i, Token* var) {
	//Check if a var is given
	if (var->type != TokenID::IDENTIFIER_VAR) {
		//It must be a variable or else it just doest make sense. Usually this shouldn't be a problem due to the parser
		throw_debug_error(i, var, "The given Identifier is not a variable");
	}

	//Check if number
	auto v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUM) {
		throw_debug_error(i, var, "The given Identifier is not a number");
	}

	*(double*)(v->data) = std::round(*(double*)(v->data));
}