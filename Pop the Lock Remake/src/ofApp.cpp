#include "ofApp.h"
#include "Lock.hpp"
#include "Line.hpp"

Lock l = Lock(glm::vec2{ 1,1 }, 0.5, ofColor(0, 0, 0), ofColor(0, 0, 0), 10);
Line line = Line(glm::vec2{ 1,1 }, ofColor(255,255, 255), 10.0, 10.0, 10.0, 0);
float diam;
glm::vec2 pos;
float angle = 90;
bool rotating = true;
//--------------------------------------------------------------
void ofApp::setup() {

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

	//Set up the line'
	float lineOffset = (diam / 3) / 2;

	line.width = diam / 1.6 - diam / 3;
	line.height = diam / 10;
	line.roundness = 20;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (rotating) {
		angle = line.rotate();
	} 
	glm::vec2 pointOfBig = pos + glm::vec2{ diam / 1.5 * cos(angle), diam / 1.5 * sin(angle) };
	glm::vec2 pointOfLil = pos + glm::vec2{ diam / 3 * cos(angle), diam / 3 * sin(angle) };
	line.pos = ((pointOfBig + pointOfLil) / 2);
}

//--------------------------------------------------------------
void ofApp::draw() {
	l.draw();
	line.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 32) {
		if (rotating) {
			rotating = false;
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

