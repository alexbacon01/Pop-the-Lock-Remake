#include "Game.hpp"

Lock l = Lock(glm::vec2{ 1,1 }, 0.5, ofColor(0, 0, 0), ofColor(0, 0, 0), 10);
Line line = Line(glm::vec2{ 1,1 }, ofColor(240, 55, 20), 10.0, 10.0, 10.0, 0);
Target target = Target(glm::vec2{ 1,1 }, 50, ofColor(225, 205, 9), 10);

float diam;
glm::vec2 pos;
float lineAngle = 90;
float targetAngle = ofRandom(360);
bool rotating = true;

	void Game::draw() {
		l.draw();
		line.draw();
		target.draw();
	}

	void Game::setup() {
		//Set up the lock
		pos = { ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0 };
		diam = ofGetWindowWidth() / 3.0;
		int res = 50;
		ofColor c1 = ofColor(2, 10, 30);
		ofColor c2 = ofColor(43, 81, 175);
		l.pos = pos;
		l.diam = diam;
		l.middleColor = c1;
		l.outerColor = c2;
		l.resolution = res;

		//Set up the line
		float lineOffset = (diam / 3) / 2;
		line.width = diam / 1.6 - diam / 3;
		line.height = diam / 10;
		line.roundness = 20;
	}

	void Game::update() {
		if (rotating) {
			lineAngle = line.rotate();
		}
		glm::vec2 pointOfBig = pos + glm::vec2{ diam / 1.5 * cos(lineAngle), diam / 1.5 * sin(lineAngle) };
		glm::vec2 pointOfLil = pos + glm::vec2{ diam / 3 * cos(lineAngle), diam / 3 * sin(lineAngle) };
		line.pos = ((pointOfBig + pointOfLil) / 2);

		glm::vec2 pointOfBigT = pos + glm::vec2{ diam / 1.5 * cos(targetAngle), diam / 1.5 * sin(targetAngle) };
		glm::vec2 pointOfLilT = pos + glm::vec2{ diam / 3 * cos(targetAngle), diam / 3 * sin(targetAngle) };
		target.pos = ((pointOfBigT + pointOfLilT) / 2);
	}

	void Game::stopLine() {
		if (rotating) {
			rotating = false;
			if (target.checkForHit(line)) {
				targetAngle = ofRandom(360);
			}
		}
	}