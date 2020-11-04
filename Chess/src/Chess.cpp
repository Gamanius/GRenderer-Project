#include <GRenderer.h>
#include <iostream>
#include <Windows.h>
#include <string>

//Global vars
GWindow::Window* window = nullptr;
GEventWrapper::Windowhandler* handler = nullptr;;
GGeneral::Dimension<int> windowDrawSize = {};
bool wantClosing = false;
#define SCREEN_START_WIDTH 800
#define SCREEN_START_HEIGHT 800
#define SCREEN_WINDOW_NAME "Cheesy Chess Remastered"

#define SPRITE_AMOUNT 14

volatile bool running = true;

//Game Vars
GFile::Graphics::Image* sprites[SPRITE_AMOUNT];
GRenderer::Texture* allTextures[SPRITE_AMOUNT];
unsigned int squareAmount = 8;
struct Chesspiece;
std::vector<Chesspiece> allChesspieces;

Chesspiece* selectedSquare;

bool drawflip = false;
bool drawflipb = false;

bool isServer = false;
bool isServerWhite = true;
bool isOnline = false;
int port = 0;
GGeneral::String ip;
GNetworking::ServerSocket* server = nullptr;
unsigned int serverclient = 0;
GNetworking::Socket* client = nullptr;

struct Move {
	GGeneral::Point<int> newPos;
	Chesspiece* remove = nullptr;

	Chesspiece* alternativepiece = nullptr;
	GGeneral::Point<int> altPos;
};

std::vector<GGeneral::Point<int>> pointsToDraw;
std::vector<Move>* allMoves = nullptr;
bool whitesTurn = true;

struct Chesspiece {
	GGeneral::Point<int> pos = {};
	byte type = 0;
	bool first = true;
	bool doubleMove = false;

	bool isWhite() { return type <= 5; }

	Chesspiece(GGeneral::Point<int> pos = {0, 0}, byte type = 0) : pos(pos), type(type) {}
	Chesspiece(int x = 0, int y = 0, byte type = 0) : type(type) {
		pos = {x,y};
	}
};

GGeneral::Point<int> getRelativeCoordinates(GGeneral::Point<int> p) {
	GGeneral::Point<int> returnValue;
	returnValue.x = ((double)p.x / windowDrawSize.width) * squareAmount;
	returnValue.y = ((double)p.y / windowDrawSize.height) * squareAmount;

	if (returnValue.x < 0)
		returnValue.x = 0;
	else if (returnValue.x > squareAmount)
		returnValue.x = squareAmount - 1;
	if (returnValue.y < 0)
		returnValue.y = 0;
	else if (returnValue.y > squareAmount)
		returnValue.y = squareAmount - 1;

	return returnValue;
}

Chesspiece* getChesspieceFromBoard(GGeneral::Point<int> r) {
	for (size_t i = 0; i < allChesspieces.size(); i++) {
		if (allChesspieces[i].pos == r) {
			return &allChesspieces[i];
		}
	}
	return nullptr;
}

void flipBoard() {
	for (size_t i = 0; i < allChesspieces.size(); i++) {
		allChesspieces[i].pos.x = std::abs((int)(allChesspieces[i].pos.x - squareAmount + 1));
		allChesspieces[i].pos.y = std::abs((int)(allChesspieces[i].pos.y - squareAmount + 1));
	}
	drawflip = !drawflip;
	if (allMoves != nullptr) {
		allMoves->clear();
		delete allMoves;
		allMoves = nullptr;
	}
	selectedSquare = nullptr;
}

