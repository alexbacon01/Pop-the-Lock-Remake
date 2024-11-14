// Line.cpp
#include <ofMain.h>
#include "Line.hpp"

/**
 * @brief Constructs a Line object with position, color, dimensions, and angle.
 */
Line::Line(glm::vec2 pos, ofColor color, float width, float height, float roundness, float angle)
    : pos{ pos }, color{ color }, width{ width }, height{ height },
    roundness{ roundness }, angle{ angle } {}

/**
 * @brief Draws the line with the specified properties.
 *
 * Renders the line as a rounded rectangle with translation and rotation.
 */
void Line::draw() {
    ofPushMatrix();
    ofSetColor(color);
    ofTranslate(pos);
    ofRotateRad(angle);
    ofDrawRectRounded(glm::vec2{ -width / 2, 0 }, width, height, roundness);
    ofPopMatrix();
}

/**
 * @brief Rotates the line by incrementing its angle.
 *
 * @return float The updated angle of the line.
 */
float Line::rotate() {
    angle += speed;
    return angle;
}

/**
 * @brief Reverses the line's direction and adjusts speed.
 */
void Line::reverse() {
    speed += (speed > 0) ? 0.001 : -0.001;
    speed *= -1;
}