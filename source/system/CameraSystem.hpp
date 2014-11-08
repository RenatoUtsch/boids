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

#ifndef SYSTEM_CAMERASYSTEM_HPP
#define SYSTEM_CAMERASYSTEM_HPP

#include "System.hpp"
#include "../math/Point.hpp"
#include "../math/EulerAngles.hpp"

class CameraSystem : public System {
public:
    /**
     * Types of cameras.
     **/
    enum CameraType {
        /// Free camera. Move it with ijkl.
        FreeCamera,

        /// Camera fixed at the tower.
        TowerCamera,

        /// Camera parallel to the ground and at a fixed distance of the boids.
        ParallelCamera,

        /// Camera at a fixed distance of the boids.
        FixedDistanceCamera
    };

private:
    /// Position of the camera in space.
    Point _position;

    /// Direction vector of the camera in space.
    EulerAngles _orientation;

    /// Camera sensitivity.
    float _cameraSensitivity;

    /// Current camera type.
    CameraType _cameraType;

    /// If the current camera is movable.
    bool _cameraMovable;

    /// If the current camera is orientable.
    bool _cameraOrientable;

    /// If the forward key is being pressed.
    bool _holdingForward;

    /// If the backward key is being pressed.
    bool _holdingBackward;

    /// If the left strafe key is being pressed.
    bool _holdingLeftStrafe;

    /// If the right strafe key is being pressed.
    bool _holdingRightStrafe;

public:
    CameraSystem();
    void init();
    void terminate();
    void update(float dt);

    /**
     * Like gluLookAt(), but with our camera.
     **/
    void lookThroughCamera();

    /// Sets the camera type to use.
    void setCameraType(CameraType camera);

    /**
     * Processes key events related to the camera.
     **/
    void keyEvent(GLFWwindow *window, int key, int scancode, int action,
            int mods);

    /**
     * Processes camera rotation.
     **/
    void cursorPosEvent(GLFWwindow *window, double xpos, double ypos);

    /// Returns the current camera type.
    inline CameraType getCameraType() {
        return _cameraType;
    }

    /// Returns the current position of the camera.
    inline Point &getCameraPosition() {
        return _position;
    }

    /// Returns the current orientation of the camera.
    inline EulerAngles &getCameraOrientation() {
        return _orientation;
    }
};

#endif // !SYSTEM_CAMERASYSTEM_HPP
