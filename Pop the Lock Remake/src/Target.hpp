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

	bool checkForMiss(Line line);

	void startExplosion();

	void updateExplosion();

	bool isHit = false;
	std::vector<glm::vec2> explosionDirections;
	std::vector<float> explosionDistances;
	float maxDistance = 50.0f; // Maximum distance lines will travel
	float lineSpeed = 4.0f;     // Speed of outward movement

};