std::vector<Move> getAllPositions(Chesspiece* piece, bool checkMate = true);
bool isKindInDanger(std::vector<Chesspiece>* pieces, bool checkForWhite) {
	if (checkForWhite) {
		Chesspiece* king = nullptr;
		for (size_t i = 0; i < pieces->size(); i++) {
			if (pieces->operator[](i).type == 5) {
				king = &pieces->operator[](i);
				break;
			}
		}
		if (king == nullptr) {
			THROWW("Found impossible game state");
			return false;
		}
		for (size_t i = 0; i < pieces->size(); i++) {
			auto c = pieces->operator[](i);
			if (!c.isWhite()) {
				auto allPos = getAllPositions(&c, false);
				for (size_t i = 0; i < allPos.size(); i++) {
					if (allPos[i].remove != nullptr)
						if (allPos[i].remove->pos == king->pos) {
							return true;
						}
				}
			}
		}
	}
	else {
		Chesspiece* king = nullptr;
		for (size_t i = 0; i < pieces->size(); i++) {
			if (pieces->operator[](i).type == 11) {
				king = &pieces->operator[](i);
				break;
			}
		}
		if (king == nullptr) {
			THROWW("Found impossible game state");
			return false;
		}
		for (size_t i = 0; i < pieces->size(); i++) {
			auto c = pieces->operator[](i);
			if (c.isWhite()) {
				auto allPos = getAllPositions(&c, false);
				for (size_t i = 0; i < allPos.size(); i++) {
					if (allPos[i].remove != nullptr)
						if (allPos[i].remove->pos == king->pos) {
							return true;
						}
				}
			}
		}
	}
	return false;
}

void reset() {
	allChesspieces.clear();
	selectedSquare = nullptr;

	for (int i = 0; i < 8; i++) {
		allChesspieces.push_back(Chesspiece(i, 6, 0));
		allChesspieces.push_back(Chesspiece(i, 1, 6));
	}
	allChesspieces.push_back(Chesspiece(0, 7, 1));
	allChesspieces.push_back(Chesspiece(7, 7, 1));
	allChesspieces.push_back(Chesspiece(1, 7, 3));
	allChesspieces.push_back(Chesspiece(6, 7, 3));
	allChesspieces.push_back(Chesspiece(2, 7, 2));
	allChesspieces.push_back(Chesspiece(5, 7, 2));
	allChesspieces.push_back(Chesspiece(3, 7, 4));
	allChesspieces.push_back(Chesspiece(4, 7, 5));

	allChesspieces.push_back(Chesspiece(0, 0, 7));
	allChesspieces.push_back(Chesspiece(7, 0, 7));
	allChesspieces.push_back(Chesspiece(1, 0, 9));
	allChesspieces.push_back(Chesspiece(6, 0, 9));
	allChesspieces.push_back(Chesspiece(2, 0, 8));
	allChesspieces.push_back(Chesspiece(5, 0, 8));
	allChesspieces.push_back(Chesspiece(3, 0, 10));
	allChesspieces.push_back(Chesspiece(4, 0, 11));
}

