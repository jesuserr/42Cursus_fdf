/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:25:20 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/08 16:20:06 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z_centering(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		fdf->map[i].z -= ((fdf->z_max + fdf->z_min) / 2.0);
		fdf->map[i].z *= fdf->scale_z;
		i++;
	}
}
