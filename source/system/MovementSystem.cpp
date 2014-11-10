/*
 * Author: Renato Utsch Gonçalves
 * Computer Science, UFMG
 * Computer Graphics
 * Practical exercise 2 - Boids
 *
 * Copyright (c) 2014 Renato Utsch <renatoutsch@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "MovementSystem.hpp"
#include "../Engine.hpp"
#include "../defs.hpp"
#include "../glfw.hpp"
#include "../gameObject/ObjectiveBoid.hpp"

void MovementSystem::init() {

}

void MovementSystem::terminate() {

}

void MovementSystem::updateObjectiveBoidSpeed(float dt) {
    ObjectiveBoid &boid = getEngine().getObjectiveBoid();

    // Increase the speed.
    if(glfwGetKey(getEngine().getWindow(), ObjectiveBoidIncreaseSpeedKey) == GLFW_PRESS)
        boid.speed += ObjectiveBoidSpeedFactor;

    // Decrease the speed.
    if(glfwGetKey(getEngine().getWindow(), ObjectiveBoidDecreaseSpeedKey) == GLFW_PRESS)
        boid.speed -= ObjectiveBoidSpeedFactor;

    // Do not allow the boid to go too fast.
    if(boid.speed > BoidMaxSpeed)
        boid.speed = BoidMaxSpeed;

    // Do not allow the speed go negative (I don't want a boid that goes
    // backwards).
    if(boid.speed < 0.0)
        boid.speed = 0.0;
}

void MovementSystem::updateObjectiveBoidDirection(float dt) {
    ObjectiveBoid &boid = getEngine().getObjectiveBoid();

    // Calculate the horizontal and vertical movements.

    // Up movement.
    if(glfwGetKey(getEngine().getWindow(), ObjectiveBoidUpKey) == GLFW_PRESS)
        boid.verticalAngle += boid.keySensitivity * dt;

    // Down movement.
    if(glfwGetKey(getEngine().getWindow(), ObjectiveBoidDownKey) == GLFW_PRESS)
        boid.verticalAngle -= boid.keySensitivity * dt;

    // Right movement.
    if(glfwGetKey(getEngine().getWindow(), ObjectiveBoidRightKey) == GLFW_PRESS)
        boid.horizontalAngle += boid.keySensitivity * dt;

    // Left movement.
    if(glfwGetKey(getEngine().getWindow(), ObjectiveBoidLeftKey) == GLFW_PRESS)
        boid.horizontalAngle -= boid.keySensitivity * dt;

    // Limit looking up to vertically up.
    if(boid.verticalAngle > 90.0)
        boid.verticalAngle = 90.0;

    // Limit looking down to vertically down.
    if(boid.verticalAngle < -90.0)
        boid.verticalAngle = -90.0;

    // Looking left and right - keep angles in the range 0.0 to 360.0.
    if(boid.horizontalAngle < 0.0)
        boid.horizontalAngle += 360.0;
    if(boid.horizontalAngle > 360.0)
        boid.horizontalAngle -= 360.0;

    // sin and cos.
    double sinVert = sin(toRads(boid.verticalAngle));
    double cosVert = cos(toRads(boid.verticalAngle));
    double sinHoriz = sin(toRads(boid.horizontalAngle));
    double cosHoriz = cos(toRads(boid.horizontalAngle));

    // Calculate the direction.
    boid.direction.x = sinHoriz * cosVert;
    boid.direction.y = -sinVert;
    boid.direction.z = -cosHoriz * cosVert;
    boid.direction.normalize();

    // Calculate the right vector to calculate the up afterwards.
    boid.right.x = cosHoriz;
    boid.right.y = 0.0;
    boid.right.z = sinHoriz;
    boid.right.normalize();

    // Calculate the up.
    boid.up = Vector::cross(boid.right, boid.direction);
    boid.up.normalize();
}

void MovementSystem::update(float dt) {
    // Change the objective boid speed.
    updateObjectiveBoidSpeed(dt);

    // Change the objective boid direction.
    updateObjectiveBoidDirection(dt);

    // Move the objective boid.
    getEngine().getObjectiveBoid().position +=
        getEngine().getObjectiveBoid().direction *
        getEngine().getObjectiveBoid().speed * dt;
}
