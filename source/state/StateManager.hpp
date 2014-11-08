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

#ifndef STATE_STATEMANAGER_HPP
#define STATE_STATEMANAGER_HPP

#include "StateContainer.hpp"
#include "State.hpp"

/**
 * Manages the states of execution.
 * This class is a singleton that can only be accessed directly by the Engine
 * class. If you want to access the only instance of this class, use
 * getEngine().getStateManager()
 *
 * @see Engine::getStateManager()
 **/
class StateManager {
    /**
     * State container.
     **/
    StateContainer _states;

    /**
     * The ID of the current state.
     * You must guarantee there is always a current state, or getCurrentState()
     * will blow up as it is a reference.
     **/
    StateId _currentStateId;

    /// The ID of the new state.
    StateId _nextStateId;

    // The Engine class is a friend function to allow it to call the getInstance()
    // static method.
    friend class Engine;

    /// Private constructor to make this class a singleton.
    StateManager() : _currentStateId(IdleStateId), _nextStateId(IdleStateId) {
        // Inits the current idle state.
        getCurrentState().init();
    }

    // Disallow copy constructor and copy assignment operators for the
    // singleton.
    StateManager(const StateManager &);             // Don't implement.
    StateManager &operator=(const StateManager &);  // Don't implement.

    /**
     * Returns the only instance of the StateManager class.
     * Only the Engine class can access this function, making the state manager
     * effectively a member of the Engine singleton.
     **/
    static StateManager &getInstance() {
        static StateManager instance; // Guaranteed to be destroyed.
                                      // Instantiated on first use.
        return instance;
    }

public:

    ~StateManager() {
        // Clean up the current state to allow its proper destruction.
        getCurrentState().cleanUp();
    }

    /**
     * Processes the current game states.
     * This must be called once every iteration of the main loop.
     **/
    inline void processStates() {
        // If the next state is different than the current state, change to it.
        if(_nextStateId != _currentStateId) {
            getCurrentState().cleanUp();
            _currentStateId = _nextStateId;
            getCurrentState().init();
        }
    }

    /**
     * Returns the current state.
     **/
    inline State &getCurrentState() {
        return *_states.getState(_currentStateId);
    }

    /**
     * Asks to change state.
     * The current state will only change to the new state when processStates()
     * is called.
     **/
    inline void changeState(StateId newState) {
        _nextStateId = newState;
    }
};

#endif // !STATE_STATEMANAGER_HPP
