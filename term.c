#include "minishell.h"

int         ft_putint(int c)
{
   return (write(STDOUT_FILENO, &c, 1));
}

int get_next_line(char **line, char *str)
{
    char buf[2];
    int i;

    i = 0;
    if (!line || read(0, NULL, 0) < 0)
        return (-1);
    *line = (char *)malloc(1);
    **line = '\0';

    while (read(0, buf, 1) > 0)
    {
        buf[1] = '\0';
		if (buf[0] == '\033')
			return (2);
			//write(1, "WTF\n", 4);
        if (buf[0] == '\n')
            return (1);
        *line = ft_strjoin(*line, buf);
    }
    return (0);
}


static char term_buffer[2048];
char buffer[100];

init_terminal_data ()
{
  char *termtype = getenv ("TERM");
  int success;

  if (termtype == 0)
    printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");

  success = tgetent (term_buffer, termtype);
  if (success < 0)
    printf("Could not access the termcap data base.\n");
  if (success == 0)
    printf("Terminal type `%s' is not defined.\n", termtype);

   char    *str;
  
   //buffer = buf;
   //str = tgetstr("ks", &buffer);
   //printf("%s %s\n", str, buffer);
   tputs(tgetstr("ks", &buffer), 1, ft_putint);
   ft_memset(buffer, 0, sizeof(buffer));

//  tputs(tgetstr("ke", &buffer), 1, ft_putint);
 //  ft_memset(buffer, 0, sizeof(buffer));

   str = tgetstr("ku", &buffer);
//  tputs(str, 1, ft_putint);

  // printf("%d\n", str);
   //printf("%s\n", str);
   //printf("%s\n", str);
   //printf("%s %s %d\n", str, "\033[[A", ft_strcmp(str, "\033[[A"));
   //
   //tputs(str, 1, ft_putint);
   char *line;

   while (1)
   {
	   if (get_next_line(&line, 0) > 1)
			write(1, ".", 1);
	  //printf("%d\n", ft_strncmp(line, str + 1, ft_strlen(str + 1)));
	   free(line);
   }
		
}
