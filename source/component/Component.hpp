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

#ifndef COMPONENT_COMPONENT_HPP
#define COMPONENT_COMPONENT_HPP

#include <stdexcept>
#include <string>
#include "component/componentIds.hpp"

class GameObject;

/**
 * GameObjects are buckets of data. The data that the GameObjects hold are
 * Components. The Components are data that is managed by the correspondent
 * System classes.
 *
 * When inheriting this class to create your own components, you MUST do two
 * things to make the component work with the GameObject-Component system of
 * this Engine.
 *
 * First, when creating your inherited class, the first line of the class
 * MUST be the following macro: COMPONENT_CLASS(ComponentName).
 * This will create the static ComponentName::Id variable and implement the
 * ComponentName::id() function that is declared in the Component class, both
 * with ComponentNameId as its value.
 *
 * Second, you need to register your component type.
 * Open the file "componentRegistration.hpp.inc" (relative to this directory)
 * and, after the last REGISTER_COMPONENT(ComponentName) line, add your own,
 * with the name of the new component as parameter. This will create an unique
 * ComponentNameId value of the ComponentId enum that will represent your
 * component in the GameObject-Component system.
 *
 * For example, if your component is called MyShinyComponent, in the definition
 * of your class, you MUST add COMPONENT_CLASS(MyShinyComponent) (note the
 * absence of semicolons) as the first line of the class:
 *
 * class MyShinyComponent : public Component {
 *     COMPONENT_CLASS(MyShinyComponent)
 *
 *     // Your shiny class contents go here...
 *     // ...
 * };
 *
 * After that, you MUST add in the file "componentRegistration.hpp.inc" the line
 * REGISTER_COMPONENT(MyShinyComponent) (note, again, the absence of semicolon)
 * after the last REGISTER_COMPONENT line.
 *
 * Doing those two simple things, your component will be integrated with the
 * GameObject-Component system.
 **/
class Component {
    /// The game object that owns this component.
    GameObject *_gameObject;

public:
    /**
     * Constructor.
     * @param gameObject The game object that will own this component.
     **/
    Component(GameObject *gameObject) : _gameObject(gameObject) {

    }

    /// Virtual destructor.
    virtual ~Component() { }

    /**
     * Returns the ID of this component.
     * You MUST NOT implement this function when inheriting this class and
     * creating your own component, because the COMPONENT_CLASS() macro you
     * add as the first line of the class will already implement this function
     * for you.
     **/
    virtual ComponentId id() = 0;

    /**
     * Returns the game object of this component.
     **/
    inline GameObject *getGameObject() {
        return _gameObject;
    }
};

/**
 * This macro must be added as the first line of your component that inherits
 * Component.
 * It adds the Id static variable to the class and implements the id() function.
 * @param ComponentName the name of the component's class.
 **/
#define COMPONENT_CLASS(ComponentName) public: \
        static const ComponentId Id = ComponentName##Id; \
        virtual ComponentId id() { return Id; } \
        private:

/**
 * Exception for component types.
 **/
class ComponentError : public std::runtime_error {

public:
    ComponentError(const std::string &what) : std::runtime_error(what) { }
};

#endif // !COMPONENT_COMPONENT_HPP
