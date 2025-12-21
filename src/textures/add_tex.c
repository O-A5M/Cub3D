#include "include.h"

t_textures    *load_tex(void)
{
    t_params    *param;
    t_textures  text[4];
    int         index;

    index = 0;
    param = params_holder();
    while (index < 4)
    {
        text[index].addr = mlx_xpm_file_to_image(param->mlx->mlx_ptr, param->textures[index], text[index].width, text[index].height);
        if (!text[index].addr)
            return (printf("Error testurn\n"), NULL);
    }
    return (text);
}