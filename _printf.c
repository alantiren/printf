#include "main.h"

#define BUFF_SIZE 1024

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            ++i;
            printed = handle_print(format, &i, list, buffer,
                flags, width, precision, size);
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer and resets the buffer index
 * @buffer: The buffer to print
 * @buff_ind: A pointer to the index of the buffer
 */
void print_buffer(char buffer[], int *buff_ind)
{
	int i;

	if (*buff_ind == 0)  /* If buffer is empty */
		return;

	for (i = 0; i < *buff_ind; i++) {
		putchar(buffer[i]);  /* Print each character */
	}
	fflush(stdout);  /* Flush the output buffer */
	*buff_ind = 0;  /* Reset the buffer index */
}
