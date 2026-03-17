*This project has been created as part of the 42 curriculum by jtoumani and stliu.*

# miniRT — My First RayTracer with MiniLibX

A ray tracing engine that renders 3D scenes from simple scene description files (`.rt` format). This project implements a complete ray tracer with support for geometric objects (spheres, planes, cylinders), lighting (ambient + diffuse), hard shadows, and bonus features like cones and specular reflection.

---

## Description

**miniRT** is a ray tracing application that generates computer-generated images based on scene description files. The program reads a `.rt` file containing object definitions, camera settings, and lighting information, then renders the scene in a window using the MiniLibX library.

### Goal
- Implement a functional ray tracer using ray-sphere, ray-plane, and ray-cylinder intersection algorithms
- Apply Phong lighting model (ambient + diffuse illumination)
- Render images with proper hard shadow computation
- Parse and validate scene files with robust error handling
- Support window management (resize, minimize, ESC to quit)

## Instructions

### Compilation

**Requirements:**
- Linux/POSIX OS
- `cc` (gcc or clang)
- `make`
- X11 development libraries (for MiniLibX)

**Build:**
```bash
cd /path/to/MiniRT
make
```

This compiles the project and creates the `miniRT` executable.

To rebuild from scratch:
```bash
make re
```

To clean build artifacts:
```bash
make clean    # removes .o files
make fclean   # removes .o files and executable
```

### Execution

Run with a scene file:
```bash
./miniRT scenes/sphere.rt
```

**Scene Format (.rt):**
```
A 0.2 255,255,255                              # Ambient: ratio color
C 0,0,-50 0,0,1 70                              # Camera: pos direction fov
L -40,50,30 0.7 255,255,255                    # Light: pos brightness color
sp 0,0,20 20 255,0,0                           # Sphere: center diameter color
pl 0,0,0 0,1,0 200,200,200                     # Plane: point normal color
cy 50,0,20 0,0,1 14 21 10,0,255                # Cylinder: center axis diam height color
co 0,0,0 0,0,1 10 20 100,100,255               # Cone: center axis radius height color
```

**Controls:**
- `ESC` — quit and close window
- Click red X on window frame — quit cleanly

---

## Features

### Mandatory Part
✓ Ray tracing with sphere, plane, cylinder intersections  
✓ Ambient lighting + diffuse (Lambert) shading  
✓ Hard shadow computation  
✓ Camera with field of view and orientation  
✓ Multiple lights support  
✓ Scene file parsing and validation  
✓ Window management (fluid resize, minimize, close)  
✓ Proper memory management (no leaks)  

### Bonus Features
✓ Cone object (second-degree surface)  
✓ Specular reflection (Phong model)  
✓ Checkerboard pattern on planes  
✓ Colored/multi-spot lights  

---

## Project Structure

```
MiniRT/
├── main/                    # Source files
│   ├── main.c              # Entry point & window loop
│   ├── parse.c             # Scene file parser
│   ├── rt_math.c           # Vector math implementations
│   ├── render.c            # Render loop & pixel coloring
│   ├── intersection.c      # Ray-object intersections
│   ├── colors.c            # Color & lighting calculations
│   └── ...
├── inc/                     # Header files
│   ├── window.h
│   ├── rt_math.h
│   ├── parser.h
│   └── ...
├── scenes/                  # Example .rt scene files
├── GNL/                     # Get Next Line library
├── Printf/                  # ft_printf & Libft
├── minilibx-linux/          # MiniLibX graphics library
├── Makefile
└── README.md
```

---

## Resources

### Ray Tracing & Graphics
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) — Foundational algorithms
- [MiniLibX Docs](https://github.com/42Paris/minilibx-linux) — Graphics library
- also Youtube and open Source Google for algebra and general help at rendering

---

## Technical Choices

- **Vector Math:** Struct-based `t_vec3` (simple and clear)
- **Storage:** Linked lists for dynamic scaling
- **Parser:** Manual token parsing (better error messages)
- **Shadows:** Hard shadows (ray-to-light blocking)
- **Rendering:** Single-threaded pixel-by-pixel ray casting

---

## Troubleshooting

**Black window / empty scene**
- Check camera direction is not parallel to plane
- Verify objects are within camera's field of view

**"Error: missing camera/ambient"**
- Scene must have exactly one C line and one A line

**Segmentation fault**
- Verify `.rt` file formatting (no extra spaces in vectors)
- Ensure all required elements are present

---

## Authors
- **jtoumani** — Ray tracer, parser, math library, rendering
- **stliu** — Rendering optimization, lighting, scenes

License: Part of 42 curriculum (42 Norm compliant)
