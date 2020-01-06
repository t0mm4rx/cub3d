#include "cub3d.h"

void print_list(t_list *lst)
{
  while (lst)
  {
    printf("%s -> ", lst->content);
    lst = lst->next;
  }
  printf("NULL");
}
