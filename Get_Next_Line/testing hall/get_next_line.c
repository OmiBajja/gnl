
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
# include <stddef.h>
# include <stdint.h>

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char 	*ft_strcat_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	r;
    char   *str;

	i = ft_strlen(dst);
	j = 0;
	r = ft_strlen(src);
    str = malloc((size + 1) * sizeof(char));
    if (!str)
        return (NULL);
    str = dst;
	while (j < (size - i - 1) && src[j])
	{
		str[i + j] = src[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(((len - start) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s[start] == '\0')
		return (str);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
char *line_printer (char *str,const int n, int *j, int *i)
{    
    char *line;
	int c;

    c = 0;
    while (str[c] && c < n && *j == 0)
    {
            if (str[c] == '\n')
		    {
                line = ft_substr(str, 0, c);
				*j = 1;
            }
            c++;
    }
	*i = c;
    return (line);
}

char *ft_stasher (char *stash, char *buffer, const int n, int *i)
{
    int c;

	c = 0;
	while (buffer[c] && (*i + c) < n)
	{    	    
		stash[c] = buffer[c];           	   	
		c++;
	}
	stash[c] = '\0';
	return (stash);
}
char *line_checker(int fd, const int n, char r)
{
    char    buffer[n];
    static char    *stash;
    int     i;
    int     j;
    int     f;
    char    *line;
    
    i = 0;
    j = 0;
    f = 0;
    if (!stash)
	{
		stash = malloc(n + 1 * sizeof(char));
		stash[0] = '\0';
	}
    while (r != 0 && j == 0)
    {
        if (stash [0] != '\0')
        {    
			line = line_printer(stash, n, &j, &i);
			if (stash[i] && j == 1)
				stash = ft_stasher(stash, &stash[i], n, &i);
			stash[i] = '\0';
        	i = 0;
		}
		if (stash[0] == '\0')
			r = read(fd, &buffer, n);
		if (r <= 0)
			return (NULL);
		line = line_printer(buffer, n, &j, &i);    
		if (buffer[i] && j == 1)
			stash = ft_stasher(stash, &buffer[i], n, &i);
		stash[i] = '\0';
		i = 0;
    }
    if (!line)
       return (NULL);
    return (line);
}

char *get_next_line(int fd)
{
    char *str;

    str = line_checker(fd, 23, 'a');
    return (str);
}

#include <stdio.h>
int main ()
{
   static int fd;
	char *line;

    fd = open("numbers", O_RDONLY);
    if (fd < 0)
        return (0);
    int i = 0;
    while (i < 2)
    {
        line = get_next_line(fd);
        i++;
		free(line);
    }
    close (fd);
    return (0);
}