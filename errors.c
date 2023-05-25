/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:39 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/25 21:42:42 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error_handler(int error)
{
	if (error == ERROR_ARGS)
		ft_printf ("%sInvalid arguments - One single map expected\n", RED);
	else if (error == ERROR_FILE)
		ft_printf ("%sError opening file\n", RED);
	exit(EXIT_FAILURE);
}
