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

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <map>
#include "component/Component.hpp"
#include "component/componentIds.hpp"

/**
 * A GameObject.
 * Each GameObject has its functionality defined by its components.
 **/
class GameObject {
    /// Type of the map of components.
    typedef std::map<ComponentId, Component *> ComponentMap;

    /// Pair related to the ComponentMap.
    typedef std::pair<ComponentId, Component *> ComponentPair;

    /**
     * A map of components given their ID.
     * This map stores pointers to components given their Id. The components
     * themselves are allocated in their respective systems.
     * You must take care to guarantee that the pointers stored in this map
     * are always valid and that the components are deallocated if and only if
     * they are removed from this map.
     * Also, there must not be a component that is stored in maps of two
     * different game objects.
     **/
    ComponentMap _components;

public:
    /**
     * Returns the component with the type specified as the template parameter.
     * @throws ComponentError in case the game object doesn't have the
     * component.
     **/
    template<class ComponentType> inline ComponentType &getComponent() {
        // Try to find the component.
        ComponentMap::iterator it = _components.find(ComponentType::Id);

        // If the component was found, return it. Else, throw an exception.
        if(it != _components.end())
            return it->second;
        else
            throw ComponentError("Invalid component");
    }

    /**
     * Makes the component given as first parameter a component of this class.
     * @param component The component to add to this object.
     * @throws ComponentError in case a component with the same ID already
     * exists in this object or if the component already has an owner.
     **/
    void addComponent(Component &component) {
        // If the component has an owner, throw an exception.
        if(component.hasGameObject())
            throw ComponentError("Component already has an owner GameObject");

        // Tries to find a component with the same ID.
        ComponentMap::iterator it = _components.find(component.id());

        // If an component was found, throw an exception. Else, add the
        // new component to the map.
        if(it != _components.end())
            throw ComponentError("A component of the same type already exists");
        else {
            component.setGameObject(*this);
            _components.insert(ComponentPair(component.id(), component));
        }
    }

    /**
     * Returns true if the game object has the component or false if not.
     **/
    bool hasComponent(ComponentId id) {
        ComponentMap::iterator it = _components.find(id);
        if(it != _components.end())
            return true;
        else
            return false;
    }
};

#endif // !GAMEOBJECT_HPP
