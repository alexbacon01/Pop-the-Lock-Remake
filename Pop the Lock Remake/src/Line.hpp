#pragma once


class Line {



public:
	Line(glm::vec2 pos, ofColor color, float width, float height, float roundness, float angle);
	glm::vec2 pos;
	ofColor color;
	float width;
	float height;
	float roundness;
	float angle;
	void draw();
	float rotate();
	float speed = 0.01;
	void reverse();

};