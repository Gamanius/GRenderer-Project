#include "GRenderer.h"

#define throw_debug_error(interpreter, tok, error) { interpreter->d_error = true;\
THROW("[Line: ", tok->line, "]: ", error);\
return;}\

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

void GFScript::Interpreter::fun_set_array(Interpreter* i, Token* var, Token* index, Token* data) {
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

void GFScript::Interpreter::d_fun_set_array(Interpreter* i, Token* var, Token* index, Token* data) {
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
		if (i->variableValues[(GGeneral::String*)data->data]->type == VarType::NUM) {
			if (v->type != VarType::NUMARRAY)
				throw_debug_error(i, var, "Identifiers type do not match");
		}
		else if (i->variableValues[(GGeneral::String*)data->data]->type == VarType::STRING)
			if (v->type != VarType::STRINGARRAY)
				throw_debug_error(i, var, "Identifiers type do not match");
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

void GFScript::Interpreter::fun_add_array(Interpreter* i, Token* var, Token* data) {
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

void GFScript::Interpreter::d_fun_add_array(Interpreter* i, Token* var, Token* data) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	void* b = nullptr;
	if (data->type == TokenID::IDENTIFIER_VAR) {
		b = i->variableValues[(GGeneral::String*)data->data]->data;
		if (i->variableValues[(GGeneral::String*)data->data]->type == VarType::NUM) {
			if (v->type != VarType::NUMARRAY)
				throw_debug_error(i, var, "Identifiers type do not match");
		}
		else if (i->variableValues[(GGeneral::String*)data->data]->type == VarType::STRING)
			if (v->type != VarType::STRINGARRAY)
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

void GFScript::Interpreter::fun_get_array(Interpreter* i, Token* var, Token* index, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	double in = 0;

	//first check the index
	if (index->type == TokenID::IDENTIFIER_VAR) {
		in = *(double*)i->variableValues[(GGeneral::String*)index->data]->data;
	}
	else {
		in = *(double*)index->data;
	}


	if (v->type == VarType::NUMARRAY) {
		//overwrite the value of v2
		delete v2->data;
		v2->data = new double(*((std::vector<double*>*)v->data)->operator[](in));
	}
	else if (v->type == VarType::STRINGARRAY) {
		//overwrite the value of v2
		delete v2->data;
		v2->data = new GGeneral::String(*((std::vector<GGeneral::String*>*)v->data)->operator[](in));
	}
	else {
		throw_debug_error(i, var2, "Wrong variable type");
	}
}

void GFScript::Interpreter::d_fun_get_array(Interpreter* i, Token* var, Token* index, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	double in = 0;

	if (index->type == TokenID::IDENTIFIER_VAR) {
		in = *(double*)i->variableValues[(GGeneral::String*)index->data]->data;
	}
	else {
		in = *(double*)index->data;
	}

	if (v2->type == VarType::NUM) {
		if (v->type != VarType::NUMARRAY)
			throw_debug_error(i, var, "Identifiers type do not match");
	}
	else if (v2->type == VarType::STRING)
		if (v->type != VarType::STRINGARRAY)
			throw_debug_error(i, var, "Identifiers type do not match");

	if (v->type == VarType::NUMARRAY) {
		if (in >= ((std::vector<double*>*)v->data)->size())
			throw_debug_error(i, index, "Array out of bounds");
		delete v2->data;
		v2->data = new double(*((std::vector<double*>*)v->data)->operator[](in));
	}
	else if (v->type == VarType::STRINGARRAY) {
		if (in >= ((std::vector<GGeneral::String*>*)v->data)->size())
			throw_debug_error(i, index, "Array out of bounds");
		delete v2->data;
		v2->data = new GGeneral::String(*((std::vector<GGeneral::String*>*)v->data)->operator[](in));
	}
	else {
		throw_debug_error(i, var2, "Wrong variable type");
	}
}

void GFScript::Interpreter::fun_size_array(Interpreter* i, Token* var, Token* var2) {
	Variable* v = i->variableValues[(GGeneral::String*)var->data];
	Variable* v2 = i->variableValues[(GGeneral::String*)var2->data];
	double s = 0;
	s = ((std::vector<void*>*)v->data)->size();
	delete v2->data;
	v2->data = new double(s);
}

void GFScript::Interpreter::d_fun_size_array(Interpreter* i, Token* var, Token* var2) {
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