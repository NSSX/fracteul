#include "fractol.h"

int motion_burning(int x, int y, t_struct *mystruct)
{ 
  if(mystruct->etat == 1)
    {
      if(x <= WIDTH && x >= 0 && y<= HEIGHT && y >= 0)
	{
	  mystruct->burn->x1 = x * (mystruct->burn->xmax - mystruct->burn->xmin) / WIDTH + mystruct->burn->xmin;
	  mystruct->burn->y1 = y * (mystruct->burn->ymax - mystruct->burn->ymin) / HEIGHT + mystruct->burn->ymin;
	  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
	  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
	  myburn(mystruct);
	  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
	}
    }
  return (0);
}

int ft_zoom_burning(int mouse, int x, int y, t_struct *mystruct)
{
  double x_zoom;
  double y_zoom;
  double i;

  if (mouse == 1)
    i = 0.8;
  else
    i = 1.2;
  x_zoom = x * (mystruct->burn->xmax - mystruct->burn->xmin) / WIDTH + mystruct->burn->xmin;
  y_zoom = y * (mystruct->burn->ymax - mystruct->burn->ymin) / HEIGHT + mystruct->burn->ymin;
  mystruct->burn->xmin = (mystruct->burn->xmin - x_zoom) * i + x_zoom;
  mystruct->burn->xmax = (mystruct->burn->xmax - x_zoom) * i + x_zoom;
  mystruct->burn->ymin = (mystruct->burn->ymin - y_zoom) * i + y_zoom;
  mystruct->burn->ymax = (mystruct->burn->ymax - y_zoom) * i + y_zoom;
  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
  myburn(mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  return (0);
}

static void burn_give(t_burn *burn)
{
  burn->xy = fabs(burn->x1 * burn->y1);
  burn->x2 = burn->x1 * burn->x1;
  burn->y2 = burn->y1 * burn->y1;
  burn->x1 = burn->x2 - burn->y2 + burn->cx;
  burn->y1 = burn->xy + burn->xy + burn->cy;
  burn->i++;
}

void burn_init(t_struct *mystruct)
{
  mystruct->burn->x = 0;
  mystruct->burn->y = 0;
  mystruct->burn->zoom_x = WIDTH;
  mystruct->burn->zoom_y = HEIGHT;
  mystruct->burn->xmin = -2.1;
  mystruct->burn->xmax = 0.6;
  mystruct->burn->ymin = -1.2;
  mystruct->burn->ymax = 1.2;
  mystruct->burn->ite = 50;
  myburn(mystruct);
}

static int ok_draw2(int x, int y)
{
  if(x < WIDTH && y < HEIGHT && x > 0 && y > 0)
    return (1);
  return (0);
}

void myburn(t_struct *mystruct)
{
  double thex1;
  double they1;
  if(mystruct->etat == 1)
    {
      thex1 = mystruct->burn->x1;
      they1 = mystruct->burn->y1;
    }
  else
    {
      thex1 = 0;
      they1 = 0;
    }
  mystruct->burn->x = 0;
  while (mystruct->burn->x < mystruct->burn->zoom_x)
    {
      mystruct->burn->y = 0;
      while (mystruct->burn->y < mystruct->burn->zoom_y)
        {
          mystruct->burn->cx = mystruct->burn->xmin + (mystruct->burn->xmax - mystruct->burn->xmin) * mystruct->burn->x / mystruct->burn->zoom_x;
          mystruct->burn->cy = mystruct->burn->ymin + (mystruct->burn->ymax - mystruct->burn->ymin) * mystruct->burn->y / mystruct->burn->zoom_y;
          mystruct->burn->x1 = thex1;
          mystruct->burn->y1 = they1;
          mystruct->burn->x2 = 0;
          mystruct->burn->y2 = 0;
          mystruct->burn->i = 0;
          while ((mystruct->burn->x2 + mystruct->burn->y2 <= 4) && (mystruct->burn->i < mystruct->ite))
            {
              burn_give(mystruct->burn);
            }
          if(ok_draw2(mystruct->burn->x , mystruct->burn->y))
            my_pixel_put_to_image(mystruct->img, mystruct->burn->x , mystruct->burn->y, RGB(0,0, mystruct->burn->i*210/mystruct->ite));
          mystruct->burn->y++;
        }
      mystruct->burn->x++;
    }
}
