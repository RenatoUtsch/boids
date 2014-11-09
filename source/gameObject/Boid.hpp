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

#ifndef GAMEOBJECT_BOID_HPP
#define GAMEOBJECT_BOID_HPP

#include "GameObject.hpp"

/**
 * The data that represents a boid.
 **/
struct Boid : public GameObject {
    /// If the display lists are going up or down.
    bool displayListGoingUp;

    /**
     * Constructor.
     * Creates a boid at the given position and velocity.
     * @param _displayList The initial display list of the boid.
     * @param _displayListGoingUp If the display lists are being incremented or
     * @param _position The position of the boid.
     * @param _speed The speed in the boid's direction.
     * @param _direction The direction of the boid.
     * @param _up Up vector of the boid. Defaults to (0.0, 1.0, 0.0).
     * decremented.
     **/
    Boid(unsigned _displayList, bool _displayListGoingUp,
            Point _position, float _speed,
            Vector _direction, Vector _up = Vector(0.0, 1.0, 0.0))
        : GameObject(_displayList, _position, _speed, _direction, _up),
        displayListGoingUp(_displayListGoingUp) {

    }
};

#endif // !GAMEOBJECT_BOID_HPP
