#include "../includes/RTv1.h"

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned long color(t_vec *uv)
{
	return (createRGB(uv->x/2950,uv->y/2950,0));
}

int     main(void)
{
	t_vec	*uv;
	uv = (t_vec *)malloc(sizeof(t_vec));
	int		image_height = uv->height;
	int		image_width = uv->width;
    void    *mlx;
    void    *win;
    void    *image;
    int     *image_data;
    int     i,j,k;

	uv->width = 1000;
	uv->height = 750;
	uv->sphere.center_x = 0;
	uv->sphere.center_y = 0;
	uv->sphere.center_z = -5;
	uv->sphere.radius = 1;

    mlx = mlx_init();
    win = mlx_new_window(mlx, uv->width, uv->height, "RT");
    image = mlx_new_image(mlx,image_width, image_height);
    image_data = (int *)mlx_get_data_addr(image, &i, &j, &k);
	uv->y = 0;
	uv->sphere.radius = 2;
	while (uv->y < uv->height)
	{
		uv->x = 0;
		while (uv->x < uv->width)
		{
			//shoot ray
			create_primary_ray(uv->x, uv->y, uv);
			if (uv->ray.opp_side < uv->sphere.radius)
			{
				image_data[uv->x] = 0xFFFFFF;
			}
			else
			{
				image_data[uv->x] = 0x000000;
			}
			uv->x++;
		}
		uv->y++;
	}
    
    mlx_put_image_to_window(mlx, win, image, 0,0);
    mlx_destroy_image(mlx, (char *)image);
    mlx_loop(mlx);
}