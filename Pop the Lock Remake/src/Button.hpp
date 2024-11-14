#pragma once


class Button {



public:
	Button(glm::vec2 pos, float width, float height, ofColor color);
	void draw(std::string text, ofTrueTypeFont font);
	bool onButton(glm::vec2 mousePos);
	glm::vec2 pos;
	float height;
	float width;
	ofColor color;

};