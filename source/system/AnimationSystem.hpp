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

#ifndef SYSTEM_ANIMATION_SYSTEM_HPP
#define SYSTEM_ANIMATION_SYSTEM_HPP

#include "System.hpp"
#include "../gameObject/Boid.hpp"
#include "../defs.hpp"
#include "../util/NonCopyable.hpp"
#include <cstdlib>

/**
 * This is the animation system, that manages the display lists that render the
 * objects in the game.
 **/
class AnimationSystem : public System, public NonCopyable {
    /**
     * First display list of the boid.
     * All the display lists of the boid are between this one and
     * _beginBoidDisplayList.
     **/
    unsigned _beginBoidDisplayList;

    /**
     * First display list after the last display list of the boid.
     * All the display lists of the boid are between _beginBoidDisplayList andh
     * this one.
     **/
    unsigned _endBoidDisplayList;

    /// Display list of the tower.
    unsigned _towerDisplayList;

    /**
     * Creates the display lists for the boids.
     **/
    void createBoidDisplayList();

    /**
     * Destroys the display lists for the boids.
     **/
    void destroyBoidDisplayList();

    /**
     * Creates the display list for the center tower.
     **/
    void createTowerDisplayList();

    /**
     * Destroys the display list for the center tower.
     **/
    void destroyTowerDisplayList();

    /**
     * Updates a single boid.
     **/
    void updateBoid(Boid &boid);

    /**
     * Updates all the boids, including the objective boid.
     **/
    void updateBoids();

public:
    void init();
    void terminate();
    void update(float dt);

    // Returns the begin boid display list.
    inline unsigned getBeginBoidDisplayList() {
        return _beginBoidDisplayList;
    }

    // Returns the tower display list.
    inline unsigned getTowerDisplayList() {
        return _towerDisplayList;
    }

    // Get random boid display list.
    inline int getRandomBoidDisplayList() {
        return _beginBoidDisplayList + std::rand() % NumBoidDisplayLists;
    }

    // Get random boid going up or down.
    inline bool getRandomBoidGoingUp() {
        return std::rand() % 2;
    }
};

#endif // !SYSTEM_ANIMATION_SYSTEM_HPP
