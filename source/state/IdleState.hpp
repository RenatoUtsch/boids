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

#ifndef STATE_IDLESTATE_HPP
#define STATE_IDLESTATE_HPP

#include "../Engine.hpp"
#include "State.hpp"
#include "../glfw.hpp"

/**
 * The IdleState is the state before the beginning of the execution of the
 * engine. It does... nothing.
 * It is like the 0 of states.
 **/
class IdleState : public State {

public:
    ~IdleState() { }

    StateId getId() {
        return IdleStateId;
    }

    void load() { }
    void init() { }

    void input() {
        // Poll events to prevent the OS from killing off our program for
        // unresponsiveness.
        glfwPollEvents();
    }

    void update(float dt) { }
    void render(float alpha) { }
    void cleanUp() { }
    void unload() { }

    void keyEvent(GLFWwindow *window, int key, int scancode, int action,
            int mods) {
        // Exit if the user presses escape.
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(getEngine().getWindow(), GL_TRUE);
    }

    void cursorPosEvent(GLFWwindow *window, double xpos, double ypos) { }
    void mouseButtonEvent(GLFWwindow *window, int button, int action,
            int mods) { }
};

#endif // !STATE_IDLESTATE_HPP
