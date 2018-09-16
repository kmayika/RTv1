
#include "/Users/kwezimayikana/Desktop/minilibx/mlx.h"
#include <stdio.h>

int     main(void)
{
    int     width = 1000;
    int     height = 750;
    void    *mlx;
    void    *win;
    void    *image;
    double fragcoord_x = 300;
    double fragcoord_y = 300;
    int     *image_data;
    int     i,j,k;
    mlx = mlx_init();
    win = mlx_new_window(mlx, width, height, "RT");
    image = mlx_new_image(mlx,width, height);
    image_data = (int *)mlx_get_data_addr(image, &i, &j, &k);

    // double  u_x = fragcoord_x /width;
    // double  v_y = fragcoord_y /height;
    // printf("%f\n", v_y);
    // u_x -= 0.5;
    // v_y -= 0.5;
    // u_x *= width/height;
    // double ro_x = 0;
    // double ro_y = 0;
    // double ro_z = -2;
    // double rd_x = u_x - ro;
    // double rd_y = v_y - ro;
    // double rd_z = 0 - ro;
    // double p_x = 0;
    // double p_y = 0;
    // double p_z = 0;
    // double dist = dist_line(ro, rd, p);
    int x;
    x = 0;
    int p = x;
    int m = (width * height);
    while (p < m)
    {
            image_data[p] = 0xF0FF00;
            p++;
            x++;
           // mlx_pixel_put(mlx, win, x++,y , 0xFFFFFF);
    }
    mlx_put_image_to_window(mlx, win, image, 0,0);
    mlx_destroy_image(mlx, (char *)image);
    mlx_loop(mlx);
}