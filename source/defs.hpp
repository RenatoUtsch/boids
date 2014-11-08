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

#ifndef DEFS_HPP
#define DEFS_HPP

#include "glfw.hpp"

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
const float FrustumFar = 1000.0;

/// Maximum number of frames per second the game will run at.
/// This value should be even.
const int MaxFps = 60;

/// Total number of display lists for the boids. The higher the better the
/// wing swing is.
const int NumBoidDisplayLists = MaxFps / 2;

/// Minimum height the boids can get.
const float MinimumHeight = 10.0;

/// Maximum height the boids can get.
const float MaximumHeight = 500.0;

/// Maximum number of display lists.
const unsigned MaxDisplayLists = 100;

/// The radius of the base of the tower at the middle of the map.
const float TowerBaseRadius = 100.0;

/// The height of the tower at the middle of the map.
const float TowerHeight = 300.0;

/// The Red color of the tower.
const float TowerColorRed = 0.617;

/// The Green color of the tower.
const float TowerColorGreen = 0.364;

/// The Blue color of the tower.
const float TowerColorBlue = 0.084;

/// Red (from rgb) color of the boids.
const float BoidColorRed = 1.0;

/// Green (from rgb) color of the boids.
const float BoidColorGreen = 0.6;

/// Blue (from rgb) color of the boids.
const float BoidColorBlue = 0.0;

/// The radius of the body of the boid.
const float BoidBodyRadius = 1.5;

/// The scale in the z direction of the boid's body circle to make it an
/// ellipsis.
const float BoidBodyScale = 3.0;

/// The height of the boid's wing.
const float BoidWingHeight = 5.0;

/// The size of the diagonal of the boid's wing base.
const float BoidWingBaseDiagonalSize = 5.0;

/// The angle between the top and bottom diagonals of the boid's wing base.
const float BoidWingBaseAngle = 75.0;

/// Fix for the wing distance of the boids.
/// The bigger this is, the closer the wings are to the body.
const float BoidWingDistanceFix = 0.6;

/// The fidelity of curved shape rendering (higher values results in
/// smoother shapes).
const int CurvedShapeFidelity = 50;

/// The angle the wings will make in each swing.
const float WingAngle = 90.0;

/// How many boids to reserve in advance.
const int ReservedBoids = 50;

/// How many initial boids.
const int InitialBoidCount = 5;

/// How much behind the first boid the camera is.
const float InitialCameraDistance = 5.0;

/// How fast the camera moves. This is just a default value.
const double DefaultCameraMovementSpeed = 100.0;

/// How sensitive mouse movements affect the camera. This is just a default
/// value.
const double DefaultCameraSensitivity = 0.2;

/// Controlling camera movement: forward.
const int CameraForwardKey = GLFW_KEY_UP;

/// Controlling camera movement: backward.
const int CameraBackwardKey = GLFW_KEY_DOWN;

/// Controlling camera movement: left strafe.
const int CameraLeftStrafeKey = GLFW_KEY_LEFT;

/// Controlling camera movement: right strafe.
const int CameraRightStrafeKey = GLFW_KEY_RIGHT;

/// Button to increase mouse sensitivity.
const int CameraIncreaseSensitivityKey = GLFW_KEY_LEFT_BRACKET;

/// Button to decrease mouse sensitivity.
const int CameraDecreaseSensitivityKey = GLFW_KEY_RIGHT_BRACKET;

/// Sensitivity increase / decrase by using the buttons.
const float CameraSensitivityChangeRate = 0.05;

/// How fast the camera moves.
const float CameraMovementSpeedFactor = 100.0;

/// Distance of the tower camera to the tower.
const float TowerCameraDistance = 10.0;

/// Red component of the background. Between 0.0 and 1.0.
const float BackgroundColorRed = 0.529;

/// Green component of the background. Between 0.0 and 1.0.
const float BackgroundColorGreen = 0.808;

/// Blue component of the background. Between 0.0 and 1.0.
const float BackgroundColorBlue = 0.98;

/// Position of the ground in the Y-Axis.
const float GroundLevel = 0.0;

/// How far on the Z-Axis and X-Axis the ground extends.
const float GroundSize = 1000.0;

/// The size of the squares.
const float GroundSquareSize = 20.0;

/// Red component of the color of the even squares. Between 0.0 and 1.0.
const float GroundEvenSquareColorRed = 0.0;

/// Green component of the color of the even squares. Between 0.0 and 1.0.
const float GroundEvenSquareColorGreen = 0.4;

/// Blue component of the color of the even squares. Between 0.0 and 1.0.
const float GroundEvenSquareColorBlue = 0.0;

/// Red component of the color of the odd squares. Between 0.0 and 1.0.
const float GroundOddSquareColorRed = 0.2;

/// Green component of the color of the odd squares. Between 0.0 and 1.0.
const float GroundOddSquareColorGreen = 0.8;

/// Blue component of the color of the odd squares. Between 0.0 and 1.0.
const float GroundOddSquareColorBlue = 0.2;

/// Button that change the camera to free camera.
const int FreeCameraToggle = GLFW_KEY_1;

/// Button that changes the camera to tower camera.
const int TowerCameraToggle = GLFW_KEY_2;

/// Button that changes the camera to parallel camera.
const int ParallelCameraToggle = GLFW_KEY_3;

/// Button that changes the camera to fixed distance camera.
const int FixedDistanceCameraToggle = GLFW_KEY_4;

/// Value to multiply the MaximumHeight. This will be the y height of the
/// sun.
const float SunHeightFactor = 1.5;

/// Red color of the sun.
const float SunColorRed = 1.0;

/// Green color of the sun.
const float SunColorGreen = 1.0;

/// Blue color of the sun.
const float SunColorBlue = 0.0;

/// Sun radius.
const float SunRadius = 100.0;

#endif // !DEFS_HPP
