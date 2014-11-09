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

CameraSystem::CameraSystem()
        : _position(0, MinimumHeight, 0),
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

    // Vector to break up our movement along the X, Y and Z axis.
    Vector movement;

    // Get the sine and cosine of our X and Y axis rotation.
    double sinXRot = sin(toRads(_orientation.alpha));
    double cosXRot = cos(toRads(_orientation.alpha));
    double sinYRot = sin(toRads(_orientation.beta));
    double cosYRot = cos(toRads(_orientation.beta));

    // Cancels moving on the Z axis when we're looking up or down.
    double pitchLimitFactor = cosXRot;

    if(_holdingForward) {
        movement.x += sinYRot * pitchLimitFactor;
        movement.y -= sinXRot;
        movement.z -= cosYRot * pitchLimitFactor;
    }
    if(_holdingBackward) {
        movement.x -= sinYRot * pitchLimitFactor;
        movement.y += sinXRot;
        movement.z += cosYRot * pitchLimitFactor;
    }
    if(_holdingLeftStrafe) {
        movement.x -= cosYRot;
        movement.z -= sinYRot;
    }
    if(_holdingRightStrafe) {
        movement.x += cosYRot;
        movement.z += sinYRot;
    }

    // Normalise the movement vector.
    movement.normalize();

    // Calculate the value to keep the movement the same speed regardless of
    // framerate.
    // Apply it to the movement vector.
    movement *= CameraMovementSpeedFactor * dt;

    // Apply the movement to our position.
    _position += movement;

    // If we are at the minimum height, put us at the minimum height.
    // The position is inverted.
    if(_position.y < MinimumHeight)
        _position.y = MinimumHeight;

    // If we are at the maximum height, put us at the maximum height.
    // The position is inverted.
    if(_position.y > MaximumHeight)
        _position.y = MaximumHeight;
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
    // Rotate the camera to the location in space.
    glRotatef(_orientation.alpha, 1.0, 0.0, 0.0); // up and down
    glRotatef(_orientation.beta, 0.0, 1.0, 0.0); // left and right

    // Translate to the position of our camera.
    glTranslatef(-_position.x, -_position.y, -_position.z);
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
    double horizMovement = (xpos - oldx) * _cameraSensitivity;
    double vertMovement = (ypos - oldy) * _cameraSensitivity;

    // Apply the movement to our rotation vector. The vertical (look up and
    // down) movement is applied to the X axis and the horizontal (look left
    // and right) movement is applied to the Y axis.
    _orientation.alpha += vertMovement;
    _orientation.beta += horizMovement;

    // Limit looking to vertically up.
    if(_orientation.alpha > 90.0)
        _orientation.alpha = 90.0;

    // Limit looking down to vertically down.
    if(_orientation.alpha < -90.0)
        _orientation.alpha = -90.0;

    // Looking left and right - keep angles in the range 0.0 to 360.o.
    // 0 degrees is looking directly down the negative Z axis "North", 90
    // degrees is "East", 180 degrees is "South", 270 degrees is "West".
    if(_orientation.beta < 0.0)
        _orientation.beta += 360.0;
    if(_orientation.beta > 360.0)
        _orientation.beta -= 360.0;
}

