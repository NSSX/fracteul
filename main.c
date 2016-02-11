#include "fractol.h"

void ft_putchar(char c)
{
  write(1, &c, 1);
}

t_line  *give_line(float xi, float yi, float xf, float yf)
{
  t_line *line;

  line = (t_line *)malloc(sizeof(t_line) * 12);
  line->x = xi;
  line->y = yi;
  line->dx = xf - xi;
  line->dy = yf - yi;
  line->xinc = (line->dx > 0) ? 1 : -1;
  line->yinc = (line->dy > 0) ? 1 : -1;
  line->dx = abs(line->dx);
  line->dy = abs(line->dy);
  return (line);
}

t_line  *first_while(t_line *line)
{
  line->x += line->xinc;
  line->cumul += line->dy;
  if (line->cumul >= line->dx)
    {
      line->cumul -= line->dx;
      line->y += line->yinc;
    }
  return (line);
}

t_line  *second_while(t_line *line)
{
  line->y += line->yinc;
  line->cumul += line->dx;
  if (line->cumul >= line->dy)
    {
      line->cumul -= line->dy;
      line->x += line->xinc;
    }
  return (line);
}

t_line  *norme_line(t_line *line)
{
  line->cumul = line->dy / 2;
  line->i = 1;
  return (line);
}

void    draw_line_on_img(t_img *myimg, t_temp *temp, int color)
{
  t_line *line;

  line = give_line(temp->x1, temp->y1, temp->x2, temp->y2);
  my_pixel_put_to_image(myimg, line->x, line->y, color);
  if (line->dx > line->dy)
    {
      line->cumul = line->dx / 2;
      line->i = 1;
      while (line->i <= line->dx)
	{
	  line = first_while(line);
	  my_pixel_put_to_image(myimg, line->x, line->y, color);
	  line->i++;
	}
    }
  else
    {
      line = norme_line(line);
      while (line->i <= line->dy)
	{
	  line = second_while(line);
	  my_pixel_put_to_image(myimg, line->x, line->y, color);
	  line->i++;
	}
    }
}


int             event_mlx(int keycode, t_struct *mystruct)
{
  
  if (keycode == 53)
    exit(1);
  return (0);
}

int mouse_mlx(int button, int x, int y, t_struct *mystruct)
{
    if(button == 1)
    {   
     
    }
  if(button == 2)
    {
     
    }
  if(button == 4)
    {
     
      }
    if(button == 5)
    {
  
    }
  
  return (0);
}

