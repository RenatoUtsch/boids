/*
 * Math library intended for computer graphics, animation, physics and games
 * (but not restricted to it).
 *
 * Copyright (c) 2014 Renato Utsch
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

#ifndef MATH_VECTOR_HH
#define MATH_VECTOR_HH

#include <iostream>
#include "math.hh"

/**
 * An implementation of a Vector (as in linear algebra).
 * The vector is implemented in affine 4d space (x, y, z, h).
 * Not to be confused with std::vector, which is a dynamic array implementation.
 **/
class Vector {

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
     * Constructor for vectors.
     * @param xVal the value in the x direction.
     * @param yVal the value in the y direction.
     * @param zVal the value in the z direction.
     * @param hVal h value. Normally is 0.0 for vectors.
     **/
    Vector(float xVal = 0.0, float yVal = 0.0, float zVal = 0.0, float hVal = 0.0)
        : x(xVal), y(yVal), z(zVal), h(hVal) {

    }

    /**
     * Scale the vector by the given factor.
     * @param factor How much to multiply the vector.
     **/
    inline void scale(float factor) {
        this->x *= factor;
        this->y *= factor;
        this->z *= factor;
    }

    /**
     * Divides the vector by the given factor.
     * @param factor How much to divide the vector.
     **/
    inline void divScale(float factor) {
        this->x /= factor;
        this->y /= factor;
        this->z /= factor;
    }

    /**
     * Returns the module of the vector.
     **/
    inline double module() const {
        return std::sqrt((this->x * this->x)
                + (this->y * this->y)
                + (this->z * this->z));
    }

    /**
     * Normalizes the vector.
     **/
    inline void normalize() {
        return this->divScale(this->module());
    }

    /**
     * Dot product between two vectors.
     * @param v1 The first vector to do the dot product.
     * @param v2 The second vector of the dot product.
     * @return The dot product between v1 and v2.
     **/
    static inline float dot(const Vector &v1, const Vector &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    /**
     * Calculates the cross product between two vectors.
     * @param v1 The first vector to do the cross product.
     * @param v2 The second vector of the cross product.
     * @return The cross product between v1 and v2.
     **/
    static inline Vector cross(const Vector &v1, const Vector &v2) {
        return Vector(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
    }

    /// += operator for vectors.
    Vector &operator+=(const Vector &right) {
        this->x += right.x;
        this->y += right.y;
        this->z += right.z;
        this->h += right.h;
        return *this;
    }

    /// -= operator for vectors.
    Vector &operator-=(const Vector &right) {
        this->x -= right.x;
        this->y -= right.y;
        this->z -= right.z;
        this->h -= right.h;
        return *this;
    }

    /// *= operator representing a scale.
    Vector &operator*=(const float &factor) {
        this->scale(factor);
        return *this;
    }

    /// /= operator representing a scale division.
    Vector &operator/=(const float &factor) {
        this->divScale(factor);
        return *this;
    }

    /// unary * operator representing the vector's module.
    float operator*() const {
        return this->module();
    }
};

/// + operator for vectors.
inline Vector operator+(Vector left, const Vector &right) {
    left += right;
    return left;
}

/// - operator for vectors.
inline Vector operator-(Vector left, const Vector &right) {
    left -= right;
    return left;
}

/// * operator for scaling vectors.
inline Vector operator*(Vector left, const float &right) {
    left *= right;
    return left;
}

/// * operator for scaling vectors.
inline Vector operator*(const float &left, Vector right) {
    right *= left;
    return right;
}

/// / operator for scaling vectors.
inline Vector operator/(Vector left, const float &right) {
    left *= right;
    return left;
}

/// == operator for vectors.
inline bool operator==(const Vector &left, const Vector &right) {
    if(left.x == right.x && left.y == right.y && left.z == right.z
            && left.h == right.h)
        return true;

    return false;
}

/// != operator for vectors.
inline bool operator!=(const Vector &left, const Vector &right) {
    return !operator==(left, right);
}

/**
 * Operator overloading for writing vectors to output streams.
 **/
inline std::ostream &operator<<(std::ostream &os, const Vector &obj) {
    os << obj.x << "i + " << obj.y << "j + " << obj.z << "k";
    return os;
}

#endif // !MATH_VECTOR_HH
