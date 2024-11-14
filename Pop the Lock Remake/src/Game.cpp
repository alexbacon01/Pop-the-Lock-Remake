#include "Game.hpp"
#include "Button.hpp"

	void Game::draw() {
		l.draw();
		line.draw();
		target.draw();
		ofColor(255, 255, 255);
		std::string string = to_string(startNumber - score);
		mainFont.drawString(string, l.pos.x - (mainFont.stringWidth(string)/2), l.pos.y + (mainFont.stringHeight(string)/2));
		if (isExploding) {
			explodingTarget.draw();
		}
	}

	void Game::setup() {
		ofBackground(backgroundColor);
		score = 0;
		menuFont.load("BRLNSR.TTF", 64);
		mainFont.load("BRLNSR.TTF", 100);

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
		target.setup();

		backgroundMusic.load("BackgroundMusic.mp3");
	}

	void Game::update() {
		if (rotating) {
			lineAngle = line.rotate();
		}
		line.pos = getPos(lineAngle);
		target.pos = getPos(targetAngle);
		
		if (target.checkForMiss(line)) {
			std::cout << " MISS ";

		}
		if (isExploding) {
			explodingTarget.updateExplosion();
			// Optionally, end the explosion effect when max distance is reached
			if (explodingTarget.explosionDistances[0] >= explodingTarget.maxDistance) {
				isExploding = false;
			}
		}


		if (!backgroundMusic.getIsPlaying()) {
			backgroundMusic.play();
		}
	

	}

	bool Game::stopLine() {
	
			if (target.checkForHit(line)) {
				// Set up the explosion effect on the "exploding" target
				explodingTarget = target;
				explodingTarget.isHit = true;
				explodingTarget.startExplosion();
				isExploding = true;
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

	void Game::restart(){
		score = 0;
	}

	void Game::menu(bool mousePressed, std::string text) {
		ofBackground(backgroundColor);
		Button button = Button(glm::vec2{ ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 }, ofGetWindowWidth() / 2, ofGetWindowHeight() / 4, ofColor(255, 255, 255));
		button.draw("Start Game", menuFont);
		if (button.onButton(glm::vec2(ofGetMouseX(), ofGetMouseY())) && mousePressed) {
			gameState = running;
		}
		ofSetColor(255, 255, 255);
		mainFont.drawString(text,ofGetWindowWidth()/2 - (mainFont.stringWidth(text) / 2), ofGetWindowHeight() / 6);
	}
