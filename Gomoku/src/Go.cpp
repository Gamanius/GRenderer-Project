#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <array>
#include <shared_mutex>
#include <bitset>
#include "GRenderer.h"
#include <unordered_map>

//Window vars
GWindow::Window* mainWindow = nullptr;

//boolean
bool drawChanges = true;

//global game vars
byte* gameData = nullptr;
std::vector<unsigned int> gameDataMoveOrder;
byte boardSize = 15;
bool isWhiteTurn = true;
bool winState = false;

//-1 indicated that mouse is not on the board currently
int boardMousePosition = 3;
//Normal mouse position in the window
GGeneral::Point<int> mousePosition;

bool isAltPressed = false;
bool isLMousePressed = false;
bool isRMousePressed = false;
bool isF4Pressed = false;

GRenderer::Texture* blackPiece           = nullptr;
GRenderer::Texture* blackPieceTrans      = nullptr;
GRenderer::Texture* whitePiece           = nullptr;
GRenderer::Texture* whitePieceTrans      = nullptr;

GFile::Graphics::Image* IblackPiece      = nullptr;
GFile::Graphics::Image* IblackPieceTrans = nullptr;
GFile::Graphics::Image* IwhitePiece      = nullptr;
GFile::Graphics::Image* IwhitePieceTrans = nullptr;

//AI
std::atomic<unsigned long long int> movesSearched = 0;

struct task {
	int move;
	int score = 0;
	bool done = false;
};

std::shared_mutex minimaxMutex;
std::vector<task> allTasks;

bool playWithAI = false;
std::vector<std::thread> allWorker;
int sizeOfMoves = 0;
byte amountOfWorker = 1;
byte depth = 3;

//multiplayer support
std::atomic_bool isMultiplayer = false;
std::atomic_bool isServer = false;
int port = 0;
GGeneral::String ip;
GNetworking::ServerSocket* serverSocket = nullptr;

bool isWhite = false;

std::vector<GNetworking::Package> allPackages;

unsigned int receiver;
GNetworking::Socket* clientSocket = nullptr;

std::thread* multiplayerThread = nullptr;
std::thread* commandLineThread = nullptr;
std::mutex globalMutex;

void updateMouseBoardPosition() {
	//get x bound of board
	auto size = mainWindow->getWindowDrawSize();
	auto sizeOfBoard = 0;
	int offset = 0;
	int distanceFromEdge = 0;
	if (size.height > size.width) {
		sizeOfBoard = size.width;
		distanceFromEdge = 100 * (sizeOfBoard / 800.0f);
		sizeOfBoard = size.width - distanceFromEdge;
		offset = std::round((size.height - sizeOfBoard) / 2.0f);
	}
	else {
		sizeOfBoard = size.height;
		distanceFromEdge = 100 * (sizeOfBoard / 800.0f);
		sizeOfBoard = size.height - distanceFromEdge;
		offset = std::round((size.width - sizeOfBoard) / 2.0f);
	}

	int sizeOfStroke = 4 * (sizeOfBoard / 800.0f);
	sizeOfStroke = sizeOfStroke > 2 ? sizeOfStroke : 2;

	//calculate the x position by approximating the mouse board position
	int distanceBetweenLines = (int)std::round(sizeOfBoard / (boardSize - 1.0f));
	//no idea how this calculation works but it somehow does so don't change it please
	int approxMousePosX = std::round((float)(mousePosition.x - (size.height < size.width ? offset : distanceFromEdge / 2.0f)) / distanceBetweenLines);
	if (approxMousePosX > boardSize - 1 || approxMousePosX < 0) {
		boardMousePosition = -1;
		return;
	}

	//somehow try to calculate the y position
	int approxMousePosY = std::round((float)(mousePosition.y - (size.height > size.width ? offset : distanceFromEdge / 2.0f)) / distanceBetweenLines);
	if (approxMousePosY > boardSize - 1 || approxMousePosY < 0) {
		boardMousePosition = -1;
		return;
	}

	boardMousePosition = approxMousePosY * boardSize + approxMousePosX;

	//GGraphics::drawRect({approxMousePos, 50, 50, 50});
}

void drawPiece(int position, int sizeOfBoard, int distanceFromEdge, GGeneral::Dimension<int> windowSize, int sizeOfStroke, int offset, GRenderer::Texture* i) {
	auto vertical = (int)((float)position / boardSize);
	auto horizontal = position - (boardSize * vertical);
	auto currentImage = i;
	int sizeOfPiece = (int)std::round(((1.0f / (boardSize - 1.0f)) * sizeOfBoard) * 0.8f);
	sizeOfPiece = sizeOfPiece < 5 ? 5 : sizeOfPiece;

	if (windowSize.height > windowSize.width) {
		GGraphics::drawImg({(int)std::round(((horizontal / (boardSize - 1.0f)) * sizeOfBoard + (distanceFromEdge / 2.0f) - (sizeOfPiece / 2.0f))), //x
				(int)std::round(((vertical / (boardSize - 1.0f)) * sizeOfBoard) - (sizeOfStroke / 2.0f) + offset - (sizeOfPiece / 2.0f))}, //y
			*currentImage, {(unsigned int)sizeOfPiece, (unsigned int)sizeOfPiece});
	}
	else {
		GGraphics::drawImg({offset - (int)std::round((sizeOfPiece / 2.0f) - ((horizontal / (boardSize - 1.0f)) * sizeOfBoard)), //x
			(int)std::round(((vertical / (boardSize - 1.0f)) * sizeOfBoard) + (distanceFromEdge / 2.0f) - (sizeOfPiece / 2.0f))}, //y
			*currentImage, {(unsigned int)sizeOfPiece, (unsigned int)sizeOfPiece});
	}
}

