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

#include "CollisionSystem.hpp"
#include "../Engine.hpp"
#include "../defs.hpp"
#include "../glfw.hpp"

void CollisionSystem::init() {

}

void CollisionSystem::terminate() {

}

void CollisionSystem::restoreBoidsPosition() {
    Engine::BoidVector &boids = getEngine().getBoids();
    size_t size = boids.size();

    // Go through each boid. If their position is different than their old
    // position, try to restore.
    for(size_t i = 0; i < size; ++i) {
        if(boids[i].position != boids[i].oldPosition) {
            std::cout << "wow, different position" << std::endl;
        }
    }
}

void CollisionSystem::calculateCollisionWithTower() {
    Engine::BoidVector &boids = getEngine().getBoids();
    size_t size = boids.size();

    // We have to do this for all boids.
    for(size_t i = 0; i < size; ++i) {

    }
}

void CollisionSystem::calculateCollisionWithGround() {
    /*
    // I think it is enough to not allow the objective boid to go lower than
    // the minimum height.
    if(getEngine().getObjectiveBoid().position.y < MinimumHeight)
        getEngine().getObjectiveBoid().position.y = MinimumHeight;
    */

    Engine::BoidVector &boids = getEngine().getBoids();
    ObjectiveBoid &obj = getEngine().getObjectiveBoid();
    size_t size = boids.size();
    float lowest = 0.0;

    // Get the lowest boid height relative to the objective boid.
    for(size_t i = 0; i < size; ++i) {
        if(boids[i].position.y < lowest)
            lowest = boids[i].position.y;
    }

    // The objective boid's height minus the lowest height can't go lower than
    // minimum height.
    if(obj.position.y + lowest < MinimumHeight)
        obj.position.y = MinimumHeight - lowest;
}

void CollisionSystem::calculateCollisionWithCeiling() {
    // I think it is enough to not allow the objective boid to go higher than
    // the maximum height.
    if(getEngine().getObjectiveBoid().position.y > MaximumHeight)
        getEngine().getObjectiveBoid().position.y = MaximumHeight;
}

void CollisionSystem::calculateCollisionBetweenBoids() {
    Engine::BoidVector &boids = getEngine().getBoids();
    size_t size = boids.size();

    // Test each boid with the others.
    for(size_t i = 0; i < size; ++i) {
        for(size_t j = i + 1; j < size; ++j) {
            // Calculate the distance between their position. If it is smaller
            // than 2 * BoidSpace, they are about to collide.
            if(Point::distance(boids[i].position, boids[j].position)
                    < 2 * BoidSpace) {
                // Move in the opposite direction of the collision.
                //Vector dir = boids[j].position - boids[i].position;
            }
        }
    }
}

void CollisionSystem::update(float dt) {
    // Try to restore to original position.
    restoreBoidsPosition();

    // Calculate new collisions.
    calculateCollisionWithTower();
    calculateCollisionWithGround();
    calculateCollisionWithCeiling();
    calculateCollisionBetweenBoids();
}

