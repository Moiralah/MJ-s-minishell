#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	HIST_ENTRY	*cur_history;
	char		*line;

	while (1)
	{
		line = readline(getcwd(NULL, 0));
		add_history(line);
		free(line);
		cur_history = current_history();
		printf("%s\n", cur_history->line);
	}
}