void paint() {
	//reset var
	drawChanges = false;

	//first clear and draw a background
	GRenderer::clear({50, 50, 50});

	//draw board
	//to keep aspect ratio get the width and height of window
	auto size = mainWindow->getWindowDrawSize();
	//Brown color
	GGraphics::setViewport(size);
	//Draw the background of the board
	GGraphics::setColor({239, 204, 128});
	auto sizeOfBoard = 0;
	int offset = 0;
	int distanceFromEdge = 0;
	if (size.height > size.width) {
		sizeOfBoard      = size.width;
		distanceFromEdge = 100 * (sizeOfBoard / 800.0f);
		sizeOfBoard      = size.width - distanceFromEdge;
		offset           = std::round((size.height - sizeOfBoard) / 2.0f);

		//draw board background
		GGraphics::drawRect({(int)std::round(distanceFromEdge / 2.0f), offset, sizeOfBoard, sizeOfBoard});
	}
	else {
		sizeOfBoard      = size.height;
		distanceFromEdge = 100 * (sizeOfBoard / 800.0f);
		sizeOfBoard      = size.height - distanceFromEdge;
		offset           = std::round((size.width - sizeOfBoard) / 2.0f);

		//draw board background
		GGraphics::drawRect({offset, (int)std::round(distanceFromEdge / 2.0f), sizeOfBoard, sizeOfBoard});
	}

	//try to draw the lines
	int sizeOfStroke = 4 * (sizeOfBoard / 800.0f);
	sizeOfStroke = sizeOfStroke > 2 ? sizeOfStroke : 1;
	GGraphics::setColor({36, 18, 18});

	if (size.height > size.width) {
		for (int i = 0; i <= boardSize - 1; i++) {
			//draw vertical lines
			GGraphics::drawRect({(int)std::round(((i / (boardSize - 1.0f)) * sizeOfBoard) - (sizeOfStroke / 2.0f) + (distanceFromEdge / 2.0f)), offset, sizeOfStroke, sizeOfBoard});
			//draw horizontal lines
			GGraphics::drawRect({(int)std::round(distanceFromEdge / 2.0f) - (int)std::round((sizeOfStroke / 2.0f)), offset + (int)std::round(((i / (boardSize - 1.0f)) * sizeOfBoard) - (sizeOfStroke / 2.0f)), sizeOfBoard + sizeOfStroke, sizeOfStroke});
		}
	}
	else {
		for (int i = 0; i <= boardSize - 1; i++) {
			//draw vertical lines
			GGraphics::drawRect({offset + (int)std::round(((i / (boardSize - 1.0f)) * sizeOfBoard) - (sizeOfStroke / 2.0f)), (int)std::round(distanceFromEdge / 2.0f), sizeOfStroke, sizeOfBoard});
			//draw horizontal lines
			GGraphics::drawRect({offset - (int)std::round((sizeOfStroke / 2.0f)), (int)std::round(((i / (boardSize - 1.0f)) * sizeOfBoard) - (sizeOfStroke / 2.0f) + (distanceFromEdge / 2.0f)), sizeOfBoard + sizeOfStroke, sizeOfStroke});
		}
	}

	//draw image
	for (size_t i = 0; i < boardSize * boardSize; i++) {
		if (gameData[i] == 0)
			continue;
		//drawPiece(i, sizeOfBoard, distanceFromEdge, size, sizeOfStroke, offset, gameData[i] == 1 ? whitePiece : blackPiece); TODo: do later
		if (gameData[i] == 1)
			drawPiece(i, sizeOfBoard, distanceFromEdge, size, sizeOfStroke, offset, whitePiece);
		else if (gameData[i] == 2) 
			drawPiece(i, sizeOfBoard, distanceFromEdge, size, sizeOfStroke, offset, blackPiece);
		else 
			drawPiece(i, sizeOfBoard, distanceFromEdge, size, sizeOfStroke, offset, whitePieceTrans);
	}

	//draw transparant image if needed
	//calculate closest x coordinate
	if (!winState) {
		updateMouseBoardPosition();
		if (isMultiplayer && isWhite == isWhiteTurn || !isMultiplayer)
			if (boardMousePosition >= 0)
				if (gameData[boardMousePosition] == 0)
					drawPiece(boardMousePosition, sizeOfBoard, distanceFromEdge, size, sizeOfStroke, offset, isWhiteTurn ? whitePieceTrans : blackPieceTrans);
	}
	
	//Swap buffers at the end
	mainWindow->swapBuffers();
}


