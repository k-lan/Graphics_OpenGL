## [Video Demonstration (box Link)](https://oregonstate.box.com/s/rnns60pzcms1vwdt272yvolld9jlqo06)

### Tools and Transformations Used

In this project, the following tools and transformations were utilized:

1. **Keytime Animation**:
   - **Keytime Interpolation**: Animated the center of the ellipse using the KeyTime method with keytime positions for `uSc` and `uTc`.

2. **Time-based Animation**:
   - **Radius Animation**: Used sine functions to animate the S-radius (`uRs`) and T-radius (`uRt`) of the ellipse, ensuring the values varied smoothly over time.

3. **Shader Programming**:
   - **Vertex Shader**: Wrote a `pattern.vert` vertex shader to transform vertices and pass necessary variables (`vST`, `vN`, `vL`, `vE`) to the fragment shader.
   - **Fragment Shader**: Wrote a `pattern.frag` fragment shader to apply per-fragment lighting and determine the color based on the ellipse equation.

4. **GLSL Program**:
   - **GLSLProgram Class**: Utilized the `GLSLProgram` C++ class to create and manage shaders from the `pattern.vert` and `pattern.frag` files.
   - **Uniform Variables**: Passed uniform variables to the shaders to control lighting (`uKa`, `uKd`, `uKs`, `uColor`, `uSpecularColor`, `uShininess`) and ellipse parameters (`uSc`, `uTc`, `uRs`, `uRt`).

5. **Lighting**:
   - **Per-fragment Lighting**: Implemented per-fragment lighting in the fragment shader to provide realistic lighting effects on the animated ellipse pattern.

6. **3D Object**:
   - **Object Selection**: Chose a sphere object with (s, t) texture coordinates for applying the animated ellipse pattern. Ensured the object had surface normal vectors for proper lighting.

7. **Animation Control**:
   - **Toggle Animation**: Implemented keyboard controls to toggle keytime-based (`'k'` key) and time-based (`'t'` key) animations on and off.