#include "Game.hpp"

	void Game::draw() {
		l.draw();
		line.draw();
		target.draw();
		ofColor(255, 255, 255);
		std::string scoreString = to_string(score);
		myFont.drawString(scoreString, l.pos.x - (myFont.stringWidth(scoreString)/2), l.pos.y + (myFont.stringHeight(scoreString)/2));
	}

	void Game::setup() {
		score = 0;
		myFont.load("BRLNSR.TTF", 100);

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
		
		//set up the target
		minTargetDist = 175;
	}

	void Game::update() {
		if (rotating) {
			lineAngle = line.rotate();
		}
		line.pos = getPos(lineAngle);
		target.pos = getPos(targetAngle);
	}

	bool Game::stopLine() {
	
			if (target.checkForHit(line)) {
				score++;
				targetAngle = getNewTargetAngle(targetAngle);
				line.reverse();
			}

		return target.checkForHit(line);
	}

	glm::vec2 Game::getPos(float angle) {
		glm::vec2 pointOfBigT = pos + glm::vec2{ diam / 1.5 * cos(angle), diam / 1.5 * sin(angle) };
		glm::vec2 pointOfLilT = pos + glm::vec2{ diam / 3 * cos(angle), diam / 3 * sin(angle) };
		return ((pointOfBigT + pointOfLilT) / 2);
	}

	float Game::getNewTargetAngle(float last) {
		float newAngle;
		bool validAngle = false;
		int maxAttempts = 100;
		bool isClockwise = line.speed < 0;

		for (int i = 0; i < maxAttempts; i++) {
			// Generate a random angle between 0 and 360 degrees
			newAngle = ofRandom(0, 360);

			// Calculate angle difference, accounting for wrap-around at 360
			float angleDifference = newAngle - last;
			if (isClockwise) {
				// Ensure angleDifference is positive in the clockwise direction
				if (angleDifference < 0) angleDifference += 360;
			}
			else {
				// Ensure angleDifference is positive in the counterclockwise direction
				if (angleDifference > 0) angleDifference -= 360;
			}
			angleDifference = abs(angleDifference);

			// Check if angleDifference meets the minimum distance
			if (angleDifference >= minTargetDist) {
				validAngle = true;
				break;
			}
		}

		// Fallback if no valid angle found
		if (!validAngle) {
			newAngle = fmod(last + (isClockwise ? minTargetDist : -minTargetDist), 360);
		}

		std::cout << "Last Angle: " << last << " New Angle: " << newAngle << " Direction: " << (isClockwise ? "Clockwise" : "Counterclockwise") << std::endl;
		return newAngle;
	}
