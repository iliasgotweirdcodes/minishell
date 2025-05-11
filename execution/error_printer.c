/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:32:18 by aromani           #+#    #+#             */
/*   Updated: 2025/05/11 22:01:26 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_printer(char *str, char* message, char *name)
{
    write(2, "minishell: ", 11);
    if (name)
        write(2, name, strlen(name));
    if (str)
        write(2, str, strlen(str));
    //write(2, ": ", 2);
    write(2, message,strlen(message));
}