std::vector<Move> getAllPositions(Chesspiece* piece, bool checkMate) {
	if (piece == nullptr)
		return std::vector<Move>();
	std::vector<Move> returnValue;

	if ((piece->type == 6 && !drawflip) || (piece->type == 0 && drawflip)) { //Black pawns
		if (getChesspieceFromBoard({piece->pos.x, piece->pos.y + 1}) == nullptr) {
			Move m;
			m.newPos = {piece->pos.x, piece->pos.y + 1};
			returnValue.push_back(m);
		}
		if (piece->first) {
			if (getChesspieceFromBoard({piece->pos.x, piece->pos.y + 1}) == nullptr && getChesspieceFromBoard({piece->pos.x, piece->pos.y + 2}) == nullptr) {
				Move m;
				m.newPos = {piece->pos.x, piece->pos.y + 2};
				returnValue.push_back(m);
			}
		}
		auto c = getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y + 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = {piece->pos.x - 1, piece->pos.y + 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		c = getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y + 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = {piece->pos.x + 1, piece->pos.y + 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		c = getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite() && c->doubleMove) {
				Move m;
				m.newPos = {piece->pos.x + 1, piece->pos.y + 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		c = getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite() && c->doubleMove) {
				Move m;
				m.newPos = {piece->pos.x - 1, piece->pos.y + 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
	}
	else if ((piece->type == 6 && drawflip) || (piece->type == 0 && !drawflip)) { //white pawns
		if (getChesspieceFromBoard({piece->pos.x, piece->pos.y - 1}) == nullptr) {
			Move m;
			m.newPos = {piece->pos.x, piece->pos.y - 1};
			returnValue.push_back(m);
		}
		if (piece->first) {
			if (getChesspieceFromBoard({piece->pos.x, piece->pos.y - 1}) == nullptr && getChesspieceFromBoard({piece->pos.x, piece->pos.y - 2}) == nullptr) {
				Move m;
				m.newPos = {piece->pos.x, piece->pos.y - 2};
				returnValue.push_back(m);
			}
		}
		auto c = getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y - 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = {piece->pos.x - 1, piece->pos.y - 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		c = getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y - 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = {piece->pos.x + 1, piece->pos.y - 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		c = getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite() && c->doubleMove) {
				Move m;
				m.newPos = {piece->pos.x + 1, piece->pos.y - 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		c = getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite() && c->doubleMove) {
				Move m;
				m.newPos = {piece->pos.x - 1, piece->pos.y - 1};
				m.remove = c;
				returnValue.push_back(m);
			}
		}
	}
	else if (piece->type == 1 || piece->type == 7) { //rook
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x + i, piece->pos.y};
			auto c = getChesspieceFromBoard({piece->pos.x + i, piece->pos.y});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x - i, piece->pos.y};
			auto c = getChesspieceFromBoard({piece->pos.x - i, piece->pos.y});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x, piece->pos.y + i};
			auto c = getChesspieceFromBoard({piece->pos.x, piece->pos.y + i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x, piece->pos.y - i};
			auto c = getChesspieceFromBoard({piece->pos.x , piece->pos.y - i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
	}
	else if (piece->type == 2 || piece->type == 8) { //bishop
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x + i, piece->pos.y + i};
			auto c = getChesspieceFromBoard({piece->pos.x + i, piece->pos.y + i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x - i, piece->pos.y - i};
			auto c = getChesspieceFromBoard({piece->pos.x - i, piece->pos.y - i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x - i, piece->pos.y + i};
			auto c = getChesspieceFromBoard({piece->pos.x - i, piece->pos.y + i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x + i, piece->pos.y - i};
			auto c = getChesspieceFromBoard({piece->pos.x + i, piece->pos.y - i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
	}
	else if (piece->type == 10 || piece->type == 4) { //queen
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x + i, piece->pos.y};
			auto c = getChesspieceFromBoard({piece->pos.x + i, piece->pos.y});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x - i, piece->pos.y};
			auto c = getChesspieceFromBoard({piece->pos.x - i, piece->pos.y});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x, piece->pos.y + i};
			auto c = getChesspieceFromBoard({piece->pos.x, piece->pos.y + i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x, piece->pos.y - i};
			auto c = getChesspieceFromBoard({piece->pos.x , piece->pos.y - i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x + i, piece->pos.y + i};
			auto c = getChesspieceFromBoard({piece->pos.x + i, piece->pos.y + i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x - i, piece->pos.y - i};
			auto c = getChesspieceFromBoard({piece->pos.x - i, piece->pos.y - i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x - i, piece->pos.y + i};
			auto c = getChesspieceFromBoard({piece->pos.x - i, piece->pos.y + i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
		for (int i = 1; i < squareAmount; i++) {
			Move m;
			m.newPos = {piece->pos.x + i, piece->pos.y - i};
			auto c = getChesspieceFromBoard({piece->pos.x + i, piece->pos.y - i});
			if (c != nullptr) {
				if (c->isWhite() != piece->isWhite()) {
					m.remove = c;
					returnValue.push_back(m);
				}
				break;
			}
			returnValue.push_back(m);
		}
	}
	else if (piece->type == 3 || piece->type == 9) {
		auto c = getChesspieceFromBoard({piece->pos.x - 2, piece->pos.y + 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x - 2, piece->pos.y + 1};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x - 2, piece->pos.y - 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x - 2, piece->pos.y - 1};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x + 2, piece->pos.y + 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x + 2, piece->pos.y + 1};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x + 2, piece->pos.y - 1});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x + 2, piece->pos.y - 1};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y + 2});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x - 1, piece->pos.y + 2};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y - 2});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x - 1, piece->pos.y - 2};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y + 2});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x + 1, piece->pos.y + 2};
			returnValue.push_back(m);
		}
		c = getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y - 2});
		if (c != nullptr) {
			if (c->isWhite() != piece->isWhite()) {
				Move m;
				m.newPos = c->pos;
				m.remove = c;
				returnValue.push_back(m);
			}
		}
		else {
			Move m;
			m.newPos = {piece->pos.x + 1, piece->pos.y - 2};
			returnValue.push_back(m);
		}
	}
	else if (piece->type == 5 || piece->type == 11) { //king
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i == 0 && j == 0)
					continue;
				Move m;
				m.newPos = {piece->pos.x + i, piece->pos.y + j};
				auto c = getChesspieceFromBoard(m.newPos);
				if (c != nullptr) {
					if (c->isWhite() != piece->isWhite()) {
						m.remove = c;
						returnValue.push_back(m);
					}
				}
				else
					returnValue.push_back(m);
			}
		}
		if (piece->first) {
			auto c = getChesspieceFromBoard({piece->pos.x + 3, piece->pos.y});
			if (c != nullptr)
				if (c->type == 1 || c->type == 7)
					if (c->first)
						if (getChesspieceFromBoard({piece->pos.x + 2, piece->pos.y}) == nullptr && getChesspieceFromBoard({piece->pos.x + 1, piece->pos.y}) == nullptr)
							if (checkMate)
								if (!isKindInDanger(&allChesspieces, piece->isWhite())) {
									Move m;
									m.alternativepiece = c;
									m.altPos = {piece->pos.x + 1, piece->pos.y};
									m.newPos = {piece->pos.x + 2, piece->pos.y};
									returnValue.push_back(m);
								}
			c = getChesspieceFromBoard({piece->pos.x - 4, piece->pos.y});
			if (c != nullptr)
				if (c->type == 1 || c->type == 7)
					if (c->first)
						if (getChesspieceFromBoard({piece->pos.x - 2, piece->pos.y}) == nullptr && getChesspieceFromBoard({piece->pos.x - 3, piece->pos.y}) == nullptr && getChesspieceFromBoard({piece->pos.x - 1, piece->pos.y}) == nullptr)
							if (checkMate)
								if (!isKindInDanger(&allChesspieces, piece->isWhite())) {
									Move m;
									m.alternativepiece = c;
									m.altPos = {piece->pos.x - 1, piece->pos.y};
									m.newPos = {piece->pos.x - 2, piece->pos.y};
									returnValue.push_back(m);
								}
		}
	}

	for (int i = returnValue.size() - 1; i >= 0; i--) {
		if (returnValue[i].newPos.x >= squareAmount || returnValue[i].newPos.x < 0 || returnValue[i].newPos.y >= squareAmount || returnValue[i].newPos.y < 0)
			returnValue.erase(returnValue.begin() + i);
	}

	if (checkMate) {
		for (int i = returnValue.size() - 1; i >= 0; i--) {
			auto temp = piece->pos;
			piece->pos = returnValue[i].newPos;

			auto temp2 = returnValue[i].remove;
			GGeneral::Point<int> temp2pos;
			if (temp2 != nullptr) {
				temp2pos = temp2->pos;
				temp2->pos = {(int)squareAmount * -10, (int)squareAmount * -10};
			}

			if (isKindInDanger(&allChesspieces, piece->isWhite())) {
				returnValue.erase(returnValue.begin() + i);
			}
			piece->pos = temp;

			if (temp2 != nullptr)
				temp2->pos = temp2pos;
		}
	}

	return returnValue;
}

