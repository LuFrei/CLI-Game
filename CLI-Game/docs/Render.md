# Renderer

## Overview
Quick overview. What are the key take aways for this system?\
What does it do?\
Why is it needed?\
When should it be used?

## Quick Start
Quick ste-byb-step guide on how to use or set up this system.\
How is it used?

## API
A list of all public properties and methods.\
And hopefully a brief explaination of each.

## Methodology
A memoire of why things where done the way they were.\
What can I do better? What features went missing?\
Write like you are writing to your future self,\
trying to under stand the source code and why it was written the way it was.

## Notes

### 11-15-2023
We need an object that any other object can instantiate and manage themselves.\
Yet it should automatically update within the render loop. Most systems I've\
seen, (OpenGL, Unity) use a "Rect" or Rectangle object that represent the space\
it ocupies on the screen.

### !!! Rect
Rect is now part of Renderer because we NEED a rect to be able to\
something in the screen.\
Rect is THE data we use for rendering, HOWEVER...\
Rect can, and probably will be used for other systems,\
Such as a collisions/physics system.

We'll keep Rect into the Render namespace for now but we\
WILL have to move this out.
