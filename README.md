# Path Tracer
https://georgeloines.com/projects/path-tracer

This application implements a pathtracer that renders a cornell box with
a shadowed area light, reflections and indirect lighting. I completed this
project for an individual coursework submission during my masters degree.

![screenshot of the application](screenshot-top.png?raw=true)

# Main Features
- Moveable camera and Qt GUI
- Toggle direct light, impulse light, indirect light and shadows on and off
- Threaded rendering
       - Multiple worker threads are started to compute ray samples
       - The GUI updates to show the image as it is being rendered
       - Rendering stats (samples / render time) are shown in the GUI
- Extra scene items (reflective spheres) can be toggled on and off

# How To Run (Mac / Linux)
- Ensure qt 5 is installed
- Run install.sh
- Run ./pathtracer

# Instructions
- Use W,A,S,D,Q and E to move the camera
- Moving the camera restarts the rendering process
- Hold left shift to move the camera faster
- Adjust rendering settings using the UI

# Debugging Overlays
I added a number of debugging modes to the renderer during development. I
decided to leave them in and make them toggleable from the UI:
- Pixel view ray directions
- Hit distance
- Hit position
- Surface diffuse color
- Surface normal durection (y/green is up)
- Surface emission
