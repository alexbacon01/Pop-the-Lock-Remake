#include "Game.hpp"

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
		line.pos = getPos(lineAngle);
		target.pos = getPos(targetAngle);
		std::cout << " Line speed: " << line.speed;
	}

	bool Game::stopLine() {
	
			if (target.checkForHit(line)) {
				targetAngle = ofRandom(360);
				line.reverse();
			}

		return target.checkForHit(line);
	}

	glm::vec2 Game::getPos(float angle) {
		glm::vec2 pointOfBigT = pos + glm::vec2{ diam / 1.5 * cos(angle), diam / 1.5 * sin(angle) };
		glm::vec2 pointOfLilT = pos + glm::vec2{ diam / 3 * cos(angle), diam / 3 * sin(angle) };
		return ((pointOfBigT + pointOfLilT) / 2);
	}
