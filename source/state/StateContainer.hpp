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

#ifndef STATE_STATECONTAINER_HPP
#define STATE_STATECONTAINER_HPP

#include "State.hpp"
#include "StateFactory.hpp"
#include <map>

/**
 * Container that wraps around STL storage to allow lazy construction of states
 * and handling loading/unloading properly.
 **/
class StateContainer {
    typedef std::map<StateId, State *> StateMap;
    typedef std::pair<StateId, State *> StateMapPair;

    /**
     * Map that stores states.
     * You must make sure that the map doesn't create default elements through
     * operator[]. This is the problem that this class has to fix.
     **/
    StateMap _states;

    /**
     * Creates a new state. Make sure the state doesn't exist when calling this
     * function!
     * This function also inserts the state into the _states map.
     * @param id The id of the new state.
     **/
    State *createState(StateId id) {
        State *state = stateFactory(id);
        state->load();
        _states.insert(StateMapPair(id, state));
        return state;
    }

    /**
     * Destroys the given state.
     * Assumes that the state being destroyed is already cleaned up..
     * Doesn't remove the state from the _states map.
     **/
    void destroyState(State *state) {
        state->unload();
        delete state;
    }

    // I am lazy and I don't want to implement this right now. Also, there
    // should only be one of this container anyways, so I won't bother.
    StateContainer(StateContainer &other);                  // Don't implement.
    StateContainer &operator=(const StateContainer &other); // Don't implement.
public:
    /// Constructor.
    StateContainer() {

    }

    /// Destructor.
    ~StateContainer() {
        // Destroy the allocated states.
        for(StateMap::iterator it = _states.begin(); it != _states.end(); ++it) {
            destroyState(it->second);
            it->second = 0;
        }

        // Clear the map.
        _states.clear();
    }

    /**
     * Returns the state with the given ID.
     * If the state doesn't exist, creates a new one and loads it. It will be
     * unloaded when this class is destroyed.
     **/
    inline State *getState(StateId id) {
        // Try to find the state. If it isn't found, create a new state with
        // it.
        StateMap::iterator it = _states.find(id);

        if(it == _states.end()) {
            // Create a new state.
            return createState(id);
        }
        else {
            // Return the existing state.
            return it->second;
        }
    }
};

#endif // !STATE_STATECONTAINER_HPP
