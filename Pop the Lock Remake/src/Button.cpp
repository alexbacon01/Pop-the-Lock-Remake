#include <ofMain.h>
#include "Button.hpp"



Button::Button(glm::vec2 pos, float width, float height, ofColor color)
	:pos{ pos }, width{ width }, height{ height }, color{ color }
{

}

void Button::draw(std::string text, ofTrueTypeFont font)
{
	ofPushStyle();
	ofSetColor(color);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofDrawRectangle(pos, width, height);
	ofSetColor(0, 0, 0);
	font.drawString(text, pos.x - (font.stringWidth(text) / 2), pos.y + (font.stringHeight(text) / 2));
	ofPopStyle();
}

bool Button::onButton(glm::vec2 mousePos) {

	if (mousePos.y <= (pos.y + height / 2) && mousePos.y >= (pos.y - height / 2) && mousePos.x >= (pos.x - width / 2) && mousePos.x <= (pos.x + width / 2)){
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetColor(0, 0, 255, 45);
		ofDrawRectangle(pos, width, height);
		std::cout << "ON BUTTON";
		ofPopStyle();
		return true;
	}
	return false;
}
