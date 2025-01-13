
#include "raycasting.h"

bool is_player(char c, t_cub *cub)
{
    int i;
    char *str;

    i = 0;
    str = "NSEW";
    while (str[i] != '\0')
    {
        if (c == str[i])
        {
            cub->start_dir = c;
            printf(YELLOW"char dir: %c\n"WHITE, cub->start_dir);
            return (true);
        }
        i++;
    }
    return (false);
}
