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

#ifndef MATH_PLANE_HPP
#define MATH_PLANE_HPP

#include "math.hpp"
#include "Point.hpp"
#include "Vector.hpp"

/**
 * Finds the A, B, C and D coefficients of the plane given 3 vertices
 * in it.
 * Saves in the vector given as last parameter.
 **/
void findPlaneEquation(const Point &p0, const Point &p1, const Point &p2,
        float planeOut[4]) {
    // Two vectors are needed to find the intersection.
    Vector v0 = p1 - p0;
    Vector v1 = p2 - p0;

    // Find the intersection and save A, B, C and D of the plane's equation.
    Vector cross = Vector::cross(v0, v1);
    planeOut[0] = cross.x;
    planeOut[1] = cross.y;
    planeOut[2] = cross.z;
    planeOut[3] = -(planeOut[0] * p0.x + planeOut[1] * p0.y + planeOut[2] * p0.z);
}

#endif // !MATH_PLANE_HPP
