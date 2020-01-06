#include "cub3d.h"

void		handle_line_map(char *line, t_info *info)
{
  ft_lstadd_back(&(info->map_tmp), ft_lstnew(ft_strdup(line)));
}

void		handle_line_info(char *line, t_info *info)
{
  char type;

  type = *line;
  if (type == 'R')
    parse_resolution(line, info);
  if (type == 'N' || type == 'S' || type == 'W' || type == 'E')
    parse_texture(line, info);
  if (type == 'C' || type == 'F' )
    parse_color(line, info);
}

void		parse_resolution(char *line, t_info *info)
{
  line += 2;
  info->width = ft_atoi(line);
  while (ft_isdigit(*line))
    line++;
  info->height = ft_atoi(line);
}

void		parse_texture(char *line, t_info *info)
{
  char type[2];

  type[0] = line[0];
  type[1] = line[1];
  while (ft_isalpha(*line))
    line++;
  line++;
  if (type[0] == 'N')
    info->texture_n = ft_strdup(line);
  if (type[0] == 'E')
    info->texture_e = ft_strdup(line);
  if (type[0] == 'W')
    info->texture_w = ft_strdup(line);
  if (type[0] == 'S' && type[1] == 'O')
    info->texture_s = ft_strdup(line);
  if (type[0] == 'S' && type[1] == ' ')
    info->texture_sprite = ft_strdup(line);
}

void		parse_color(char *line, t_info *info)
{
  char          type;
  unsigned char res[3];

  type = *line;
  line += 2;
  res[0] = (unsigned char)ft_atoi(line);
  while (ft_isdigit(*line))
    line++;
  line += (*line == ',');
  res[1] = (unsigned char)ft_atoi(line);
  while (ft_isdigit(*line))
    line++;
  line += (*line == ',');
  res[2] = (unsigned char)ft_atoi(line);
  if (type == 'C')
    set_color(info->ceil, res[0], res[1], res[2]);
  else if (type == 'F')
    set_color(info->floor, res[0], res[1], res[2]);
}
