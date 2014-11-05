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

#ifndef OBJECTS_HPP
#define OBJECTS_HPP

/*
 * This class manages the creation of game objects.
 */

class GameObject;

/**
 * This function dynamically creates a boid and returns it.
 * You MUST deallocate it after using.
 **/
GameObject *createBoid();

/**
 * This function dynamically creates a sphere obstacle centered at (0, 0, 0) and
 * returns it.
 * You MUST deallocate it after using.
 * @param radius The radius of the sphere.
 **/
GameObject *createSphereObstacle(float radius);

/**
 * This function dynamically creates a cone obstacle with its base centered at
 * (0, 0, 0) and returns it.
 * You MUST deallocate it after using.
 * @param radius The radius of the base of the cone.
 * @param height The height of the cone.
 **/
GameObject *createConeObstacle(float radius, float height);

#endif // !OBJECTS_HPP
