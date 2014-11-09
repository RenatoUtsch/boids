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

#ifndef GAMEOBJECT_GAMEOBJECT_HPP
#define GAMEOBJECT_GAMEOBJECT_HPP

#include "../math/Point.hpp"
#include "../math/Vector.hpp"

/**
 * A GameObject.
 **/
struct GameObject  {
    /// Current display list.
    unsigned displayList;

    /// Position of the object in the space.
    Point position;

    /// Speed of the object in his direction.
    float speed;

    /// Direction of the object.
    Vector direction;

    /// Up vector of the object. Defaults to (0.0, 1.0, 0.0).
    Vector up;

    /**
     * Constructor.
     * Creates an object at the given position with the given direction, up
     * and speed.
     * @param _displayList the display list of the object.
     * @param _position Position of the object.
     * @param _speed Speed in the object's direction.
     * @param _direction Direction of the object.
     * @param _up Up vector of the object (defaults to (0.0, 1.0, 0.0)).
     **/
    GameObject(unsigned _displayList, Point _position, float _speed,
            Vector _direction, Vector _up = Vector(0.0, 1.0, 0.0))
            : displayList(_displayList), position(_position), speed(_speed),
            direction(_direction), up(_up) {

    }
};

#endif // !GAMEOBJECT_GAMEOBJECT_HPP