bool _prepare() {
	bool b;
	b = GRenderer::init();
	if (!b) {
		return b;
	}

	//Retrieve screen coords
	auto s = GWindow::Monitor::getPrimaryMonitorInformation();
	GGeneral::Point<int> p;
	p.x = s->digitalPosition.x + (s->screenDimension.width / 2) - (SCREEN_START_WIDTH / 2);
	p.y = s->digitalPosition.y + (s->screenDimension.height / 2) - (SCREEN_START_HEIGHT / 2);
	//Place the window in the middle
	window = new GWindow::Window(SCREEN_WINDOW_NAME, p, {SCREEN_START_WIDTH, SCREEN_START_HEIGHT});
	b = window->createOpenGLcontext();
	window->setOpenGLContextActive();
	b = b && GGraphics::init();
	GRenderer::enableBlend();

	handler = new GEventWrapper::Windowhandler(window);
	//handler->addCallback(mouseCallback)

	//Lade alle Sprites
	sprites[0] = GFile::Graphics::loadImage("rsc/white_pawn.png"); // Typ 0
	sprites[1] = GFile::Graphics::loadImage("rsc/white_rook.png");
	sprites[2] = GFile::Graphics::loadImage("rsc/white_bishop.png");
	sprites[3] = GFile::Graphics::loadImage("rsc/white_knight.png");
	sprites[4] = GFile::Graphics::loadImage("rsc/white_queen.png");
	sprites[5] = GFile::Graphics::loadImage("rsc/white_king.png"); //Typ 5

	sprites[6] = GFile::Graphics::loadImage("rsc/black_pawn.png"); //6
	sprites[7] = GFile::Graphics::loadImage("rsc/black_rook.png");
	sprites[8] = GFile::Graphics::loadImage("rsc/black_bishop.png");
	sprites[9] = GFile::Graphics::loadImage("rsc/black_knight.png");
	sprites[10] = GFile::Graphics::loadImage("rsc/black_queen.png");
	sprites[11] = GFile::Graphics::loadImage("rsc/black_king.png"); //11

	sprites[12] = GFile::Graphics::loadImage("rsc/frame.png");
	sprites[13] = GFile::Graphics::loadImage("rsc/frame_b.png");

	for (size_t i = 0; i < SPRITE_AMOUNT; i++) {
		if (sprites[i] == nullptr) {
			THROW("Files couldn't be loaded");
			return false;
		}
	}

	for (size_t i = 0; i < 12; i++) {
		sprites[i]->flip();
	}

	for (size_t i = 0; i < SPRITE_AMOUNT; i++) {
		allTextures[i] = new GRenderer::Texture(*sprites[i]);
	}

	for (int i = 0; i < 8; i++) {
		allChesspieces.push_back(Chesspiece(i, 6, 0));
		allChesspieces.push_back(Chesspiece(i, 1, 6));
	}
	allChesspieces.push_back(Chesspiece(0, 7, 1));
	allChesspieces.push_back(Chesspiece(7, 7, 1));
	allChesspieces.push_back(Chesspiece(1, 7, 3));
	allChesspieces.push_back(Chesspiece(6, 7, 3));
	allChesspieces.push_back(Chesspiece(2, 7, 2));
	allChesspieces.push_back(Chesspiece(5, 7, 2));
	allChesspieces.push_back(Chesspiece(3, 7, 4));
	allChesspieces.push_back(Chesspiece(4, 7, 5));

	allChesspieces.push_back(Chesspiece(0, 0, 7));
	allChesspieces.push_back(Chesspiece(7, 0, 7));
	allChesspieces.push_back(Chesspiece(1, 0, 9));
	allChesspieces.push_back(Chesspiece(6, 0, 9));
	allChesspieces.push_back(Chesspiece(2, 0, 8));
	allChesspieces.push_back(Chesspiece(5, 0, 8));
	allChesspieces.push_back(Chesspiece(3, 0, 10));
	allChesspieces.push_back(Chesspiece(4, 0, 11));

	return b;
}

