#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream) 
{
    char c, *new_buffer;
    size_t input = 0;
    ssize_t r, ret;
    char *buffer = malloc(INITIAL_BUFFER_SIZE);

	if (!buffer) 
	{
		perror("Failed to allocate memory");
		return -1;
	}
	while (1)
	{
		r = read(fileno(stream), &c, 1);
		if (r == -1) {
            perror("Read error");
            free(buffer);
            return -1;
        }
        if (r == 0 && input == 0) {
            free(buffer);
            return -1;
        }

        if (r == 0 || c == '\n') {
            buffer[input] = '\0';
            break; 
        }
	 if (input >= *n) {
            *n = (*n == 0) ? INITIAL_BUFFER_SIZE : *n * 2;
            new_buffer = realloc(buffer, *n);
            if (!new_buffer) {
                perror("Failed to reallocate memory");
                free(buffer);
                return -1;
            }
            buffer = new_buffer;
        }

        buffer[input++] = c;
    }

    *lineptr = buffer;
    ret = input;

    return ret;
}
