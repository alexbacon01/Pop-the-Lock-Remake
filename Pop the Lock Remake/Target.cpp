#include <ofMain.h>
#include "Target.hpp"
Target::Target(glm::vec2 pos, float diam, ofColor color, int resolution)
	:pos{ pos }, diam{ diam }, color{ color }, resolution{
	resolution
	}
{

}

void Target::draw() {
	ofSetCircleResolution(50);


	// circle
	ofSetColor(color);
	ofDrawCircle(pos.x, pos.y, diam / 1.5);

}