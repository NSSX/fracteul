#include "fractol.h"

int motion_julia(int x, int y, t_struct *mystruct)
{
  if(mystruct->etat == 1)
    {
      if(x <= WIDTH && x >= 0 && y<= HEIGHT && y >= 0)
	{
	  mystruct->j->cx = x * (mystruct->j->xmax - mystruct->j->xmin) / WIDTH + mystruct->j->xmin;
	  mystruct->j->cy = y * (mystruct->j->ymax - mystruct->j->ymin) / HEIGHT + mystruct->j->ymin;
	  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
	  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
	  myjulia(mystruct);
	  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
	}
    }
  return (0);
}


int ft_zoom(int mouse, int x, int y, t_struct *mystruct)
{
  double x_zoom;
  double y_zoom;
  double i;

  if (mouse == 1)
    i = 0.8;
  else
    i = 1.2;
  x_zoom = x * (mystruct->j->xmax - mystruct->j->xmin) / WIDTH + mystruct->j->xmin;
  y_zoom = y * (mystruct->j->ymax - mystruct->j->ymin) / HEIGHT + mystruct->j->ymin;
  mystruct->j->xmin = (mystruct->j->xmin - x_zoom) * i + x_zoom;
  mystruct->j->xmax = (mystruct->j->xmax - x_zoom) * i + x_zoom;
  mystruct->j->ymin = (mystruct->j->ymin - y_zoom) * i + y_zoom;
  mystruct->j->ymax = (mystruct->j->ymax - y_zoom) * i + y_zoom;
  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
  myjulia(mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  return (0);
}

static void julia_give(t_julia *j)
{
  j->xy = j->x1 * j->y1;
  j->x2 = j->x1 * j->x1;
  j->y2 = j->y1 * j->y1;
  j->x1 = j->x2 - j->y2 + j->cx;
  j->y1 = j->xy + j->xy + j->cy;
  j->i++;
}


void julia_init(t_struct *mystruct)
{
  mystruct->j->zoom_x = WIDTH;
  mystruct->j->zoom_y = HEIGHT;
  mystruct->j->xmin = -2;
  mystruct->j->xmax = 2;
  mystruct->j->ymin = -2;
  mystruct->j->ymax = 2;
  mystruct->j->x = 0;
  mystruct->j->y = 0;
  mystruct->j->ite = 50;
  mystruct->j->cx = -0.7;
  mystruct->j->cy = 0.2;
  myjulia(mystruct);
}

static int ok_draw2(int x, int y)
{
  if(x < WIDTH && y < HEIGHT && x > 0 && y > 0)
    return (1);
  return (0);
}

void myjulia(t_struct *mystruct)
{
  mystruct->j->x = 0;
  while (mystruct->j->x < mystruct->j->zoom_x)
    {
      mystruct->j->y = 0;
      while (mystruct->j->y < mystruct->j->zoom_y)
        {
          mystruct->j->x1 = mystruct->j->xmin + (mystruct->j->xmax - mystruct->j->xmin) * mystruct->j->x / mystruct->j->zoom_x;
          mystruct->j->y1 = mystruct->j->ymin + (mystruct->j->ymax - mystruct->j->ymin) * mystruct->j->y / mystruct->j->zoom_y;
          mystruct->j->x2 = 0;
          mystruct->j->y2 = 0;
          mystruct->j->i = 0;
          while ((mystruct->j->x2 + mystruct->j->y2 <= 4) && (mystruct->j->i < mystruct->ite))
            {
              julia_give(mystruct->j);
            }
          if(ok_draw2(mystruct->j->x , mystruct->j->y))
            my_pixel_put_to_image(mystruct->img, mystruct->j->x , mystruct->j->y, RGB(mystruct->j->i*210/mystruct->ite,0, mystruct->j->i*210/mystruct->ite));
          mystruct->j->y++;
        }
      mystruct->j->x++;
    }
}