void update() {
	window->fetchEvents();
	windowDrawSize = window->getWindowDrawSize();
	GGraphics::setViewport(windowDrawSize);

	if (isServer) {
		if (server->isConnected(serverclient)) {
			auto data = server->receive(serverclient);
			if (data.data != nullptr) {
				if (data.data[0] == 'c') {
					auto p = reinterpret_cast<Chesspiece*> (&data.data[1]);
					allChesspieces.clear();
					for (size_t i = 0; i < (data.size - 2) / 16; i++) {
						allChesspieces.push_back(p[i]);
					}
					flipBoard();
					drawflip = false;
					whitesTurn = !whitesTurn;
				}
				else if (data.data[0] == 't' && data.data[1] == 'u') {
					//whitesTurn = !whitesTurn;
				}
				else if (data.data[0] == 'w') {
					reset();
					whitesTurn = true;
					drawflip = false;
					if (data.data[1] == 1) {
						LOGI("remis");
					}
					else if (data.data[1] == 2) {
						LOGI("black won");
					}
					else if (data.data[1] == 3) {
						LOGI("white won");
					}
				}
			}
		}
		else {
			window->setState(GWindow::WindowState::HIDDEN);
			delete server;
			LOGI("Connection reset");
			running = false;
			GGeneral::Logger::wait();
			exit(0);
		}
	}
	else if (isOnline) {
		if (client->isConnected()) {
			auto data = client->receive();
			if (data.data != nullptr) {
				GGeneral::String s;

				if (data.data[0] == 'r' && data.data[1] == '1') {
					LOGI("Board has been reset by server");
					whitesTurn = true;
					reset();
					flipBoard();
				}
				else if (data.data[0] == 's') {
					LOGI("Switched sides by server");
					reset();
					flipBoard();
					isServerWhite = data.data[1];
					if (isServerWhite) {
						LOG("You are now black");
					}
					else {
						LOG("You are now white");
					}
				}
				else if (data.data[0] == 'c') {
					auto p = reinterpret_cast<Chesspiece*> (&data.data[1]);
					allChesspieces.clear();
					for (size_t i = 0; i < (data.size - 2) / 16; i++) {
						allChesspieces.push_back(p[i]);
					}
					flipBoard();
					drawflip = true;
					whitesTurn = !whitesTurn;
				}
				else if (data.data[0] == 't' && data.data[1] == 'u') {
					//whitesTurn = !whitesTurn;
				}
				else if (data.data[0] == 'w') {
					reset();
					flipBoard();
					whitesTurn = true;
					drawflip = true;
					if (data.data[1] == 1) {
						LOGI("remis");
					}
					else if (data.data[1] == 2) {
						LOGI("black won");
					}
					else if (data.data[1] == 3) {
						LOGI("white won");
					}
				}
			}
		}
		else {
			window->setState(GWindow::WindowState::HIDDEN);
			delete server;
			LOGI("Connection reset");
			running = false;
			GGeneral::Logger::wait();
			exit(0);
		}
	}

	if (selectedSquare != nullptr) {
		if (allMoves == nullptr) {
			allMoves = new std::vector<Move>(getAllPositions(getChesspieceFromBoard(selectedSquare->pos)));
			//Check for checkmate
			int check = 0;
			for (size_t i = 0; i < allChesspieces.size(); i++) {
				if (allChesspieces[i].isWhite() == whitesTurn || !allChesspieces[i].isWhite() == !whitesTurn)
					check += getAllPositions(&allChesspieces[i]).size();
			}
			if (check == 0) {
				int who = 0;
				if (isKindInDanger(&allChesspieces, !whitesTurn)) {
					LOGI("Remis");
					who = 1;
				}
				else if (whitesTurn) {
					LOGI("Black won?");
					who = 2;
				}
				else {
					LOGI("White won?");
					who = 3;
				}

				if (isOnline) {
					if (isServer) {
						auto data = new byte[2];
						data[0] = 'w';
						data[1] = who;

						server->send(serverclient, data, 2);
						delete[] data;
					}
					else {
						flipBoard();
						whitesTurn = true;
						drawflip = true;
						auto data = new byte[2];
						data[0] = 'w';
						data[1] = who;

						client->send(data, 2);
						delete[] data;
					}
				}
				else {
					GGeneral::Logger::wait();
					reset();
					drawflip = false;
					whitesTurn = true;
					return;
				}
			}
			pointsToDraw.clear();
			for (size_t i = 0; i < allMoves->size(); i++) {
				pointsToDraw.push_back(allMoves->operator[](i).newPos);
			}
		}

		if (handler->isKeyPressed(GWindow::VK::LEFT_MB) && allMoves != nullptr) {
			auto newpos = getRelativeCoordinates(handler->getMousePosition());
			Move* move = nullptr;
			for (size_t i = 0; i < allMoves->size(); i++) {
				if (newpos == allMoves->operator[](i).newPos) {
					move = &allMoves->operator[](i);
					break;
				}
			}
			if (move != nullptr) {
				if (std::abs(selectedSquare->pos.y - move->newPos.y) >= 2 && (selectedSquare->type == 0 || selectedSquare->type == 6)) {
					selectedSquare->doubleMove = true;
				}
				else
					selectedSquare->doubleMove = false;
				selectedSquare->pos = move->newPos;
				selectedSquare->first = false;
				selectedSquare = nullptr;

				whitesTurn = !whitesTurn;

				if (move->remove != nullptr) {
					for (size_t i = 0; i < allChesspieces.size(); i++) {
						if (&allChesspieces[i] == move->remove) {
							allChesspieces.erase(allChesspieces.begin() + i);
							break;
						}
					}
				}

				if (move->alternativepiece != nullptr) {
					move->alternativepiece->pos = move->altPos;
				}

				delete allMoves;
				allMoves = nullptr;

				if (isOnline) {
					auto data = new byte[allChesspieces.size() * sizeof(Chesspiece) + 2];
					data[0] = 'c';
					auto p = reinterpret_cast<Chesspiece*> (&data[1]);
					for (size_t i = 0; i < allChesspieces.size(); i++) {
						p[i] = allChesspieces[i];
					}
					data[allChesspieces.size() * sizeof(Chesspiece) + 1] = '\0';
					if (isServer) {
						server->send(serverclient, data, allChesspieces.size() * sizeof(Chesspiece) + 2);
						delete[] data;
						data = new byte[2];
						data[0] = 't';
						data[1] = 'u';
						server->send(serverclient, data, 2);
					}
					else {
						client->send(data, allChesspieces.size() * sizeof(Chesspiece) + 2);
						delete[] data;
						data = new byte[2];
						data[0] = 't';
						data[1] = 'u';
						client->send(data, 2);
					}
					delete[] data;
				}
				else
					flipBoard();
			}
		}
	}

	if (handler->isKeyPressed(GWindow::VK::LEFT_MB) && selectedSquare == nullptr) {
		auto c = getChesspieceFromBoard(getRelativeCoordinates(handler->getMousePosition()));
		if (c != nullptr)

			if ((whitesTurn && c->isWhite()) || (!whitesTurn && !c->isWhite())) {
				if (isOnline) {
					if (!isServer && isServerWhite && !whitesTurn || !isServer && !isServerWhite && whitesTurn) {
						delete allMoves;
						allMoves = nullptr;
						selectedSquare = c;
					}
					else if (isServer && isServerWhite && whitesTurn || isServer && !isServerWhite && !whitesTurn) {
						delete allMoves;
						allMoves = nullptr;
						selectedSquare = c;
					}
				}
				else {
					delete allMoves;
					allMoves = nullptr;
					selectedSquare = c;
				}
			}
	}

	if (handler->isKeyPressed(GWindow::VK::RIGHT_MB) || handler->isKeyPressed(GWindow::VK::ESCAPE)) {
		selectedSquare = nullptr;
		delete allMoves;
		allMoves = nullptr;
	}

	if (handler->isKeyPressed(GWindow::VK::MIDDLE_MB) && !drawflipb) {
		flipBoard();
		drawflipb = true;
	}
	else if (!handler->isKeyPressed(GWindow::VK::MIDDLE_MB))
		drawflipb = false;
}

