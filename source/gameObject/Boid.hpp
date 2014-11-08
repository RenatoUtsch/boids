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
     * Creates a boid at the given position, velocity and orientation.
     * @param _position The position of the boid.
     * @param _velocity The velocity of the boid.
     * @param _orientation The orientation of the boid.
     * @param _displayList The initial display list of the boid.
     * @param _displayListGoingUp If the display lists are being incremented or
     * decremented.
     **/
    Boid(Point _position, Vector _velocity, EulerAngles _orientation,
            unsigned _displayList, bool _displayListGoingUp)
        : GameObject(_position, _velocity, _orientation, _displayList),
        displayListGoingUp(_displayListGoingUp) {

    }
};

#endif // !GAMEOBJECT_BOID_HPP
