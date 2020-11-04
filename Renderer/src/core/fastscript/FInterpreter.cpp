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

void GFScript::Interpreter::op_equalnumarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data) {
	//Get name of the identifier
	auto s = (GGeneral::String*)(identifier->data);
	i->variablesNames.push_back(s);

	//Create variable
	auto v = new Variable(VarType::NUMARRAY, data);

	//and save it somewhere
	i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
}

void GFScript::Interpreter::d_op_equalnumarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data) {
	//Check if var already exist
	auto s = (GGeneral::String*)(identifier->data);
	if (i->variableValues.find(s) == i->variableValues.end()) {
		i->variablesNames.push_back(s);

		//Create variable
		auto v = new Variable(VarType::NUMARRAY, data);

		//and save it somewhere
		i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
	}
	else {
		throw_debug_error(i, identifier, "Identifier already exists!");
	}
}

void GFScript::Interpreter::op_equalstrarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data) {
	//Get name of the identifier
	auto s = (GGeneral::String*)(identifier->data);
	i->variablesNames.push_back(s);

	//Create variable
	auto v = new Variable(VarType::STRINGARRAY, data);

	//and save it somewhere
	i->variableValues.insert(std::pair<GGeneral::String*, Variable*>(s, v));
}

void GFScript::Interpreter::d_op_equalstrarray(Interpreter* i, Token* type, Token* identifier, Token* amount, std::vector<double*>* data) {
	//Check if var already exist
	auto s = (GGeneral::String*)(identifier->data);
	if (i->variableValues.find(s) == i->variableValues.end()) {
		i->variablesNames.push_back(s);

		//Create variable
		auto v = new Variable(VarType::STRINGARRAY, data);

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

void GFScript::Interpreter::fun_set_a(Interpreter* i, Token* var, Token* index, Token* data) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	double in = 0;
	void* d = nullptr;

	if (index->type == TokenID::IDENTIFIER_VAR) {
		in = *(double*)i->variableValues[(GGeneral::String*)index->data]->data;
	}
	else {
		in = *(double*)index->data;
	}

	if (data->type == TokenID::IDENTIFIER_VAR) {
		d = i->variableValues[(GGeneral::String*)data->data]->data;
	}
	else {
		d = data->data;
	}

	switch (v->type) {
	case VarType::NUMARRAY:
	{
		auto vec = (std::vector<double*>*) v->data;
		delete vec->operator[](in);
		double* newdouble = new double;
		*newdouble = *(double*)d;
		vec->operator[](in) = newdouble;
		break;
	}
	case VarType::STRINGARRAY:
	{
		auto vec = (std::vector<GGeneral::String*>*) v->data;
		delete vec->operator[](in);
		GGeneral::String* newdouble = new GGeneral::String;
		*newdouble = GGeneral::String(*(GGeneral::String*)d);
		vec->operator[](in) = newdouble;
		break;
	}
	default:
		THROWW("[Line:", var->line, "]: Couldn't set value because of wrong type: ", data->type);
	}
}

void GFScript::Interpreter::d_fun_set_a(Interpreter* i, Token* var, Token* index, Token* data) {
	auto v = i->variableValues[(GGeneral::String*)var->data];
	double in = 0;
	void* d = nullptr;

	if (index->type == TokenID::IDENTIFIER_VAR) {
		in = *(double*)i->variableValues[(GGeneral::String*)index->data]->data;
	}
	else if (index->type == TokenID::NUMBER_LITERAL) {
		in = *(double*)index->data;
	}
	else {
		throw_debug_error(i, index, "Parameter Index has a wrong parameter");
	}

	if (data->type == TokenID::IDENTIFIER_VAR) {
		d = i->variableValues[(GGeneral::String*)data->data]->data;
		if (i->variableValues[(GGeneral::String*)data->data]->type != v->type) {
			throw_debug_error(i, var, "Identifiers type do not match");
		}
	}
	else {
		d = data->data;
		if (!((data->type == TokenID::NUMBER_LITERAL && v->type == VarType::NUM) || (data->type == TokenID::STRING_LITERAL && v->type == VarType::STRING))) {
			throw_debug_error(i, data, "Identifiers type does not match with the given literal");
		}
	}

	switch (v->type) {
	case VarType::NUMARRAY:
	{
		auto vec = (std::vector<double*>*) v->data;
		if (in >= vec->size())
			throw_debug_error(i, index, "Array out of bounds");
		delete vec->operator[](in);
		double* newdouble = new double;
		*newdouble = *(double*)d;
		vec->operator[](in) = newdouble;
		break;
	}
	case VarType::STRINGARRAY:
	{
		auto vec = (std::vector<GGeneral::String*>*) v->data;
		if (in >= vec->size())
			throw_debug_error(i, index, "Array out of bounds");
		delete vec->operator[](in);
		GGeneral::String* newdouble = new GGeneral::String;
		*newdouble = GGeneral::String(*(GGeneral::String*)d);
		vec->operator[](in) = newdouble;
		break;
	}
	default:
		THROWW("[Line:", var->line, "]: Couldn't set value because of wrong type: ", data->type);
	}
}

void GFScript::Interpreter::fun_add_a(Interpreter* i, Token* var, Token* data) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	void* b = nullptr;
	if (data->type == TokenID::IDENTIFIER_VAR) {
		b = i->variableValues[(GGeneral::String*)data->data]->data;
	}
	else {
		b = data->data;
	}

	if (v->type == VarType::STRINGARRAY) {
		(*(std::vector<GGeneral::String*>*)v->data).push_back(new GGeneral::String(*(GGeneral::String*)b));
	}
	else if (v->type == VarType::NUMARRAY) {
		((std::vector<double*>*)v->data)->push_back(new double(*(double*)b));
	}
	else {
		THROWW("[Line:", var->line, "]: Couldn't set add to array because of wrong type: ", v->type);
	}
}