byte checkWin(byte* data, byte boardSize, const std::vector<unsigned int>& moveorder) {
	//checks will always be from left to right and from down to up
	for (size_t i = 0; i < moveorder.size(); i++) {
		//Check if there is a piece
		//if there is check if there are more of the pieces
		auto piece = data[moveorder[i]];
		bool isWinner = true;

		//check if there are enough pieces horizontally by getting x coordinate
		int yPos = moveorder[i] / boardSize;
		int xPos = moveorder[i] - yPos * boardSize;
		if (xPos <= boardSize - 5) {
			//check horizontally
			for (size_t j = moveorder[i]; j < 5 + moveorder[i]; j++) {
				if (data[j] != piece) {
					isWinner = false;
					break;
				}
			}

			if (isWinner)
				return piece;
		}

		//check horizontally
		isWinner = true;
		//check if vertical win is possible
		if (yPos <= boardSize - 5) {
			for (size_t j = 0; j < 5; j++) {
				if (data[j * boardSize + moveorder[i]] != piece) {
					isWinner = false;
					break;
				}
			}

			if (isWinner)
				return piece;
		}

		//check staircase
		//...┬─┬─┬─┬─┬─┐
		//...┼─┼─┼─┼─X─┤
		//...┼─┼─┼─X─┼─┤
		//...┼─┼─X─┼─┼─┤
		//...┼─X─┼─┼─┼─┤
		//...X─┼─┼─┼─┼─┤
		//^^^^like this^^^^
		//this took way to much time to make
		isWinner = true;
		if (yPos <= boardSize - 5 && xPos <= boardSize - 5) {
			for (size_t j = 1; j < 5; j++) {
				if (data[boardSize * j + moveorder[i] + j] != piece) {
					isWinner = false;
					break;
				}
			}

			if (isWinner)
				return piece;
		}

		//check staircase
		//...┬─┬─┬─┬─┬─┐
		//...X─┼─┼─┼─┼─┤
		//...┼─X─┼─┼─┼─┤
		//...┼─┼─X─┼─┼─┤
		//...┼─┼─┼─X─┼─┤
		//...┼─┼─┼─┼─X─┤
		//^^^^like this^^^^
		//this took way to much time to make
		isWinner = true;
		if (yPos <= boardSize - 5 && xPos >= 4) {
			for (size_t j = 1; j < 5; j++) {
				if (data[boardSize * j + moveorder[i] - j] != piece) {
					isWinner = false;
					break;
				}
			}

			if (isWinner)
				return piece;
		}
		
	}
	return 255;
}


int staticEvaluation(byte* data, int boardSize, bool whiteTurn, const std::vector<unsigned int>& moveorder) {

	movesSearched++;
	int score = 0;
	byte wincheck = checkWin(data, boardSize, moveorder);
	if (wincheck != 255) {
		if (wincheck == 1) {
			score = INT_MAX;
		}
		else
			score = INT_MIN;

		return score;
	}

	for (size_t i = 0; i < moveorder.size(); i++) {
		//1 marks white piece and 2 black!!
		//white wants the highest score

		byte piece = data[moveorder[i]];
			
		int yPos = moveorder[i] / boardSize;
		int xPos = moveorder[i] - yPos * boardSize;
		//check for how many horizontally
		for (int j = 1; j < 5; j++) {
			if (piece != data[moveorder[i] + j] || j >= boardSize) {
				//if (!(xPos <= boardSize - 5) || data[moveorder[i] + j] != 0)
				//	j--;
				//
				//if (xPos == 0)
				//	j--;
				//else if (moveorder[i] > 0)
				//	//check if there are 4 in a row and only one defender meaning certain win
				//	if (data[moveorder[i] - 1] != 0 && j == 4 && !((bool)(piece - 1)) == whiteTurn)
				//		j++;
				//	else if (data[moveorder[i] - 1] != 0)
				//		j--;

				if (j > 1)
					if (piece == 2)
						score -= pow(j, 2);
					else
						score += pow(j, 2);
				break;
			}
		}

		//check vertically
		for (int j = 0; j < 5; j++) {
			if (piece != data[moveorder[i] + j * boardSize] || yPos + j >= boardSize) {
				if (j > 1)
					if (piece == 2)
						score -= pow(j, 2);
					else
						score += pow(j, 2);
				break;
			}
		}

		//check diagonal right
		for (int j = 0; j < 5; j++) {
			if (piece != data[moveorder[i] + j * boardSize + j] || yPos + j >= boardSize || j >= boardSize) {
				if (j > 1)
					if (piece == 2)
						score -= pow(j, 2);
					else
						score += pow(j, 2);
				break;
			}
		}

		//check diagonal left
		for (int j = 0; j < 5; j++) {
			if (piece != data[moveorder[i] + j * boardSize - j] || yPos + j >= boardSize) {
				if (j > 1)
					if (piece == 2)
						score -= pow(j, 2);
					else
						score += pow(j, 2);
				break;
			}
			
		}
	}

	return score;
}

