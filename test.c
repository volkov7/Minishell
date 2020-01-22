#include <sys/stat.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	struct  stat st;
	// char	*file = "hello   world";
	char	*line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	// printf("%s\n", argv[1]);
	linelen = getline(&line, &linecap, stdin);
	line[linelen - 1] = '\0';
	// fwrite(line, linelen, 1, stdout);
	if (lstat(line, &st) != -1)
		printf("%s - FOUNDED\n", line);
	else
		printf("%s - NOT_FOUND\n", line);
	return (0);
}