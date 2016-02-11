#ifndef FRACTOL_H
#define FRACTOL_H
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
# define WIDTH 800
# define HEIGHT 600

typedef struct                                                  s_img
{
  void                    *mlx;
  void                    *win;
  unsigned long   img_color;
  char                    *data;
  void                    *img_ptr;
  int                             sizeline;
  int                             bpp;
  int                             x;
  int                             y;
  int                             endian;
  void                    *mlx_ptr;
}                                                                               t_img;


typedef struct                                                  s_temp
{
  int x1;
  int x2;
  int y1;
  int y2;
  int val1;
  int val2;
  int color;
}                                                                               t_temp;

typedef struct                                                  s_line
{
  int dx;
  int dy;
  int i;
  int xinc;
  int yinc;
  int cumul;
  int x;
  int y;
}                                                                               t_line;

typedef struct s_spec
{
  double x;
  double y;
  double x1;
  double x2;
  double y1;
  double y2;
  double mousex;
  double mousey;
  double zoom;
}    t_spec;



typedef struct s_julia
{
  int x;
  int y;
  int i;
  double zoom_x;
  double zoom_y;
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  double cx;
  double cy;
  double x1;
  double x2;
  double y1;
  double y2;
  double xy;
  double ite;
}                      t_julia;

typedef struct s_mandel
{
  int x;
  int y;
  int i;
  double zoom_x;
  double zoom_y;
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  double cx;
  double cy;
  double x1;
  double x2;
  double y1;
  double y2;
  double xy;
  double ite;
}                      t_mandel;

typedef struct s_mystruct
{
  void *mlx;
  void *win;
  char                    ***coord;
  int                             i;
  int                             maxline;
  double                             zoom;
  t_img                   *img;
  t_spec *spec;
  int ite;
  float xv;
  float yv;
  int other;
  int etat;
  double jv1;
  double jv2;
  double zo;
  double mx;
  double my;
  float offx;
  float offy;
  float mxite;
  float vale;
  float ratio;
  t_julia *j;
  t_mandel *mandel;
}               t_struct;
void mymandel(t_struct *mystruct);
void myjulia(t_struct *mystruct);
void            ffjulia(t_img *myimg, t_spec *spec);
void the_mand(t_img *myimg, int zo);
void lets_try(t_img *myimg, double zo, double v1, double v2, double mx, double my, float ite);
void draw_julia(t_img *myimg);
void    my_pixel_put_to_image(t_img *myimg, int x, int y, int color);
void draw_fractal(t_img *myimg, float x, float y, float h, int ite, int other, int zooma, float v1, float v2);
int motion(int x, int y, t_struct *mystruct);
int ft_zoom(int mouse, int x, int y, t_struct *mystruct);
void julia_init(t_struct *mystruct);
int ft_zoom_mandel(int mouse, int x, int y, t_struct *mystruct);
void mandel_init(t_struct *mystruct);

#endif
