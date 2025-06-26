# cub3d

## Contents

1. [Project Overview](#1-Project-overview)
2. [Project Structure](#2-Project-Structure)
3. [Description of individual steps](#3-Description-of-individual-steps)
4. [How to run](#4-How-to-run)

## 1. Project overview
cub3D was a project where we built a simple first-person 3D rendering engine using raycasting, inspired by the classic Wolfenstein 3D. Our goal was to create a dynamic view inside a maze from a first-person perspective, using [MLX42](https://github.com/codam-coding-college/MLX42) for graphical rendering. We loaded and parsed a .cub configuration file to define the map, wall textures, and floor/ceiling colors, and implemented movement, rotation, and wall rendering

For this project I teamed-up with [maustel](https://github.com/maustel). We split the project into parsing and raycasting.

## 2. Project Structure

3.1 [Parsing](#31-parsing)  
3.2 [Initialising MLX variables](#32-Initialising-MLX-variables)  
3.3 [Set initial vectors](#33-Set-initial-vectors)  
3.4 [Movement](#34-Movement)  
3.5 [Floor and Ceiling](#35-Floor-and-Ceiling)  
3.6 [Raycasting](#36-Raycasting)   

## 3. Description of individual steps

### 3.1 Parsing

### 3.2 Initialising MLX variables

First, the MLX instance is initialized, a new image is created to serve as the drawing surface, and this image is projected onto the game window. At the same time, the necessary textures are loaded into memory.

### 3.3 Set initial vectors

Next, the initial player values are set. This includes determining the player’s starting position on the map and centering them within their starting tile. Then, the player’s initial direction vector (indicating where they’re looking) is defined, along with the plane vector, which is perpendicular to the direction and used for the camera’s field of view.

### 3.4 Movement

Once initialization is complete, the MLX loop hook is started, and the game_loop function is hooked into it. Inside this loop, key inputs are handled: the WASD keys allow for directional movement while respecting wall collision logic, the Left and Right Arrow keys rotate the player by updating both the direction and plane vectors, and the Escape key cleanly exits the game, freeing all allocated resources.

### 3.5 Floor and Ceiling

Additionally, in each iteration of the game_loop, the background of the image is reset. The screen is split into two halves: the upper half represents the ceiling, and the lower half the floor, each filled with different colors to enhance the 3D illusion.

### 3.6 Raycasting

In Cub3D, the 3D environment is simulated using a raycasting engine, which projects a 2D map into a pseudo-3D first-person view. The core of this engine lies in the raycasting loop, which is executed once per frame for each vertical column of pixels on the screen.

The process begins by casting a ray for each vertical column of the screen. For every pixel column x, we calculate the direction of the ray based on the player's current orientation and the camera plane, which gives a field-of-view effect. This ray determines what part of the map the player is looking at in that direction.

Once the direction is known, we determine the player's position on the map grid and compute how far the ray must travel to hit a wall. Using DDA (Digital Differential Analysis), we step through the map grid square by square, checking for intersections with walls. This is done efficiently by comparing distances to the next vertical and horizontal grid lines, and stepping accordingly.

When a wall is hit, we calculate the distance from the player to the wall, correcting for distortion caused by the ray's angle (i.e., avoiding the fish-eye effect). From this distance, we compute the height of the wall slice to be drawn on the screen: walls closer to the player appear taller, while those farther away appear shorter, mimicking perspective.

Next, we identify which wall texture to use based on the side hit and the ray's direction. We also compute the exact hit point on the wall and scale it to match the corresponding X coordinate in the texture, ensuring that textures are properly aligned and oriented (including mirroring when necessary).

Finally, for each pixel in the vertical column, we determine the correct Y coordinate in the texture based on the distance from the top of the wall slice, fetch the color from the texture, and draw it onto the screen using mlx_put_pixel. 

## 4. How to run

Clone repository
```
git clone https://github.com/dhuss42/cub3d.git cub3d
```

navigate into repository
```
cd cub3d
```

run make
```
make
```

start program
```
./cub3D tests/valid/map_04.cub 
```

make sure to have cmake installed or the MLX42 will throw an error
