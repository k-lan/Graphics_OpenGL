# Graphics with OpenGL
## Fall Term 2023, Oregon State University

This is my overview of CS 450: Introduction to Graphics projects. This course at Oregon State University introduced me to fundamental and advanced graphics programming techniques. Below is a summary of each project, detailing the key objectives, tools, and technologies used. For a more immersive experience, I highly recommend viewing the video demonstrations found at the top of each projects `README.md` file, titled `Video Demonstration`. These links will route you to an Oregon State University Box link.

## Project Summaries

### Project #1: Using Transformations to Animate a Carousel Horse
This project focused on understanding and applying geometric transformations to animate a carousel horse. By implementing translation, rotation, and scaling transformations, I animated the horse to move in a circular path, bob up and down, and rock back and forth. The project also included toggling between different camera views.

**Key Tools and Techniques**:
- Translation, Rotation, and Scaling
- Camera Views (Inside and Outside)
- Display Lists

### Project #2: Lighting
In this project, I created a 3D scene with dynamic lighting. The scene featured multiple objects, each with different material properties. A moving light source was implemented to demonstrate both point light and spot light effects. The project also included toggling light colors and light modes.

**Key Tools and Techniques**:
- Dynamic Light Source
- Point Light and Spot Light
- Material Properties and Lighting Modes

### Project #3: Keytime Animation
This project involved keytime animation, allowing for smooth interpolation of object properties over time. By animating various quantities such as light position, object position, and color, I created a dynamic 3D scene. Keyframing techniques were used to control the animation cycles.

**Key Tools and Techniques**:
- Keytime Interpolation
- Smooth Interpolation with Coons Cubic Curves
- Animation of Light and Object Properties

### Project #4: Texture Mapping
The goal of this project was to texture map planets with accurate scaling. Each planet was represented as a sphere with appropriate textures, and a moving point light source was added to showcase dynamic lighting effects. The project included toggling between different texture modes and demonstrating the use of texture mapping hardware.

**Key Tools and Techniques**:
- Texture Mapping and Binding
- Dynamic Lighting with GL_MODULATE Mode
- Sphere Creation and Scaling

### Project #5: Shaders
In this project, I created an animated ellipse pattern using an OpenGL fragment shader. The ellipse center and radii were animated using keytime and time-based methods, respectively. Per-fragment lighting was applied to enhance the visual effects.

**Key Tools and Techniques**:
- OpenGL Shaders (Vertex and Fragment)
- Keytime and Time-based Animation
- Per-fragment Lighting
- Uniform Variables for Shader Control

### Final Project: Low-Poly Cozy Scene
For the final project, I designed a low-poly camping scene on a floating island in space. The scene included a starry sky background, a campfire with dynamic lighting and particle effects, and multiple viewpoints. The project emphasized creativity and advanced graphics techniques, such as particle systems and texture mapping.

**Key Tools and Techniques**:
- Particle Systems
- Dynamic Lighting and Keyframing
- Texture Mapping and Animation
- Creative Scene Design

## Viewing Video Demonstrations
To fully appreciate the visual and interactive aspects of these projects, please view the video demonstrations provided in the projects respective `Video Demonstration` links. These videos showcase the dynamic and engaging nature of the graphics techniques implemented throughout the course. Otherwise, each project *should* run with `make` and then `./sample`, assuming OpenGL and other necessary libraries are installed.