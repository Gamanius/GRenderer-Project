#include <GRenderer.h>
#include <iostream>
#include <string>

GWindow::Window* window;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

unsigned int Client_width;
unsigned int Client_height;

bool W_pressed = false;
bool S_pressed = false;
bool UP_pressed = false;
bool DOWN_pressed = false;

bool start = true;

GGeneral::String ip;
unsigned int port;
bool isServer = false;
GNetworking::Socket* socket = nullptr;
GNetworking::ServerSocket* server = nullptr;
unsigned int client = 0;
byte* defaultBuffer;

GGeneral::Rectangle<float> player1 = { 10, 0, 10, 100 }, player2 = { WINDOW_WIDTH - 30, 0, 10, 100 };
GGeneral::Rectangle<float> ball = { 1264 / 2.0f - 5, 681 / 2.0f - 5, 10, 10 };
GMath::vec2<float> ballVelocity;

unsigned long counter = 0;

#define abort() window->setState(GWindow::WindowState::HIDDEN); GGeneral::ErrorHandler::printAll(); LOGI("Program end. Press enter to close this window"); GGeneral::Logger::wait(); std::cin.get(); exit(-1);

void callback(int id, GWindow::WindowEvent events, void* data) {
	if (events == GWindow::WindowEvent::KEY_PRESS) {
		auto k = (GWindow::VK)(int)data;
		if (isServer) {
			if (k == GWindow::VK::W) {
				W_pressed = true;
			}
			if (k == GWindow::VK::S) {
				S_pressed = true;
			}
		}
		else {
			if (k == GWindow::VK::UPARROW) {
				UP_pressed = true;
			}
			if (k == GWindow::VK::DOWNARROW) {
				DOWN_pressed = true;
			}
		}
		if (k == GWindow::VK::ESCAPE) {
			window->forceCloseRequest();
		}
	}
	if (events == GWindow::WindowEvent::KEY_RELEASE) {
		auto k = (GWindow::VK)(int)data;
		if (isServer) {
			if (k == GWindow::VK::W) {
				W_pressed = false;
			}
			if (k == GWindow::VK::S) {
				S_pressed = false;
			}
		}
		else {
			if (k == GWindow::VK::UPARROW) {
				UP_pressed = false;
			}
			if (k == GWindow::VK::DOWNARROW) {
				DOWN_pressed = false;
			}
		}
	}
}

void init() {
	defaultBuffer = new byte[MAX_NET_BUFFER_SIZE];

	auto s = window->getWindowDrawSize();
	GGraphics::setViewport(s);
	Client_height = s.height;
	Client_width = s.width;

	player1 = { 10, s.height / 2.0f - 50, 10, 100 };
	player2 = { s.width - 20.0f, s.height / 2.0f - 50, 10, 100 };

	ballVelocity[1] = -1;
	ballVelocity[0] = -1;
}

void draw() {
	using namespace GGraphics;
	setColor({ 255, 255, 255 });
	//Draw player
	drawRect({ (int)player1.position.x,(int)player1.position.y, (int)player1.dimension.width,(int)player1.dimension.height });
	drawRect({ (int)player2.position.x,(int)player2.position.y, (int)player2.dimension.width,(int)player2.dimension.height });
	setColor({ 200, 200, 200 });
	//Draw lines in the middle
	static int amount = 16;
	for (size_t i = 0; i < amount; i++) {
		if (i % 2 == 0)
			drawRect({ (int)((Client_width / 2.0f) - 5), (int)(((Client_height / (float)amount) * i) + (Client_height / (float)amount / 2.0f)), 10,(int)(Client_height / (float)amount) });
	}
	setColor({ 255, 255, 255 });
	//Draw the ball
	drawRect({ (int)ball.position.x,(int)ball.position.y, (int)ball.dimension.width,(int)ball.dimension.height });
}

