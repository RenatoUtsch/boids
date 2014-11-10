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

#ifndef MATH_MATRIX4D_HPP
#define MATH_MATRIX4D_HPP

#include "../glfw.hpp"
#include <cstring>
#include <new>
#include <stdexcept>
#include <string>

class Matrix4d;

namespace glext {
    /**
     * Multiply the current OpenGL matrix by the given matrix.
     * @param matrix the (m)atrix to use.
     **/
    inline void glMultMatrixm(const Matrix4d &matrix);
}

/**
 * Represents a 4x4 matrix to be used with OpenGL.
 **/
class Matrix4d {
public:
    /// The number of lines of the matrix.
    static const int numLines = 4;

    /// The number of columns of the matrix.
    static const int numColumns = 4;

private:
    /// The data of the matrix.
    float _data[numLines * numColumns];

public:
    /**
     * Acessing elements from the data. Fails silently (or not).
     **/
    float &operator[](int index) {
        return _data[index];
    }

    /**
     * Acessing elements from the data. Fails silently (or not).
     * Const version.
     **/
    const float &operator[](int index) const {
        return _data[index];
    }

    /**
     * Accessing elements from the data; throws std::out_of_range in case of
     * error.
     **/
    float &at(int index) {
        if(index >= numLines * numColumns)
            throw std::out_of_range("Trying to access invalid element");
        return _data[index];
    }

    /**
     * Accessing elements from the data; throws std::out_of_range in case of
     * error.
     * Const version.
     **/
    const float &at(int index) const {
        if(index >= numLines * numColumns)
            throw std::out_of_range("Trying to access invalid element");
        return _data[index];
    }

    /**
     * Accessing element from the data as a two dimensional array.
     * Throws std::out_of_range in case of error.
     **/
    float &at(int row, int column) {
        if(row * numLines + column >= numLines * numColumns)
            throw std::out_of_range("Trying to access invalid element");
        return _data[row * numLines + column];
    }

    /**
     * Accessing element from the data as a two dimensional array.
     * Throws std::out_of_range in case of error.
     * Const version.
     **/
    const float &at(int row, int column) const {
        if(row * numLines + column >= numLines * numColumns)
            throw std::out_of_range("Trying to access invalid element");
        return _data[row * numLines + column];
    }

    /// Friend function to multiply the current OpenGL matrix by this one.
    friend inline void glext::glMultMatrixm(const Matrix4d &matrix);
};

namespace glext {
    /**
     * Multiplies the current matrix by the given matrix.
     **/
    inline void glMultMatrixm(const Matrix4d &matrix) {
        glMultMatrixf(matrix._data);
    }
}


#endif // !MATH_MATRIX4D_HPP
