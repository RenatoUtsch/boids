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

#ifndef STATE_STATE_HPP
#define STATE_STATE_HPP

struct GLFWwindow;

class Engine;

/**
 * Each state has an ID that is represented here.
 **/
enum StateId {
    /**
     * Idle state that does nothing, except listening to GLFW's close event.
     **/
    IdleStateId = 0,

    /**
     * Running state. Normal state of the engine.
     **/
    RunStateId,

    /**
     * Paused state. Does nothing until the state is restored to another state.
     **/
    PauseStateId,

    /**
     * Debug state. Goes step by step.
     **/
    DebugStateId
};

/**
 * Each implementation of the State class stores the functions related to
 * a state of execution. This class must be derived and each derived class will
 * implement a state.
 **/
class State {

public:
    /// Virtual destructor.
    virtual ~State() { }

    /**
     * Returns the ID of the current state.
     **/
    virtual StateId getId() = 0;

    /**
     * The load function will be responsible for loading the state's necessary
     * data. It will be called only once, when starting the state, but never
     * again, not even when the state restarts.
     * It is the first function to be called when a state starts.
     **/
    virtual void load() = 0;

    /**
     * The init function prepares the state's data. It is called when the state
     * is started and every time it is restarted.
     * This function should not load any data, only prepare it. This allows a
     * fast restart of state if a restart is required - with no loading or
     * unloading of data involved.
     **/
    virtual void init() = 0;

    /**
     * The input function processes input.
     * This function should call glfwPollEvents() to handle events received by
     * the operating system.
     * This function must be non-blocking, so it must NEVER call
     * glfwWaitEvents().
     **/
    virtual void input() = 0;

    /**
     * The update function advances the game by dt time.
     * All gameplay logic should happen in this state.
     * @param dt The difference in time to simulate the game.
     **/
    virtual void update(float dt) = 0;

    /**
     * The render function renders the current game state to the screen.
     * @param dt The time we are after the last physics update to display the
     * physics-affected objects at the right position.
     **/
    virtual void render(float dt) = 0;

    /**
     * The cleanUp function frees any objects no longer required and sets the
     * state up for changing state or restarting. It is called when the current
     * state is being put on hold or when the game is exiting, before the
     * unload function.
     * No data should be unloaded, the idea is to just set everything up to be
     * initialized cleanly again.
     **/
    virtual void cleanUp() = 0;

    /**
     * The unload function is called during state termination, i.e., when the
     * game is exiting, and unloads all data loaded in the load state.
     **/
    virtual void unload() = 0;

    /**
     * Callback for key events from glfw.
     **/
    virtual void keyEvent(GLFWwindow *window, int key, int scancode, int action,
            int mods) = 0;

    /**
     * Callback for mouse cursor position events from glfw.
     **/
    virtual void cursorPosEvent(GLFWwindow *window, double xpos,
            double ypos) = 0;

    /**
     * Callback for mouse button events from glfw.
     **/
    virtual void mouseButtonEvent(GLFWwindow *window, int button, int action,
            int mods) = 0;
};

#endif // !STATE_STATE_HPP
