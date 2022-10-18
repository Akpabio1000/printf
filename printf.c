#include "main.h"

/**
 * _printf - custom type of the inbuilt printf function
 * @format: first string
 * Return: the number of characters printed
 * (excluding the null byte)
 */

int _printf(const char *format, ...)
{
	int len;
	int total_len;
	int i;
	int j;
	va_list list;
	char *buffer;
	char *str;
	char *(*f)(va_list);

	len = 0;
	total_len = 0;
	i = 0;
	j = 0;

	/* validate format */
	if (format == NULL)
		return (-1);

	buffer = create_buffer();
	if (buffer == NULL)
		return (-1);

	/* initialize list_pointer */
	va_start(list, format);

	while (format[i] != '\0')
	{
		/* while format is not '%' */
		if (format[i] != '%')
		{
			len = buffer_check(buffer, len);
			buffer[len++] = format[i++];
			total_len++;
		}
		else /* if %, find function */
		{
			i++;
			/* case in which \0 comes after % */
			if (format[i] == '\0')
			{
				va_end(list);
				free(buffer);
				return (-1);
			}
			/* case in which % comes after % */
			if (format[i] == '%')
			{
				len = buffer_check(buffer, len);
				buffer[len++] = format[i];
				total_len++;
			}
			else
			{
				f = get_func(format[i]); /* get function */
				if (f == NULL)
				{
					len = buffer_check(buffer, len);
					buffer[len++] = '%';
					total_len++;
					buffer[len++] = format[i];
					total_len++;
				}
				else /* return string, copy to buffer */
				{
					str = f(list);
					if (str == NULL)
					{
						va_end(list);
						free(buffer);
						return (-1);
					}
					if (format[i] == 'c' && str[0] == '\0')
					{
						len = buffer_check(buffer, len);
						buffer[len++] = '\0';
						total_len++;
					}
					j = 0;
					while (str[j] != '\0')
					{
						len = buffer_check(buffer, len);
						buffer[len++] = str[j];
						total_len++;
						j++;
					}
					free(str);
				}
			} i++;
		}
	}
	write_buffer(buffer, len, list);
	return (total_len);
}
