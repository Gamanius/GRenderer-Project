#include "../GRenderer.h"

#define GET_TOKEN tokens->operator[](*position).token
#define ASS(x, y) x = y; if(x == nullptr) { if(node != nullptr) node->dereference(); delete node; return nullptr; }
#define ERR(...) THROW("[Line: ", tokens->operator[](*position).line, "]:", __VA_ARGS__); if(node != nullptr) node->dereference(); delete node; return nullptr;

void GScript::Node::dereference() {
	if (left != nullptr)
		left->dereference();
	main = Token();
	if (right != nullptr)
		right->dereference();
}

GScript::Node* getExpression(const std::vector<GScript::Token>* tokens, unsigned int* position);

GScript::Node* getFactor(const std::vector<GScript::Token>* tokens, unsigned int* position) {
	GScript::Node* node = new GScript::Node();
	if (GET_TOKEN == GScript::TokenID::DOUBLE_LITERAL || GET_TOKEN == GScript::TokenID::INTEGER_LITERAL) {
		node->main = tokens->operator[](*position);
		(*position)++;
	}
	else if (GET_TOKEN == GScript::TokenID::LPARAN) {
		(*position)++;
		ASS(node, getExpression(tokens, position));
		if (GET_TOKEN != GScript::TokenID::RPARAN) {
			ERR("Expected )");
		}
		(*position)++;
	}
	else {
		ERR("Expected number but found '", tokens->operator[](*position).svalue, "'");
	}
	return node;
}

GScript::Node* getTerm(const std::vector<GScript::Token>* tokens, unsigned int* position) {
	GScript::Node* node = new GScript::Node();
	ASS(node->left, getFactor(tokens, position));

	if (GET_TOKEN == GScript::TokenID::OP_MULTIPLY || GET_TOKEN == GScript::TokenID::OP_DIVIDE) {
	AGAIN:
		node->main = tokens->operator[](*position);
		(*position)++;
		ASS(node->right, getFactor(tokens, position));
	}
	if (GET_TOKEN == GScript::TokenID::OP_MULTIPLY || GET_TOKEN == GScript::TokenID::OP_DIVIDE) {
		auto temp = node;
		node = new GScript::Node();
		node->left = temp;
		goto AGAIN;
	}
	else if (node->right == nullptr) {
		auto temp = node->left;
		node->left = nullptr;
		delete node;
		return temp;
	}
	return node;
}

GScript::Node* getExpression(const std::vector<GScript::Token>* tokens, unsigned int* position) {
	GScript::Node* node = new GScript::Node();
	ASS(node->left, getTerm(tokens, position));

	if (GET_TOKEN == GScript::TokenID::OP_PLUS || GET_TOKEN == GScript::TokenID::OP_MINUS) {
	AGAIN:
		node->main = tokens->operator[](*position);
		(*position)++;
		ASS(node->right, getTerm(tokens, position));
	}
	else if (GET_TOKEN == GScript::TokenID::BREAK || GET_TOKEN == GScript::TokenID::RPARAN) {
		auto temp = node->left;
		node->left = nullptr;
		delete node;
		return temp;
	}
	else {
		ERR("Expected another operator like +, -, * or /");
	}
	if (GET_TOKEN == GScript::TokenID::OP_PLUS || GET_TOKEN == GScript::TokenID::OP_MINUS) {
		auto temp = node;
		node = new GScript::Node();
		node->left = temp;
		goto AGAIN;
	}

	return node;
}

void GScript::Interpreter::Parser::setTokens(const std::vector<Token>* tok) {
	position = 0;
	delete abstractSyntaxTree;
	tokens = tok;
}

bool GScript::Interpreter::Parser::createAbstractSyntaxTree() {
	abstractSyntaxTree = getExpression(tokens, &position);
	if (tokens->operator[](position).token != GScript::TokenID::BREAK) {
		THROWW("[Line: ", tokens->operator[](position).line, "]: Expected a ; but didn't found '", tokens->operator[](position).svalue, "' ...is this parser broken or is there a syntax error that got ignored?");
	}
	if (abstractSyntaxTree == nullptr) {
		THROW("An error occured while creating the abstract syntax tree");
		return false;
	}
	return true;
}