#pragma once


class Lock {



public:
	Lock(glm::vec2 pos, float diam, ofColor middleColor, ofColor outerColor, int resolution);
	glm::vec2 pos;
	float diam;
	ofColor middleColor;
	ofColor outerColor;
	int resolution;
	void draw();

};