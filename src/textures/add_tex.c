#include "include.h"

void    **load_tex(void)
{
    t_params    *param;
    void        *ret[4];
    int         index;

    index = 0;
    param = params_holder();
    while (index < 4)
    {
        ret[index] = mlx_xpm_file_to_image();
    }
}