std::vector<int> getAllPossibleMoves(byte* data, int boardSize, const std::vector<unsigned int>& moveorder) {
	bool empty = true;
	std::vector<int> returnvalue;
	for (size_t i = 0; i < moveorder.size(); i++) {
		empty = false;

		int yPos = moveorder[i] / boardSize;
		int xPos = moveorder[i] - yPos * boardSize;

		//if the stone is not on the right most edge
		if (xPos < boardSize - 1) {
			if (yPos < boardSize - 1) 
				if (data[moveorder[i] + 1 + boardSize] == 0)
					returnvalue.push_back(moveorder[i] + 1 + boardSize);
				
			if (data[moveorder[i] + 1] == 0) 
				returnvalue.push_back(moveorder[i] + 1);

			if (yPos != 0) 
				if (data[moveorder[i] + 1 - boardSize] == 0)
					returnvalue.push_back(moveorder[i] + 1 - boardSize);
		}

		//left edge
		if (xPos != 0) {
			if (yPos < boardSize - 1)
				if (data[moveorder[i] - 1 + boardSize] == 0)
					returnvalue.push_back(moveorder[i] - 1 + boardSize);

			if (data[moveorder[i] - 1] == 0)
				returnvalue.push_back(moveorder[i] - 1);

			if (yPos != 0)
				if (data[moveorder[i] - 1 - boardSize] == 0)
					returnvalue.push_back(moveorder[i] - 1 - boardSize);
		}

		//up
		if (yPos != 0) {
			if (data[moveorder[i] - boardSize] == 0)
				returnvalue.push_back(moveorder[i] - boardSize);
		}

		//down
		if (yPos < boardSize - 1) 
			if (data[moveorder[i] + boardSize] == 0)
				returnvalue.push_back(moveorder[i] + boardSize);
	}

	if (empty) {
		returnvalue.push_back((boardSize * boardSize) / 2);
	}

	std::sort(returnvalue.begin(), returnvalue.end());
	returnvalue.erase(std::unique(returnvalue.begin(), returnvalue.end()), returnvalue.end());

	return returnvalue;
}


int minimax(byte* data, int boardSize, unsigned int depth, bool whiteTurn, std::vector<unsigned int>& moveorder, int alpha = INT_MIN, int beta = INT_MAX) {
	auto win = checkWin(data, boardSize, gameDataMoveOrder);
	if (win != 255) {
		if (win == 1) {
			return INT_MAX;
		}
		else
			return INT_MIN;
	}
	else if (depth == 0)
		return staticEvaluation(data, boardSize, whiteTurn, moveorder);

	//maximize
	if (whiteTurn) {
		int maxEval = INT_MIN;
		auto allmoves = getAllPossibleMoves(data, boardSize, moveorder);
		for (size_t i = 0; i < allmoves.size(); i++) {
			//set stone in array
			data[allmoves[i]] = 1;
			//push into move order
			moveorder.push_back(allmoves[i]);

			//do the thing
			auto eval = minimax(data, boardSize, depth - 1, !whiteTurn, moveorder, alpha, beta);

			moveorder.erase(moveorder.end() - 1);
			maxEval = max(eval, maxEval);
			alpha = max(alpha, eval);
			//reset later
			data[allmoves[i]] = 0;

			if (beta <= alpha)
				break;
		}

		return maxEval;
	} else {
		int minEval = INT_MAX;
		auto allmoves = getAllPossibleMoves(data, boardSize, moveorder);
		for (size_t i = 0; i < allmoves.size(); i++) {
			//set stone in array
			data[allmoves[i]] = 2;
			moveorder.push_back(allmoves[i]);

			auto eval = minimax(data, boardSize, depth - 1, !whiteTurn, moveorder, alpha, beta);

			moveorder.erase(moveorder.end() - 1);
			minEval = min(eval, minEval);
			beta = min(eval, beta);
			//reset later
			data[allmoves[i]] = 0;

			if (beta <= alpha)
				break;
		}

		return minEval;
	}
}

void calculateBestMoves() {
	thread_local byte* personalGamedata = (byte*)malloc(boardSize * boardSize);
	thread_local std::vector<unsigned int> personalMoves(gameDataMoveOrder.begin(), gameDataMoveOrder.end());
	memcpy(personalGamedata, gameData, boardSize * boardSize);

	for (size_t i = 0; i < sizeOfMoves; i++) {
		minimaxMutex.lock();
		auto& d = allTasks[i];
		if (d.done == false) {
			d.done = true;
		}
		else {
			minimaxMutex.unlock();
			continue;
		}
		minimaxMutex.unlock();
		personalGamedata[d.move] = 1;
		personalMoves.push_back(d.move);
		allTasks[i].score = minimax(personalGamedata, boardSize, depth, false, personalMoves);
		personalMoves.erase(personalMoves.end() - 1);
		personalGamedata[d.move] = 0;
	}

	free(personalGamedata);
}

