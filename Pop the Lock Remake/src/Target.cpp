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
    // Get the game window center (which is the rotation center)
    glm::vec2 center = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);

    // Convert angles to the same coordinate space (0 to 2PI)
    float lineAngle = fmod(abs(line.angle) + TWO_PI, TWO_PI);

    // Calculate target angle relative to center
    float targetAngle = atan2(pos.y - center.y, pos.x - center.x);
    if (targetAngle < 0) targetAngle += TWO_PI;

    // Calculate the absolute difference between angles
    float angleDiff = abs(lineAngle - targetAngle);
    if (angleDiff > PI) {
        angleDiff = TWO_PI - angleDiff;
    }

    // Define hit tolerance in radians (adjust this value as needed)
    float tolerance = PI / 12.0f; // 15 degrees

    // Check if the line's angle is close enough to the target's angle
    return angleDiff <= tolerance;
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
    // Get the center of rotation (game window center)
    glm::vec2 center = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);

    // Get the current line angle (0 to 2PI)
    float lineAngle = fmod(abs(line.angle) + TWO_PI, TWO_PI);

    // Calculate target angle relative to center (0 to 2PI)
    float targetAngle = atan2(pos.y - center.y, pos.x - center.x);
    if (targetAngle < 0) targetAngle += TWO_PI;

    // Store the previous line angle
    static float prevLineAngle = lineAngle;

    // Define the miss detection zone (slightly larger than hit tolerance)
    float missZone = PI / 10.0f; // 18 degrees
    float hitZone = PI / 12.0f;  // 15 degrees (same as hit tolerance)

    // Calculate angular differences
    float angleDiff = abs(lineAngle - targetAngle);
    if (angleDiff > PI) {
        angleDiff = TWO_PI - angleDiff;
    }

    // Determine if we just passed the target
    bool passedTarget = false;
    if (line.speed > 0) { // Clockwise rotation
        float passAngle = targetAngle + hitZone; // Check if we've passed beyond the hit zone
        if (passAngle >= TWO_PI) passAngle -= TWO_PI;

        // Check if we crossed over the target angle + hit zone
        if (prevLineAngle < passAngle && lineAngle > passAngle) {
            passedTarget = true;
        }
        // Handle wrap-around at 2PI
        if (prevLineAngle > lineAngle && abs(prevLineAngle - lineAngle) > PI) {
            if (passAngle > min(prevLineAngle, lineAngle) &&
                passAngle < max(prevLineAngle, lineAngle)) {
                passedTarget = true;
            }
        }
    }
    else { // Counter-clockwise rotation
        float passAngle = targetAngle - hitZone; // Check if we've passed beyond the hit zone
        if (passAngle < 0) passAngle += TWO_PI;

        // Check if we crossed over the target angle - hit zone
        if (prevLineAngle > passAngle && lineAngle < passAngle) {
            passedTarget = true;
        }
        // Handle wrap-around at 0
        if (lineAngle > prevLineAngle && abs(lineAngle - prevLineAngle) > PI) {
            if (passAngle > min(prevLineAngle, lineAngle) &&
                passAngle < max(prevLineAngle, lineAngle)) {
                passedTarget = true;
            }
        }
    }

    // Update previous angle for next frame
    prevLineAngle = lineAngle;

    // Return true if we passed the target and were within the miss zone
    return passedTarget && (angleDiff <= missZone);
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
