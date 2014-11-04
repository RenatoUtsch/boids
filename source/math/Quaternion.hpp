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

#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP

#include <iostream>
#include <stdexcept>
#include "math.hpp"
#include "Matrix4d.hpp"
#include "Vector.hpp"

/**
 * A quaternion of the form (w + xi + yj + zk) implementation.
 * This particular implementation is focused on the usage of quaternions to
 * represent orientation when positioning something in computer graphics.
 **/
class Quaternion {

public:
    /// Represents the real part of the quaternion.
    float w;

    /// Represents the pure (xi + yj + zk) part of the quaternion.
    Vector v;

    /**
     * Constructor of a quaternion.
     * @param w Real part of the quaternion.
     * @param v Real vector representing the pure (xi + yj + zk) part of the
     * quaternion.
     **/
    Quaternion(float _w, Vector _v)
        : w(_w), v(_v) {

    }

    /**
     * Constructor of a quaternion.
     * This constructor is defined as a helper function to ease the creation
     * of quaternions.
     * @param _w Real part of the quaternion.
     * @param _x i part (representing xi) of the quaternion.
     * @param _y j part (representing yj) of the quaternion.
     * @param _z k part (representing zk) of the quaternion.
     **/
    Quaternion(float _w = 1.0, float _x = 0.0, float _y = 0.0, float _z = 0.0)
            : w(_w), v(_x, _y, _z) {

    }

    /**
     * Returns the magnitude of the quaternion.
     **/
    inline double magnitude() {
        return std::sqrt((this->w * this->w)
                + (this->v.module() * this->v.module()));
    }

    /**
     * Returns the conjugate of the quaternion.
     **/
    inline Quaternion conjugate() {
        return Quaternion(this->w,
                -this->v.x,
                -this->v.y,
                -this->v.z);
    }

    /**
     * Replaces the data of the given matrix with rotation data and returns it.
     * Throws length_error in case the matrix isn't 4x4.
     * @param matrix The matrix to replace the data.
     **/
    inline void toMatrix(Matrix4d &matrix) {
        float ww = this->w * this->w,
            xx = this->v.x * this->v.x,
            yy = this->v.y * this->v.y,
            zz = this->v.z * this->v.z,
            wx2 = 2.0 * this->w * this->v.x,
            wy2 = 2.0 * this->w * this->v.y,
            wz2 = 2.0 * this->w * this->v.z,
            xy2 = 2.0 * this->v.x * this->v.y,
            xz2 = 2.0 * this->v.x * this->v.z,
            yz2 = 2.0 * this->v.y * this->v.z;

        matrix[0] = ww + xx - yy - zz;
        matrix[1] = xy2 + wz2;
        matrix[2] = xz2 - wy2;
        matrix[3] = 0.0;
        matrix[4] = xy2 - wz2;
        matrix[5] = ww - xx + yy - zz;
        matrix[6] = yz2 + wx2;
        matrix[7] = 0.0;
        matrix[8] = xz2 + wy2;
        matrix[9] = yz2 - wx2;
        matrix[10] = ww - xx - yy + zz;
        matrix[11] = 0.0;
        matrix[12] = 0.0;
        matrix[13] = 0.0;
        matrix[14] = 0.0;
        matrix[15] = 1.0;
    }

    /**
     * Converts a quaternion to a rotation matrix and returns it.
     **/
    inline Matrix4d toMatrix() {
        Matrix4d ret;
        this->toMatrix(ret);
        return ret;
    }

    /// += operator for quaternions.
    Quaternion &operator+=(const Quaternion &right) {
        this->w += right.w;
        this->v.x += right.v.x;
        this->v.y += right.v.y;
        this->v.z += right.v.z;
        return *this;
    }

    /// -= operator for quaternions.
    Quaternion &operator-=(const Quaternion &right) {
        this->w -= right.w;
        this->v.x -= right.v.x;
        this->v.y -= right.v.y;
        this->v.z -= right.v.z;
        return *this;
    }

    /// *= operator for quaternions.
    Quaternion &operator*=(const Quaternion &right) {
        Quaternion res((this->w * right.w) - (this->v.x * right.v.x)
                - (this->v.y * right.v.y) - (this->v.z * right.v.z),
                (this->w * right.v.x) + (this->v.x * right.w)
                + (this->v.y * right.v.z) - (this->v.z * right.v.y),
                (this->w * right.v.y) + (this->v.y * right.w)
                - (this->v.x * right.v.z) + (this->v.z * right.v.x),
                (this->w * right.v.z) + (this->v.z * right.w)
                + (this->v.x * right.v.y) - (this->v.y * right.v.x));
        *this = res;
        return *this;
    }

    /**
     * Dot product between two quaternions.
     * @param q1 The first quaternion to do the dot product.
     * @param q2 The second quaternion of the dot product.
     * @return The dot product between q1 and q2.
     **/
    static inline float dot(const Quaternion &q1, const Quaternion &q2) {
        return q1.w * q2.w + q1.v.x * q2.v.x + q1.v.y * q2.v.y
            + q1.v.z * q2.v.z;
    }

    /**
     * Spherical Linear intERPolation between unit quaternions q1 and q2
     * with interpolation parameter t.
     **/
    static inline Quaternion slerp(const Quaternion &q1, Quaternion q2,
            float t) {
        float theta, mult1, mult2;

        // Reverse the sign of q2 if q1.q2 < 0.
        if(dot(q1, q2) < 0.0) {
            q2.w = -q2.w;
            q2.v.x = -q2.v.x;
            q2.v.y = -q2.v.y;
            q2.v.z = -q2.v.z;
        }

        theta = acos(dot(q1, q2));

        // To avoid division by 0 and by very small numbers, the approximation
        // of sin(angle) by angle is used when theta is mall (0.000001 is chosen
        // arbitrarily).
        if(theta > 0.000001) {
            float sinTheta = sin(theta);
            mult1 = sin((1 - t) * theta) / sinTheta;
            mult2 = sin(t * theta) / sinTheta;
        }
        else {
            mult1 = 1 - t;
            mult2 = t;
        }

        // Create and return the slerp quaternion.
        return Quaternion(mult1 * q1.w + mult2 * q2.w,
                mult1 * q1.v.x + mult2 * q2.v.x,
                mult1 * q1.v.y + mult2 * q2.v.y,
                mult1 * q1.v.z + mult2 * q2.v.z);
    }
};

/// + operator for quaternions.
inline Quaternion operator+(Quaternion left, const Quaternion &right) {
    left += right;
    return left;
}

/// - operator for quaternions.
inline Quaternion operator-(Quaternion left, const Quaternion &right) {
    left -= right;
    return left;
}

/// * operator for quaternions.
inline Quaternion operator*(Quaternion left, const Quaternion &right) {
    left *= right;
    return left;
}

/// == Operator for quaternions.
inline bool operator==(const Quaternion &left, const Quaternion &right) {
    if(left.w == right.w && left.v.x == right.v.x
            && left.v.y == right.v.y && left.v.z == right.v.z)
        return true;

    return false;
}

/// != Operator for quaternions.
inline bool operator!=(const Quaternion &left, const Quaternion &right) {
    return !operator==(left, right);
}

/**
 * Operator overloading for writing Quaternions to output streams.
 **/
inline std::ostream &operator<<(std::ostream &os, const Quaternion &obj) {
    os << obj.w << " + " << obj.v.x << "i + " << obj.v.y << "j + " << obj.v.z
        << "k";

    return os;
}

#endif // !MATH_QUATERNION_HPP
