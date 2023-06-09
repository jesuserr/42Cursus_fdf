/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:25:20 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/09 12:19:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Applied scale_z depends on z_max to z_min range */
/* Line equation used for that purpose */
/* For 42.fdf applied scale is 0.1 // Minimum 0.05 */
/* fdf->scale_z = (-0.00072 * (fdf->z_max - fdf->z_min)) + 0.10792; */

void	z_centering(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->scale_z = (-0.0004 * (fdf->z_max - fdf->z_min)) + 0.1044;
	if (fdf->scale_z < 0.05)
		fdf->scale_z = 0.05;
	printf("\n%d %d %f\n", fdf->z_min, fdf->z_max, fdf->scale_z);
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		fdf->map[i].z -= ((fdf->z_max + fdf->z_min) / 2.0);
		fdf->map[i].z *= fdf->scale_z;
		i++;
	}
}
