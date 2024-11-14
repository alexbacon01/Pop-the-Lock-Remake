#include <ofMain.h>
#include "Target.hpp"
#include "Line.hpp"

/**
 * @brief Constructs a Target with specified position, diameter, color, and resolution.
 *
 * @param pos The position of the target.
 * @param diam The diameter of the target.
 * @param color The color of the target.
 * @param resolution The circle resolution (used for smoothness of drawing).
 */
Target::Target(glm::vec2 pos, float diam, ofColor color, int resolution)
    : pos{ pos }, diam{ diam }, color{ color }, resolution{ resolution } {
}

/**
 * @brief Draws the target and, if hit, the explosion effect.
 *
 * Draws a circle to represent the target. If the target is hit, it also draws
 * explosion lines radiating outward from the center of the target.
 */
void Target::draw() {
    ofSetCircleResolution(50);

    // Draw target circle
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, diam / 1.5);

    // Draw the explosion lines if the target is hit
    if (isHit) {
        updateExplosion();

        ofSetColor(255, 255, 255); // Explosion line color
        ofSetLineWidth(3); // Set thickness for explosion lines

        float lengthOffset = 20.0f; // Extra length to make lines longer
        for (size_t i = 0; i < explosionDirections.size(); i++) {
            if (explosionDistances[i] < maxDistance) {
                // Define start and end points for a longer line
                glm::vec2 startPoint = pos + explosionDirections[i] * (explosionDistances[i] - lineSpeed);
                glm::vec2 endPoint = pos + explosionDirections[i] * (explosionDistances[i] + lengthOffset);
                ofDrawLine(startPoint, endPoint);
            }
        }
        ofSetLineWidth(1); // Reset line width to default after drawing
    }
}

/**
 * @brief Sets up audio resources for the target.
 *
 * Loads multiple sound files representing different "pop" effects for when the target
 * is hit, adding them to a vector of sounds.
 */
void Target::setup() {
    int numSounds = 5;
    sounds.resize(numSounds);
    for (int i = 1; i <= numSounds; i++) {
        std::string fileName = "Pop" + std::to_string(i) + ".mp3";
        sounds[i - 1].load(fileName);
    }
}

/**
 * @brief Checks if the line hits the target.
 *
 * Calculates the closest point on the line to the target center and checks if
 * this point falls within the target's diameter, indicating a hit.
 *
 * @param line The Line object to check for collision.
 * @return bool True if the line hits the target; otherwise, false.
 */
bool Target::checkForHit(Line line) {
    float closestX = glm::clamp(pos.x, line.pos.x, line.pos.x + line.width);
    float closestY = glm::clamp(pos.y, line.pos.y, line.pos.y + line.height);

    float distance = sqrt((pos.x - closestX) * (pos.x - closestX) + (pos.y - closestY) * (pos.y - closestY));

    return distance <= diam;
}

/**
 * @brief Checks if the line missed the target while passing near it.
 *
 * This function calculates the line's proximity to the target and detects if the line
 * has passed the target based on their angles relative to the center of the circle.
 *
 * @param line The Line object to check for a miss.
 * @return bool True if the line passed near but missed the target; otherwise, false.
 */
bool Target::checkForMiss(Line line) {
    // Set a threshold for proximity to the target center
    float proximityThreshold = diam / 2.0f;

    // Calculate distance from line's current position to target's position
    float currentDistance = glm::distance(line.pos, pos);
    bool isCloseToTarget = currentDistance <= proximityThreshold;

    // Get angles for line and target relative to the center
    float lineAngle = atan2(line.pos.y - pos.y, line.pos.x - pos.x);
    float targetAngle = atan2(pos.y - pos.y, pos.x - pos.x);

    // Normalize angles to [0, 2*PI]
    if (lineAngle < 0) lineAngle += TWO_PI;
    if (targetAngle < 0) targetAngle += TWO_PI;

    // Calculate the angular difference based on direction
    bool isClockwise = line.speed > 0;
    bool passedTarget = false;

    if (isClockwise) {
        // For clockwise, the line misses if it moves from an angle less than targetAngle to greater than targetAngle
        passedTarget = lineAngle > targetAngle && (lineAngle - targetAngle) < PI;
    }
    else {
        // For counterclockwise, the line misses if it moves from an angle greater than targetAngle to less than targetAngle
        passedTarget = lineAngle < targetAngle && (targetAngle - lineAngle) < PI;
    }

    // Register a miss only if the line is close to the target and has passed it
    return isCloseToTarget && passedTarget;
}

/**
 * @brief Starts the explosion effect by initializing directions and distances for explosion lines.
 *
 * Generates multiple lines radiating outward from the target center, each with a unique direction
 * to simulate an explosion effect. A random "pop" sound is played when the effect starts.
 */
void Target::startExplosion() {
    int numLines = 20;
    explosionDirections.clear();
    explosionDistances.clear();
    for (int i = 0; i < numLines; i++) {
        float angle = ofDegToRad(i * (360.0 / numLines));
        glm::vec2 direction = glm::vec2(cos(angle), sin(angle));
        explosionDirections.push_back(direction);
        explosionDistances.push_back(0.0f); // Start at 0 distance for each line
    }
    int soundIndex = ofRandom(0, sounds.size());
    sounds[soundIndex].play();
    isHit = true;
}

/**
 * @brief Updates the explosion effect, increasing the distance of each line.
 *
 * This function updates the distances for each explosion line based on the line speed.
 * This creates the effect of lines radiating outward from the target center.
 */
void Target::updateExplosion() {
    if (isHit) {
        for (size_t i = 0; i < explosionDirections.size(); i++) {
            // Increment distance based on line speed
            explosionDistances[i] += lineSpeed;
        }
    }
}
