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
#include "math/math.hpp"

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
const int FrustumFieldOfView = 60;

/// Nearest z value of the viewing frustum. Please note that OpenGL uses
/// the near value as -near. Because of that, a near of 1.0, for example,  will
/// actually be the z value of -1.0 in the 3D space.
const float FrustumNear = 1.0;

/// Farthest z value of the viewing frustum. Please note that OpenGL uses
/// the far value as -far. Because of that, a far of 100.0, for example, will
/// actually be the z value of -100.0 in the 3D space.
const float FrustumFar = 2000.0;

/// Maximum number of frames per second the game will run at.
/// This value should be even.
const int MaxFps = 60;

/// Total number of display lists for the boids. The higher the better the
/// wing swing is.
const int NumBoidDisplayLists = MaxFps / 2;

/// Minimum height the boids can get.
const float MinimumHeight = 20.0;

/// Maximum height the boids can get.
const float MaximumHeight = 500.0;

/// Maximum number of display lists.
const unsigned MaxDisplayLists = 100;

/// The radius of the base of the tower at the middle of the map.
const float TowerBaseRadius = 100.0;

/// The height of the tower at the middle of the map.
const float TowerHeight = 300.0;

/// The Red color of the tower.
const float TowerColorRed = 0.396;

/// The Green color of the tower.
const float TowerColorGreen = 0.263;

/// The Blue color of the tower.
const float TowerColorBlue = 0.129;

/// Red (from rgb) color of the objective boid.
const float ObjectiveBoidColorRed = 1.0;

/// Green (from rgb) color of the objective boid.
const float ObjectiveBoidColorGreen = 0.4;

/// Blue (from rgb) color of the objective boid.
const float ObjectiveBoidColorBlue = 0.4;

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

/// The size of the diagonal of the boid's wing base.
const float BoidWingBaseDiagonalSize = 4.0;

/// The angle between the top and bottom diagonals of the boid's wing base.
const float BoidWingBaseAngle = 75.0;

/// Fix for the wing distance of the boids.
/// The bigger this is, the closer the wings are to the body.
const float BoidWingDistanceFix = 0.6;

/// The height of the boid's wing.
const float BoidWingHeight = 7.5;

/// The x position of the boid wing's top prior to rotating.
const float BoidWingTopX = (BoidWingBaseDiagonalSize / 2) * cos(BoidWingBaseAngle / 2);

/// The y position of the boid wing's top prior to rotating.
const float BoidWingTopY = 0.0;

/// Module of the initial velocity of the objective boid.
const float ObjectiveBoidInitialSpeed = 30.0;

/// Maximum distance a boid can be from other when being added.
const float NewBoidMaximumDistance = 20.0;

/// Maximum boid speed.
const float BoidMaxSpeed = 100.0;

/// Boid space: the radius of a sphere from the center of a boid that other
/// boids won't enter.
const float BoidSpace = BoidBodyRadius + BoidWingHeight + 5.0;

/// Sensitivity of the objective boid to the keys.
const float DefaultObjectiveBoidKeySensitivity = 50.0;

/// Up key for the objective boid.
const int ObjectiveBoidUpKey = GLFW_KEY_W;

/// Down key for the objective boid.
const int ObjectiveBoidDownKey = GLFW_KEY_S;

/// Left key for the objective boid.
const int ObjectiveBoidLeftKey = GLFW_KEY_A;

/// Right key for the objective boid.
const int ObjectiveBoidRightKey = GLFW_KEY_D;

/// Speed increase key for the objective boid.
const int ObjectiveBoidIncreaseSpeedKey = GLFW_KEY_E;

/// Speed decrease key for the objective boid.
const int ObjectiveBoidDecreaseSpeedKey = GLFW_KEY_Q;

/// Factor when increasing or decreasing speed (how fast the speed changes).
const float ObjectiveBoidSpeedFactor = 0.1;

/// The fidelity of curved shape rendering (higher values results in
/// smoother shapes).
const int CurvedShapeFidelity = 50;

/// The angle the wings will make in each swing.
const float WingAngle = 100.0;

/// How many boids to reserve in advance.
const int ReservedBoids = 50;

/// How many initial boids.
const int InitialBoidCount = 5;

/// How much behind the first boid the camera is.
const float InitialCameraDistance = 70.0;

/// How much to add to the distance with each added boid.
const float CameraDistanceFactor = 10.0;

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
const float GroundEvenSquareColorGreen = 0.2;

/// Blue component of the color of the even squares. Between 0.0 and 1.0.
const float GroundEvenSquareColorBlue = 0.0;

/// Red component of the color of the odd squares. Between 0.0 and 1.0.
const float GroundOddSquareColorRed = 0.0;

/// Green component of the color of the odd squares. Between 0.0 and 1.0.
const float GroundOddSquareColorGreen = 0.8;

/// Blue component of the color of the odd squares. Between 0.0 and 1.0.
const float GroundOddSquareColorBlue = 0.0;

/// Button that change the camera to free camera.
const int FreeCameraToggle = GLFW_KEY_1;

/// Button that changes the camera to tower camera.
const int TowerCameraToggle = GLFW_KEY_2;

/// Button that changes the camera to parallel camera.
const int ParallelCameraToggle = GLFW_KEY_3;

/// Button that changes the camera to behind camera.
const int BehindCameraToggle = GLFW_KEY_4;

/// Value to multiply the MaximumHeight. This will be the y height of the
/// sun.
const float SunHeightFactor = 1.5;

/// How much lower from the sun height the light is.
const float LightHeight = 5.0;

/// Red color of the sun.
const float SunColorRed = 1.0;

/// Green color of the sun.
const float SunColorGreen = 1.0;

/// Blue color of the sun.
const float SunColorBlue = 0.0;

/// Sun radius.
const float SunRadius = 100.0;

/// Close key.
const int CloseKey = GLFW_KEY_ESCAPE;

/// Pause key.
const int PauseKey = GLFW_KEY_P;

/// Debug state mouse button.
const int DebugMouseButton = GLFW_MOUSE_BUTTON_RIGHT;

/// Mouse button to step when on debug state.
const int StepMouseButton = GLFW_MOUSE_BUTTON_LEFT;

/// Key to add a boid.
const int AddBoidKey = GLFW_KEY_EQUAL;

/// Key to remove a random boid.
const int RemoveBoidKey = GLFW_KEY_MINUS;

/// Red (from RGB) component of the shadow color. Between 0.0 and 1.0.
const float ShadowColorRed = 0.2;

/// Green (from RGB) component of the shadow color. Between 0.0 and 1.0.
const float ShadowColorGreen = 0.2;

/// Blue (from RGB) component of the shadow color. Between 0.0 and 1.0.
const float ShadowColorBlue = 0.2;

/// Red (from RGB) component of the fog. Between 0.0 and 1.0.
const float FogColorRed = 0.5;

/// Green (from RGB) component of the fog. Between 0.0 and 1.0.
const float FogColorGreen = 0.5;

/// Blue (from RGB) component of the fog. Between 0.0 and 1.0.
const float FogColorBlue = 0.5;

/// Fog density.
const float FogDensity = 0.35;

/// Fog start depth.
const float FogStart = 200.0;

/// Fog end depth.
const float FogEnd = 500.0;

/// Key to toggle fog.
const int ToggleFogKey = GLFW_KEY_F;

/// Toggles the different orders of rotation and translation
/// of the boids. Use 1 and 0.
#define BOIDS_ROTATE_AFTER 1

#endif // !DEFS_HPP
