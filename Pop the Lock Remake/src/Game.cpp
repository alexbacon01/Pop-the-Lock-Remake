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
   // if (target.checkForMiss(line)) {
    //    if (!missSound.getIsPlaying()) {
     //       missSound.play();
     //       gameState = endMenu;
     //   }
  //  }

    // Update explosion if isExploding is true
    if (isExploding) {
        explodingTarget.updateExplosion();
        // end the explosion effect when max distance is reached
        if (explodingTarget.explosionDistances[0] >= explodingTarget.maxDistance) {
            isExploding = false;
            target.isHit = false;
            onTarget = false;
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

    if (target.checkForHit(line)) {
        onTarget = true;
    }
    

    if (onTarget && !target.isHit && !target.checkForHit(line)) {
        if (!missSound.getIsPlaying()) {
        missSound.play();
        gameState = endMenu;
        std::cout << "MISSED";
        onTarget = false;
        }
    }

    std::cout << "Target is hit " << target.isHit;


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
        target.isHit = true;
        score++;
        minTargetDist -= 2;
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
    // Normalize last angle to [0, 360)
    last = fmod(last + 360, 360);

    bool isClockwise = line.speed < 0;
    float minAngle, maxAngle;

    // Define valid angle range based on direction and minimum distance
    if (isClockwise) {
        minAngle = fmod(last + minTargetDist, 360);
        maxAngle = fmod(last + 360 - minTargetDist, 360);
    }
    else {
        minAngle = fmod(last - 360 + minTargetDist, 360);
        maxAngle = fmod(last - minTargetDist, 360);
    }

    float newAngle = last;  // Initialize to last angle

        // Generate random angle, avoiding the excluded zone
        if (isClockwise) {
            // Generate angle in the allowed range after the current position
            newAngle = ofRandom(minAngle, minAngle + (360 - 2 * minTargetDist));
            newAngle = fmod(newAngle + 360, 360);
        }
        else {
            // Generate angle in the allowed range before the current position
            newAngle = ofRandom(maxAngle - (360 - 2 * minTargetDist), maxAngle);
            newAngle = fmod(newAngle + 360, 360);
        }

        // Verify the distance
        float angleDiff = abs(newAngle - last);
        if (angleDiff > 180) {
            angleDiff = 360 - angleDiff;
        }

    // Double-check final distance
    float finalDiff = abs(newAngle - last);
    if (finalDiff > 180) {
        finalDiff = 360 - finalDiff;
    }

    // If still too close, force minimum separation
    if (finalDiff < minTargetDist) {
        if (isClockwise) {
            newAngle = fmod(last + minTargetDist + 45, 360);
        }
        else {
            newAngle = fmod(last - minTargetDist - 45 + 360, 360);
        }
    }

    return newAngle;
}

/**
 * @brief Resets the game score to zero.
 *
 * This function resets the score counter to zero, line speed and target distance to start values, and menu message to default lost. effectively restarting
 * the game progress.
 */
void Game::restart() {
    gameState = running;
    score = 0;
    line.speed = line.startSpeed; 
    minTargetDist = startMinTargetDist;
    menuMessage = "You Lost!";
    target.isHit = false;
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
        restart();
    }
    ofSetColor(255, 255, 255);
    mainFont.drawString(menuMessage, ofGetWindowWidth() / 2 - (mainFont.stringWidth(menuMessage) / 2), ofGetWindowHeight() / 6);
}
