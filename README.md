# ActionDependencySystem
## What is it?
This is a C++ proof of concept implementation of an idea that involves chaining together "actions" in a Directed Acyclic Graph, then exectuting these in order, depending on how they are connected. These can be executed sequentially or in parallel.

An "action" is just an object (C++ class inheriting a common interface), that can run any (maybe :D) code written by the user, simple examples implement a file copy, or running of a powershell script or a wait.

## How to build it?
Can be built easily in Visual Studio given the requirements below. 

To use it in your own application you will need to build the "ActionDependencySystem" Project in release mode and from there you can use the headers, .dll and .lib files to build other applications.

## Requirements
- Visual Studio 2017
- C++17

## Notes
This was initially an idea for a prototype for use in a credit system for brokers to represent complex matrices for their customers. This is merely a high level framework and could be used for running anything really.
The testing portion of this has not been written yet. :D
