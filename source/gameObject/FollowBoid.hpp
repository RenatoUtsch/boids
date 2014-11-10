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

#ifndef GAMEOBJECT_FOLLOWBOID_HPP
#define GAMEOBJECT_FOLLOWBOID_HPP

#include "Boid.hpp"

/**
 * A boid that follows the objective boid.
 **/
struct FollowBoid : public Boid {

    /**
     * Constructor.
     * Creates the boid with the given position (relative to the objective boid).
     * The objective boid must already have been created.
     **/
    FollowBoid(unsigned _displayList, bool _displayListGoingUp,
            Point _position, float _speed,
            Vector _direction, Vector _up = Vector(0.0, 1.0, 0.0))
        : Boid(_displayList, _displayListGoingUp, _position, _speed,
                _direction, _up) {

    }

    Point getAbsolutePosition() const;
    Point getRelativePosition() const;
};

#endif // !GAMEOBJECT_FOLLOWBOID_HPP
