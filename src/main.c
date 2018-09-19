#include "../includes/RTv1.h"

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned long color(t_vec *uv)
{
	return (createRGB(uv->x/2950,uv->y/2950,0));
}

void	create_primary_ray(t_vec *uv)
{
	if (uv->width > uv->height)
	{
		uv->field_of_view = 60.0;
		float	aspect_ratio = ((float)uv->width) / ((float)uv->height);
		float	screen_x = (((((float)uv->x + 0.5)/ (float)uv->width) * 2.0 - 1.0) * aspect_ratio) * uv->field_of_view;
		float	screen_y = (1 - (((float)uv->y + 0.5)/ (float)uv->height) * 2.0) * uv->field_of_view;

		uv->ray.ray_direction_x = screen_x;
		uv->ray.ray_direction_y = screen_y;
		uv->ray.ray_direction_z = -1.0;
	}

}

float	dot_product_line_seg(t_vec *uv)
{
	float a = (uv->ray.line_seg_x * uv->ray.ray_direction_x) + (uv->ray.line_seg_y * uv->ray.ray_direction_y) + (uv->ray.line_seg_z * uv->ray.ray_direction_z);
	return (a);

}

float	dot_product(t_vec *uv)
{
	float b = (uv->ray.line_seg_x * uv->ray.line_seg_x) + (uv->ray.line_seg_y * uv->ray.line_seg_y ) + (uv->ray.line_seg_z * uv->ray.line_seg_z );
	return (b);
}

void	is_intercect(t_vec *uv)
{
	uv->ray.line_seg_x = uv->sphere.center_x - uv->ray.ray_origin_x;
	uv->ray.line_seg_y = uv->sphere.center_y - uv->ray.ray_origin_y;
	uv->ray.line_seg_z = uv->sphere.center_z - uv->ray.ray_origin_z;
	float	adjacent_length;
	adjacent_length = dot_product_line_seg(uv);
	float pythagoras = dot_product(uv);
	uv->ray.opp_side = pythagoras - (adjacent_length * adjacent_length);

}

int     main(void)
{
	t_vec	*uv;
	uv = (t_vec *)malloc(sizeof(t_vec));
	// int		image_height = uv->height;
	// int		image_width = uv->width;
    void    *mlx;
    void    *win;
    // void    *image;
    // int     *image_data;
    // int     i,j,k;

	uv->width = 1000;
	uv->height = 750;
	uv->sphere.center_x = 0;
	uv->sphere.center_y = 0;
	uv->sphere.center_z = -5;
	uv->sphere.radius = 1;
	uv->ray.ray_origin_x = 0;
	uv->ray.ray_origin_y = 0;
	uv->ray.ray_origin_z = 0;

    mlx = mlx_init();
    win = mlx_new_window(mlx, uv->width, uv->height, "RT");
    // image = mlx_new_image(mlx,image_width, image_height);
    // image_data = (int *)mlx_get_data_addr(image, &i, &j, &k);
	uv->y = 0;
	uv->sphere.radius = 2;
	while (uv->y < uv->height)
	{
		uv->x = 0;
		while (uv->x < uv->width)
		{
			//shoot ray
			mlx_pixel_put(mlx,win,0,0, 0xF00000);
			create_primary_ray(uv);
			is_intercect(uv);
			if (uv->ray.opp_side < (uv->sphere.radius * uv->sphere.radius))
			{
				mlx_pixel_put(mlx,win,uv->x,uv->y, 0xFF0FFF);
				// image_data[uv->x] = 0xFFFFFF;
			}
			else
			{
				mlx_pixel_put(mlx,win,uv->x,uv->y, 0x0000FF);
				// image_data[uv->x] = 0x000000;
			}
			uv->x++;
		}
		uv->y++;
	}
    // mlx_put_image_to_window(mlx, win, image, 0,0);
    // mlx_destroy_image(mlx, (char *)image);
    mlx_loop(mlx);
}