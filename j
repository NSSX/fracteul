  x_zoom = x * (mystruct->mandel->xmax - mystruct->mandel->xmin) / WIDTH + mystruct->mandel->xmin;
  y_zoom = y * (mystruct->mandel->ymax - mystruct->mandel->ymin) / HEIGHT + mystruct->mandel->ymin;
  mystruct->mandel->xmin = (mystruct->mandel->xmin - x_zoom) * i + x_zoom;
  mystruct->mandel->xmax = (mystruct->mandel->xmax - x_zoom) * i + x_zoom;//faute
  mystruct->mandel->ymin = (mystruct->mandel->ymin - y_zoom) * i + y_zoom;
  mystruct->mandel->ymax = (mystruct->mandel->ymax - y_zoom) * i + y_zoom;
  mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
  mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  mystruct->mandel->x = 0;
  mystruct->mandel->y = 0;
  mystruct->mandel->zoom_x = WIDTH;
  mystruct->mandel->zoom_y = HEIGHT;
  mystruct->mandel->xmin = -2;
  mystruct->mandel->xmax = 2;
  mystruct->mandel->ymin = -2;
  mystruct->mandel->ymax = 2;
  mystruct->mandel->ite = 50;
  mystruct->mandel->x = 0;
  while (mystruct->mandel->x < mystruct->mandel->zoom_x)
      mystruct->mandel->y = 0;
      while (mystruct->mandel->y < mystruct->mandel->zoom_y)
          mystruct->mandel->cx = mystruct->mandel->xmin + (mystruct->mandel->xmax - mystruct->mandel->xmin) * mystruct->mandel->x / mystruct->mandel->zoom_x;
          mystruct->mandel->cy = mystruct->mandel->ymin + (mystruct->mandel->ymax - mystruct->mandel->ymin) * mystruct->mandel->y / mystruct->mandel->zoom_y;
          mystruct->mandel->x1 = 0;
	  mystruct->mandel->y1 = 0;
	  mystruct->mandel->x2 = 0;
          mystruct->mandel->y2 = 0;
          mystruct->mandel->i = 0;
          while ((mystruct->mandel->x2 + mystruct->mandel->y2 <= 4) && (mystruct->mandel->i < mystruct->mandel->ite))
              mandel_give(mystruct->mandel);
          if(ok_draw2(mystruct->mandel->x , mystruct->mandel->y))
            my_pixel_put_to_image(mystruct->img, mystruct->mandel->x , mystruct->mandel->y, RGB(mystruct->mandel->i*210/mystruct->j->ite,0, mystruct->mandel->i*210/mystruct->mandel->ite));
          mystruct->mandel->y++;
      mystruct->mandel->x++;
