/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:07:14 by aromani           #+#    #+#             */
/*   Updated: 2025/05/03 16:54:05 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_addnew(t_gc **gc, void * add)
// {
// 	t_gc	*tmp;

// 	tmp = malloc(sizeof (t_gc));
// 	if (!tmp)
// 		return (write (2, "Error Allocation\n", 17), exit(1));
// 	tmp->address = add;
// 	tmp->next = NULL;
// 	*gc = tmp;
// }

void struct_fill(t_gc **gc, void *add)
{
    t_gc    *new_node;
    t_gc    *last;

    new_node = malloc(sizeof(t_gc));
    if (!new_node)
    {
        write(2, "Error Allocation\n", 17);
        exit(1);
    }
    new_node->address = add;
    new_node->next = NULL;
    if (*gc == NULL)
    {
        *gc = new_node;
        return ;
    }
    last = *gc;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

int isinstruct(t_gc **gc,void *add)
{
    t_gc *tmp;

    tmp = *gc;
    while (tmp)
    {
        if (ft_strcmp(tmp->address, add) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void *ft_malloc(size_t size, t_gc **gc)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    // if (ptr_exist(gc, add) == 1)
    //{
    //    return (ptr)
    //}
    struct_fill(gc,ptr);
    return (ptr);
}

void ft_gcfree(t_gc **gc)
{
    t_gc *tmp;
    t_gc *tm;

    if (!gc || !*gc)
        return ;
    tmp = *gc;
    while (tmp)
    {
        tm = tmp;
        free(tmp->address);
        tmp = tmp->next;
        free(tm);
    }
    *gc = NULL;
}

// void f ()
// {
//     system("leaks a.out");
// }
// int main()
// {
//     t_gc *list;
//     list = malloc(sizeof(t_gc));
//     char *str = ft_malloc(5, &list);
//     if (!str)
//         return (0);
//     str[0] = 'a';
//     str[1] = 'a';
//     str[2] = 'a';
//     str[3] = 'a';
//     str[4] = '\0';
//     ft_gcfree(&list);
//     atexit(f);
// }
