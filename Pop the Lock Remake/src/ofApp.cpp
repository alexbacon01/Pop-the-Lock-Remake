#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gameRunning = true;
		game.setup();
	
}

//--------------------------------------------------------------
void ofApp::update() {
	if (gameRunning) {
		game.update();
	}

	std::cout << gameRunning;
}

//--------------------------------------------------------------
void ofApp::draw() {

		game.draw();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (gameRunning) {
		if (key == 32) { //space bar
			if (!game.stopLine()) {
				gameRunning = false;
			} else {

			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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

