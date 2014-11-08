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

#include "AnimationSystem.hpp"
#include "../defs.hpp"
#include "../glfw.hpp"
#include "../util/draw.hpp"
#include "../Engine.hpp"
#include <iostream>

void AnimationSystem::createBoidDisplayList() {
    // Start at the next display list.
    _beginBoidDisplayList = getEngine().getRenderSystem().getNextDisplayList();

    _endBoidDisplayList = _beginBoidDisplayList + NumBoidDisplayLists;

    // Update the next display list.
    getEngine().getRenderSystem().setNextDisplayList(_endBoidDisplayList);

    // How much the wings will be higher by each frame.
    float wingUpRate = WingAngle / NumBoidDisplayLists;

    // These display lists are created at (0, 0, 0). You must position them
    // accordingly. The boid will be looking in the  direction.
    for(unsigned i = _beginBoidDisplayList; i != _endBoidDisplayList; ++i) {
        glNewList(i, GL_COMPILE);
            // Color of the boid.
            glColor3f(BoidColorRed, BoidColorGreen, BoidColorBlue);

            // Draw the body.
            glPushMatrix();
                // Scale the circle to make an ellipsis.
                glScalef(1.0, 1.0, BoidBodyScale);

                GLUquadricObj *quadObj = gluNewQuadric();
                gluSphere(quadObj, BoidBodyRadius, CurvedShapeFidelity,
                        CurvedShapeFidelity);
            glPopMatrix();

            // Draw the left wing.
            glPushMatrix();
                // Rotate and translate to the left.
                glTranslatef(-BoidBodyRadius + BoidWingDistanceFix, 0.0, 0.0);
                glRotatef(90.0, 0.0, 1.0, 0.0);

                // Rotate using the display list index as parameter.
                glRotatef(wingUpRate * i, 1.0, 0.0, 0.0);

                // Put the wing at the most down angle.
                glRotatef(-WingAngle / 2.0, 1.0, 0.0, 0.0);

                util::drawPyramid(BoidWingHeight, BoidWingBaseDiagonalSize,
                        BoidWingBaseAngle);
            glPopMatrix();

            // Draw the right wing.
            glPushMatrix();
                // Rotate and translate to the right.
                glTranslatef(BoidBodyRadius - BoidWingDistanceFix, 0.0, 0.0);
                glRotatef(-90.0, 0.0, 1.0, 0.0);

                // Rotate using the display list index as parameter.
                glRotatef(wingUpRate * i, 1.0, 0.0, 0.0);

                // Put the wing at the most down angle.
                glRotatef(-WingAngle / 2.0, 1.0, 0.0, 0.0);

                util::drawPyramid(BoidWingHeight, BoidWingBaseDiagonalSize,
                        BoidWingBaseAngle);
            glPopMatrix();
        glEndList();
    }
}

void AnimationSystem::destroyBoidDisplayList() {
    // Destroy all display lists.
    glDeleteLists(_beginBoidDisplayList,
            (_endBoidDisplayList - _beginBoidDisplayList));
}

void AnimationSystem::destroyTowerDisplayList() {
    glDeleteLists(_towerDisplayList, 1);
}

void AnimationSystem::createTowerDisplayList() {
    // Draw at the next display list and increment it.
    _towerDisplayList = getEngine().getRenderSystem().getNextDisplayList();
    getEngine().getRenderSystem().incrementNextDisplayList();

    // Draw a tower with its base centered at (0, 0, 0).
    glNewList(_towerDisplayList, GL_COMPILE);
        glPushMatrix();
            // Set up the color of the tower.
            glColor3f(TowerColorRed, TowerColorGreen, TowerColorBlue);

            // Rotate the tower to point to the top.
            glRotatef(-90, 1.0, 0.0, 0.0);

            // Draw the tower.
            GLUquadricObj *quadObj = gluNewQuadric();
            gluCylinder(quadObj, TowerBaseRadius, 0.0, TowerHeight,
                    CurvedShapeFidelity, CurvedShapeFidelity);
        glPopMatrix();
    glEndList();
}

void AnimationSystem::init() {
    // Create the display lists for the boids.
    createBoidDisplayList();

    // Create the display lists for the cone.
    createTowerDisplayList();
}

void AnimationSystem::terminate() {
    // Clean up the display lists.

    // Destroy the display lists for the boids.
    destroyBoidDisplayList();

    // Destroy the display lists for the tower.
    destroyTowerDisplayList();
}

void AnimationSystem::updateBoids() {
    // Update each boid.
    for(Engine::BoidVector::iterator it = getEngine().getBoids().begin();
            it != getEngine().getBoids().end(); ++it) {
        // Update the boids by adding 1 to the display list until it is at the end,
        // when we'll start to go down instead.
        if(it->displayListGoingUp) {
            if(it->displayList == _endBoidDisplayList - 1) {
                // Start going down.
                it->displayListGoingUp = false;
                --it->displayList;
            }
            else {
                ++it->displayList;
            }
        }
        else {
            if(it->displayList == _beginBoidDisplayList) {
                // Start going up.
                it->displayListGoingUp = true;
                ++it->displayList;
            }
            else {
                --it->displayList;
            }
        }
    }
}

void AnimationSystem::update(float dt) {
    // Update the boids.
    updateBoids();
}
