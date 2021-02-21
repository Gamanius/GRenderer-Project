#include "GRenderer.h"
#include <array>

#define FETCH()\
if (position >= amountTokens) {\
	THROW("Unexpectedly reached end of file");\
	return false;\
} else \
currentToken = &(instance->tokens->operator[](position));\

#define DEBUGIFY(fun) d_##fun

/**
 * yesss
 * @param fun the function to add
 * @param debugfun the debug function to add
 * @param in the tokenids to match
 * @param instance the interpreter instance
 * @param tokens the tokens available
 * @param iterator the iterator. in other words where to start in the tokens
 * @param output the output array to add the tokens and functions
 * @param debug set to true to add the debug function
 * @param ignore will not add the token of the index given in the vector
 * @param multi if set to true will check the last token multiple times
 * @param printErrors if set to true it will print out errors
 * @return true 
 * @return false 
 */
bool push(void* fun, void* debugfun, std::vector<std::vector<GFScript::TokenID>> in, GFScript::Interpreter* instance, std::vector<GFScript::Token>* tokens, size_t* iterator, std::vector<void*>* output, bool debug, std::vector<size_t> ignore, bool multi = false, bool printErrors = true) {
	//Check if the following tokens math the given token that were in the "in" parameter
	size_t startOfIterator = *iterator;
	GFScript::Token currentToken = tokens->at(*iterator);
	bool secondLoopSuccessfull = false;
	for (size_t i = 0; i < in.size(); i++) {
		if (multi && i == in.size() - 1)
			break;
		for (size_t j = 0; j < in[i].size(); j++) {
			if(in[i][j] == currentToken.type) {
				secondLoopSuccessfull = true;
				break;
			}
		}
		if (secondLoopSuccessfull) {
			(*iterator)++;
			//EOF check
			if(*iterator >= tokens->size()) {
				THROW("Unexpectedly reached end of file"); 
				return false; 
			}
			secondLoopSuccessfull = false;
			currentToken = tokens->at(*iterator);
			continue;
		} 
		//Print error if there are no matches and exit
		GGeneral::String errorString;
		for (size_t j = 0; j < in[i].size(); j++) {
			errorString << in[i][j];
		}
		if(printErrors)
			THROW("[Line: ", currentToken.line, "]: Expected ", errorString);
		//reset the iterator
		*iterator = startOfIterator;
		return false;
	}
	
	//Add the amount of elements and the function
	output->push_back(0);
	auto startOffset = output->size() - 1;
	if (debug)
		output->push_back(debugfun);
	else
		output->push_back(fun);

	for (size_t j = startOfIterator; j < *iterator; j++) {
		for (size_t i = 0; i < ignore.size(); i++) {
			if (j - startOfIterator == ignore[i])
				goto SKIP;
		}
		output->push_back((void*)&tokens->at(j));
	SKIP:;
	}
	
	

	//loop di loop
	if (multi) {
		std::vector<double*>* vec = new std::vector<double*>;
		output->push_back(0);
		auto multiStartOffset = output->size() - 1;
		for (; *iterator < tokens->size(); (*iterator)++) {
			if (in[in.size() - 1][0] == tokens->at(*iterator).type) {
				vec->push_back((double*)tokens->at(*iterator).data);
			}
			else
				break;
		}
		output->push_back((void*)vec);
		output->at(multiStartOffset) = (void*)vec->size();
	} 

	output->at(startOffset) = (void*)(output->size() - startOffset - 2);


	currentToken = tokens->at(*iterator);
	if (currentToken.type != GFScript::TokenID::BREAK) {
		THROW("[Line: ", currentToken.line, "]: Expected a new line");
		return false;
	}

	return true;
}