int motion(int x, int y, t_struct *mystruct)
{
  /*
      static int xp;
  static int yp;
  static float xv;
  static float yv;
  static int other;
  static float v1;
  static float v2;

  if(!v1)
    v1 = 0;
  if(!v2)
    v2 = 0;
  if(!other)
    other = 2;
  if(!xv)
    xv = 0.5;
  if(!yv)
    yv = 0.1;
  if(!xp)
    xp = x;
  if(!yp)
    yp = y;
  if(x < xp)
    {
      v1 -= 0.030;
      mystruct->jv1 -= 0.030;
    }
  else if(x > xp)
    {
      v1 += 0.030;
      mystruct->jv1 += 0.030;
    }
  if(y < yp)
    {
      v2 -= 0.030;
      mystruct->jv2 -= 0.030;
    }
  else if(y > yp)
    {
      mystruct->jv2 += 0.030;
      v2 += 0.030;
    }
  xp = x;
  yp = y;
  if(mystruct->etat == 1)
    {
  mystruct->xv = xv;
  mystruct->yv = yv;
  mystruct->other = other;
  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, 500, 500);
  draw_fractal(mystruct->img, mystruct->xv, mystruct->yv, 1, mystruct->ite, mystruct->other,100,v1,v2);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
    }
  else
    {
      mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
      mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, 500, 500);
      lets_try(mystruct->img, mystruct->zoom, mystruct->jv1, mystruct->jv2, mystruct->mx, mystruct->my, mystruct->mxite);     
      mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
      }*/
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

void color_img(t_img *myimg)
{
  int i;
  int j;
 
  i = 0;
  j = 0;
  while(i < 800)
    {
      while(j < 800)
	{
	  my_pixel_put_to_image(myimg, j, i, 0x0000FF);
	  j++;
	}
      j = 0;
      i++;
    }
}

int ok_draw(int x, int y)
{
  if(x < 500 && y < 500 && x > 0 && y > 0)
    return (1);
  return (0);
}

void draw_julia(t_img *myimg)
{
  float x1 = -1.5;
  float x2 = 1.5;
  float y1 = -1.2;
  float y2 = 1.2;
  float zoom = 400;
  float max_ite = 50;
  float image_x = (x2 - x1) * zoom;
  float image_y = (y2 - y1) * zoom;

  for(int x = 0; x < image_x; x++)
    {
      for(int y = 0; y < image_y; y++)
        {
          float c_r = 0.285;//0.285;
          float c_i = 0.01;
          float z_r = x / zoom + x1;
          float z_i = y / zoom + y1;
          float i = 0;
          do
            {
              float tmp = z_r;
              z_r = z_r * z_r - z_i * z_i + c_r;
              z_i = 2*z_i*tmp + c_i;
              i = i + 1;
            }while((z_r * z_r + z_i * z_i) < 4 && i < max_ite);
          if(i == max_ite)
            {
              if(ok_draw(x,y) == 1)
                my_pixel_put_to_image(myimg, x, y, 0x000000);
            }
          else
            {
              if(ok_draw(x,y) == 1)
                my_pixel_put_to_image(myimg, x, y, RGB(0, 0, i*255/max_ite));
            }
        }
    }

}


void draw_fractal(t_img *myimg, float mx, float my, float h, int ite, int other, int zooma, float v1, float v2)
{
  // -5 a 0
  float x1 = mx - h;
  float x2 = mx + h;
  // -5 a 0
  float y1 = my - h;
  float y2 = my + h;
  float zoom = zooma;
  float max_ite = 50;//detaille
  float image_x = (x2 - x1) * zoom;
  float image_y = (y2 - y1) * zoom;


  for(int x = 0; x < image_x; x++)
    {
      for(int y = 0; y < image_y; y++)
	{
	  float c_r = x / zoom + x1;
	  float c_i = y / zoom + y1;
	  float z_r = v1;//0;//FAIT VARIER
	  float z_i = v2;//FAIT VARIER
	  float i = 0;
	  do
	    {	      
	      float tmp = z_r; 
	      z_r = z_r * z_r - z_i * z_i + c_r;
	      z_i = 2*z_i*tmp + c_i;
	      i = i + 1;
	    }while((z_r * z_r + z_i * z_i) < 4 && i < max_ite);
	  if(i == max_ite)
	    {
	      if(ok_draw(x,y) == 1)
		my_pixel_put_to_image(myimg, x, y, 0x000000);
	    }
	  else
	    {
	      if(ok_draw(x,y) == 1)
		my_pixel_put_to_image(myimg, x, y, RGB(i*255/max_ite,0, i*255/max_ite));
	    }
	}
    }
}
void ligne(t_img *myimg)
{
  int x;
  int y;

  x = 0;
  y = 0; 
  while(x < 500)
    {
      my_pixel_put_to_image(myimg, x, 250, 0x00FFFF);
      x++;
    }
  while(y < 500)
    {
      my_pixel_put_to_image(myimg, 250, y, 0x00FFFF);
      y++;
    }
}

int             main(int argc, char **argv)
{
  t_struct *mystruct;
  t_img *myimg;
  t_temp *temp;
  t_julia *jul;
  t_mandel *m;

  m = (t_mandel *)malloc(sizeof(t_mandel) * 20);
  jul = (t_julia *)malloc(sizeof(t_julia) * 20);
  temp = (t_temp *)malloc(sizeof(t_temp) * 20);
  myimg = (t_img *)malloc(sizeof(t_img) * 20);
  mystruct = (t_struct *)malloc(sizeof(t_struct) * 20);
  mystruct->mlx = mlx_init();
  mystruct->win = mlx_new_window(mystruct->mlx, WIDTH, HEIGHT, "42");
  myimg->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);  
  mystruct->j = jul;
  mystruct->mandel = m;
  mystruct->img = myimg;
  // julia_init(mystruct); 
  mandel_init(mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, myimg->img_ptr, 0, 0);
  mlx_key_hook(mystruct->win, event_mlx, mystruct);
  mlx_mouse_hook (mystruct->win, ft_zoom_mandel, mystruct);
  mlx_hook(mystruct->win, 6, (1L<<6),motion, mystruct);
  mlx_loop(mystruct->mlx);
  return (0);
}
