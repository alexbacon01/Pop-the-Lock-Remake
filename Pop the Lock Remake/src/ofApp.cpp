#include "ofApp.h"
#include "Game.hpp"

Game game;
//--------------------------------------------------------------
void ofApp::setup() {
	game.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	game.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	game.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 32) { //space bar
		game.stopLine();
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

