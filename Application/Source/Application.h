
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

struct Mouse {
	Mouse() {
		reset();
	}
	void reset() {
		x_diff = 0;
		y_diff = 0;
		scroll = 0;
		left = 0;
		right = 0;
		up = 0;
		down = 0;
	}
	bool left, right, up, down;
	int x_diff, y_diff;
	float scroll;
};

class Application {
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
private:
	//Declare a window object
	StopWatch m_timer;
};
#endif