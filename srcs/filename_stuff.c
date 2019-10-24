/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdraugr- <cdraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:25:49 by cdraugr-          #+#    #+#             */
/*   Updated: 2019/10/24 10:42:16 by cdraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*parse_filename(int32_t argc, char **argv)
{
	char	*input;
	char	*output;
	char	*dot_pointer;

	output = NULL;
	if (argc != 2)
		ft_error("Usage: ./asm <sourcefile.s>");
	if (ft_chrcnt(argv[1], '.') == 0)
		return (NULL);
	input = ft_strtrim(argv[1]);
	dot_pointer = ft_strrchr(input, '.');
	if (!ft_strequ(dot_pointer, ".s"))
		return (NULL);
	output = ft_strnew(dot_pointer - input + 4);
	ft_strncpy(output, input, dot_pointer - input + 1);
	ft_strcat(output, "cor");
	ft_strdel(&input);
	return (output);
}

void		print_output_filename(char **filename)
{
	ft_putstr("\033[1;32mGenerate a champion at ");
	ft_putstr(*filename);
	ft_putendl("\033[0m");
	ft_strdel(filename);
}
