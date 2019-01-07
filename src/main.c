#include "../includes/RTv1.h"

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned long color(t_vec *uv)
{
	return (createRGB(/*uv->x * 255/uv->width*/0,uv->y * 255/uv->height, 0));
}

float	length_vec(t_vec *uv)
{
	return ((sqrt ((uv->ray.ray_direction_x * uv->ray.ray_direction_x) + (uv->ray.ray_direction_y * uv->ray.ray_direction_y) + (uv->ray.ray_direction_z * uv->ray.ray_direction_z))));
}

void	normalize_vec(t_vec *uv)
{
	//normalize by diving vector with magnitude of vector ||v|| = sqrt(x2 + y2 + z2)
	uv->ray.ray_direction_x /= length_vec(uv);
	uv->ray.ray_direction_y /= length_vec(uv);
	uv->ray.ray_direction_z /= length_vec(uv);

}

void	create_primary_ray(t_vec *uv)
{
	if (uv->width > uv->height)
	{

		/*(float)uv->x + 0.5) makes sure ray passes in the centre of pixel (assuming pixels are 1 unit by 1 unit),
			divide this by width to normalise it to screen (width,height) to fit and multiply by 2 and minus 1 so that 
			it stays between the 2x2 unit screen we imagined
			multiply by aspect ratio for rendered image to stay the same shape regardless  of screen width and height
			multiply by  FOV for zoom in and out*/
		uv->field_of_view = tan((uv->field_of_view_angle * M_PI/180)/2);
		float	aspect_ratio = ((float)uv->width) / ((float)uv->height);
		float	screen_x = (((((float)uv->x + 0.5)/ (float)uv->width) * 2.0 - 1.0) * aspect_ratio) * uv->field_of_view;
		float	screen_y = (1 - (((float)uv->y + 0.5)/ (float)uv->height) * 2.0) * uv->field_of_view;

		uv->ray.ray_direction_x = screen_x;
		uv->ray.ray_direction_y = screen_y;
		// all our primary rays go forward from "camera---screen----environment" that's why z = -1
		uv->ray.ray_direction_z = -1.0;
	}
	//vectors remain less than 1
	normalize_vec(uv);

}

float	dot_product_line_seg(t_vec *uv)
{
	//ray direction already has angle
	float a = (uv->ray.line_seg_x * uv->ray.ray_direction_x) + (uv->ray.line_seg_y * uv->ray.ray_direction_y) + (uv->ray.line_seg_z * uv->ray.ray_direction_z);
	return (a);

}

float	dot_product(t_vec *uv)
{
	float b = sqrt(uv->ray.line_seg_x * uv->ray.line_seg_x) + (uv->ray.line_seg_y * uv->ray.line_seg_y ) + (uv->ray.line_seg_z * uv->ray.line_seg_z );
	return (b);
}

void	is_intercect(t_vec *uv)
{
	/*create a line segment between the ray origin to center of sphere (x,y,z)
		adjacent side is primary ray from camera */
	uv->ray.line_seg_x = uv->sphere.center_x - uv->ray.ray_origin_x;
	uv->ray.line_seg_y = uv->sphere.center_y - uv->ray.ray_origin_y;
	uv->ray.line_seg_z = uv->sphere.center_z - uv->ray.ray_origin_z;
	uv->ray.adjacent_length = dot_product_line_seg(uv);
	//pythagoras for hypotenuse x2 + y2 + x2
	float pythagoras = dot_product(uv);
	//if opposite is bigger than raduis, then no intercept and vice versa
	uv->ray.opp_side = (pythagoras - (uv->ray.adjacent_length * uv->ray.adjacent_length));

}

void	ray_trace_init(t_vec *uv)
{
	uv->width = 1000;
	uv->height = 750;
    uv->mlx = mlx_init();
    uv->win = mlx_new_window(uv->mlx, uv->width, uv->height, "RT");
	//rendered scenes, must make input file for these
	uv->sphere.center_x = 0;
	uv->sphere.center_y = 0;
	uv->sphere.center_z = -5;
	uv->sphere.radius = 5;
	//primary rays so these can be altered to change cam position
	uv->ray.ray_origin_x = 0;
	uv->ray.ray_origin_y = 0;
	uv->ray.ray_origin_z = 0;
	uv->field_of_view_angle = 90;
	uv->y = 0;
	uv->sphere.rad_sqrt = (uv->sphere.radius);

}

void	render(t_vec *uv)
{
	uv->y = 0;
	while (uv->y < uv->height)
	{
		uv->x = 0;
		while (uv->x < uv->width)
		{
			//shoot primary ray from camera--------------"hit pixel"
			create_primary_ray(uv);
			is_intercect(uv);

			if (uv->ray.opp_side < uv->sphere.rad_sqrt)
			{
				mlx_pixel_put(uv->mlx,uv->win,uv->x,uv->y, color(uv));
				// image_data[uv->x] = 0xFFFFFF;
			}
			else
			{
				mlx_pixel_put(uv->mlx,uv->win,uv->x,uv->y, 0x000008);
				// image_data[uv->x] = 0x000000;
			}
			uv->x++;
		}
		uv->y++;
	}
}

int		exit_prog(void)
{
	exit (1);
}

int		keyhooks(int key, t_vec *uv)
{
	if (key == 53)
	{
		exit_prog();
	}
	if (key == 126)
	{
		uv->field_of_view_angle -= 2;
	}

	if (key == 125)
	{
		uv->field_of_view_angle += 2;
	}

	if (key == 123)
	{
		uv->sphere.center_x -= 1;
		uv->sphere.center_y -= 1;
	}
	if (key == 124)
	{
		uv->sphere.center_x += 1;
		uv->sphere.center_y += 1;
	}
	mlx_clear_window(uv->mlx, uv->win);
	render(uv);
	return (0);
}

int     main(void)
{
	t_vec	*uv;
	uv = (t_vec *)malloc(sizeof(t_vec));
	// int		image_height = uv->height;
	// int		image_width = uv->width;
    // void    *image;
    // int     *image_data;
    // int     i,j,k;
    // image = mlx_new_image(mlx,image_width, image_height);
    // image_data = (int *)mlx_get_data_addr(image, &i, &j, &k);
	ray_trace_init(uv);
	render(uv);
    // mlx_put_image_to_window(mlx, win, image, 0,0);
    // mlx_destroy_image(mlx, (char *)image);
	mlx_hook(uv->win,2,0, keyhooks, uv);
	mlx_hook(uv->win,17,0, exit_prog, uv);
    mlx_loop(uv->mlx);
}