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

#include "Engine.hpp"
#include "defs.hpp"
#include "glfw.hpp"
#include "callbacks.hpp"
#include "state/IdleState.hpp"
#include "util/sleep.hpp"
#include <iostream>
#include <cstdlib>

void Engine::initWindowSystem() {
    // Initialize GLFW.
    if(!glfwInit()) {
        std::cerr << "Failed to init GLFW." << std::endl;
        std::exit(2);
    }

    // Initialize the window.
    _window = glfwCreateWindow(InitialWindowWidth, InitialWindowHeight,
            "Boids by Renato Utsch", NULL, NULL);
    if(!_window) {
        glfwTerminate();
        std::cerr << "Failed to create a window." << std::endl;
        std::exit(2);
    }
    glfwSetWindowPos(_window, InitialWindowPosX, InitialWindowPosY);
    glfwMakeContextCurrent(_window); // Draw in _window.

    // Set up the callbacks.
    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
    glfwSetKeyCallback(_window, keyCallback);
    glfwSetCursorPosCallback(_window, cursorPosCallback);
    glfwSetMouseButtonCallback(_window, mouseButtonCallback);

    // Get the cursor position.
    glfwGetCursorPos(_window, &_cursorXPos, &_cursorYPos);
}

void Engine::initSystems() {
    _renderSystem.init();
    _animationSystem.init();
    _cameraSystem.init();
    _collisionSystem.init();
    _movementSystem.init();
}

void Engine::initObjects() {
    // Position the objective boid randomly in the center of the map.
    float boidPosX = std::rand() % ((int) GroundSize) - GroundSize / 2;
    float boidPosY = std::rand() % ((int)(MaximumHeight - MinimumHeight) / 2)
        + MinimumHeight;
    float boidPosZ = std::rand() % ((int) GroundSize) - GroundSize / 2;

    // Do not position the boid in the tower.
    if(std::abs(boidPosX) < TowerBaseRadius)
        boidPosX += 2 * TowerBaseRadius;
    if(std::abs(boidPosZ) < TowerBaseRadius)
        boidPosZ += 2 * TowerBaseRadius;

    // Create the position point.
    Point objBoidPos = Point(boidPosX, boidPosY, boidPosZ);

    // Random direction.
    Vector objBoidDir = Vector((rand() % 1000) / 1000.0,
            (rand() % 1000) / 1000.0,
            (rand() % 1000) / 1000.0);

    // Add the objective boid moving to the center of the map.
    _objectiveBoid = new ObjectiveBoid(
            getAnimationSystem().getRandomBoidDisplayList(),
            getAnimationSystem().getRandomBoidGoingUp(),
            objBoidPos, ObjectiveBoidInitialSpeed, objBoidDir);

    // Add a boid.
    addBoid();
    addBoid();

    // Add a tower.
    _tower = new Tower(getAnimationSystem().getTowerDisplayList());
}

void Engine::terminateWindowSystem() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Engine::terminateSystems() {
    _animationSystem.terminate();
    _cameraSystem.terminate();
    _collisionSystem.terminate();
    _movementSystem.terminate();
    _renderSystem.terminate();
}

void Engine::terminateObjects() {
    // Remove the objective boid.
    delete _objectiveBoid;
    _objectiveBoid = 0;

    // Remove all the boids.
    _boids.clear();

    // Delete the tower.
    delete _tower;
    _tower = 0;
}

void Engine::updateMiddlePosition() {
    _middle.x = 0.0;
    _middle.y = 0.0;
    _middle.z = 0.0;

    // Sum all the positions of the other boids.
    for(Engine::BoidVector::iterator it = getEngine().getBoids().begin();
            it != getEngine().getBoids().end(); ++it) {
        _middle.x += it->getRelativePosition().x;
        _middle.y += it->getRelativePosition().y;
        _middle.z += it->getRelativePosition().z;
    }

    // Divide by the number of boids, getting the middle of the boids.
    float size = _boids.size();
    if(size) {
        _middle.x /= size;
        _middle.y /= size;
        _middle.z /= size;
    }
}

void Engine::mainLoop() {
    const double fpsTime = 100 / MaxFps; // Minimum time of a frame.
    const double dt = 0.01; // Number of ms per update.
    double accumulator = 0.0;
    double current, after, sleep;
    double previous = glfwGetTime();
    _elapsedTime = 0.0; // Global elapsed time.

    // Run the game until a close event is issued.
    while(!glfwWindowShouldClose(_window)) {
        current = glfwGetTime();
        accumulator += current - previous;
        previous = current;

        // Clamp the accumulator if it is too big to avoid the spiral of death.
        if(accumulator > 0.25)
            accumulator = 0.25;

        // Process states.
        getStateManager().processStates();

        // Get input.
        getStateManager().getCurrentState().input();

        // Update the game simulation.
        while(accumulator >= dt) {
            getStateManager().getCurrentState().update(dt);
            _elapsedTime += dt;
            accumulator -= dt;
        }

        // Render.
        getStateManager().getCurrentState().render(accumulator);

        // Get the sleep time.
        after = glfwGetTime();
        sleep = fpsTime - (after - current);

        // Sleep for the rest of the frame to clamp at MaxFps.
        if(sleep > 0.0)
            util::sleep(sleep);
        else
            std::cerr << "Can't keep up!" << std::endl;
    }
}

