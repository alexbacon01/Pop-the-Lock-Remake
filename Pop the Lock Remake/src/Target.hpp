#pragma once
#include "Line.hpp"

class Target {



public:
	Target(glm::vec2 pos, float diam, ofColor color, int resolution);
	glm::vec2 pos;
	float diam;
	ofColor color;

	int resolution;
	void draw();
	bool checkForHit(Line line);

};