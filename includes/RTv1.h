#ifndef RTV1_H
#define RTV1_H
#include "/Users/kwezimayikana/Desktop/minilibx/mlx.h"
//#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct			s_sphere
{
	float radius;
	float center_x;
	float center_y;
	float center_z;
	float rad_sqrt;
	float dist_to_int;
	float near_intercept;
	float far_intercept;
	float thickness;

}						t_sphere;

typedef struct			s_ray
{
	float opp_side;
	float ray_origin_x;
	float ray_origin_y;
	float ray_origin_z;
	float ray_direction_x;
	float ray_direction_y;
	float ray_direction_z;
	float	line_seg_x;
	float	line_seg_y;
	float	line_seg_z;

}						t_ray;

typedef struct			s_vec
{
	unsigned int		y;
	unsigned int		x;
	double				z;
	unsigned int		height;
	unsigned int		width;
	float				field_of_view;
	float				field_of_view_angle;
	float				light_pos;
	float				light;

    void    *mlx;
    void    *win;
	struct	s_sphere 	sphere;
	struct	s_ray 		ray;
}						t_vec;

#endif
