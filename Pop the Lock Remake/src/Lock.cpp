#include <ofMain.h>
#include "Lock.hpp"
Lock::Lock(glm::vec2 pos, float diam, ofColor middleColor, ofColor outerColor, int resolution)
	:pos{ pos }, diam{ diam }, middleColor{ middleColor }, outerColor{ outerColor }, resolution{
	resolution
	}
{

}

void Lock::draw() {
	ofSetCircleResolution(50);

	//outer circle
	ofSetColor(outerColor);
	ofDrawCircle(pos.x, pos.y, diam);

	//middle circle
	ofSetColor(middleColor);
	ofDrawCircle(pos.x, pos.y, diam / 1.5);

	//inner circle
	ofSetColor(outerColor);
	ofDrawCircle(pos.x, pos.y, diam / 3);
}