/*
 * Author: Renato Utsch Gonçalves
 * Computer Science, UFMG
 * Computer Graphics
 * Practical exercise 1 - Boids
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

#ifndef DEFS_HPP
#define DEFS_HPP

/**
 * Definition of the constants used in the software and of the global variables.
 **/

/// Initial window width.
const int InitialWindowWidth = 640;

/// Initial window height.
const int InitialWindowHeight = 480;

/// Initial x position of the window.
const int InitialWindowPosX = 100;

/// Initial y position of the window.
const int InitialWindowPosY = 100;

/// Field of view (in degrees) of the viewing frustum.
const int FrustumFieldOfView = 90;

/// Nearest z value of the viewing frustum. Please note that OpenGL uses
/// the near value as -near. Because of that, a near of 1.0, for example,  will
/// actually be the z value of -1.0 in the 3D space.
const float FrustumNear = 1.0;

/// Farthest z value of the viewing frustum. Please note that OpenGL uses
/// the far value as -far. Because of that, a far of 100.0, for example, will
/// actually be the z value of -100.0 in the 3D space.
const float FrustumFar = 100.0;

/// Maximum number of frames per second the game will run at.
const int MaxFps = 60;

/// Minimum height the boids can get.
const float MinimumHeight = 10.0;

/// Maximum height the boids can get.
const float MaximumHeight = 1000.0;

#endif // !DEFS_HPP
