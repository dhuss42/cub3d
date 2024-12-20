#include "raycasting.h"

// create a dot at player position
// create vector for looking direction
// move dot when keys are pressed
//  update position of player
// make rotation able

t_vector    find_position(char **map, char identifier)
{
    int y;
    int x;
    t_vector pos;

    pos.x = -1;
    pos.y = -1;
    y = 0;
    while (map[y] != NULL)
    {
        x = 0;
        while (map[y][x] != '\0')
        {
            if (map[y][x] == identifier)
            {
                pos.x = x;
                pos.y = y;
                return (pos);
            }
            x++;
        }
        y++;
    }
    return (pos);
}

void    determine_dir(t_cub *cub, char dir)
{
    if (dir == 'N')
    {
       cub->player_angle = 90.0f;
    }
    else if (dir == 'E')
    {
        cub->player_angle = 0.0f;
    }
    else if (dir == 'S')
    {
        cub->player_angle = 270.0f;
    }
    else if (dir == 'W')
    {
        cub->player_angle = 180.0f;
    }
    cub->dir_player.x = cos(cub->player_angle);
    cub->dir_player.x = sin(cub->player_angle);
}
// floats for continous values

// If the player is facing East (0°), cos(0) gives 1 (along the x-axis), and sin(0) gives 0 (along the y-axis). 
// So, the direction vector is (1, 0), which points straight to the right.


int create_vectors(t_cub *cub)
{
    char dir;

    dir = 'N'; // change later
    cub->pos_player = find_position(cub->map, dir);
    determine_dir(cub, dir);

    return (0);
}
