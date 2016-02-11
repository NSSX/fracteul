#include "fractol.h"

int             event_mlx(int keycode, t_struct *mystruct)
{

  if (keycode == 53)
    exit(1);
  if(keycode == 42)
    {
      if (mystruct->etat == 1)
	{
	  mystruct->etat = 0;
	}
      else
	mystruct->etat = 1;
    }
  if(keycode == 69)
    {
      mystruct->ite += 40;
    }
  if(keycode == 78)
    {
      mystruct->ite -= 40;
    }
  return (0);
}

void    my_pixel_put_to_image(t_img *myimg, int x, int y, int color)
{
  int                             i;
  unsigned char   color1;
  unsigned char   color2;
  unsigned char   color3;

  myimg->data = mlx_get_data_addr(myimg->img_ptr,
                                  &myimg->bpp, &myimg->sizeline, &myimg->endian);
  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8] = color % 256;
  color /= 256;
  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 1] = color % 256;
  color /= 256;
  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 2] = color % 256;
}

void error_arg(void)
{
  ft_putstr("Choix de Fractale : /fractol\n");
  ft_putstr("                             Julia\n");
  ft_putstr("                             Mandel\n");
  ft_putstr("                             Burning\n");
}

int             main(int argc, char **argv)
{
  t_struct *mystruct;
  t_img *myimg;
  t_temp *temp;
  t_julia *jul;
  t_mandel *m;
  t_burn *b;


  if(argc != 2)
    {
      error_arg();
      return (0);
    }
  b = (t_burn *)malloc(sizeof(t_burn) * 1);
  m = (t_mandel *)malloc(sizeof(t_mandel) * 1);
  jul = (t_julia *)malloc(sizeof(t_julia) * 1);
  temp = (t_temp *)malloc(sizeof(t_temp) * 1);
  myimg = (t_img *)malloc(sizeof(t_img) * 1);
  mystruct = (t_struct *)malloc(sizeof(t_struct) * 1);
  mystruct->mlx = mlx_init();
  mystruct->win = mlx_new_window(mystruct->mlx, WIDTH, HEIGHT, "42");
  myimg->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
  mystruct->j = jul;
  mystruct->mandel = m;
  mystruct->burn = b;
  mystruct->img = myimg;
  mystruct->etat = 0;
  mystruct->ite = 50; 
 if(ft_strequ(argv[1], "Julia") == 1)
    {
      julia_init(mystruct);
      mlx_mouse_hook (mystruct->win, ft_zoom, mystruct);
      mlx_hook(mystruct->win, 6, (1L<<6),motion_julia, mystruct);
    }
  else if(ft_strequ(argv[1],"Mandel") == 1)
    {
      mandel_init(mystruct);
      mlx_mouse_hook (mystruct->win, ft_zoom_mandel, mystruct);
      mlx_hook(mystruct->win, 6, (1L<<6), motion_mandel, mystruct);
    }
  else if(ft_strequ(argv[1],"Burning") == 1)
    {
      burn_init(mystruct);
      mlx_mouse_hook (mystruct->win, ft_zoom_burning, mystruct);
      mlx_hook(mystruct->win, 6, (1L<<6),motion_burning, mystruct);
    }
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, myimg->img_ptr, 0, 0);
  mlx_key_hook(mystruct->win, event_mlx, mystruct);
  mlx_loop(mystruct->mlx);
  return (0);
}
