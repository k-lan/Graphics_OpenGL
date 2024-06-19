## [Video Demonstration (box Link)](https://oregonstate.box.com/s/bx2jckwfqdppo16fc47z9dmx5g3mid20)

### Tools and Transformations Used

In this project, the following tools and transformations were utilized:

1. **Texture Mapping**:
   - **Texture Loading**: Each texture image was read into the program using the `BmpToTexture` function and stored in GPU memory by binding to a texture name.
   - **Texture Binding**: Display lists were created for each planet, properly scaled, and with the appropriate texture bound to them.
   - **Texture Modes**: Implemented toggling between different texture modes (`GL_REPLACE`, `GL_MODULATE`, and no texture) using keybind `t`.

2. **3D Objects**:
   - **OsuSphere**: A display list was created to hold an `OsuSphere` with a radius of 1.0, which was then used to represent each planet with the correct scaling and texture.

3. **Lighting**:
   - **Dynamic Light Source**: A moving point light source was placed in the scene to demonstrate the `GL_MODULATE` mode's effect on textures. The light source's motion was controlled to show dynamic lighting on the textures.

4. **Scene Control**:
   - **Planet Selection**: Implemented keyboard controls to switch between different planets, each displayed with the correct scale and texture. `e` for Earth, `v` for Venus, and so on...
   - **Texture Mode Toggle**: Implemented a toggle control to switch between no texture, `GL_REPLACE` texture mode, and `GL_MODULATE` texture mode using the 't' key.