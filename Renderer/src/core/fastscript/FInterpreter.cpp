#include "GRenderer.h"

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
			THROW("The Interpreter: ", this, " encountered a fatal problem and cannot continue execution");
			return false;
		}
		}
	}
	return true;
}