void draw() {
	GRenderer::clear({0, 0, 0});

	for (int i = 0; i < squareAmount; i++) {
		for (int j = 0; j < squareAmount; j++) {
			//Choose correct color
			if (j % 2 == 0) {
				if (i % 2 == 0) {
					GGraphics::setColor({153, 153, 153});
				}
				else {
					GGraphics::setColor({46, 46, 46});
				}
			}
			else {
				if (i % 2 == 1) {
					GGraphics::setColor({153, 153, 153});
				}
				else {
					GGraphics::setColor({46, 46, 46});
				}
			}

			auto dim = windowDrawSize;
			//Draw the rectangles
			auto rec = GGeneral::Rectangle<int>((int)(i * dim.width / squareAmount), (int)(j * dim.height / squareAmount), (int)(dim.width / squareAmount + 1),
				(int)(dim.height / squareAmount + 1));
			//LOG(rec);
			GGraphics::drawRect(rec);
		}
	}

	for (auto& c : allChesspieces) {
		GGeneral::Dimension<unsigned int> dim;
		dim.width = std::round(((double)windowDrawSize.width / squareAmount) - (windowDrawSize.width / 125.0));
		dim.height = std::round(((double)windowDrawSize.height / squareAmount) - (windowDrawSize.height / 125.0));

		GGeneral::Point< int> pos;
		pos.y = std::abs(std::round((c.pos.y + 1) * ((double)windowDrawSize.height / squareAmount) - (windowDrawSize.height / 250.0)) - windowDrawSize.height);
		pos.x = std::round(c.pos.x * ((double)windowDrawSize.width / squareAmount) + (windowDrawSize.width / 250.0));
		GGraphics::drawImg(pos, *allTextures[c.type], dim);
	}

	if (selectedSquare != nullptr) {
		auto rec = GGeneral::Rectangle<int>((int)(selectedSquare->pos.x * windowDrawSize.width / squareAmount), (int)((squareAmount - selectedSquare->pos.y - 1) * windowDrawSize.height / squareAmount), (int)(windowDrawSize.width / squareAmount + 1),
			(int)(windowDrawSize.height / squareAmount + 1));
		GGraphics::drawImg(rec.position, *allTextures[12], GGeneral::Dimension<unsigned int>(rec.dimension.width, rec.dimension.height));

		for (auto& p : pointsToDraw) {
			auto rec1 = GGeneral::Rectangle<int>((int)(p.x * windowDrawSize.width / squareAmount), (int)((squareAmount - p.y - 1) * windowDrawSize.height / squareAmount), (int)(windowDrawSize.width / squareAmount + 1),
				(int)(windowDrawSize.height / squareAmount + 1));

			GGraphics::drawImg(rec1.position, *allTextures[13], GGeneral::Dimension<unsigned int>(rec1.dimension.width, rec1.dimension.height));
		}
	}
}

