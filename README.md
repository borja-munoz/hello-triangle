# hello-triangle

When learning a new programming language, usually the first example is usually a variation of a program that outputs the text "Hello, World" to the console.

When learning new computer graphics APIs, it is common to do something similar but with a program that renders a triangle, with vertices of red, green and blue color that are interpolated.

This repository contains examples for different computer graphics APIs with fixed and programmable pipelines:

- OpenGL
- DirectX
- Vulkan
- Metal
- WebGPU

The code is based on different resources, including:

- The Getting Started tutorial at https://learnopengl.com
- The OpenGL Programming Guide

## OpenGL 

The OpenGL examples use these additional libraries:

- GLFW: https://github.com/glfw/glfw. For creating windows, contexts and surfaces, reading input, handling events, etc.

- GLAD: https://glad.dav1d.de/. To abstract the OpenGL driver and the operating system. We have chosen:

   - Language: C/C++
   - Specification: OpenGL
   - API: gl version 4.1 (last supported version in MacOS)
   - Profile: Core

For MacOS we need to link also the following frameworks (in addition to the OpenGL framework):

- Cocoa
- IOKit
- CoreVideo

## DirectX


## Vulkan


## Metal


## WebGPU