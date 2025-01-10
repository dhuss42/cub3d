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
       cub->player_angle = PI / 2;
    }
    else if (dir == 'E')
    {
        cub->player_angle = 0;
    }
    else if (dir == 'S')
    {
        cub->player_angle = 3 * PI / 2;
    }
    else if (dir == 'W')
    {
        cub->player_angle = PI;
    }
    cub->dir_player.x = cos(cub->player_angle);
    cub->dir_player.y = sin(cub->player_angle);
    printf(RED"dir player.x: %f /\n"WHITE, cub->dir_player.x);
    printf(RED"dir player.y: %f /\n"WHITE, cub->dir_player.y);
}
// floats for continous values

// If the player is facing East (0°), cos(0) gives 1 (along the x-axis), and sin(0) gives 0 (along the y-axis). 
// So, the direction vector is (1, 0), which points straight to the right.

void    determine_plane(t_cub *cub)
{
    t_vector    camera;

    camera = cub->plane;
    camera.x = cub->dir_player.y;
    camera.y = cub->dir_player.x; // 0.66?

    // inverse of direction vector
    // needs to be variable based on the starting direction
}

int create_vectors(t_cub *cub)
{
    printf("char dir: %c\n", cub->start_dir);
    cub->pos_player = find_position(cub->map, cub->start_dir);
    determine_dir(cub, cub->start_dir);
    determine_plane(cub);
    return (0);
}
