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
#include "../math/Vector.hpp"
#include "../math/Point.hpp"

void util::drawCircle(float radius) {
    float t = 0.0; // Angle parameter.
    float angleIncrement = 2 * M_PI / CurvedShapeFidelity;

    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, 0.0, 1.0);
        for(int i = 0; i < CurvedShapeFidelity; ++i) {
            glVertex3f(radius * cos(t), radius * sin(t), 0.0);
            t += angleIncrement;
        }
    glEnd();
}

void util::drawPyramid(float height, float topX, float topY, float diagonalSize,
        float diagonalAngle) {
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
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(diagonalSizeX, diagonalSizeY, 0.0);
        glVertex3f(-diagonalSizeX, diagonalSizeY, 0.0);
        glVertex3f(-diagonalSizeX, -diagonalSizeY, 0.0);
        glVertex3f(diagonalSizeX, -diagonalSizeY, 0.0);
    glEnd();

    // Points
    Point p0 = Point(topX, topY, -height);
    Point p1 = Point(-diagonalSizeX, diagonalSizeY, 0.0);
    Point p2 = Point(-diagonalSizeX, -diagonalSizeY, 0.0);
    Point p3 = Point(diagonalSizeX, -diagonalSizeY, 0.0);
    Point p4 = Point(diagonalSizeX, diagonalSizeY, 0.0);

    // Vectors.
    Vector v10 = p0 - p1;
    Vector v20 = p0 - p2;
    Vector v30 = p0 - p3;
    Vector v40 = p0 - p4;
    Vector v12 = p2 - p1;
    Vector v23 = p3 - p2;
    Vector v34 = p4 - p3;
    Vector v41 = p1 - p4;

    // Normals of the faces.
    Vector baseNormal = Vector(0.0, 0.0, 1.0);
    Vector leftNormal = Vector::cross(v10, v12).normalize();
    Vector bottomNormal = Vector::cross(v20, v23).normalize();
    Vector rightNormal = Vector::cross(v30, v34).normalize();
    Vector topNormal = Vector::cross(v40, v41).normalize();

    // Normals of the points.
    Vector n0 = (leftNormal + bottomNormal + rightNormal + topNormal).normalize();
    Vector n1 = (leftNormal + baseNormal + topNormal).normalize();
    Vector n2 = (bottomNormal + baseNormal + leftNormal).normalize();
    Vector n3 = (baseNormal + bottomNormal + rightNormal).normalize();
    Vector n4 = (baseNormal + rightNormal + topNormal).normalize();

    // Create the triangles that compose the body of the pyramid.
    glBegin(GL_TRIANGLE_FAN);
        // Vertex at the top of the pyramid.
        glext::glNormalv(-1 * n0);
        glext::glVertexp(p0);

        // Top triangle.
        glext::glNormalv(-1 * n1);
        glext::glVertexp(p1);
        glext::glNormalv(-1 * n2);
        glext::glVertexp(p2);

        // Right triangle.
        glext::glNormalv(-1 * n3);
        glext::glVertexp(p3);

        // Bottom triangle.
        glext::glNormalv(-1 * n4);
        glext::glVertexp(p4);

        // Left triangle.
        glext::glNormalv(-1 * n1);
        glext::glVertexp(p1);
    glEnd();
}
