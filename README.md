# NURBS Modeler — Implementazione di un modellatore di curve NURBS in OpenGL

An interactive 2D curve modeler written in C++ and OpenGL that lets you draw, edit and inspect **Bézier**, **B-Spline** and **NURBS** curves in real time.

Bachelor's thesis project by **Chiara Frascaria** (Sapienza Università di Roma), supervisor **Prof. Hendrik Speleers**. Presented on 27/04/2023.

Requirements: **Windows**, **Visual Studio 2019 or later** with the *Desktop development with C++* workload, and a GPU with OpenGL 3.3+.

All dependencies are bundled in `librerie/`:

- GLFW 3.3.7 (Win64 binaries)
- glad
- Dear ImGui 1.88(https://github.com/ocornut/imgui)
- stb


If the build cannot find GLFW or glad, they must be set in project properties of Visual Studio`.

## Features

- Multiple curves in the same scene, listed in a curve hierarchy
- Add, move and remove control points with the mouse and keyboard
- Choose the degree (with an adjustable min/max range)
- Toggle between **Bézier** and **B-Spline/NURBS** mode
- **NURBS weights**: one vertical slider per control point, color-matched to its basis function
- Live plot of the **basis functions** under the settings panel
- Move along the curve with the `t` slider and **show the de Casteljau / de Boor construction** step by step
- **Split** a Bézier curve at `t` (subdivision)
- **Degree elevation** of a Bézier curve
- Predefined **circle** mode (an exact NURBS circle)
- Pan and zoom on an infinite grid

![NURBS Modeler screenshot](docs/screenshot.png)

## Controls

| Input | Action |
|---|---|
| Right mouse button | Add a control point |
| Left mouse button (drag) | Move the selected control point |
| Middle mouse button (drag) | Pan the view |
| Mouse wheel up / down | Zoom in / out |
| `F` | Remove the first control point |
| `L` | Remove the last control point |
| `↑` / `↓` | Move the camera forward / backward |
| `Q` / `E` | Move the camera left / right |
| `A` / `D` | Rotate the camera |
| `Esc` / `X` | Quit |
## Author

**Chiara Frascaria** — Bachelor's thesis, supervisor Prof. Hendrik Speleers.