static void callback(int windowInstance, GWindow::WindowEvent event, void* data) {
	switch (event) {
	case GWindow::WindowEvent::MOUSE_MOVE:
	{
		mousePosition = *(GGeneral::Point<int>*)data;
		mousePosition.y = mousePosition.y * -1 + mainWindow->getWindowDrawSize().height;
		break;
	}
	case GWindow::WindowEvent::WINDOW_STATE:
	case GWindow::WindowEvent::WINDOW_RESIZE:
	case GWindow::WindowEvent::WINDOW_FOCUS:
	case GWindow::WindowEvent::WINDOW_MOVE:
		drawChanges = true;
		break;
	case GWindow::WindowEvent::KEY_PRESS: 
	{
		auto key = (GWindow::VK)(int)data;

		switch (key) {
		case GWindow::VK::LEFT_MB:
			isLMousePressed = true;
			break;
		case GWindow::VK::RIGHT_MB:
			isRMousePressed = true;
			break;
		case GWindow::VK::ALT:
			isAltPressed = true;
			break;
		case GWindow::VK::F4:
			isF4Pressed = true;
			break;
		}

		break;
	}
	case GWindow::WindowEvent::KEY_RELEASE:
	{
		auto key = (GWindow::VK)(int)data;

		switch (key) {
		case GWindow::VK::LEFT_MB:
			isLMousePressed = false;
			break;
		case GWindow::VK::RIGHT_MB:
			isRMousePressed = false;
			break;
		case GWindow::VK::ALT:
			isAltPressed = false;
			break;
		case GWindow::VK::F4:
			isF4Pressed = false;
			break;
		//case GWindow::VK::ESCAPE:
		//	memset(gameData, 0, boardSize * boardSize);
		//	drawChanges = true;
		//	break;
		}
		break;
	}
	case GWindow::WindowEvent::WINDOW_CLOSE:
	{
		break;
	}
	default:
		break;
	}

}

//can be used by another thread to force a draw
void forceDraw() {
	drawChanges = true;

	//send any kind of message to stop the blocking of the main thread if called by another thread
	PostMessage((HWND)mainWindow->getID(), WM_KEYUP, VK_F24, 0);
}

void clearBoard() {
	memset(gameData, 0, boardSize * boardSize);
	gameDataMoveOrder.clear();
	isWhiteTurn = false;
	winState = false;
	forceDraw();
}


static void serverThreadUpdateFunction() {
	if (isServer) {
		LOG("---Server Thread has started---");
		LOG("Waiting for connection");
		LOG("Searching on port: ", port);

		serverSocket = new GNetworking::ServerSocket(port);

		receiver = serverSocket->accept();
		isMultiplayer = true;
		LOGI("Connected!");

		for (;;) {
			if (!serverSocket->isConnected(receiver)) {
				LOGE("Connection lost to player");
				break;
			}
			auto p = serverSocket->receive(receiver);
			globalMutex.lock();
			if (p.data != nullptr) {
				allPackages.push_back(std::move(p));
			}
			globalMutex.unlock();
			//notify main thread that something was received
			forceDraw();
		}
	} else {
		LOG("---Multiplayer Thread has started---");
		LOG("Waiting for connection");
		LOG("Searching for IP: ", ip, ":", port);

		clientSocket = new GNetworking::Socket(ip, port);

		if (!clientSocket->isConnected()) {
			LOGE(GGeneral::ErrorHandler::getLastError());
			clientSocket->~Socket();
			delete clientSocket;
		}
		else {
			LOG("Connected");
			isMultiplayer = true;
			for (;;) {
				if (!clientSocket->isConnected()) {
					LOGE("Connection lost to host");
					break;
				}

				auto p = clientSocket->receive();
				globalMutex.lock();
				if (p.data != nullptr) {
					allPackages.push_back(std::move(p));
				}
				globalMutex.unlock();
				//notify main thread that something was received
				forceDraw();
			}
		}
	}

	isMultiplayer = false;
	isServer = false;
	SetWindowText((HWND)mainWindow->getID(), L"Go");
	LOG("Multiplayer thread terminated");
}

bool sendData(std::string s) {
	if (isMultiplayer) {
		byte* data = new byte[s.size()];
		memcpy(data, s.c_str(), s.size());

		globalMutex.lock();
		if (isServer) {
			serverSocket->send(receiver, data, s.size());
		} else {
			clientSocket->send(data, s.size());
		}
		globalMutex.unlock();
		delete[] data;
		return true;
	}
	return false;
}

