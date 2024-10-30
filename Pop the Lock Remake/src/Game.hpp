#pragma once

#include "ofMain.h"
#include "Lock.hpp"
#include "Line.hpp"
#include "Target.hpp"

class Game {

public:
	void draw();
	void setup();
	void update();
	void stopLine();
};
