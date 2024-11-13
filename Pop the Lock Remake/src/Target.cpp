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

	return distance <= diam;
}

bool Target::checkForMiss(Line line) {
    // Set a threshold for proximity to the target center
    float proximityThreshold = diam / 2.0f;

    // Calculate distance from line's current position to target's position
    float currentDistance = glm::distance(line.pos, pos);
    bool isCloseToTarget = currentDistance <= proximityThreshold;

    // Get angles for line and target relative to the center
    float lineAngle = atan2(line.pos.y - pos.y, line.pos.x - pos.x);
    float targetAngle = atan2(pos.y - pos.y, pos.x - pos.x);

    // Normalize angles to [0, 2*PI]
    if (lineAngle < 0) lineAngle += TWO_PI;
    if (targetAngle < 0) targetAngle += TWO_PI;

    // Calculate the angular difference based on direction
    bool isClockwise = line.speed > 0;
    bool passedTarget = false;

    if (isClockwise) {
        // For clockwise, the line misses if it moves from an angle less than targetAngle to greater than targetAngle
        passedTarget = lineAngle > targetAngle && (lineAngle - targetAngle) < PI;
    }
    else {
        // For counterclockwise, the line misses if it moves from an angle greater than targetAngle to less than targetAngle
        passedTarget = lineAngle < targetAngle && (targetAngle - lineAngle) < PI;
    }

    // Register a miss only if the line is close to the target and has passed it
    return isCloseToTarget && passedTarget;
}