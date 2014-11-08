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

#include "draw.hpp"
#include "../glfw.hpp"
#include "../defs.hpp"
#include "../math/math.hpp"

void util::drawCircle(float radius) {
    float t = 0.0; // Angle parameter.
    float angleIncrement = 2 * M_PI / CurvedShapeFidelity;

    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i < CurvedShapeFidelity; ++i) {
            glVertex3f(radius * cos(t), radius * sin(t), 0.0);
            t += angleIncrement;
        }
    glEnd();
}

void util::drawPyramid(float height, float diagonalSize, float diagonalAngle) {
    // Calculate the division of the diagonal size by 2.
    float diagonalSizeBy2 = diagonalSize / 2.0;

    // Calculate the angle between the top and bottom diagonals divided by 2.
    float topBottomAngleBy2 = diagonalAngle / 2.0;

    // Diagonal size in the X direction.
    float diagonalSizeX = diagonalSizeBy2 * cos(topBottomAngleBy2);

    // Diagonal size in the Y direction.
    float diagonalSizeY = diagonalSizeBy2 * sin(topBottomAngleBy2);

    // create the base.
    glBegin(GL_QUADS);
        glVertex3f(diagonalSizeX, diagonalSizeY, 0.0);
        glVertex3f(-diagonalSizeX, diagonalSizeY, 0.0);
        glVertex3f(-diagonalSizeX, -diagonalSizeY, 0.0);
        glVertex3f(diagonalSizeX, -diagonalSizeY, 0.0);
    glEnd();

    // Create the triangles that compose the body of the pyramid.
    glBegin(GL_TRIANGLE_FAN);
        // Vertex at the top of the pyramid.
        glVertex3f(0.0, 0.0, -height);

        // Top triangle.
        glVertex3f(-diagonalSizeX, diagonalSizeY, 0.0);
        glVertex3f(diagonalSizeX, diagonalSizeY, 0.0);

        // Right triangle.
        glVertex3f(diagonalSizeX, -diagonalSizeY, 0.0);

        // Bottom triangle.
        glVertex3f(-diagonalSizeX, -diagonalSizeY, 0.0);

        // Left triangle.
        glVertex3f(-diagonalSizeX, diagonalSizeY, 0.0);
    glEnd();
}
