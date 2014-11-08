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

#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include "glfw.hpp"
#include "Engine.hpp"

/*
 * Callbacks for GLFW.
 */

/**
 * Callback for error events from glfw. Calls the engine's errorEvent.
 **/
inline void errorCallback(int error, const char *description) {
    getEngine().errorEvent(error, description);
}

/**
 * Callback for framebuffer (window) resize events from glfw. Calls the
 * engine's framebufferSizeEvent.
 **/
inline void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    getEngine().getRenderSystem().framebufferSizeEvent(window, width, height);
}

/**
 * Callback for key events from glfw. Calls the current state's keyEvent.
 **/
inline void keyCallback(GLFWwindow *window, int key, int scancode, int action,
        int mods) {
    getEngine().getStateManager().getCurrentState().keyEvent(window, key,
            scancode, action, mods);
}

/**
 * Callback for mouse cursor position events from glfw. Calls the current
 * state's cursor position event.
 **/
inline void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    getEngine().getStateManager().getCurrentState().cursorPosEvent(window, xpos,
            ypos);
}

/**
 * Callback for mouse button events from glfw. Calls the current state's
 * mouseButtonEvent.
 **/
inline void mouseButtonCallback(GLFWwindow *window, int button, int action,
        int mods) {
    getEngine().getStateManager().getCurrentState().mouseButtonEvent(window,
            button, action, mods);
}

#endif // !CALBACKS_HPP
