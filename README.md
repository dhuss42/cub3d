# cub3d

## Contents

1. [Project Overview](#1-Project-overview)
2. [Project Structure](#2-Project-Structure)
3. [Description of individual steps](#3-Description-of-individual-steps)
4. [How to run](#4-How-to-run)

## 1. Project overview


Moreover, it is the second project in which we had to work with an external library the [MLX42](https://github.com/codam-coding-college/MLX42).


This project was the second team-based assignment at 42. For this project I teamed-up with [maustel](https://github.com/maustel). We split the project into parsing and raycasting.

## 2. Project Structure

1. [Parsing](#parsing)
2. 

## 3. Description of individual steps

### Parsing

### Initialising MLX variables

First, the MLX instance is initialized, a new image is created to serve as the drawing surface, and this image is projected onto the game window. At the same time, the necessary textures are loaded into memory.

### Set initial vectors

Next, the initial player values are set. This includes determining the player’s starting position on the map and centering them within their starting tile. Then, the player’s initial direction vector (indicating where they’re looking) is defined, along with the plane vector, which is perpendicular to the direction and used for the camera’s field of view.

### Movement

Once initialization is complete, the MLX loop hook is started, and the game_loop function is hooked into it. Inside this loop, key inputs are handled: the WASD keys allow for directional movement while respecting wall collision logic, the Left and Right Arrow keys rotate the player by updating both the direction and plane vectors, and the Escape key cleanly exits the game, freeing all allocated resources.

### Floor and Ceiling

Additionally, in each iteration of the game_loop, the background of the image is reset. The screen is split into two halves: the upper half represents the ceiling, and the lower half the floor, each filled with different colors to enhance the 3D illusion.

### Raycasting

In Cub3D, the 3D environment is simulated using a raycasting engine, which projects a 2D map into a pseudo-3D first-person view. The core of this engine lies in the raycasting loop, which is executed once per frame for each vertical column of pixels on the screen.

The process begins by casting a ray for each vertical column of the screen. For every pixel column x, we calculate the direction of the ray based on the player's current orientation and the camera plane, which gives a field-of-view effect. This ray determines what part of the map the player is looking at in that direction.

Once the direction is known, we determine the player's position on the map grid and compute how far the ray must travel to hit a wall. Using DDA (Digital Differential Analysis), we step through the map grid square by square, checking for intersections with walls. This is done efficiently by comparing distances to the next vertical and horizontal grid lines, and stepping accordingly.

When a wall is hit, we calculate the distance from the player to the wall, correcting for distortion caused by the ray's angle (i.e., avoiding the fish-eye effect). From this distance, we compute the height of the wall slice to be drawn on the screen: walls closer to the player appear taller, while those farther away appear shorter, mimicking perspective.

Next, we identify which wall texture to use based on the side hit and the ray's direction. We also compute the exact hit point on the wall and scale it to match the corresponding X coordinate in the texture, ensuring that textures are properly aligned and oriented (including mirroring when necessary).

Finally, for each pixel in the vertical column, we determine the correct Y coordinate in the texture based on the distance from the top of the wall slice, fetch the color from the texture, and draw it onto the screen using mlx_put_pixel. 

## 4. How to run

Clone repository
```
git clone
```

navigate into repository
```
cd
```

run make
```
make
```

make sure to have cmake installed or the MLX42 will throw an error
