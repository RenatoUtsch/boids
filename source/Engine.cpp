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

    // Random speed.
    float objBoidSpeed = (rand() % 1000) / 1000;

    // Direction of the objective boid.
    Vector objBoidDir = Vector(0.0, 0.0, -1.0);

    // Add the objective boid moving to the center of the map.
    _objectiveBoid = new Boid( getAnimationSystem().getRandomBoidDisplayList(),
            getAnimationSystem().getRandomBoidGoingUp(),
            objBoidPos, objBoidSpeed, objBoidDir);

    // Add a boid.
    _boids.push_back(Boid(getAnimationSystem().getRandomBoidDisplayList(),
                getAnimationSystem().getRandomBoidGoingUp(),
                Point(10, 10, -10), objBoidSpeed, objBoidDir));

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
    std::srand(std::time(NULL));

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

void Engine::errorEvent(int error, const char *description) {
    std::cerr << "Error: " << description << " (error " << error << ")"
        << std::endl;
    std::exit(error);
}

