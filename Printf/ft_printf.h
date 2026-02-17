/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:44:24 by jtoumani          #+#    #+#             */
/*   Updated: 2025/04/01 13:45:33 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "Libft/libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putstr(char *s, int j);
int	ft_putchar(char c, int j);
int	ft_putnbr(int n, int j);
int	ft_puthexa(size_t n, int j, char format);
int	ft_unsignednbr(unsigned int n, int j);

#endif
