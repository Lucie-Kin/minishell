/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:05 by libousse          #+#    #+#             */
/*   Updated: 2024/09/18 14:02:04 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*raw_cmdl;

	if (!envp[0])
		return (output_error_UPDATE(1, 
				compose_err_msg(SHELL_NAME, 0, "No environment variable")));
	raw_cmdl = readline("$ ");
	printf("Entered command is: \"%s\"\n", raw_cmdl);
	free(raw_cmdl);
	return (0);

	/*
	t_pl	pl;

	// Init stuff
	if (argc != 5)
		return (0);
	if (!init_pipeline(&pl, argc, argv, envp))
		return (free_pipeline_resources_in_parent(&pl));
	// Pipeline itself should be good
	return (execute_pipeline(&pl));
	*/
}

/*
	Parsing the command line, the infiles and outfiles can only fail on ENOMEM 
	(no more memory on the heap). This is why I just execute all of these 
	functions and then return this error if one of them failed.

	I parse these before the heredocs because they don't prompt the user for 
	input. There's no point in prompting if you're going to discard the data 
	anyway.

	If all went well thus far, you can parse the heredocs. In this context, 
	ENOMEM is not the only possible error.
*/

int	init_pipeline(t_pl *pl, int argc, char **argv, char **envp)
{
	pl->len = argc - 3;
	pl->index = -1;
	pl->exit_code = 0;
	pl->err_msg = 0;
	pl->envp = envp;
	pl->path = split_path(envp);
	pl->fd_pipe_len = pl->len - 1;
	pl->fd_pipe = 0;
	pl->fd_src[0] = -1;
	pl->fd_src[1] = -1;
	pl->fd_hd = -1;
	pl->fd_inf = -1;
	pl->fd_outf = -1;
	pl->cmdl = parse_cmdl(argv + 2, pl->len);
	pl->inf = get_infiles(pl->len, argv[1]);
	pl->outf = get_outfiles(pl->len, argv[argc - 1],
			O_CREAT | O_TRUNC | O_WRONLY); // or O_APPEND instead of O_TRUNC
	pl->favor_hd = get_favor_hd_array(pl);
	pl->hd = 0;
	if (!pl->cmdl || !pl->inf || !pl->outf || !pl->favor_hd)
		pl->exit_code = ENOMEM;
	else
		pl->hd = get_heredocs(pl->len, 0, &pl->exit_code); // Delimiter instead of 0
	return (!pl->exit_code);
}
