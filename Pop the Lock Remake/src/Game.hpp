#pragma once

#include "ofMain.h"
#include "Lock.hpp"
#include "Line.hpp"
#include "Target.hpp"

class Game {
	private:
		Lock l = Lock(glm::vec2{ 1,1 }, 0.5, ofColor(0, 0, 0), ofColor(0, 0, 0), 10);
		Line line = Line(glm::vec2{ 1,1 }, ofColor(240, 55, 20), 10.0, 10.0, 10.0, 0);
		Target target = Target(glm::vec2{ 1,1 }, 50, ofColor(225, 205, 9), 10);
		float diam;
		glm::vec2 pos;
		float lineAngle = 90;
		float targetAngle = ofRandom(360);
		bool rotating = true;
		ofTrueTypeFont myFont;
		glm::vec2 Game::getPos(float angle);
	public:
		void draw();
		void setup();
		void update();
		bool stopLine();
		int score;
};
