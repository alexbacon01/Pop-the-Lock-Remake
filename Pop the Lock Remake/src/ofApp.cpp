// ofApp.cpp
#include "ofApp.h"

/**
 * @brief Sets up the initial game state and mouse state.
 *
 * Initializes the game setup and resets the mouse click state.
 */
void ofApp::setup() {
    isMousePressed = false;
    game.setup();
}

/**
 * @brief Updates the game state if the game is running.
 *
 * Continues game logic if in running state; stops background music otherwise.
 */
void ofApp::update() {
    if (game.gameState == running) {
        game.update();
    }
    else {
        game.backgroundMusic.stop();
    }
}

/**
 * @brief Draws the game screen or menu based on the game state.
 *
 * Renders the game if running, or the main menu if not.
 */
void ofApp::draw() {
    if (game.gameState == running) {
        game.draw();
    }
    else {
        game.menu(isMousePressed, "Pop the Lock");
    }
}

/**
 * @brief Handles keyboard press events.
 *
 * Processes space bar presses to attempt stopping the line on the target.
 *
 * @param key The key code of the pressed key.
 */
void ofApp::keyPressed(int key) {
    game.keyPressed = true;
    if (game.gameState == running && key == 32) { // space bar
        if (!game.stopLine()) {
            if (!game.missSound.getIsPlaying()) {
                game.missSound.play();
            }
            game.gameState = endMenu;
            game.score = 0;
        }
    }
}

/**
 * @brief Handles mouse movement events.
 *
 * Resets the mouse pressed state when the mouse is moved.
 *
 * @param x The x-coordinate of the mouse.
 * @param y The y-coordinate of the mouse.
 */
void ofApp::mouseMoved(int x, int y) {
    isMousePressed = false;
}

// Empty event handlers
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) { isMousePressed = true; }
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::keyReleased(int key) {}
