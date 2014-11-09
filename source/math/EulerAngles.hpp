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

#ifndef MATH_EULER_ANGLES_HPP
#define MATH_EULER_ANGLES_HPP

#include "../glfw.hpp"
#include "math.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"

/**
 * Implementation of euler angles to represent the orientation of an object.
 **/
class EulerAngles {

public:
    /// Represents the alpha value of the euler angle.
    float alpha;

    /// Represents the beta value of the euler angle.
    float beta;

    /// Represents the gamma value of the euler angle.
    float gamma;

    /**
     * Constructor of the class.
     * @param alphaVal the alpha value (orientation in the x axis) of the euler
     * angles.
     * @param betaVal the beta value (orientation in the y axis) of the euler
     * angles.
     * @param gammaVal the gamma value (orientation in the z axis) of the euler
     * angles.
     **/
    EulerAngles(float alphaVal = 0.0, float betaVal = 0.0, float gammaVal = 0.0)
            : alpha(alphaVal), beta(betaVal), gamma(gammaVal) {

    }

    /**
     * Constructs the euler angles from a direction vector.
     * @param direction The direction vector.
     * @param up up vector.
     **/
#if 0
    EulerAngles(Vector direction, Vector up) {
        // Seriously buggy.
        direction.normalize();
        up.normalize();
        Vector w0 = Vector(-direction.y, direction.x, 0.0);
        //Vector u0 = Vector::cross(w0, direction);

        float alphaInRads = asin(direction.z);
        float betaInRads = asin(Vector::dot(w0, up));

        alpha = -toDegrees(alphaInRads);
        beta = toDegrees(betaInRads);
        gamma = 0.0;
    }
#endif

    /**
     * Converts the euler angles to quaternions and returns the quaternion.
     **/
    inline Quaternion toQuaternion() const {
        float piDiv180 = M_PI / 180.0,
            piMultAlpha = piDiv180 * (this->alpha / 2.0),
            piMultBeta = piDiv180 * (this->beta / 2.0),
            piMultGamma = piDiv180 * (this->gamma / 2.0);

        Quaternion q1(cos(piMultAlpha), sin(piMultAlpha), 0.0, 0.0),
                   q2(cos(piMultBeta), 0.0, sin(piMultBeta), 0.0),
                   q3(cos(piMultGamma), 0.0, 0.0, sin(piMultGamma));

        return q1 * q2 * q3;
    }

    /**
     * Converts the euler angles to vectors pointing in the direction of
     * the orientation.
     **/
#if 0
    inline Vector toVector() const {
        // Seriously buggy.
        float alphaRads = toRads(alpha);
        float betaRads = toRads(beta);
        float cosAlpha = cos(alphaRads);

        return Vector(cosAlpha * sin(betaRads),
                sin(alphaRads),
                -cosAlpha * cos(betaRads));
    }
#endif

    /// += operator for euler angles.
    EulerAngles &operator+=(const EulerAngles &right) {
        this->alpha += right.alpha;
        this->beta += right.beta;
        this->gamma += right.gamma;
        return *this;
    }

    /// -= operator for euler angles.
    EulerAngles &operator-=(const EulerAngles &right) {
        this->alpha -= right.alpha;
        this->beta -= right.beta;
        this->gamma -= right.gamma;
        return *this;
    }
};

/// + operator for euler angles.
inline EulerAngles operator+(EulerAngles left, const EulerAngles &right) {
    left += right;
    return left;
}

/// - operator for euler angles.
inline EulerAngles operator-(EulerAngles left, const EulerAngles &right) {
    left -= right;
    return left;
}

/// == operator for euler angles.
inline bool operator==(const EulerAngles &left, const EulerAngles &right) {
    if(left.alpha == right.alpha && left.beta == right.beta
            && left.gamma == right.gamma)
        return true;

    return false;
}

/// != operator for euler angles.
inline bool operator!=(const EulerAngles &left, const EulerAngles &right) {
    return !operator==(left, right);
}

/// Operator overloading for writing euler angles to output streams.
inline std::ostream &operator<<(std::ostream &os, const EulerAngles &obj) {
    os << obj.alpha << "alpha, " << obj.beta << "beta, " << obj.gamma
        << "gamma";

    return os;
}

namespace glext {
    /**
     * This function calls the correct glRotatef functions to rotate by
     * the given euler Angles.
     * @param angles the euler (A)ngles to rotate.
     **/
    inline void glRotatea(const EulerAngles &angles) {
        glRotatef(angles.alpha, 1.0, 0.0, 0.0);
        glRotatef(angles.beta, 0.0, 1.0, 0.0);
        glRotatef(angles.gamma, 0.0, 0.0, 1.0);
    }
}

#endif // !MATH_EULER_ANGLES_HPP