static void commandLine() {
	while (running) {
		std::string s;
		getline(std::cin, s);
		if (s == "reset") {
			reset();
			auto data = new byte[3];
			data[0] = 'r';
			data[1] = '1';
			data[2] = '\0';
			server->send(serverclient, data, 3);
			delete[] data;
			LOGI("Reseted Board");
		}
		else if (s == "stop") {
			selectedSquare = nullptr;
			allChesspieces.clear();

			LOGI("Removed Board");
		}
		else if (s == "switch") {
			reset();
			isServerWhite = !isServerWhite;
			auto data = new byte[3];
			data[0] = 's';
			data[1] = isServerWhite;
			data[2] = '\0';
			server->send(serverclient, data, 3);
			delete[] data;
		}
	}
}

int main(int argc, char** argv) {
	LOGI("Initiating");
	if (_prepare() == false) {
		LOGF("An error occurred while initiating");
		GGeneral::ErrorHandler::printAll();
		LOGI("Press Enter to continue");
		GGeneral::Logger::wait();
		std::cin.get();
		exit(-1);
	}
	LOGS("Done");
	LOGI("Using Version: ", G_RENDERER_VERSION);
	LOGI("Using OpenGL Version: ", GRenderer::getGLString(GRenderer::GLString::VERSION));

	if (argc == 3) {
		isOnline = true;
		isServer = true;
		if (GGeneral::String(argv[1]).compare("server")) {
			auto s = GGeneral::String(argv[2]);
			port = std::stoi(s.cStr());

			LOGI("Searching for sockets on port: ", port);
			server = new GNetworking::ServerSocket(port);
			serverclient = server->accept();
			server->setBlockingMode(false, serverclient);
			LOGS("Found Client");
		}
		else {
			LOGE("An error occurred: ");
			GGeneral::ErrorHandler::printAll();
			LOG("Press Enter to continue");
			GGeneral::Logger::wait();
			std::cin.get();
			exit(-1);
		}
	}
	else if (argc == 4) {
		flipBoard();
		isOnline = true;
		if (GGeneral::String(argv[1]).compare("noserver")) {
			auto s = GGeneral::String(argv[2]);
			port = std::stoi(s.cStr());
			ip = GGeneral::String(argv[3]);

			LOGI("Searching for Server...");

			client = new GNetworking::Socket(ip, port);
			if (!client->isConnected()) {
				LOGE("An error occurred: ");
				GGeneral::ErrorHandler::printAll();
				LOG("Press Enter to continue");
				GGeneral::Logger::wait();
				std::cin.get();
				exit(-1);
			}
			client->setBlockingMode(false);
			LOGS("Found Server");
		}
		else {
			LOGE("An error occurred: ");
			GGeneral::ErrorHandler::printAll();
			LOG("Press Enter to continue");
			GGeneral::Logger::wait();
			std::cin.get();
			exit(-1);
		}
		isServer = false;
	}

	//	window->setResizable(false);
	if (isServer)
		window->setIcon("rsc/icon.ico");
	window->setState(GWindow::WindowState::NORMAL);

	std::thread t;
	if (isServer)
		t = std::thread(commandLine);

	while (wantClosing == false) {
		if (GRenderer::ddelta() >= 16) {
			draw();
			window->swapBuffers();
		}
		update();

		wantClosing = window->getCloseRequest();
	}

	if (isServer) {
		window->setState(GWindow::WindowState::HIDDEN);
		delete server;
		LOGI("Press Enter to continue");
		running = false;
		t.join();
		GGeneral::Logger::wait();
	}

	GGeneral::ErrorHandler::printAll();
	GGeneral::Logger::wait();
}