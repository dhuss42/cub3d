
#include "../cub.h"

#define mapWidth 100
#define mapHeight 100
#define screenWidth 500
#define screenHeight 500


void	draw_cell(mlx_image_t *image, int start_x, int start_y, int cell_size, uint32_t color)
{
	int y;
	int x;

	y = 0;

	if (start_x >= screenWidth || start_y >= screenHeight)
		return;
	// printf("TEST\n");
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

void	create_map(mlx_t **mlx, char **map)
{
	mlx_image_t *image;
	int	x;
	int	y;
	int cell_size = 50;
	int	start_x;
	int start_y;

	*mlx = mlx_init(screenWidth, screenHeight, "Minimap", true);
	if (*mlx == NULL)
	{
		printf("mlx_init\n");
		exit(1);
	}
	image = mlx_new_image(*mlx, screenWidth, screenHeight);
	if (image == NULL)
	{
		printf("mlx_image\n");
		exit(2);
	}
	y = 0;
	while ( (map[y] != NULL))
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			// printf("drawcell\n");
			start_x = x * cell_size;
			start_y = y * cell_size;
			if (map[y][x] == '1')
				draw_cell(image, start_x, start_y, cell_size, 0xFF0000FF);
			else if (map[y][x] == '0')
				draw_cell(image, start_x, start_y, cell_size, 0xFFFFFFFF);
			else if (map[y][x] == 'P')
				draw_cell(image, start_x, start_y, cell_size, 0x00FFFFFF);
			else
				draw_cell(image, start_x, start_y, cell_size, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_image_to_window(*mlx, image, 0, 0);
	// iterate over double char
	// make wall for 1
	// make space for 0
}

int main()
{
	mlx_t	*mlx;

	char	*map[] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"100000P001",
		"1000000001",
		"1000000001",
		"1111111111",
		NULL
	};

	create_map(&mlx, map);
	mlx_loop(mlx);

	// for (int i = 0; i < 10; i++) {
	// 	printf("%s\n", map[i]);
	// }

	return 0;
}