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

#ifndef GAMEOBJECT_GAMEOBJECT_HPP
#define GAMEOBJECT_GAMEOBJECT_HPP

#include "../math/Point.hpp"
#include "../math/Vector.hpp"
#include "../math/EulerAngles.hpp"

/**
 * A GameObject.
 **/
struct GameObject  {
    /// Position of the object in the space.
    Point position;

    /// Velocity of the object.
    Vector velocity;

    /// Orientation of the object.
    EulerAngles orientation;

    /// Current display list.
    unsigned displayList;

    /**
     * Constructor.
     * Creates an object at the given position with the given orientation and
     * velocity.
     * @param _position Position of the object.
     * @param _velocity Velocity of the object.
     * @param _orientation Orientation of the object.
     * @param _displayList the display list of the object.
     **/
    GameObject(Point _position, Vector _velocity, EulerAngles _orientation,
            unsigned _displayList)
        : position(_position),
        velocity(_velocity),
        orientation(_orientation),
        displayList(_displayList) {

    }
};

#endif // !GAMEOBJECT_GAMEOBJECT_HPP
