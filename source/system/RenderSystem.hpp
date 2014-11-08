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

#ifndef SYSTEM_RENDERSYSTEM_HPP
#define SYSTEM_RENDERSYSTEM_HPP

#include "System.hpp"
#include "../glfw.hpp"
#include "../math/Vector.hpp"

class RenderSystem : public System {
    /// Next display list that is not used.
    unsigned _nextDisplayList;

    /// Ground display list.
    unsigned _groundDisplayList;

    /// Sun display list.
    unsigned _sunDisplayList;

    /// Creates the ground.
    void createGround();

    /// Creates the sun.
    void createSun();

    /// Destroys the ground.
    void destroyGround();

    /// Destroys the sun.
    void destroySun();

public:
    void init();
    void terminate();
    void update(float dt);

    /**
     * Returns the next display list.
     **/
    inline unsigned getNextDisplayList() {
        return _nextDisplayList;
    }

    /**
     * Sets the next display list.
     **/
    inline void setNextDisplayList(unsigned next) {
        _nextDisplayList = next;
    }

    /**
     * Increments the next display list value.
     **/
    inline void incrementNextDisplayList() {
        ++_nextDisplayList;
    }

    /**
     * Framebuffer resize event. Called after a window resize.
     * This function sets up the OpenGL projection again for the given window
     * to match the new framebuffer size.
     * The framebuffer size is is the size of the window in pixels, not in screen
     * coordinates. OpenGL expects the size in pixels, and, while the screen
     * coordinates and pixels are the same in some platforms, they differ in
     * others (i.e. Macs with Retina Display).
     * Because of that, we listen to changes in the framebuffer, and not to
     * changes in the window.
     * @param window The window that was resized.
     * @param width The new width of the framebuffer.
     * @param height The new height of the framebuffer.
     **/
    void framebufferSizeEvent(GLFWwindow *window, int width, int height);
};

#endif // !SYSTEM_RENDERSYSTEM_HPP
