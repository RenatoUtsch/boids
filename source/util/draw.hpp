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

#ifndef UTIL_DRAW_HPP
#define UTIL_DRAW_HPP

/*
 * Utility drawing functions.
 */

namespace util {
    /**
     * Draws a circle centered at (0, 0, 0).
     * @param radius The radius of the circle.
     **/
    void drawCircle(float radius);

    /**
     * Draws a pyramid with its base centered at (0, 0, 0) and pointed in the
     * -z direction. The base is, then, in the xy plane with z = 0.
     * @param height The height of the pyramid.
     * @param topX X value of the top of the pyramid.
     * @param topY Y value of the top of the pyramid.
     * @param diagonalSize The size of the diagonal of the base.
     * @param diagonalAngle The angle between the top and bottom diagonals.
     **/
    void drawPyramid(float height, float topX, float topY, float diagonalSize,
            float diagonalAngle);
}

#endif // !UTIL_DRAW_HPP
