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

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "util/noncopyable.hpp"
#include "state/State.hpp"
#include "glfw.hpp"

/**
 * This class represents the main engine of the game.
 * This class is a singleton. You can access its instance by
 * Engine::getInstance() or by the convenience function getEngine().
 * @see Engine::getInstance()
 * @see getEngine()
 **/
class Engine {
    /// The window of the engine.
    GLFWwindow *_window;

    /// The current state of the engine.
    State *_currentState;

    /// Inits the window system.
    void initWindowSystem();

    /// Terminates the window system.
    void terminateWindowSystem();

    /**
     * Main loop of the engine. Responsible for the frame-by-frame updates.
     **/
    void mainLoop();

    /// Private constructor to make this class a singleton.
    Engine();

    // Disallow copy constructor and copy assignment operators for the
    // singleton.
    Engine(const Engine &);             // Don't implement.
    Engine &operator=(const Engine &);  // Don't implement.

public:
    /**
     * Returns the only instance of the Engine class.
     * The convenience function getEngine() is provided to replace the verbose
     * and ugly syntax Engine::getInstance() with the same result.
     * @see getEngine()
     **/
    static Engine &getInstance() {
        static Engine instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.

        return instance;
    }

    /// Destructor.
    ~Engine();

    /**
     * Takes control of execution and runs the game until an interrupt signal
     * is given or the player asks to quit.
     * This function takes care of initing the engine and terminating it.
     * @return 0 on success or nonzero on error. This allows the run
     * function to be used in main()'s return statement.'
     **/
    int run();

    /**
     * Error event to be generated by anyone, but mainly by glfw.
     * @param error The ID of the error.
     * @param description The char description of the error.
     **/
    void errorEvent(int error, const char *description);

    /**
     * Window resize event. Called after the window was resized.
     * @param window The window that was resized.
     * @param width The new width of the window.
     * @param height The new height of the window.
     **/
    void windowSizeEvent(GLFWwindow *window, int width, int height);

    /**
     * Returns the current state of this engine.
     **/
    inline State &getCurrentState() {
        return *_currentState;
    }

    /**
     * Returns the window of the engine.
     **/
    inline GLFWwindow *getWindow() {
        return _window;
    }
};

/**
 * Acessor for the only engine instance of this game.
 * The same as Engine::getInstance(), only more beautiful to write.
 **/
inline Engine &getEngine() {
    return Engine::getInstance();
}

#endif // !ENGINE_HPP
