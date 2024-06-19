## [Video Demonstration (box Link)](https://oregonstate.box.com/s/9p9b8lrwjeoy1n6tbpl1pp5v502rydux)

### Tools and Transformations Used

In this project, the following transformations and tools will be utilized:

1. **Translation**:
   - **Up and Down Movement**: Translate the horse along the Y-axis to create a bobbing effect.
   - **Translation from Origin**: Move the horse from the origin to the circumference of the circle.

2. **Rotation**:
   - **Revolution Around the Circle**: Rotate the horse around the Y-axis to simulate the carousel motion.
   - **Rocking Motion (Pitching)**: Rotate the horse back and forth around the X-axis to create a rocking effect.

3. **Camera Views**:
   - **Outside View**: Utilize `gluLookAt()` to provide an external perspective of the entire scene.
   - **Inside View**: Utilize `gluLookAt()` to provide a view from the center of the carousel looking outward.
   - Use `s` or `S` to toggle between both views.

4. **Display Lists**:
   - Create display lists for rendering the horse geometry, in polygon from.

5. **Perspective and Orthographic Projections**:
   - Default view is perspective, toggle orthographic with `o` or `O`.