#pragma once

#include "ofMain.h"
#include "Lock.hpp"
#include "Line.hpp"
#include "Target.hpp"
enum game_state { running, startMenu, endMenu };
class Game {
	private:
		Lock l = Lock(glm::vec2{ 1,1 }, 0.5, ofColor(0, 0, 0), ofColor(0, 0, 0), 10);
		Line line = Line(glm::vec2{ 1,1 }, ofColor(240, 55, 20), 10.0, 10.0, 10.0, 0);
		float diam;
		glm::vec2 pos;
		float lineAngle = 90;
		float targetAngle = ofRandom(360);
		bool rotating = true;
		ofTrueTypeFont mainFont;
		ofTrueTypeFont menuFont;
		glm::vec2 Game::getPos(float angle);
		int startNumber = 30;
		float minTargetDist = 175.0; //minimum distance for the next targets location from the last one.
		float startMinTargetDist = minTargetDist;
		ofColor backgroundColor = ofColor(0, 0, 0);
		Target explodingTarget = target;
		bool isExploding = false;
		bool onTarget = false;

	public:
		void draw();
		void setup();
		void update();
		bool stopLine();
		float getNewTargetAngle(float last);
		void restart();
		void menu(bool mousePressed);
		int score;
		bool keyPressed;
		game_state gameState = startMenu;
		ofSoundPlayer missSound;
		ofSoundPlayer backgroundMusic;
		Target target = Target(glm::vec2{ 1,1 }, 50, ofColor(225, 205, 9), 10);
		std::string menuMessage = "Pop the Lock";
};
