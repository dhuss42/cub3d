#include "raycasting.h"

#define mapWidth 10
#define mapHeight 10
#define screenWidth 640
#define screenHeight 480

void    draw_player(t_cub *cub)
{
    int player_pixel_x = cub->pos_player.x * 50 + 25;  // Center of the cell
    int player_pixel_y = cub->pos_player.y * 50 + 25; 

    mlx_put_pixel(cub->image, player_pixel_x, player_pixel_y, 0xFF000000);
}

void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color)
{
    int y;
    int x;

    if (start_x >= screenWidth || start_y >= screenHeight)
        return;
    y = 0;
    while (y < cell_size && (start_y + y) < screenHeight)
    {
        x = 0;
        while (x < cell_size && (start_x + x) < screenWidth)
        {
            mlx_put_pixel(image, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}

void	create_map(t_cub *cub)
{
    int x;
    int y;
    int cell_size = 50;
    int start_x, start_y;

    cub->mlx = mlx_init(screenWidth, screenHeight, "Minimap", true);
    if (cub->mlx == NULL)
    {
        printf("Failed to initialize mlx\n");
        exit(EXIT_FAILURE);
    }
    cub->image = mlx_new_image(cub->mlx, screenWidth, screenHeight);
    if (cub->image == NULL)
    {
        printf("Failed to create image\n");
        exit(EXIT_FAILURE);
    }
    y = 0;
    while (cub->map[y] != NULL)
    {
        x = 0;
        while (cub->map[y][x] != '\0')
        {
            start_x = x * cell_size;
            start_y = y * cell_size;
            if (cub->map[y][x] == '1')
                draw_cell(cub->image, start_x, start_y, cell_size, 0xFF0000FF);
            else if (cub->map[y][x] == '0')
                draw_cell(cub->image, start_x, start_y, cell_size, 0xFFFFFFFF);
            else if (cub->map[y][x] == 'N')
                draw_cell(cub->image, start_x, start_y, cell_size, 0xFFFFFFFF); 
            else
                draw_cell(cub->image, start_x, start_y, cell_size, 0x00000000);

            x++;
        }
        y++;
    }
    draw_player(cub);
    
    mlx_image_to_window(cub->mlx, cub->image, 0, 0);
}

int main()
{
    t_cub   cub;

    char	*map[] = {
        "1111111111",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "100000N001",
        "1000000001",
        "1000000001",
        "1111111111",
        NULL
    };

    cub.map = map;
    create_vectors(&cub);
    create_map(&cub);
    mlx_loop(cub.mlx);

    return 0;
}
