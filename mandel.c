#include "fractol.h"


int motion_mandel(int x, int y, t_struct *mystruct)
{
  if(mystruct->etat == 1)
    {
      if(x <= WIDTH && x >= 0 && y<= HEIGHT && y >= 0)
	{
	  mystruct->mandel->x1 = x * (mystruct->mandel->xmax - mystruct->mandel->xmin) / WIDTH + mystruct->mandel->xmin;
	  mystruct->mandel->y1 = y * (mystruct->mandel->ymax - mystruct->mandel->ymin) / HEIGHT + mystruct->mandel->ymin;
	  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
	  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
	  mymandel(mystruct);
	  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
	}
    }
  return (0);
}

int ft_zoom_mandel(int mouse, int x, int y, t_struct *mystruct)
{
  double x_zoom;
  double y_zoom;
  double i;

  if (mouse == 1)
    i = 0.8;
  else
    i = 1.2;
  x_zoom = x * (mystruct->mandel->xmax - mystruct->mandel->xmin) / WIDTH + mystruct->mandel->xmin;
  y_zoom = y * (mystruct->mandel->ymax - mystruct->mandel->ymin) / HEIGHT + mystruct->mandel->ymin;
  mystruct->mandel->xmin = (mystruct->mandel->xmin - x_zoom) * i + x_zoom;
  mystruct->mandel->xmax = (mystruct->mandel->xmax - x_zoom) * i + x_zoom;//faute
  mystruct->mandel->ymin = (mystruct->mandel->ymin - y_zoom) * i + y_zoom;
  mystruct->mandel->ymax = (mystruct->mandel->ymax - y_zoom) * i + y_zoom;
  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
  mymandel(mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  return (0);
}

static void mandel_give(t_mandel *mandel)
{
  mandel->xy = mandel->x1 * mandel->y1;
  mandel->x2 = mandel->x1 * mandel->x1;
  mandel->y2 = mandel->y1 * mandel->y1;
  mandel->x1 = mandel->x2 - mandel->y2 + mandel->cx;
  mandel->y1 = mandel->xy + mandel->xy + mandel->cy;
  mandel->i++;
}

void mandel_init(t_struct *mystruct)
{
  mystruct->mandel->x = 0;
  mystruct->mandel->y = 0;
  mystruct->mandel->zoom_x = WIDTH;
  mystruct->mandel->zoom_y = HEIGHT;
  mystruct->mandel->xmin = -2.1;
  mystruct->mandel->xmax = 0.6;
  mystruct->mandel->ymin = -1.2;
  mystruct->mandel->ymax = 1.2;
  mystruct->mandel->ite = 50;
  mymandel(mystruct);
}

static int ok_draw2(int x, int y)
{
  if(x < WIDTH && y < HEIGHT && x > 0 && y > 0)
    return (1);
  return (0);
}

void mymandel(t_struct *mystruct)
{
  double thex1;
  double they1;

  if(mystruct->etat == 1)
    {
  thex1 = mystruct->mandel->x1;
  they1 = mystruct->mandel->y1;
    }
  else
    {
      thex1 = 0;
      they1 = 0;
    }
  mystruct->mandel->x = 0;
  while (mystruct->mandel->x < mystruct->mandel->zoom_x)
    {
      mystruct->mandel->y = 0;
      while (mystruct->mandel->y < mystruct->mandel->zoom_y)
        {
          mystruct->mandel->cx = mystruct->mandel->xmin + (mystruct->mandel->xmax - mystruct->mandel->xmin) * mystruct->mandel->x / mystruct->mandel->zoom_x;
          mystruct->mandel->cy = mystruct->mandel->ymin + (mystruct->mandel->ymax - mystruct->mandel->ymin) * mystruct->mandel->y / mystruct->mandel->zoom_y;
          mystruct->mandel->x1 = thex1;
	  mystruct->mandel->y1 = they1;
	  mystruct->mandel->x2 = 0;
          mystruct->mandel->y2 = 0;
          mystruct->mandel->i = 0;
          while ((mystruct->mandel->x2 + mystruct->mandel->y2 <= 4) && (mystruct->mandel->i < mystruct->ite))
            {
              mandel_give(mystruct->mandel);
            }
          if(ok_draw2(mystruct->mandel->x , mystruct->mandel->y))
            my_pixel_put_to_image(mystruct->img, mystruct->mandel->x , mystruct->mandel->y, RGB(0,0, mystruct->mandel->i*210/mystruct->ite));
          mystruct->mandel->y++;
        }
      mystruct->mandel->x++;
    }
}

