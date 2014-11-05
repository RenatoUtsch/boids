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

#ifndef COMPONENT_COMPONENTIDS_HPP
#define COMPONENT_COMPONENTIDS_HPP

/**
 * This macros starts the registering of components by creating their component
 * ids. It is simply a macro for the ComponentId enum.
 * The NullComponentId represents no component/an invalid component.
 * NullComponentId and InvalidComponentId can be used interchangeably.
 **/
#define COMPONENT_REGISTERING_BEGIN enum ComponentId { NullComponentId = 0,

/**
 * This macro ends the creation of component ids. It is simply a macro for the
 * ending of the ComponentId enum.
 * The InvalidComponentId has the same value as the NullComponentId to make the
 * two interchangeable.
 **/
#define COMPONENT_REGISTERING_END InvalidComponentId = 0 };

/**
 * This macro registers your component in the GameObject-Component system.
 * After creating your component class by inheriting Component, you MUST
 * add the component name below with this macro.
 **/
#define REGISTER_COMPONENT(ComponentName) ComponentName##Id,

/*
 * Start the creation of the ComponentId enum.
 */
COMPONENT_REGISTERING_BEGIN

// Include the REGISTER_COMPONENT calls for the created components.
#include "componentRegistration.hpp.inc"

COMPONENT_REGISTERING_END

// Undef the macros because they aren't needed anymore.
#undef COMPONENT_REGISTERING_BEGIN
#undef COMPONENT_REGISTERING_END
#undef REGISTER_COMPONENT

#endif // !COMPONENT_COMPONENTIDS_HPP