bool GFScript::Interpreter::Parser::createCode(bool debug) {
	auto amountTokens = instance->tokens->size();

	for (size_t position = 0; position < amountTokens; position++) {
		auto currentToken = &(instance->tokens->operator[](position));
		switch (currentToken->type) {
			//num identifier = value
		case GFScript::TokenID::NUM_IDENTIFIER:
		{
			if (push((void*)op_equalnum, (void*)DEBUGIFY(op_equalnum), {
				{ GFScript::TokenID::NUM_IDENTIFIER },
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::EQUALS },
				{ GFScript::TokenID::NUMBER_LITERAL },
				}, instance, instance->tokens, &position, &instance->functions, debug, {2}) == false) {
				return false;
			}

			break;
		}
		case GFScript::TokenID::STRING_IDENTIFIER:
		{
			if (push((void*)op_equalstr, (void*)DEBUGIFY(op_equalstr), {
				{ GFScript::TokenID::STRING_IDENTIFIER },
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::EQUALS },
				{ GFScript::TokenID::STRING_LITERAL },
				}, instance, instance->tokens, &position, &instance->functions, debug, {2}) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::NUMARRAY_IDENTIFIER:
		{
			if (push((void*)op_equalnumarray, (void*)DEBUGIFY(op_equalnumarray), {
				{ GFScript::TokenID::NUMARRAY_IDENTIFIER },
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::EQUALS },
				{ GFScript::TokenID::NUMBER_LITERAL },
				}, instance, instance->tokens, &position, &instance->functions, debug, {2}, true) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::STRINGARRAY_IDENTIFIER:
		{
			if (push((void*)op_equalstrarray, (void*)DEBUGIFY(op_equalstrarray), {
				{ GFScript::TokenID::STRINGARRAY_IDENTIFIER },
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::EQUALS },
				{ GFScript::TokenID::STRING_LITERAL },
				}, instance, instance->tokens, &position, &instance->functions, debug, {2}, true) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::IDENTIFIER_VAR:
		{
			if (push((void*)op_plus1, (void*)DEBUGIFY(op_plus1), {
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::OP_PLUS },
				{ GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::IDENTIFIER_VAR },
				}, instance, instance->tokens, &position, &instance->functions, debug, {1}, false, false)) {
				break;
			} 
			else if (push((void*)op_minus1, (void*)DEBUGIFY(op_minus1), {
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::OP_MINUS },
				{ GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::IDENTIFIER_VAR },
				}, instance, instance->tokens, &position, &instance->functions, debug, {1}, false, false)) {
				break;
			}
			else if (push((void*)op_multiply1, (void*)DEBUGIFY(op_multiply1), {
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::OP_MULTIPLY },
				{ GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::IDENTIFIER_VAR },
				}, instance, instance->tokens, &position, &instance->functions, debug, {1}, false, false)) {
				break;
			}
			else if (push((void*)op_divide1, (void*)DEBUGIFY(op_divide1), {
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::OP_DIVIDE },
				{ GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::IDENTIFIER_VAR },
				}, instance, instance->tokens, &position, &instance->functions, debug, {1}, false, false)) {
				break;
			}
			else if (push((void*)op_equalset, (void*)DEBUGIFY(op_equalset), {
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::EQUALS },
				{ GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::IDENTIFIER_VAR },
				}, instance, instance->tokens, &position, &instance->functions, debug, {1}, false, false)) {
				break;
			}
			return false;
		}
		case GFScript::TokenID::FUNCTION_PRINT:
		{
			if (push((void*)fun_print, (void*)DEBUGIFY(fun_print), {
				{ GFScript::TokenID::FUNCTION_PRINT },
				{ GFScript::TokenID::NUMBER_LITERAL, TokenID::STRING_LITERAL, TokenID::IDENTIFIER_VAR },
				}, instance, instance->tokens, &position, &instance->functions, debug, {0}) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::FUNCTION_ADDARRAY:
		{
			if (push((void*)fun_add_array, (void*)DEBUGIFY(fun_add_array), {
				{ GFScript::TokenID::FUNCTION_ADDARRAY },
				{ GFScript::TokenID::IDENTIFIER_VAR},
				{ GFScript::TokenID::IDENTIFIER_VAR, GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::STRING_LITERAL }
				}, instance, instance->tokens, &position, &instance->functions, debug, {0}) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::FUNCTION_SIZEARRAY:
		{
			if (push((void*)fun_size_array, (void*)DEBUGIFY(fun_size_array), {
				{ GFScript::TokenID::FUNCTION_SIZEARRAY },
				{ GFScript::TokenID::IDENTIFIER_VAR},
				{ GFScript::TokenID::IDENTIFIER_VAR}
				}, instance, instance->tokens, &position, &instance->functions, debug, {0}) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::FUNCTION_SETARRAY:
		{
			if (push((void*)fun_set_array, (void*)DEBUGIFY(fun_set_array), {
				{ GFScript::TokenID::FUNCTION_SETARRAY },
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::IDENTIFIER_VAR, GFScript::TokenID::NUMBER_LITERAL },
				{ GFScript::TokenID::IDENTIFIER_VAR, GFScript::TokenID::NUMBER_LITERAL, GFScript::TokenID::STRING_LITERAL }
				}, instance, instance->tokens, &position, &instance->functions, debug, {0}) == false) {
				return false;
			}
			break;
		}
		case GFScript::TokenID::FUNCTION_GETARRAY:
		{
			if (push((void*)fun_get_array, (void*)DEBUGIFY(fun_get_array), {
				{ GFScript::TokenID::FUNCTION_GETARRAY },
				{ GFScript::TokenID::IDENTIFIER_VAR },
				{ GFScript::TokenID::IDENTIFIER_VAR, GFScript::TokenID::NUMBER_LITERAL },
				{ GFScript::TokenID::IDENTIFIER_VAR }
				}, instance, instance->tokens, &position, &instance->functions, debug, {0}) == false) {
				return false;
			}
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