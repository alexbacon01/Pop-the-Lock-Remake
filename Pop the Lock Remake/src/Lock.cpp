// Lock.cpp
#include <ofMain.h>
#include "Lock.hpp"

/**
 * @brief Constructs a Lock object with position, diameter, and colors.
 */
Lock::Lock(glm::vec2 pos, float diam, ofColor middleColor, ofColor outerColor, int resolution)
    : pos{ pos }, diam{ diam }, middleColor{ middleColor },
    outerColor{ outerColor }, resolution{ resolution } {}

/**
 * @brief Draws the lock with multiple circles.
 */
void Lock::draw() {
    ofSetCircleResolution(50);

    ofSetColor(outerColor);
    ofDrawCircle(pos.x, pos.y, diam);

    ofSetColor(middleColor);
    ofDrawCircle(pos.x, pos.y, diam / 1.5);

    ofSetColor(outerColor);
    ofDrawCircle(pos.x, pos.y, diam / 3);
}