static void commandLineThreadFunction() {
	LOGI("Command line thread started");
	std::string s;

	for (;;) {
		getline(std::cin, s);

		if (s == "ip") {
			if (isMultiplayer == false) {
				LOGI("Currently in non multiplayer mode");
			}
			else {
				if (isServer)
					LOGI("Currently listening on port: ", port);
				else
					LOGI("Currently searching for: ", ip, ":", port);
			}
		}
		if (s == "ai") {
			if (!isMultiplayer)
				if (playWithAI) {
					playWithAI = false;
					LOGI("Now in two player mode");
				}
				else {
					clearBoard();
					playWithAI = true;
					LOGI("Now playing against AI");
				}
			else
				LOGW("This is currently not possible");
		}
		else if (s == "help") {
			GGeneral::String d = \
				"\n---Offline Mode---\n"\
				"clear: Will clear the board\n"\
				"show: Will show the window if hidden\n"\
				"hide: Will hide the window if shown\n"\
				"exit: Will close the program\n"
				"\n"
				"portconfig: Enter a new port to set the port\n"\
				"ipconfig: Set a new IP\n"\
				"connect: Will try to connect to the given IP and Port\n"\
				"host: Will listen on given port\n"\
				"\n"\
				"depth: Set a new depth for the AI to calculate\n"\
				"worker: Set amount of threads to calculate for the AI\n"\
				"ai: Turn on or off Singleplayer or 2 Player mode\n"\
				"\n"\
				"---Online Mode---\n"\
				"start: Will start a session. The host starts\n"\
				"stop: Will stop a session\n"\
				"ostart: Will start a session. The host does not start\n"\
				"ip: Will return the port and/or IP\n"\
				"disconnect: Will disconnect\n"\
				"msg [message here]: Will send a message";
			LOGI(d);
		}
		else if (s == "clear") {
			if (isMultiplayer && !isServer) {
				LOGI("Can't clear board due to not being host");
			}
			else {
				sendData("reset1");
				clearBoard();
				LOGI("Cleared board");
			}
		}
		else if (s == "show") {
			mainWindow->setState(GWindow::WindowState::NORMAL);
			forceDraw();
			LOGI("Window state is now normal");
		} else if (s == "portconfig") {
			LOGI("Enter port: ");
			getline(std::cin, s);
			//get port
			try {
				port = std::stoi(s);
			}
			catch (const std::exception& e) {
				LOGE("Cannot convert port into int: ", e.what());
			}
			LOGI("Port is now set to: ", port);
		} else if (s == "ipconfig") {
			LOGI("Enter IP: ");
			getline(std::cin, s);
			ip = GGeneral::String(s.c_str());
			LOGI("IP is now set to: ", ip);
		}
		else if (s == "hide") {
			mainWindow->setState(GWindow::WindowState::HIDDEN);
			LOGI("Window is now hidden");
		}
		else if (s == "exit") {
			mainWindow->sendCloseRequest();
			LOGI("Sent close request");
			forceDraw();
		}
		else if (s == "connect") {
			if (isMultiplayer)
				LOGW("This is currently not possible");
			else {
				SetWindowText((HWND)mainWindow->getID(), L"Go - Currently online");
				isServer = false;
				//start the multiplayer thread
				multiplayerThread = new std::thread(serverThreadUpdateFunction);
			}
		}
		else if (s == "disconnect") {
			if (!isMultiplayer)
				LOGW("This is currently not possible");
			else {
				if (isServer && serverSocket != nullptr) {
					serverSocket->forceDisconnect(receiver);
					delete serverSocket;
				}
				else if (clientSocket != nullptr) {
					clientSocket->disconnect();
					delete clientSocket;
				}

				isServer = false;
				isMultiplayer = false;
			}
		}
		else if (s == "host") {
			if (isMultiplayer)
				LOGW("This is currently not possible");
			else {
				SetWindowText((HWND)mainWindow->getID(), L"Go - Serverside");
				isServer = true;
				//start the multiplayer thread
				multiplayerThread = new std::thread(serverThreadUpdateFunction);
			}
		}
		else if (s.find("msg ") == 0) {
			if (sendData(s)) {
				LOG("Message has been send");
			}
			else {
				LOGW("This is currently not possible");
			}
		}
		else if (s == "start") {
			if (!isMultiplayer || !isServer)
				LOGW("This is currently not possible");
			else {
				//start session
				sendData("1startsession");
				LOG("Starting session");
				mainWindow->setState(GWindow::WindowState::NORMAL);
				clearBoard();
				isWhite = false;
					
			}
		}
		else if (s == "ostart") {
			if (!isMultiplayer || !isServer)
				LOGW("This is currently not possible");
			else {
				//start session
				sendData("0startsession");
				LOG("Starting session");
				mainWindow->setState(GWindow::WindowState::NORMAL);
				clearBoard();
				isWhite = true;
			}
		}
		else if (s == "stop") {
			if (!isMultiplayer || !isServer)
				LOGW("This is currently not possible");
			else {
				//start session
				sendData("stahp");
				LOG("Ending session");
				mainWindow->setState(GWindow::WindowState::HIDDEN);

			}
		}
		else if (s == "depth") {
			LOGI("Enter new Depth (old: ", depth, "): ");
			getline(std::cin, s);
			//convert
			try {
				depth = std::stoi(s);
			}
			catch (const std::exception& e) {
				LOGE("Cannot convert port into int: ", e.what());
			}
			LOGI("Depth is now set to: ", depth);
		} else if (s == "worker") {
			LOGI("Enter amount of threads (old: ", amountOfWorker, "): ");
			getline(std::cin, s);
			//convert
			try {
				amountOfWorker = std::stoi(s);
			}
			catch (const std::exception& e) {
				LOGE("Cannot convert port into int: ", e.what());
			}
			LOGI("Amount of threads is now set to: ", amountOfWorker);
		}
		else {
			LOGI("Unrecognized command. Type help for a list of all possible commands");
		}
	}
}

