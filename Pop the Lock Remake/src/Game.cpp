#include "Game.hpp"
#include "Button.hpp"

/**
 * @brief Draws the game elements on the screen.
 *
 * This function handles the drawing of all game elements, including the lock circle,
 * rotating line, target, and score. If the game is in the explosion state, it also
 * draws the explosion effect.
 */
void Game::draw() {
    l.draw();
    line.draw();
    if (isExploding) {
        explodingTarget.draw();
    }
    target.draw();\
    //draw middle number
    ofColor(255, 255, 255);
    std::string string = to_string(startNumber - score);
    mainFont.drawString(string, l.pos.x - (mainFont.stringWidth(string) / 2), l.pos.y + (mainFont.stringHeight(string) / 2));

}

/**
 * @brief Sets up initial game parameters and resources.
 *
 * This function initializes game properties, including score, fonts, and the
 * configuration of the lock, line, and target. It also loads audio resources
 * for background music and miss sound effects.
 */
void Game::setup() {
    ofBackground(backgroundColor);
    score = 0;
    menuFont.load("BRLNSR.TTF", 64);
    mainFont.load("BRLNSR.TTF", 100);

    // Set up the lock
    pos = { ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0 };
    diam = ofGetWindowWidth() / 3.0;
    int res = 50;
    ofColor c1 = ofColor(2, 10, 30);
    ofColor c2 = ofColor(43, 81, 175);
    l.pos = pos;
    l.diam = diam;
    l.middleColor = c1;
    l.outerColor = c2;
    l.resolution = res;

    // Set up the line
    float lineOffset = (diam / 3) / 2;
    line.width = diam / 1.6 - diam / 3;
    line.height = diam / 10;
    line.roundness = 20;

    // Set up the target
    minTargetDist = 175;
    target.setup();

    // Load audio resources
    backgroundMusic.load("BackgroundMusic.mp3");
    missSound.load("error.mp3");
}

/**
 * @brief Updates the game state, rotating line and checking conditions.
 *
 * This function updates the line rotation and checks for misses and explosions.
 * It also ensures background music plays continuously in the game loop.
 */
void Game::update() {
    if (rotating) {
        lineAngle = line.rotate();
    }
    line.pos = getPos(lineAngle);
    target.pos = getPos(targetAngle);

    // Check if the line missed the target
    if (target.checkForMiss(line)) {
        std::cout << " MISS ";
        if (!missSound.getIsPlaying()) {
            missSound.play();
            gameState = endMenu;
        }
    }

    // Update explosion if isExploding is true
    if (isExploding) {
        explodingTarget.updateExplosion();
        // end the explosion effect when max distance is reached
        if (explodingTarget.explosionDistances[0] >= explodingTarget.maxDistance) {
            isExploding = false;
        }
    }

    // Play background music if not already playing
    if (!backgroundMusic.getIsPlaying() && gameState == running) {
        backgroundMusic.play();
    }

    if (score == startNumber) {
        menuMessage = "You won!";
        gameState = endMenu;
    }
}

/**
 * @brief Stops the rotating line and checks if it hit the target.
 *
 * This function stops the line rotation, checks if the line hit the target,
 * and triggers the explosion effect on a hit. If a hit occurs, it also updates
 * the target angle and reverses the line direction.
 *
 * @return bool True if the line hits the target; otherwise false.
 */
bool Game::stopLine() {
    if (target.checkForHit(line)) {
        // Set up the explosion effect on the "exploding" target
        explodingTarget = target;
        explodingTarget.isHit = true;
        explodingTarget.startExplosion();
        isExploding = true;
        score++;
        targetAngle = getNewTargetAngle(targetAngle);
        line.reverse();
    }

    return target.checkForHit(line);
}

/**
 * @brief Calculates a position on the lock circle for a given angle.
 *
 * Given an angle, this function computes a point along the circular path that the
 * line or target follows, creating a midpoint position between two different radii circles.
 *
 * @param angle The angle in radians where the point is calculated.
 * @return glm::vec2 The position on the lock circle.
 */
glm::vec2 Game::getPos(float angle) {
    glm::vec2 pointOfBigT = pos + glm::vec2{ diam / 1.5 * cos(angle), diam / 1.5 * sin(angle) };
    glm::vec2 pointOfLilT = pos + glm::vec2{ diam / 3 * cos(angle), diam / 3 * sin(angle) };
    return ((pointOfBigT + pointOfLilT) / 2);
}

/**
 * @brief Generates a new target angle, ensuring a minimum distance from the last angle.
 *
 * This function attempts to generate a new angle for the target that is a minimum
 * distance from the last target angle. If no valid angle is found, it defaults to
 * adding/subtracting the minimum distance.
 *
 * @param last The previous target angle.
 * @return float The new target angle.
 */
float Game::getNewTargetAngle(float last) {
    float newAngle;
    bool validAngle = false;
    int maxAttempts = 100;
    bool isClockwise = line.speed < 0;

    for (int i = 0; i < maxAttempts; i++) {
        // Generate a random angle between 0 and 360 degrees
        newAngle = ofRandom(0, 360);

        // Calculate angle difference, accounting for wrap-around at 360
        float angleDifference = newAngle - last;
        if (isClockwise) {
            if (angleDifference < 0) angleDifference += 360;
        }
        else {
            if (angleDifference > 0) angleDifference -= 360;
        }
        angleDifference = abs(angleDifference);

        // Check if angleDifference meets the minimum distance
        if (angleDifference >= minTargetDist) {
            validAngle = true;
            break;
        }
    }

    // Fallback if no valid angle found
    if (!validAngle) {
        newAngle = fmod(last + (isClockwise ? minTargetDist : -minTargetDist), 360);
    }

    std::cout << "Last Angle: " << last << " New Angle: " << newAngle << " Direction: " << (isClockwise ? "Clockwise" : "Counterclockwise") << std::endl;
    return newAngle;
}

/**
 * @brief Resets the game score to zero.
 *
 * This function resets the score counter to zero, effectively restarting
 * the game progress.
 */
void Game::restart() {
    score = 0;
}

/**
 * @brief Draws the main menu screen with a start button.
 *
 * This function displays the main menu screen with a button to start
 * the game. If the button is clicked, the game transitions to the
 * running state.
 *
 * @param mousePressed True if the mouse is clicked.
 * @param text The title text to display on the menu.
 */
void Game::menu(bool mousePressed) {
    ofBackground(backgroundColor);
    Button button = Button(glm::vec2{ ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 }, ofGetWindowWidth() / 2, ofGetWindowHeight() / 4, ofColor(255, 255, 255));
    button.draw("Start Game", menuFont);
    if (button.onButton(glm::vec2(ofGetMouseX(), ofGetMouseY())) && mousePressed) {
        gameState = running;
        score = 0;
    }
    ofSetColor(255, 255, 255);
    mainFont.drawString(menuMessage, ofGetWindowWidth() / 2 - (mainFont.stringWidth(menuMessage) / 2), ofGetWindowHeight() / 6);
}
