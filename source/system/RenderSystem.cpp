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

#include "RenderSystem.hpp"
#include "../Engine.hpp"
#include "../defs.hpp"
#include "../util/draw.hpp"
#include "../math/Plane.hpp"

void RenderSystem::createGround() {
    // Get the next display list.
    _groundDisplayList = getNextDisplayList();
    incrementNextDisplayList();

    glNewList(_groundDisplayList, GL_COMPILE);
        // Save the two colors.
        float colors[2][3] = { {GroundOddSquareColorRed,
                                GroundOddSquareColorGreen,
                                GroundOddSquareColorBlue},
                               {GroundEvenSquareColorRed,
                                GroundEvenSquareColorGreen,
                                GroundEvenSquareColorBlue} };

        // Current color.
        int curr = 0;

        // Draw the ground.
        glNormal3f(0.0, 1.0, 0.0);
        for(int i = -GroundSize; i < GroundSize; i += GroundSquareSize) {
            // Draw a square.
            glBegin(GL_QUADS);
                for(int j = -GroundSize; j < GroundSize; j += GroundSquareSize) {
                    glColor3f(colors[curr][0], colors[curr][1], colors[curr][2]);
                    glVertex3f(j, GroundLevel, i);
                    glVertex3f(j + GroundSquareSize, GroundLevel, i);
                    glVertex3f(j + GroundSquareSize, GroundLevel,
                            i + GroundSquareSize);
                    glVertex3f(j, GroundLevel, i + GroundSquareSize);

                    // Update the current color.
                    curr = (curr + 1) % 2;
                }
            glEnd();

            // Update the current color.
            curr = (curr + 1) % 2;
        }
    glEndList();
}

void RenderSystem::createSun() {
    // Get the next display list.
    _sunDisplayList = getNextDisplayList();
    incrementNextDisplayList();

    glNewList(_sunDisplayList, GL_COMPILE);
        glPushMatrix();
            // Color of the sun.
            glColor3f(SunColorRed, SunColorGreen, SunColorBlue);

            // Translate it to 1.5 times the maximum height.
            glTranslatef(0.0, SunHeightFactor * MaximumHeight, 0.0);

            // Rotate the sun to the top.
            glRotatef(90, 1.0, 0.0, 0.0);

            // Draw a sun.
            util::drawCircle(100.0);
        glPopMatrix();
    glEndList();
}

void RenderSystem::destroyGround() {
    glDeleteLists(_groundDisplayList, 1);
}

void RenderSystem::destroySun() {
    glDeleteLists(_sunDisplayList, 1);
}

void RenderSystem::drawShadow() {
    glDisable(GL_LIGHT0);

    // Shadow's color.
    glColor3f(ShadowColorRed, ShadowColorGreen, ShadowColorBlue);
    glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(1.0, 0.0, 1.0); // Collapse the y-value.

        // Draw the boids again.
        drawObjectiveBoid();
        drawFollowBoids();
    glPopMatrix();

    glEnable(GL_LIGHT0);
}

void RenderSystem::drawObjectiveBoid() {
    // Objective boid color.
    glColor3f(ObjectiveBoidColorRed, ObjectiveBoidColorGreen,
            ObjectiveBoidColorBlue);

    // Translate the objective boid and the other boids.
    glext::glTranslatep(getEngine().getObjectiveBoid().position);

    // Get the objective boid rotation.
    Matrix4d rotation = Vector::toRotationMatrix(
            getEngine().getObjectiveBoid().direction,
            getEngine().getObjectiveBoid().up);

    glPushMatrix();
        // Rotate the objective boid.
        glext::glMultMatrixm(rotation);

        glCallList(getEngine().getObjectiveBoid().displayList);
    glPopMatrix();
}

void RenderSystem::drawFollowBoids() {
    // Get the objective boid rotation.
    Matrix4d rotation = Vector::toRotationMatrix(
            getEngine().getObjectiveBoid().direction,
            getEngine().getObjectiveBoid().up);

    glColor3f(BoidColorRed, BoidColorGreen, BoidColorBlue);
    for(Engine::BoidVector::iterator it = getEngine().getBoids().begin();
            it != getEngine().getBoids().end(); ++it) {
        glPushMatrix();
            // Rotate and translate.
#if BOIDS_ROTATE_AFTER
                glext::glMultMatrixm(rotation);
                glext::glTranslatep(it->position);
#else
                glext::glTranslatep(it->position);
                glext::glMultMatrixm(rotation);
#endif

            glCallList(it->displayList);
        glPopMatrix();
    }

}

void RenderSystem::setUpFog() {
    if(_fogEnabled) {
        std::cout << "fog!" << std::endl;
        glClearColor(FogColorRed, FogColorGreen, FogColorBlue, 1.0);
        glEnable(GL_FOG);
    }
    else {
        glClearColor(BackgroundColorRed, BackgroundColorGreen,
                BackgroundColorBlue, 1.0);
        glDisable(GL_FOG);
    }
}

RenderSystem::RenderSystem() : _toggleFog(false), _fogEnabled(false) {

}

void RenderSystem::init() {
    // Blue background.
    glClearColor(BackgroundColorRed, BackgroundColorGreen, BackgroundColorBlue,
            1.0);

    // Get the framebuffer size.
    int width, height;
    glfwGetFramebufferSize(getEngine().getWindow(), &width, &height);

    // Set up the OpenGL projection by (supposedly) emitting a GLFW event.
    framebufferSizeEvent(getEngine().getWindow(), width, height);

    // Enable lightning things.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    // Enable 3D things.
    glEnable(GL_DEPTH_TEST);

    // Configuring the light.
    float ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    float specularLight[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    // Configuring the fog.
    float fogColor[] = {FogColorRed, FogColorGreen, FogColorBlue, 1.0};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, FogDensity);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_START, FogStart);
    glFogf(GL_FOG_END, FogEnd);
    setUpFog();

    // Colors.
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Init the display lists.
    _nextDisplayList = glGenLists(MaxDisplayLists);

    // Create the environment.
    createGround();
    createSun();
}

void RenderSystem::terminate() {
    // Destroy the environment.
    destroyGround();
    destroySun();
}

void RenderSystem::update(float dt) {
    // Fog things.
    if(_toggleFog) {
        _toggleFog = false;
        if(_fogEnabled)
            _fogEnabled = false;
        else
            _fogEnabled = true;

        setUpFog();
    }

    // Clear.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();

    // Position the camera.
    getEngine().getCameraSystem().lookThroughCamera();

    // Draw the light.
    glDisable(GL_LIGHTING);
    float sunPosition[] = {0.0, SunHeightFactor * MaximumHeight - LightHeight,
        0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    glEnable(GL_LIGHTING);

    // Draw the ground.
    glCallList(_groundDisplayList);

    // Draw the shadows.
    drawShadow();

    // Draw the sun.
    glCallList(_sunDisplayList);

    // Draw the center tower.
    glCallList(getEngine().getTower().displayList);

    // Draw the objective boid. MUST be drawn before the other boids.
    drawObjectiveBoid();

    // Draw the other boids.
    drawFollowBoids();

    // Draw the boids. Their position is relative to the objective boid
    // Swap the buffers.
    glPopMatrix();
    glfwSwapBuffers(getEngine().getWindow());
}

void RenderSystem::framebufferSizeEvent(GLFWwindow *window, int width,
        int height) {
    // Set up the OpenGL projection.
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FrustumFieldOfView, (GLfloat) width / height, FrustumNear,
            FrustumFar);
    glMatrixMode(GL_MODELVIEW);
}