bool init(int argc, char** argv) {
	//init the renderer instance
	auto succ = GRenderer::init();
	//no multi threading...
	GGeneral::Logger::terminateThread();
	G_ASSERT_EX(succ, GGeneral::ErrorHandler::printAll(); return false;);

	//create window and make it visible
	mainWindow = new GWindow::Window("Go");
	mainWindow->setWindowHints(GWindow::Window::ContextHints::PROFILE_MASK, 0);
	succ = mainWindow->createOpenGLcontext();
	G_ASSERT_EX(succ, GGeneral::ErrorHandler::printAll(); return false;);
	succ = mainWindow->setOpenGLContextActive();
	G_ASSERT_EX(succ, GGeneral::ErrorHandler::printAll(); return false;);
	mainWindow->setCallbackFunction(callback);
	mainWindow->setMinimumWindowSize({400, 400});
	mainWindow->setIcon("rsc/icon.ico");

	GRenderer::enableBlend();

	//Print some nice stuff
	LOGI("Using Version: ", G_RENDERER_VERSION);
	LOGI("Using GPU: ", GRenderer::getGLString(GRenderer::GLString::RENDERER));
	LOGI("Vendor: ", GRenderer::getGLString(GRenderer::GLString::VENDOR));
	LOGI("OpenGL Version: ", GRenderer::getGLString(GRenderer::GLString::VERSION));

	amountOfWorker = std::thread::hardware_concurrency() / 2;
	if (amountOfWorker == 0)
		amountOfWorker = 1;

	//Parse arguments and check for server
	//check if the programm should start in server mode
	std::vector<GGeneral::String> allArgs;
	for (size_t i = 0; i < argc; i++) {
		allArgs.push_back(GGeneral::String(argv[i]));
	}
	if(argc >= 3) {
		if (allArgs[1].compare("server")) {
			SetWindowText((HWND)mainWindow->getID(), L"Go - Serverside");
			//get port
			try {
				port = std::stoi(allArgs[2].cStr());
			}
			catch (const std::exception& e) {
				LOGE("Cannot convert port into int: ", e.what());
				exit(-1);
			}
			isServer = true;
			
			multiplayerThread = new std::thread(serverThreadUpdateFunction);
		} else if (allArgs[1].compare("noserver") && argc > 3) {
			SetWindowText((HWND)mainWindow->getID(), L"Go - Currently online");
			//get port
			try {
				port = std::stoi(allArgs[3].cStr());
			}
			catch (const std::exception& e) {
				LOGE("Cannot convert port into int: ", e.what());
				exit(-1);
			}
			//this is a nightmare
			ip = GGeneral::String(allArgs[2]);

			multiplayerThread = new std::thread(serverThreadUpdateFunction);
		}
	} else
		mainWindow->setState(GWindow::WindowState::NORMAL);
		

	//Load images
	IblackPiece      = GFile::Graphics::loadImage("rsc/black_circle.png");
	IblackPieceTrans = GFile::Graphics::loadImage("rsc/black_circle_alpha.png");
	IwhitePiece      = GFile::Graphics::loadImage("rsc/white_circle.png");
	IwhitePieceTrans = GFile::Graphics::loadImage("rsc/white_circle_alpha.png");

	G_ASSERT_EX(IblackPiece      != nullptr, GGeneral::ErrorHandler::printAll(); return false;);
	G_ASSERT_EX(IblackPieceTrans != nullptr, GGeneral::ErrorHandler::printAll(); return false;);
	G_ASSERT_EX(IwhitePiece      != nullptr, GGeneral::ErrorHandler::printAll(); return false;);
	G_ASSERT_EX(IwhitePieceTrans != nullptr, GGeneral::ErrorHandler::printAll(); return false;);

	blackPiece      = new GRenderer::Texture(*IblackPiece);
	blackPieceTrans = new GRenderer::Texture(*IblackPieceTrans);
	whitePiece      = new GRenderer::Texture(*IwhitePiece);
	whitePieceTrans = new GRenderer::Texture(*IwhitePieceTrans);

	G_ASSERT_EX(blackPiece != nullptr, GGeneral::ErrorHandler::printAll(); return false;);
	G_ASSERT_EX(whitePiece != nullptr, GGeneral::ErrorHandler::printAll(); return false;);
	
	//Initialize graphics
	succ = GGraphics::init();
	G_ASSERT_EX(succ, GGeneral::ErrorHandler::printAll(); return false;);

	//create game information
	//0 Marks no piece
	//1 marks white piece
	//2 marks black piece
	gameData = new byte[boardSize * boardSize];
	clearBoard();

	//Start command line thread
	commandLineThread = new std::thread(commandLineThreadFunction);

	return true;
}

