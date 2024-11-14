#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	isMousePressed = false;
	game.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (game.gameState == running) {
		game.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (game.gameState == running) {
		game.draw();
	} else{
		game.menu(isMousePressed, "Pop the Lock");
	}

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	game.keyPressed = true;
	if (game.gameState == running) {
		if (key == 32) { //space bar
			if (!game.stopLine()) {
				game.gameState = endMenu;
				game.score = 0;
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	isMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

