## [Video Demonstration (box Link)](https://oregonstate.box.com/s/h5c7qd4zby6iglfldxhmeimtqs7j610s)

### Tools and Transformations Used

In this project, the following tools and transformations were utilized:

1. **Lighting**:
   - **Dynamic Light Source**: A light source was created that moves above the scene in a circular pattern.
   - **Point Light and Spot Light**: The light source could be toggled between a point light and a spot light using the `p` and `s` keyboard keys.
   - **Light Source Color**: The light source color could be changed using the `w`, `r`, `g`, `b`, and `y` keyboard keys for white, red, green, blue, and yellow respectively.

2. **3D Objects**:
   - **OBJ Files**: A 3D cat and sphere are utilized.
   - **Material Properties**: Different material properties were assigned to objects, including dull and shiny surfaces (GL_SHININESS).

3. **Scene Setup**:
   - **Grid**: A grid was placed under the scene to help visualize the lighting effects.
   - **Light Source Indicator**: A small, unlit sphere was used at the light source location to indicate its position.

4. **Camera and Viewing**:
   - **Perspective Projection**: Perspective projection was used for the entire scene.

5. **Animation Control**:
   - **Timing the Animation**: Dividing the current time in ms by the set `MS_PER_CYCLE` was used to control the animation cycle of the light source.