void GFScript::Interpreter::d_fun_add_a(Interpreter* i, Token* var, Token* data) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	void* b = nullptr;
	if (data->type == TokenID::IDENTIFIER_VAR) {
		b = i->variableValues[(GGeneral::String*)data->data]->data;
		if (i->variableValues[(GGeneral::String*)data->data]->type != v->type)
			throw_debug_error(i, var, "Identifiers type do not match");
	}
	else {
		b = data->data;
		if (!((data->type == TokenID::NUMBER_LITERAL && v->type == VarType::NUM) || (data->type == TokenID::STRING_LITERAL && v->type == VarType::STRING)))
			throw_debug_error(i, data, "Identifiers type does not match with the given literal");
	}

	if (v->type == VarType::STRINGARRAY) {
		(*(std::vector<GGeneral::String*>*)v->data).push_back(new GGeneral::String(*(GGeneral::String*)b));
	}
	else if (v->type == VarType::NUMARRAY) {
		((std::vector<double*>*)v->data)->push_back(new double(*(double*)b));
	}
	else {
		THROWW("[Line:", var->line, "]: Couldn't set add to array because of wrong type: ", v->type);
	}
}

void GFScript::Interpreter::fun_get_a(Interpreter* i, Token* var, Token* index, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	double in = 0;
	if (index->type == TokenID::IDENTIFIER_VAR) {
		in = *(double*)i->variableValues[(GGeneral::String*)index->data]->data;
	}
	else {
		in = *(double*)index->data;
	}

	delete v2->data;

	if (v->type == VarType::NUMARRAY) {
		v2->data = new double(*((std::vector<double*>*)v->data)->operator[](in));
	}
	else if (v->type == VarType::STRINGARRAY)
		v2->data = new GGeneral::String(*((std::vector<GGeneral::String*>*)v->data)->operator[](in));
}

void GFScript::Interpreter::d_fun_get_a(Interpreter* i, Token* var, Token* index, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	double in = 0;
	if (index->type == TokenID::IDENTIFIER_VAR) {
		in = *(double*)i->variableValues[(GGeneral::String*)index->data]->data;
	}
	else {
		in = *(double*)index->data;
	}

	if (v2->type != v->type)
		throw_debug_error(i, var, "Identifiers do not match");

	delete v2->data;

	if (v->type == VarType::NUMARRAY) {
		if (in >= ((std::vector<double*>*)v->data)->size())
			throw_debug_error(i, index, "Array out of bounds");
		v2->data = new double(*((std::vector<double*>*)v->data)->operator[](in));
	}
	else if (v->type == VarType::STRINGARRAY) {
		if (in >= ((std::vector<GGeneral::String*>*)v->data)->size())
			throw_debug_error(i, index, "Array out of bounds");
		v2->data = new GGeneral::String(*((std::vector<GGeneral::String*>*)v->data)->operator[](in));
	}
}

void GFScript::Interpreter::fun_size_a(Interpreter* i, Token* var, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	double s = 0;
	s = ((std::vector<void*>*)v->data)->size();
	delete v2->data;
	v2->data = new double(s);
}

void GFScript::Interpreter::d_fun_size_a(Interpreter* i, Token* var, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	if (v->type != VarType::NUMARRAY && v->type != VarType::STRINGARRAY)
		throw_debug_error(i, var, "Identifier is not an array");

	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	if (v2->type != VarType::NUM)
		throw_debug_error(i, var2, "Identifier is not a numeric Variable");

	double s = 0;
	s = ((std::vector<void*>*)v->data)->size();
	delete v2->data;
	v2->data = new double(s);
}

bool GFScript::Interpreter::prepare(bool prepare) {
	Parser parser(this);
	return parser.createCode(prepare);
}

bool GFScript::Interpreter::execute() {
	for (size_t position = 0; position < functions.size(); position++) {
		if (d_error) {
			THROW("Interpreter needs to stop due to an error.");
			return false;
		}
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
			return false;
		}
		}
	}
	return true;
}