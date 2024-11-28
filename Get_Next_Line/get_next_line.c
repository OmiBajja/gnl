
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
char *line_printer (char *str,const int n, int *j)
{    
    int i;
    char *line;

    i = 0;
    while (str[i] && i < n && j == 0)
            {
                if (str[i] == '\n')
                {
                    *j = 1;
                    line = ft_substr(str, 0, i);
                }
                i++;
            }
    return (line);
}
char *line_checker(int fd, const int n, char r)
{
    char    buffer[n];
    static char    *stash;
    int     i;
    int     j;
    static int     c;
    int     f;
    char    *line;
    
    i = 0;
    j = 0;
    f = 0;
    stash = malloc(n * sizeof(char));
    stash[0] = '\0';
    while (r != 0 && j == 0)
    {
        if (stash [0] != '\0')
            line = line_printer(stash, n, &j);
        i = 0;
        r = read(fd, &buffer, n);
        line = line_printer(buffer, n, &j);    
            /*while (buffer[i] && i < n && j == 0)
            {
                if (buffer[i] == '\n')
                {
                    if (stash[0] != '\0')
                    {
                        line = ft_strcat_gnl(stash, buffer, i + c);
                        printf("%s\n",line);
                    }
                    else
                    {
                        line = ft_substr(buffer, 0, i);
                        printf("%s\n",line);
                        j++;
                   // }
                }*/
                i++;
                c = 0;
                while (buffer[i + c] && i + c < n)
                {
                    stash[c] = buffer[i + c];
                    c++;
                }
                while (c + f < n)
                {
                    stash[c + f] = '\0';
                    f++;
                }
            //}
            i = 0;
    }
    if (!line)
       return (NULL);
    line[c] = '\0';
    c--;
    return (line);
}

char *get_next_line(int fd)
{
    char *str;

    str = line_checker(fd, 15, 'a');
    return (str);
}

#include <stdio.h>
int main ()
{
   static int fd;

    fd = open("numbers", O_RDONLY);
    if (fd < 0)
        return (0);
    int i = 0;
    while (i < 4)
    {
        get_next_line(fd);
        i++;
    }
    close (fd);
    return (0);
}