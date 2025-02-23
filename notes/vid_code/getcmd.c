/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:14:41 by huidris           #+#    #+#             */
/*   Updated: 2025/01/09 17:56:22 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *IO_redirection(char *command, int pid)
{
	int	ch;
	int	len;
	int filename;

    if (ft_strchr(command, '<') >= 0)
        ch = '<';
    else if (ft_strchr(command, '>') >= 0)
        ch = '>';
    if (ch == -1)
        return(command);
    command = ft_substr(0, ft_strchr(command, ch), len);
    filename = ft_substr(ft_strchr(ch) + 1, end, len);
    if (ft_strchr(command, ch) == 0)
	{<
        Command = ft_substr(ft_strch(' ') + 1, end, len);
        Filename = ft_substr(ft_strrch(ch) + 1, ft_strch(' '), len);
    }
    if (command[ft_strch(ch) + 1] == '>')
        dup2(pid[1], open(Filename, O_CREATE | O_APPEND);
    else if (command[ft_strch(ch) + 1] == '<')
        heredoc();
    else if (ft_strch(ch) == '>')
        dup2(pid[1], open(Filename, O_WRITE);
    else if (ft_strch(ch) == '<')
        dup2(pid[0], open(Filename, O_RDONLY);
    return(Command);
}

//| MAIN |
//Input = Readline
//Commands = Ft_split(Input, '|')

pipe(pid)
While i < len(Commands)
{
    if (pid == 0) {

//| MAIN |
//Input = Readline
//Commands = Ft_split(Input, '|')
		dup2(pid[0], STDOUT)
        dup2(pid[1], STDIN)
        Command = IO_redirection(Command, pid)
        Ft_split(Command, ' ')
        Execve(Command[0], Command) (Use the vector version)
    }
    Waitpid(0)
    Close(pid[0])
    Close(pid[1])
}

// Function read a line from a file
int readline(char *location)
{
    // Initialising a File Pointer in read mode
    FILE *ostream;
    ostream = fopen(location, "r");

    // If file does not exist --> return 0
    if (ostream == NULL)
    {
        return 0;
    }

    // Else read the file character by character
    char result;
    int count = 0;
    result = getc(ostream);

    // While we dont encounter a newline --> continue reading
    while(result != 10)
    {
        printf("%c",result);
        result = getc(ostream);
        count++;
    }
    printf("\n");

    // Return the number of characters read
    return count;
}

// Driver Code
int main()
{
    printf("%d\n",readline("data.txt"));
}
