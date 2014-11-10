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

#ifndef GAMEOBJECT_OBJECTIVEBOID_HPP
#define GAMEOBJECT_OBJECTIVEBOID_HPP

#include "Boid.hpp"
#include "../defs.hpp"

/**
 * The data that represents the objective boid.
 **/
struct ObjectiveBoid : public Boid {
    /// Right direction.
    Vector right;

    /// Horizontal angle of the boid.
    float horizontalAngle;

    /// Vertical angle of the boid.
    float verticalAngle;

    /// Sensitivity of the boid to the keys.
    float keySensitivity;

    /**
     * Constructor.
     * Creates the objective boid at the given position and velocity.
     **/
    ObjectiveBoid(unsigned _displayList, bool _displayListGoingUp,
            Point _position, float _speed,
            Vector _direction, Vector _up = Vector(0.0, 1.0, 0.0))
            : Boid(_displayList, _displayListGoingUp, _position, _speed,
                    _direction, _up),
            keySensitivity(DefaultObjectiveBoidKeySensitivity) {
        // Convert the direction to angles.
        direction.normalize();
        float vertRads = asin(-direction.y);
        verticalAngle = toDegrees(vertRads);
        horizontalAngle = toDegrees(acos(-direction.z / cos(vertRads)));

        // Update the right direction.
        right.x = cos(toRads(horizontalAngle));
        right.y = 0.0;
        right.z = sin(toRads(horizontalAngle));
    }

    Point getAbsolutePosition() const {
        return position;
    }

    Point getRelativePosition() const {
        return Point();
    }
};

#endif // !GAMEOBJECT_OBJECTIVEBOID_HPP
