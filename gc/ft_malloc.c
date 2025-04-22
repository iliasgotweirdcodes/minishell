/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:07:14 by aromani           #+#    #+#             */
/*   Updated: 2025/04/22 22:20:56 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addnew(t_gc **gc, void * add)
{
	t_gc	*tmp;

	tmp = malloc(sizeof (t_gc));
	if (!tmp)
		return (write (2, "Error Allocation\n", 17), exit(1));
	tmp->address = add;
	tmp->next = NULL;
	*gc = tmp;
}

t_gc	*struct_fill(t_gc *gc, void* add)
{
	t_gc	*tmp;
	t_gc	*tm;

	if (gc == NULL)
		ft_addnew(&gc, add);
	else
	{
		tmp = malloc(sizeof (t_gc));
		if (!tmp)
			return (write (2, "Error Allocation\n", 17), exit(1), NULL);
		tmp->address = add;
		tmp->next = NULL;
		tm = gc;
		while (tm->next != NULL)
			tm = tm->next;
		tm->next = tmp;
	}
	return (gc);
}

void *ft_malloc(size_t size, t_gc **gc)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    *gc = struct_fill(*gc,ptr);
    return (ptr);
}

void ft_gcfree(t_gc **gc)
{
    t_gc *current;
    t_gc *next;

    if (!gc || !*gc)
        return;
    
    current = *gc;
    while (current != NULL)
    {
        next = current->next;
        if (current->address)
        {
            free(current->address);
            current->address = NULL;
        }
        free(current);
        current = next;
    }
    *gc = NULL;
}

void ft_gcprint(t_gc *gc)
{
    int count = 0;
    while (gc)
    {
        printf("Node %d: %p\n", count++, gc->address);
        gc = gc->next;
    }
}
void f ()
{
    system("leaks a.out");
}
int main()
{
    t_gc *list;

    
    list = malloc(sizeof(t_gc));
    char *str = ft_malloc(5, &list);
    if (!str)
        return (0);
    str[0] = 'a';
    str[1] = 'a';
    str[2] = 'a';
    str[3] = 'a';
    str[4] = '\0';
    ft_gcfree(&list);
    atexit(f);
}