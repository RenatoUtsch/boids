/*
 * Author: Renato Utsch Gonçalves
 * Computer Science, UFMG
 * Computer Graphics
 * Practical exercise 1 - Boids
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
    glfwSetWindowSizeCallback(_window, windowSizeCallback);
    glfwSetKeyCallback(_window, keyCallback);
    glfwSetCursorPosCallback(_window, cursorPosCallback);
    glfwSetMouseButtonCallback(_window, mouseButtonCallback);
}

void Engine::terminateWindowSystem() {
    glfwDestroyWindow(_window);
    glfwTerminate();
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
        : _window(0) {
    // Load everything that is needed.

}

Engine::~Engine() {
    // Unload everything that is needed.

}

int Engine::run() {
    // Inits the systems.
    initWindowSystem();

    // Main loop of the engine.
    mainLoop();

    // Terminates the systems.
    terminateWindowSystem();

    return 0;
}

void Engine::errorEvent(int error, const char *description) {
    std::cerr << "Error: " << description << " (error " << error << ")"
        << std::endl;
    std::exit(error);
}

void Engine::windowSizeEvent(GLFWwindow *window, int width, int height) {

}
