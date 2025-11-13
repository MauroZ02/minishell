/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:52 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/13 17:14:03 by mzangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	*prompt;
	int		i;

	i = 0;
	prompt = "minishell> ";
	while (1)
	{
		line = readline(prompt);
		if (line[i] == '\0')
		{
			free(line);
			printf("exit");
			exit(1);
		}


	}
	return (0);
}