# Entity

## Overview
Entity represents any and all objects with in our game. Think of 'GameObject's in Unity.
We keep all basic necessary information for objects to exist within the gameworld (visible, or not.)
Right now, This includes:
- position
- size
- !rotation

## Quick Start
Simply inheret from the Entity class.
Right now you have to update the Move() function in your child class to add any extra functionality like moving the 

## API
A list of all public properties and methods.\
And hopefully a brief explaination of each.

## Methodology
The idea is for this to become the central hub for most interactions between the engine and developer-made items.

#### Position was changed from an int to a float:
While the screen is mostly composed of large cells and charcters can only move 1 unit at a time, we can use floating points to emulate exact position, and move cells once a whole number has changed.
Additionally, We may want to later make smaller cells and define a unit to be multiple cells wide/high.
Or better yet, we can decouple the screen's cells and the game world, allowing for scaling/zoom, etc.

## Notes
### TODO:
Actually Make the entity the central system for systems to interact
Right now, it just holds the size and position info.