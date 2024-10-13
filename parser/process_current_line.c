/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_current_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libousse <libousse@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:39:45 by libousse          #+#    #+#             */
/*   Updated: 2024/10/13 17:09:37 by libousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// DELETE WHEN REAL EXECUTOR ---------------------------------------------------
static int	dummy_executor(t_sh *sh)
{
	size_t	i;
	char	*cleaned;

	i = 0;
	printf("Dummy executor receives = [");
	while (sh->rl.tokens[i])
	{
		cleaned = get_clean_token(sh->rl.tokens[i]);
		printf("`%s` (`%s`)", sh->rl.tokens[i], cleaned);
		free(cleaned);
		if (sh->rl.tokens[i + 1])
			printf(", ");
		++i;
	}
	printf("]\n");
	printf("Heredoc content = [\n`%s`\n]\n", sh->rl.heredocs);
	if (!ft_strcmp(sh->rl.tokens[0], "exit"))
		sh->keep_running = 0;
	if (!ft_strcmp(sh->rl.tokens[0], "error"))
		return (42);
	return (0);
}
//------------------------------------------------------------------------------

void	process_current_line(t_sh *sh)
{
	//t_pl	pl;
	char	*cmdl;
	int		is_legal;

	sh->rl.arr = 0;
	is_legal = extract_first_command_line(sh);
	append_heredoc_lines_with_a_newline_char(sh);
	add_input_to_history(sh);
	if (is_legal)
	{
		cmdl = concatenate_all_cmdl_lines(sh);
		sh->rl.tokens = tokenize(cmdl, 1, ft_isspace);
		free(cmdl);
		expansion(sh);
		sh->rl.heredocs = concatenate_all_heredoc_lines(sh);
		if (sh->rl.tokens && sh->rl.tokens[0])
		{
			/*
			   The order is:
			   - Interpretation: whether a string is a literal or has a meaning.
			   For example, `"<<"` vs `<<`. Once the cleanup occurs, there's no 
			   telling which is which.
			   - [DONE] Token cleanup before sending to the executor.
			*/
			// - Fill up `pl` and pass it to the executor instead of `tokens`.
			sh->exit_code = dummy_executor(sh);
		}
		free_entire_array((void **)sh->rl.tokens, free);
		free(sh->rl.heredocs);
		// - Free `pl`.
	}
	free_entire_array((void **)sh->rl.arr, free_rl_arr_element);
	return ;
}

void	free_rl_arr_element(void *ptr)
{
	size_t		i;
	t_rl_arr	*elem;

	if (!ptr)
		return ;
	elem = ptr;
	free(elem->value);
	if (elem->delimiters)
	{
		i = 0;
		while (elem->delimiters[i])
		{
			free(elem->delimiters[i]);
			++i;
		}
		free(elem->delimiters);
	}
	free(elem);
	return ;
}

//------------------------------------------------------------------------------
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

/*
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
		pl->hd = get_heredocs(pl->len, 0, &pl->exit_code); // Del. instead of 0
	return (!pl->exit_code);
}
*/
