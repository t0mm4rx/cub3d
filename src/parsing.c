#include "cub3d.h"

t_info  *parse(char *file)
{
    t_info  *res;
    int     fd;
    int     status;
    char    *line;

    fd = open(file, O_RDONLY);
    res = ft_calloc(sizeof(t_info), 1);
    if (fd < 0)
      parsing_error(res);
    while ((status = get_next_line(fd, &line)) > 0)
    {
      handle_line(line, res);
      free(line);
    }
    handle_line(line, res);
    free(line);
    if (!check_parsing(res))
      parsing_error(res);
    return (res);
}

void     handle_line(char *line, t_info *info)
{
  (void)info;
  if (*line == '\0')
    return ;
  if (!ft_isdigit(*line) && info->map_started)
    parsing_error(info);
  if (ft_isdigit(*line))
  {
    info->map_started = 1;
    handle_line_map(line, info);
  }
  else
    handle_line_info(line, info);
}

int       check_parsing(t_info *info)
{
  if (info->width <= 0 || info->height <= 0)
    return (0);
  if (!info->texture_n || !info->texture_s || !info->texture_w
    || !info->texture_e || !info->texture_sprite)
    return (0);
  return (1);
}

void      parsing_error(t_info *info)
{
  free(info);
  write(1, "Error\n", 6);
  exit(0);
}
