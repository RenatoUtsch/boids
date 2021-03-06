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

#ifndef STATE_RUNSTATE_HPP
#define STATE_RUNSTATE_HPP

#include "../Engine.hpp"
#include "State.hpp"
#include "../glfw.hpp"

/**
 * Run state is the normal state of execution in the game.
 **/
class RunState : public State {

public:
    StateId getId() {
        return RunStateId;
    }

    void load() { }
    void init() { }

    void input() {
        double xpos, ypos;
        glfwGetCursorPos(getEngine().getWindow(), &xpos, &ypos);

        // Save the last position of the cursor.
        getEngine().setLastCursorPos(xpos, ypos);

        // Poll events.
        glfwPollEvents();
    }

    void update(float dt) {
        // Update the systems.
        getEngine().getAnimationSystem().update(dt);
        getEngine().getCameraSystem().update(dt);
        getEngine().getCollisionSystem().update(dt);
        getEngine().getMovementSystem().update(dt);
    }

    void render(float alpha) {
        getEngine().getRenderSystem().update(alpha);
    }

    void cleanUp() { }
    void unload() { }

    void keyEvent(GLFWwindow *window, int key, int scancode, int action,
            int mods) {
        if(action == GLFW_PRESS) {
            switch(key) {
                case CloseKey:
                    // Exit if the user presses escape.
                    glfwSetWindowShouldClose(getEngine().getWindow(), GL_TRUE);
                    break;

                case PauseKey:
                    // Go to pause state.
                    getEngine().getStateManager().changeState(PauseStateId);
                    break;

                case AddBoidKey:
                    // Add a new boid.
                    getEngine().addBoid();
                    break;

                case RemoveBoidKey:
                    // Remove a random boid.
                    getEngine().removeRandomBoid();
                    break;

                case ToggleFogKey:
                    // Toggle fog.
                    getEngine().getRenderSystem().toggleFog();
                    break;
            }
        }

        // Let the camera system process its camera movement.
        getEngine().getCameraSystem().keyEvent(window, key, scancode, action,
                mods);
    }

    void cursorPosEvent(GLFWwindow *window, double xpos, double ypos) {
        // Let the camera system process its camera orientation.
        getEngine().getCameraSystem().cursorPosEvent(window, xpos, ypos);
    }

    void mouseButtonEvent(GLFWwindow *window, int button, int action,
            int mods) {
        if(action == GLFW_PRESS) {
            switch(button) {
                case DebugMouseButton:
                    // Go to debug state.
                    getEngine().getStateManager().changeState(DebugStateId);
                    break;
            }
        }
    }
};

#endif // !STATE_RUNSTATE_HPP