void update() {
	counter++;
	auto delta = GRenderer::delta();

	if (isServer) {
		static bool wpress = false, spress = false;
		static GMath::vec2<float> ballvelo;

		if (wpress != W_pressed || spress != S_pressed || round(ballvelo[0]) != round(ballVelocity[0]) || round(ballvelo[1]) != round(ballVelocity[1])) {
			wpress = W_pressed;
			spress = S_pressed;
			ballvelo[0] = ballVelocity[0];
			ballvelo[1] = ballVelocity[1];

			auto send = reinterpret_cast<float*>(defaultBuffer);
			send[0] = wpress;
			send[1] = spress;
			send[2] = ballVelocity[0];
			send[3] = ballVelocity[1];
			send[4] = player1.position.x;
			send[5] = player1.position.y;
			send[6] = ball.position.x;
			send[7] = ball.position.y;
			server->send(client, defaultBuffer, sizeof(float) * 8);
		}

		auto pack = server->receive(client);
		if (pack.size == -1) {
			LOGI("Connection has been reset. Program needs to terminate");
			abort();
		}
		if (pack.data != nullptr) {
			int* pos = (int*)pack.data;
			player2.position.x = pos[0];
			player2.position.y = pos[1];
			UP_pressed = pos[2];
			DOWN_pressed = pos[3];
		}
	}
	else {
		static bool uppress = false, downpress = false;
		auto pack = socket->receive();
		if (!socket->isConnected()) {
			LOGI("Connection has been reset. Program needs to terminate");
			abort();
		}
		else if (pack.data != nullptr) {
			float* pos = (float*)pack.data;
			W_pressed = pos[0];
			S_pressed = pos[1];
			ballVelocity[0] = pos[2];
			ballVelocity[1] = pos[3];

			player1.position.x = pos[4];
			player1.position.y = pos[5];
			ball.position.x = pos[6];
			ball.position.y = pos[7];
		}

		if (uppress != UP_pressed || downpress != DOWN_pressed) {
			uppress = UP_pressed;
			downpress = DOWN_pressed;
			auto send = reinterpret_cast<int*>(defaultBuffer);
			send[0] = player2.position.x;
			send[1] = player2.position.y;
			send[2] = UP_pressed;
			send[3] = DOWN_pressed;
			socket->send(defaultBuffer, sizeof(float) * 4);
		}
	}

	if (UP_pressed) {
		player2.position.y += delta / 2.0f;
	}
	if (DOWN_pressed) {
		player2.position.y -= delta / 2.0f;
	}

	if (W_pressed) {
		player1.position.y += delta / 2.0f;
	}
	if (S_pressed) {
		player1.position.y -= delta / 2.0f;
	}

	if (player1.position.y < 0) {
		player1.position.y = 0;
	}
	else if (player1.position.y + 100 > Client_height) {
		player1.position.y = Client_height - 100;
	}

	if (player2.position.y < 0) {
		player2.position.y = 0;
	}
	else if (player2.position.y + 100 > Client_height) {
		player2.position.y = Client_height - 100;
	}

	if (!start) {
		ball.position.x += ballVelocity[0] * delta / 4.0f;
		ball.position.y += ballVelocity[1] * delta / 4.0f;
	}

	if (ball.position.y < 0) {
		ball.position.y = 0;
		ballVelocity[1] = 1;
	}
	else if (ball.position.y + 10 > Client_height) {
		ball.position.y = Client_height - 10;
		ballVelocity[1] = -1;
	}

	//Custom collision checking
	if ((ball.position.x < player1.position.x + player1.dimension.width) && (ball.position.y - ball.dimension.height <= player1.position.y + player1.dimension.height) && (ball.position.y >= player1.position.y))
		ballVelocity[0] = 1;
	if ((ball.position.x + ball.dimension.width > player2.position.x) && (ball.position.y - ball.dimension.height <= player2.position.y + player2.dimension.height) && (ball.position.y >= player2.position.y))
		ballVelocity[0] = -1;

	if ((ball.position.x + ball.dimension.width - 20 > player2.position.x) || (ball.position.x + 20 < player1.position.x + player1.dimension.width)) {
		ball = { 1264 / 2.0f - 5, 681 / 2.0f - 5, 10, 10 };
	}

	//if ((ball.position.x + 20 < player1.position.x + player1.dimension.width)) {
	//	LOGS("Player 2 won somehow...");
	//	GGeneral::Logger::wait();
	//
	//	window->forceCloseRequest();
	//
	//	std::cin.get();
	//}
	//if (ball.position.x + ball.dimension.width - 20 > player2.position.x) {
	//	LOGS("Player 1 won somehow...");
	//	GGeneral::Logger::wait();
	//
	//	window->forceCloseRequest();
	//
	//	std::cin.get();
	//}

	start = false;
}

void parseargs(int argc, const char** argv) {
	if (argc <= 1) {
		LOGF("Missing parameters");
		abort();
	}

	std::vector<GGeneral::String> allParam;
	for (size_t i = 0; i < argc; i++) {
		allParam.push_back(GGeneral::String(argv[i]));
	}

	if (allParam[1].find("noserver") != GGeneral::String::npos) {
		ip = GGeneral::String(allParam[2]);
		port = std::stoi(allParam[3].cStr());
		LOG("Using IP: '", ip, "' on Port: ", port);
		isServer = false;
	}
	else if (allParam[1].find("server") != GGeneral::String::npos) {
		port = std::stoi(allParam[2].cStr());
		LOG("Hosting on Port: ", port);
		isServer = true;
	}
	else {
		LOGF("Couldn't parse parameters");
		abort();
	}
}

int main(int argc, const char** argv) {
	LOGI("Initializing");
	if (!(GRenderer::init() && GNetworking::init())) {
		LOGF("Couldn't initialize");
		abort();
	}
	LOGS("Initialized");

	parseargs(argc, argv);

	if (isServer) {
		LOGI("Searching for other Sockets...");
		server = new GNetworking::ServerSocket(port);
		client = server->accept();
		server->setBlockingMode(false, client);
		if (client == ~0) {
			LOGF("An fatal error occurred while trying to accept Socket");
			abort();
		}
		LOGS("Connected");
	}
	else {
		LOGI("Searching for server...");
		socket = new GNetworking::Socket(ip, port);
		auto b = socket->isConnected();
		socket->setBlockingMode(false);
		if (!b) {
			LOGF("An fatal error occurred while trying to Connect");
			abort();
		}
		LOGS("Connection successful");
	}

	window = new GWindow::Window("Pong C++ Edition", { 50, 50 }, { WINDOW_WIDTH, WINDOW_HEIGHT });
	window->setResizable(false);
	window->createOpenGLcontext();
	window->setOpenGLContextActive(true);
	window->setCallbackFunction(callback);
	window->setState(GWindow::WindowState::NORMAL);
	GGraphics::init();
	init();

	while (!window->getCloseRequest()) {
		GRenderer::clear({ 50, 50, 50 });
		update();
		draw();
		window->swapBuffers();
		window->fetchEvents();
	}

	GGeneral::Logger::wait();
}