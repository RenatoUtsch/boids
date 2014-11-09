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

#include "CameraSystem.hpp"
#include "../Engine.hpp"
#include "../defs.hpp"
#include "../gameObject/Boid.hpp"
#include "../math/math.hpp"

CameraSystem::CameraSystem()
        : _position(0, MinimumHeight, 0),
        _horizontalAngle(M_PI),
        _verticalAngle(0.0),
        _cameraSpeed(DefaultCameraMovementSpeed),
        _cameraSensitivity(DefaultCameraSensitivity),
        _cameraType(FixedDistanceCamera),
        _cameraMovable(false), _cameraOrientable(false),
        _holdingForward(false), _holdingBackward(false),
        _holdingLeftStrafe(false), _holdingRightStrafe(false) {

}

void CameraSystem::init() {
    // Hide the cursor.
    glfwSetInputMode(getEngine().getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraSystem::terminate() {

}

void CameraSystem::orientCameraToTheBoids() {
    //Vector direction = getEngine().getObjectiveBoid().position - _position;
}

void CameraSystem::positionCameraBehindTheBoids() {
    Vector direction = getEngine().getObjectiveBoid().direction;
    direction *= InitialCameraDistance;

    _position.x = getEngine().getObjectiveBoid().position.x - direction.x;
    _position.y = getEngine().getObjectiveBoid().position.y - direction.y;
    _position.z = getEngine().getObjectiveBoid().position.z - direction.z;
}

void CameraSystem::moveCamera(float dt) {
    // Move the camera only if it is movable.
    if(!_cameraMovable)
        return;

    // Move forward.
    if(glfwGetKey(getEngine().getWindow(), CameraForwardKey) == GLFW_PRESS)
        _position += _direction * dt * _cameraSpeed;

    // Move backward.
    if(glfwGetKey(getEngine().getWindow(), CameraBackwardKey) == GLFW_PRESS)
        _position -= _direction * dt * _cameraSpeed;

    // Strafe right.
    if(glfwGetKey(getEngine().getWindow(), CameraRightStrafeKey) == GLFW_PRESS)
        _position += _right * dt * _cameraSpeed;

    // Strafe left.
    if(glfwGetKey(getEngine().getWindow(), CameraLeftStrafeKey) == GLFW_PRESS)
        _position -= _right * dt * _cameraSpeed;
}

void CameraSystem::update(float dt) {
    // Move the camera.
    moveCamera(dt);

    // If the camera has to look to the boids, look.
    if(_cameraType == TowerCamera || _cameraType == ParallelCamera)
        orientCameraToTheBoids();

    // If is to position the camera behind the boids, position.
    if(_cameraType == ParallelCamera || _cameraType == FixedDistanceCamera)
        positionCameraBehindTheBoids();
}

void CameraSystem::lookThroughCamera() {
    gluLookAt(_position.x, _position.y, _position.z,
            _direction.x, _direction.y, _direction.z,
            _up.x, _up.y, _up.z);
}

void CameraSystem::setCameraType(CameraType camera) {
    // For each camera type, set the camera's properties.
    switch(camera) {
        case FreeCamera:
            // Set camera properties.
            _cameraMovable = true;
            _cameraOrientable = true;
            _cameraType = FreeCamera;

           break;

        case TowerCamera:
            // Set camera properties.
            _cameraMovable = false;
            _cameraOrientable = false;
            _cameraType = TowerCamera;

            // Set the position as in the top of the tower.
            _position.x = 0.0;
            _position.y = TowerHeight + TowerCameraDistance;
            _position.z = 0.0;

            // Look at the boids.
            orientCameraToTheBoids();

            break;

        case ParallelCamera:
            // Set camera properties.
            _cameraMovable = false;
            _cameraOrientable = false;
            _cameraType = ParallelCamera;

            // Look at the boids.
            orientCameraToTheBoids();

            break;

        case FixedDistanceCamera:
            // Set camera properties.
            _cameraMovable = false;
            _cameraOrientable = true;
            _cameraType = FixedDistanceCamera;

            // Look at the boids.
            orientCameraToTheBoids();

            break;
    }
}

void CameraSystem::keyEvent(GLFWwindow *window, int key, int scancode,
        int action, int mods) {
    // If is a press, toggle the flag.
    if(action == GLFW_PRESS) {
        switch(key) {
            case CameraForwardKey:
                _holdingForward = true;
                break;

            case CameraBackwardKey:
                _holdingBackward = true;
                break;

            case CameraLeftStrafeKey:
                _holdingLeftStrafe = true;
                break;

            case CameraRightStrafeKey:
                _holdingRightStrafe = true;
                break;

            case CameraIncreaseSensitivityKey:
                _cameraSensitivity += CameraSensitivityChangeRate;
                break;

            case CameraDecreaseSensitivityKey:
                _cameraSensitivity -= CameraSensitivityChangeRate;
                break;

            case FreeCameraToggle:
                setCameraType(FreeCamera);
                break;

            case TowerCameraToggle:
                setCameraType(TowerCamera);
                break;

            case ParallelCameraToggle:
                setCameraType(ParallelCamera);
                break;

            case FixedDistanceCameraToggle:
                setCameraType(FixedDistanceCamera);
                break;
        }
    }
    if(action == GLFW_RELEASE) { // If a key is released, toggle the flag.
        switch(key) {
            case CameraForwardKey:
                _holdingForward = false;
                break;

            case CameraBackwardKey:
                _holdingBackward = false;
                break;

            case CameraLeftStrafeKey:
                _holdingLeftStrafe = false;
                break;

            case CameraRightStrafeKey:
                _holdingRightStrafe = false;
                break;
        }
    }
}

void CameraSystem::cursorPosEvent(GLFWwindow *window, double xpos, double ypos) {
    // Orient the camera only if it is orientable.
    if(!_cameraOrientable)
        return;

    // Get the last cursor position.
    double oldx, oldy;
    getEngine().getLastCursorPos(&oldx, &oldy);

    // Calculate the horizontal and vertical mouse movement.
    _horizontalAngle += (xpos - oldx) * _cameraSensitivity;
    _verticalAngle += (ypos - oldy) * _cameraSensitivity;

    // Limit looking up to vertically up.
    float pid2 = M_PI / 2.0;
    if(_verticalAngle > pid2)
        _verticalAngle = pid2;

    // Limit looking down to vertically down.
    if(_verticalAngle < -pid2)
        _verticalAngle = -pid2;

    // Looking left and right - keep angles in the range 0.0 to 360.o.
    // 0 degrees is looking directly down the negative Z axis "North", 90
    // degrees is "East", 180 degrees is "South", 270 degrees is "West".
    float pim2 = 2.0 * M_PI;
    if(_horizontalAngle < 0.0)
        _horizontalAngle += pim2;
    if(_horizontalAngle > pim2)
        _horizontalAngle -= pim2;

    // Calculate the direction.
    float cosVerticalAngle = cos(_verticalAngle);
    _direction.x = cosVerticalAngle * sin(_horizontalAngle);
    _direction.y = sin(_verticalAngle);
    _direction.z = cosVerticalAngle * cos(_horizontalAngle);

    // Calculate the right.
    _right.x = sin(_horizontalAngle - pid2);
    _right.y = 0.0;
    _right.z = cos(_horizontalAngle - pid2);

    // Calculates the up.
    _up = Vector::cross(_right, _direction);
}

