## [Video Demonstration (box Link)](https://oregonstate.box.com/s/m032gj9mv1t545penukt9aej2rjdu91k)

### Tools and Transformations Used

In this project, the following tools and transformations were utilized:

1. **Keytime Animation**:
   - **Smooth Interpolation**: Employed Coons cubic curves for smooth interpolation of keytimes, allowing for smooth transitions between key values without needing to specify slopes.
   - **Keytimes Class**: Used the Keytimes class methods to define and interpolate values at specific times.

2. **Animation of Quantities**:
   - **Light Source**: Animated the light sources RGB values.
   - **Viewing**: Animated the Y value of the camera.
   - **Object Transformation**: The object spins in an inconsistent manner. The lightsource also has animated XYZ values.
   - **Object Color**: Animated the G component of the object.
   - **Additional Quantities**: Animated four additional quantities of choice to enhance the scene.

3. **3D Object**:
   - **Object Selection**: Chose a 3D object capable of being lighted, ensuring it had surface normal vectors for proper lighting.
   - **Object Animation**: Animated the object's properties over a 10-second duration, ensuring it returned to its original state at the end of the cycle.

4. **Lighting**:
   - **Lighting Parameters**: Selected appropriate lighting parameters to enhance scene visibility and clarity.

5. **Timing and Animation Control**:
   - **Cycle Timing**: Dividing the current time in ms by the set `MS_PER_CYCLE` was used to control the animation cycle of the light source.