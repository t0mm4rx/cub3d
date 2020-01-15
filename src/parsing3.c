#include "cub3d.h"

static void destroy_node(void *content)
{
  free(content);
}

static int  check_line_ones(char *line)
{
  int i;

  i = 0;
  if (line[i++] != '1')
    return (0);
  while (line[i])
  {
    if (line[i] != ' ' && line[i] != '1')
      return (0);
    i++;
  }
  return (1);
}

void         destroy_info(t_info *info)
{
  if (info && info->map_tmp)
    ft_lstclear(&info->map_tmp, &destroy_node);
  free(info);
}

int           check_map(t_info *info)
{
  unsigned int  target;
  t_list        *ptr;

  ptr = info->map_tmp;
  target = ft_strlen(ptr->content);
  if (!check_line_ones(ptr->content))
    return (0);
  ptr = ptr->next;
  while (ptr)
  {
    if (ft_strlen(ptr->content) != target)
      return (0);
    if (((char*)ptr->content)[0] != '1' || ((char*)ptr->content)[target - 1] != '1')
      return (0);
    if (!ptr->next && !check_line_ones(ptr->content))
      return (0);
    ptr = ptr->next;
  }
  info->map_width = (target + 1) / 2;
  info->map_height = ft_lstsize(info->map_tmp);
  return (1);
}

void          create_map(t_info *info)
{
  int     x;
  int     y;
  t_list  *ptr;
  char    *line;

  ptr = info->map_tmp;
  info->map = ft_calloc(sizeof(int*), info->map_width);
  x = -1;
  while (++x < info->map_width)
    info->map[x] = ft_calloc(sizeof(int), info->map_height);
  y = 0;
  while (y < info->map_height)
  {
    line = ptr->content;
    x = 0;
    while (x < info->map_width)
    {
      if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
      {
        info->px = x;
        info->py = y;
        info->orientation = *line;
      }
      else
        info->map[x][y] = ft_atoi(line);
      line += 2;
      x++;
    }
    ptr = ptr->next;
    y++;
  }
}