void update() {
	//close thing you know
	if (isF4Pressed && isAltPressed)
		mainWindow->sendCloseRequest();

	//get new mouse position
	auto last = boardMousePosition;
	updateMouseBoardPosition();
	if (last != boardMousePosition)
		drawChanges = true;

	//placing of the stones
	if(isLMousePressed && boardMousePosition != -1 && winState == false) {
		//only if multiplayer
		if (isMultiplayer) {
			if(isWhite == isWhiteTurn) {
				if (gameData[boardMousePosition] == 0) {
					gameData[boardMousePosition] = !isWhiteTurn + 1;
					gameDataMoveOrder.push_back(boardMousePosition);
					isWhiteTurn = !isWhiteTurn;

					GGeneral::String data;
					data << boardMousePosition;
					data << "placing";
					data << isWhiteTurn;
					//not good but it will work
					sendData(data.cStr());

					//check if someone won
					byte win = checkWin(gameData, boardSize, gameDataMoveOrder);
					if (win != 255) {
						if (win == 1) {
							LOGI("White has won");
						}
						else if (win == 2) {
							LOGI("Black has won");
						}
						winState = true;
						//mainWindow->setState(GWindow::WindowState::HIDDEN);
					}
					drawChanges = true;
					//reset the bool so the mouse has to be pressed again
					isLMousePressed = false;
				}
			}
		}
		else {
			if (gameData[boardMousePosition] == 0 || gameData[boardMousePosition] == 3) {
				gameData[boardMousePosition] = !isWhiteTurn + 1;
				gameDataMoveOrder.push_back(boardMousePosition);
				isWhiteTurn = !isWhiteTurn;

				//check if someone won
				byte win = checkWin(gameData, boardSize, gameDataMoveOrder);
				if (win != 255) {
					if (win == 1) {
						LOGI("White has won");
					}
					else if (win == 2) {
						LOGI("Black has won");
					}
					//mainWindow->setState(GWindow::WindowState::HIDDEN);
					winState = true;
				}
				//only do AI if play with AI and if there are still moves left to play
				else if (isWhiteTurn && playWithAI) {
					auto allmoves = getAllPossibleMoves(gameData, boardSize, gameDataMoveOrder);

					for (size_t i = 0; i < allmoves.size(); i++) {
						allTasks.push_back({allmoves[i]});
					}
					sizeOfMoves = allmoves.size();

					std::vector<std::thread> allWorker;
					for (size_t i = 0; i < amountOfWorker; i++) {
						allWorker.push_back(std::thread(calculateBestMoves));
					}

					for (size_t i = 0; i < amountOfWorker; i++) {
						allWorker[i].join();
					}

					int maxEval = INT_MIN;
					int move = allmoves[0];
					for (size_t i = 0; i < allmoves.size(); i++) {
						auto eval = allTasks[i].score;
						if (eval > maxEval) {
							maxEval = eval;
							move = allmoves[i];
						}
					}

					LOGI("Amount of position searched: ", movesSearched.load(), "; Evaluation: ", maxEval);
					allTasks.clear();
					movesSearched = 0;
					gameData[move] = 1;
					gameDataMoveOrder.push_back(move);

					isWhiteTurn = false;


					//check if someone won
					win = checkWin(gameData, boardSize, gameDataMoveOrder);
					if (win != 255) {
						if (win == 1) {
							LOGI("White has won");
						}
						else if (win == 2) {
							LOGI("Black has won");
						}
						//mainWindow->setState(GWindow::WindowState::HIDDEN);
						winState = true;
					}
				}

				drawChanges = true;
				//reset the bool so the mouse has to be pressed again
				isLMousePressed = false;
			}
		}
	}

	//check if something has been received by the other networking thread
	globalMutex.lock();

	for (size_t i = 0; i < allPackages.size(); i++) {
		auto data = GGeneral::String((char*)allPackages[i].data);
		//reset transmission
		if (data.compare("reset1")) {
			clearBoard();
		}

		//message command
		if (data.find("msg") == 0) {
			LOG(data.cStr() + 3);
		}

		//session start
		if (data.find("startsession") == 1) {
			LOG("Session started by host");
			mainWindow->setState(GWindow::WindowState::NORMAL);
			clearBoard();
			if (data.cStr()[0] == '0') {
				isWhite = false;
			} else {
				isWhite = true;
			}
		}

		//stahp
		if (data.compare("stahp")) {
			LOG("Session stopped by host");
			mainWindow->setState(GWindow::WindowState::HIDDEN);
		}

		if (data.find("placing") != GGeneral::String::npos) {
			auto pos = data.find("placing");
			std::string s;
			for (size_t i = 0; i < pos; i++) {
				s += data.cStr()[i];
			}
			auto d = std::stoi(s);
			isWhiteTurn = data.cStr()[data.getSize() - 1] == '1';
			gameData[d] = isWhiteTurn + 1;
			gameDataMoveOrder.push_back(d);

			//check if someone won
			byte win = checkWin(gameData, boardSize, gameDataMoveOrder);
			if (win != 255) {
				if (win == 1) {
					LOGI("White has won");
				}
				else if (win == 2) {
					LOGI("Black has won");
				}
				mainWindow->setState(GWindow::WindowState::HIDDEN);
			}
		}
	}

	allPackages.clear();
	globalMutex.unlock();
}

int main(int argc, char** argv) {
	//Init the stuff
	if (init(argc, argv) == false)
		return -1;

	//Dont exit the loop until getting a close request
	while (!mainWindow->getCloseRequest()) {
		update();
		if (drawChanges)
			paint();

		//get events
		mainWindow->fetchEvents(true);
	}

	//print the rest of the warnings and errors and clean up
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	GGeneral::ErrorHandler::printAll();
	return 0;
}