#include <ofMain.h>
#include "Line.hpp"
Line::Line(glm::vec2 pos, ofColor color, float width, float height, float roundness, float angle)
	:pos{ pos },
	color{ color },
	width{ width },
	height{ height },
	roundness{ roundness },
	angle{ angle }
{

}

void Line::draw() {
	ofPushMatrix();
	ofSetColor(color);
	ofTranslate(pos);
	ofRotateRad(angle);
	ofDrawRectRounded(glm::vec2{ -width/2, 0 }, width, height, roundness);
	ofPopMatrix();
}

float Line::rotate() {
	angle += speed;
	return angle;
}

void Line::reverse() {
	if (speed > 0) {
		speed += 0.005;
	}
	else {
		speed -= 0.005;
	}
	speed *= -1;
}