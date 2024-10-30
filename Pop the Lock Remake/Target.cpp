#include <ofMain.h>
#include "Target.hpp"
#include "Line.hpp"
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

bool Target::checkForHit(Line line) {
	float closestX = glm::clamp(pos.x, line.pos.x, line.pos.x + line.width);
	float closestY = glm::clamp(pos.y, line.pos.y, line.pos.y + line.height);

	float distance = sqrt((pos.x - closestX) * (pos.x - closestX) + (pos.y - closestY) * (pos.y - closestY));

	std::cout << (distance <= diam / 2.0);

	return distance <= diam / 2.0;
	
}