Engine::Engine()
        : _window(0), _objectiveBoid(0), _tower(0) {
    // Reserve space for the boids.
    _boids.reserve(ReservedBoids);

    // Init the rand() system.
    std::srand(time(NULL));

    // Create the window.
    initWindowSystem();
}

Engine::~Engine() {
    // Terminate the window.
    terminateWindowSystem();
}

int Engine::run() {
    // Inits the systems.
    initSystems();

    // Inits the objects.
    initObjects();

    // Enter the run state.
    getStateManager().changeState(RunStateId);

    // Main loop of the engine.
    mainLoop();

    // Terminates the objects.
    terminateObjects();

    // Terminates the systems.
    terminateSystems();

    return 0;
}

void Engine::addBoid() {
    const float boidSpace2 = 2 * BoidSpace;
    const int objectiveVectors = 9; // Number of vectors that can be used with obj.
    const int followVectors = 13; // Number of vectors that can be used with follow.
    bool isObjectiveBoid = true;

/*
    Vector directions[] = {
        // Used also by obj when inserting a new boid relative to
        // obj (objectiveBoid).
        Vector(-boidSpace2, -boidSpace2,    -boidSpace2),
        Vector(0.0,         -boidSpace2,    -boidSpace2),
        Vector(boidSpace2,  -boidSpace2,    -boidSpace2),
        Vector(-boidSpace2, 0.0,            -boidSpace2),
        Vector(0.0,         0.0,            -boidSpace2),
        Vector(boidSpace2,  0.0,            -boidSpace2),
        Vector(-boidSpace2, boidSpace2,     -boidSpace2),
        Vector(0.0,         boidSpace2,     -boidSpace2),
        Vector(boidSpace2,  boidSpace2,     -boidSpace2),

        // Used when adding relative to other follow boids.
        Vector(-boidSpace2, -boidSpace2,    0.0),
        Vector(boidSpace2,  -boidSpace2,    0.0),
        Vector(-boidSpace2, boidSpace2,     0.0),
        Vector(boidSpace2,  boidSpace2,     0.0)
    };
*/
    // Number of existing boids.
    size_t num = _boids.size();

    // Do this until we find a suitable place for the new boid.
    for(;;) {
        // Start with the objective boid.
        const Boid *boid = &getEngine().getObjectiveBoid();
        size_t numVectors = objectiveVectors;

        // Choose a random existing boid if there is at least 1 follow boid.
        // Else, stay with the objective boid.
        if(num) {
            size_t boidId = rand() % (num + 5);
            if(boidId < num) {
                boid = &_boids[boidId];
                numVectors = followVectors;
                isObjectiveBoid = false;
            }
        }

        // Choose a random direction.
        //size_t dir = rand() % numVectors;
        Vector direction = Vector(rand() % 1000, rand() % 1000, rand() % 1000);
        direction.normalize();
        direction *= boidSpace2;

        // Get the new position.
        //Point pos = boid->getRelativePosition() + directions[dir];
        Point pos;
        if(isObjectiveBoid)
            pos = boid->getRelativePosition() - direction - boid->direction * BoidSpace;
        else
            pos = boid->getRelativePosition() - direction;

        // Check the distances to all the other boids. If we find a boid
        // that is at a distance smaller tan boidSpace2 from pos, try again.
        // It is guaranteed that in case the boid is the objective boid,
        // no collision will happen.
        bool boidFound = num ? false : true;
        for(size_t i = 0; i < num; ++i) {
            if(Point::distance(pos, _boids[i].getRelativePosition())
                    > boidSpace2) {
                boidFound = true;
                break;
            }
        }
        if(!boidFound)
            continue;

        // Add the new boid relative to boid.
        // getRelativePosition() returns (0.0, 0.0, 0.0) if the boid is the
        // objective boid.
        _boids.push_back(FollowBoid(getAnimationSystem().getRandomBoidDisplayList(),
                getAnimationSystem().getRandomBoidGoingUp(), pos,
                boid->speed, boid->direction, boid->up));

        break;
    }

    // Calculate the middle position again.
    updateMiddlePosition();
}

void Engine::removeRandomBoid() {
    // Do not remove if the boids vector is empty.
    if(!_boids.size())
        return;

    // Get the size of the boid vector, generate a random number mod it.
    // Remove the random boid.
    size_t size = _boids.size();
    size_t boidToRemove = rand() % size;

    // Get the iterator position of the boid to remove.
    BoidVector::iterator it = _boids.begin();
    for(size_t i = 0; i != boidToRemove; ++i, ++it)
        if(it == _boids.end() - 1) // Sanity check.
            break;

    // Remove the boid.
    _boids.erase(it);

    // Calculate the middle position again.
    updateMiddlePosition();
}

void Engine::errorEvent(int error, const char *description) {
    std::cerr << "Error: " << description << " (error " << error << ")"
        << std::endl;
    std::exit(error);
}

