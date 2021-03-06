/*
 * Math library intended for computer graphics, animation, physics and games
 * (but not restricted to it).
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

#ifndef MATH_POINT_HPP
#define MATH_POINT_HPP

#include <iostream>
#include "../glfw.hpp"
#include "Vector.hpp"

/**
 * An implementation of a Point (as in linear algebra).
 * The point is implemented in affine 4d space (x, y, z, h).
 **/
class Point {

public:
    /// Value in the x direction.
    float x;

    /// Value in the y direction.
    float y;

    /// Value in the z direction.
    float z;

    /**
     * h value.
     * All operations in the normal 3D space should result in a h value of 1.0
     * in case the result of the operation is a point or in a h value of 0.0 if
     * the result of the operation is a vector.
     * In case this doesn't happen, there are only two possibilities: one, you
     * made something wrong and this is an error, or two, you are working with
     * the projective space.
     * If you aren't working with the projective space and the result is
     * different than 1.0 for points and 0.0 for vectors, then you made
     * something wrong.
     **/
    float h;

    /**
     * Constructor for points.
     * @param xVal the value in the x direction.
     * @param yVal the value in the y direction.
     * @param zVal the value in the z direction.
     * @param hVal h value.
     **/
    Point(float xVal = 0.0, float yVal = 0.0, float zVal = 0.0, float hVal = 1.0)
        : x(xVal), y(yVal), z(zVal), h(hVal) {

    }

    /**
     * Calculates the distance between two points.
     **/
    static float distance(const Point &p1, const Point &p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2)
                + std::pow(p1.y - p2.y, 2)
                + std::pow(p1.z - p2.z, 2));
    }

    /// += operator for point-vector addition.
    Point &operator+=(const Vector &right) {
        this->x += right.x;
        this->y += right.y;
        this->z += right.z;
        this->h += right.h;
        return *this;
    }

    /// -= operator for point-vector subtraction.
    Point &operator-=(const Vector &right) {
        this->x -= right.x;
        this->y -= right.y;
        this->z -= right.z;
        this->h -= right.h;
        return *this;
    }
};

/// + operator for point-vector addition.
inline Point operator+(Point left, const Vector &right) {
    left += right;
    return left;
}

/// - operator for point-vector subtraction.
inline Point operator-(Point left, const Vector &right) {
    left -= right;
    return left;
}

/**
 * Subtracts two points. This results in a vector.
 **/
inline Vector operator-(const Point &left, const Point &right) {
    return Vector(left.x - right.x, left.y - right.y, left.z - right.z,
            left.h - right.h);
}

/// == operator for points.
inline bool operator==(const Point &left, const Point &right) {
    if(left.x == right.x && left.y == right.y && left.z == right.z
            && left.h == right.h)
        return true;

    return false;
}

/// != operator for points.
inline bool operator!=(const Point &left, const Point &right) {
    return !operator==(left, right);
}

/// Operator overloading for writing points to output streams.
inline std::ostream &operator<<(std::ostream &os, const Point &obj) {
    os << obj.x << "i + " << obj.y << "j + " << obj.z << "k";
    return os;
}

namespace glext {
    /**
     * Specify an OpenGL vertex using a Point class.
     * @param point The (p)oint to use as a vertex.
     **/
    inline void glVertexp(const Point &point) {
        glVertex4f(point.x, point.y, point.z, point.h);
    }

    /**
     * Translate the to the point position.
     * @param opint The (p)oint to translate to.
     **/
    inline void glTranslatep(const Point &point) {
        glTranslatef(point.x, point.y, point.z);
    }
}

#endif // !MATH_POINT_HPP
