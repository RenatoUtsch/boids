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
        _horizontalAngle(0.0),
        _verticalAngle(0.0),
        _cameraSpeed(DefaultCameraMovementSpeed),
        _cameraSensitivity(DefaultCameraSensitivity),
        _cameraType(BehindCamera),
        _cameraMovable(false), _cameraOrientable(false) {

}

void CameraSystem::init() {
    // Hide the cursor.
    glfwSetInputMode(getEngine().getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraSystem::terminate() {

}

void CameraSystem::orientCameraToTheBoids() {
    Vector direction;

    // If is the behind camera, position it with relation to the objective
    // boid.
    //Else, direct the camera to the middle of the boids.
    if(_cameraType == BehindCamera || _cameraType == ParallelCamera)
        direction = getEngine().getObjectiveBoid().position - _position;
    else
        direction = getEngine().getAbsoluteMiddlePosition() - _position;

    _direction = direction;
    _direction.normalize();
    _up = getEngine().getObjectiveBoid().up;
    _right = Vector::cross(_direction, _up);
    _right.normalize();
}

void CameraSystem::positionCameraBehindTheBoids() {
    Vector direction = getEngine().getObjectiveBoid().direction;
    direction *= InitialCameraDistance
        + CameraDistanceFactor * (getEngine().getBoids().size() + 1);

    _position.x = getEngine().getObjectiveBoid().position.x - direction.x;
    _position.y = getEngine().getObjectiveBoid().position.y - direction.y;
    _position.z = getEngine().getObjectiveBoid().position.z - direction.z;
}

void CameraSystem::positionCameraLeftTheBoids() {
    // Get the direction when looking to the right.
    Vector right = getEngine().getObjectiveBoid().right;

    right *= InitialCameraDistance
        + CameraDistanceFactor * (getEngine().getBoids().size() + 1);

    _position.x = getEngine().getObjectiveBoid().position.x - right.x;
    _position.y = getEngine().getObjectiveBoid().position.y - right.y;
    _position.z = getEngine().getObjectiveBoid().position.z - right.z;
}

void CameraSystem::calculateDirectionVectors() {
    double sinVert = sin(toRads(_verticalAngle));
    double cosVert = cos(toRads(_verticalAngle));
    double sinHoriz = sin(toRads(_horizontalAngle));
    double cosHoriz = cos(toRads(_horizontalAngle));

    // Calculate the direction.
    _direction.x = sinHoriz * cosVert;
    _direction.y = -sinVert;
    _direction.z = -cosHoriz * cosVert;
    _direction.normalize();

    // Calculate the right vector.
    _right.x = cosHoriz;
    _right.y = 0.0;
    _right.z = sinHoriz;
    _right.normalize();

    // Calculate the up.
    _up = Vector::cross(_right, _direction);
    _up.normalize();
}

void CameraSystem::moveCamera(float dt) {
    // Move the camera only if it is movable.
    if(!_cameraMovable)
        return;

    // Move forward.
    if(glfwGetKey(getEngine().getWindow(), CameraForwardKey) == GLFW_PRESS)
        _position += _direction * _cameraSpeed * dt;

    // Move backward.
    if(glfwGetKey(getEngine().getWindow(), CameraBackwardKey) == GLFW_PRESS)
        _position -= _direction * _cameraSpeed * dt;

    // Strafe right.
    if(glfwGetKey(getEngine().getWindow(), CameraRightStrafeKey) == GLFW_PRESS)
        _position += _right * _cameraSpeed * dt;

    // Strafe left.
    if(glfwGetKey(getEngine().getWindow(), CameraLeftStrafeKey) == GLFW_PRESS)
        _position -= _right * _cameraSpeed * dt;

    // Minimum and maximum heights.
    if(_position.y < MinimumHeight)
        _position.y = MinimumHeight;
    if(_position.y > MaximumHeight)
        _position.y = MaximumHeight;
}

void CameraSystem::update(float dt) {
    static bool firstUpdate = true;

    // If is the first update, position the camera looking to the boid.
    if(firstUpdate) {
        setCameraType(BehindCamera);
        firstUpdate = false;
    }

    // Move the camera.
    moveCamera(dt);

    // If is to position the camera behind the boids, position.
    if(_cameraType == BehindCamera)
        positionCameraBehindTheBoids();
    else if(_cameraType == ParallelCamera)
        positionCameraLeftTheBoids();

    // If the camera has to look to the boids, look.
    if(_cameraType == TowerCamera || _cameraType == ParallelCamera
            || _cameraType == BehindCamera)
        orientCameraToTheBoids();
}

void CameraSystem::lookThroughCamera() {
    if(_cameraType == TowerCamera || _cameraType == ParallelCamera) {
        gluLookAt(_position.x, _position.y, _position.z,
                _position.x + _direction.x, _position.y + _direction.y,
                _position.z + _direction.z,
                0.0, 1.0, 0.0);
    }
    else {
        gluLookAt(_position.x, _position.y, _position.z,
                _position.x + _direction.x, _position.y + _direction.y,
                _position.z + _direction.z,
                _up.x, _up.y, _up.z);
    }
}

void CameraSystem::setCameraType(CameraType camera) {
    double vertRads;

    // For each camera type, set the camera's properties.
    switch(camera) {
        case FreeCamera:
            // Set camera properties.
            _cameraMovable = true;
            _cameraOrientable = true;
            _cameraType = FreeCamera;

            // Fix the camera angles.
            _direction.normalize();
            vertRads = asin(-_direction.y);
            _verticalAngle = toDegrees(vertRads);
            _horizontalAngle = toDegrees(acos(-_direction.z / cos(vertRads)));

            // Calculate the direction vectors.
            calculateDirectionVectors();

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

            // Position the camera at the left of the boids.
            positionCameraLeftTheBoids();

            // Look at the boids.
            orientCameraToTheBoids();

            break;

        case BehindCamera:
            // Set camera properties.
            _cameraMovable = false;
            _cameraOrientable = false;
            _cameraType = BehindCamera;

            // Position the camera behind the boids.
            positionCameraBehindTheBoids();

            // Look at the boids.
            orientCameraToTheBoids();

            break;
    }
}

void CameraSystem::keyEvent(GLFWwindow *window, int key, int scancode, int action,
        int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case FreeCameraToggle:
                setCameraType(FreeCamera);
                break;

            case TowerCameraToggle:
                setCameraType(TowerCamera);
                break;

            case ParallelCameraToggle:
                setCameraType(ParallelCamera);
                break;

            case BehindCameraToggle:
                setCameraType(BehindCamera);
                break;

            case CameraIncreaseSensitivityKey:
                _cameraSensitivity += CameraSensitivityChangeRate;
                break;

            case CameraDecreaseSensitivityKey:
                _cameraSensitivity -= CameraSensitivityChangeRate;
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
    if(_verticalAngle > 90.0)
        _verticalAngle = 90.0;

    // Limit looking down to vertically down.
    if(_verticalAngle < -90.0)
        _verticalAngle = -90.0;

    // Looking left and right - keep angles in the range 0.0 to 360.0.
    // 0 degrees is looking directly down the negative Z axis "North", 90
    // degrees is "East", 180 degrees is "South", 270 degrees is "West".
    if(_horizontalAngle < 0.0)
        _horizontalAngle += 360.0;
    if(_horizontalAngle > 360.0)
        _horizontalAngle -= 360.0;

    // Calculate the direction vectors.
    calculateDirectionVectors();
}

