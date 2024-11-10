#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

// Function to write a single character to standard output and update the size counter.
static void ft_putchar(char c, int *size)
{
    int temp;

    if (*size == -1) // If there's an error, do nothing
        return ;
    temp = write(1, &c, 1); // Write the character
    if (temp == -1) // If write fails, set size to -1
        *size = -1;
    else
        *size += temp; // Increment size by the number of characters written
}

// Function to write a string to standard output and update the size counter.
static void ft_putstr(const char *str, int *size)
{
    if (!str) // If string is null, print "(null)"
    {
        ft_putstr("(null)", size);
        return ;
    }
    while (*str) // Write each character of the string
    {
        ft_putchar(*str, size);
        str++;
    }
}

// Function to write an integer to standard output and update the size counter.
static void ft_putnbr(int nbr, int *size)
{
    if (nbr == -2147483648) // Handle minimum integer value
    {
        ft_putstr("-2147483648", size);
        return;
    }
    if (nbr < 0) // Handle negative numbers
    {
        ft_putchar('-', size);
        nbr = -nbr;
    }
    if (nbr > 9) // Recursive call to print each digit
        ft_putnbr(nbr / 10, size);
    ft_putchar(nbr % 10 + '0', size); // Print last digit
}

// Function to write an unsigned integer to standard output and update the size counter.
static void ft_putuni(unsigned int nbr, int *size)
{
    if (nbr > 9) // Recursive call to print each digit
        ft_putuni(nbr / 10, size);
    ft_putchar(nbr % 10 + '0', size); // Print last digit
}

// Function to write a hexadecimal number to standard output and update the size counter.
static void ft_puthex(unsigned int nbr, char *hex, int *size)
{
    if (nbr > 15) // Recursive call to print each hexadecimal digit
        ft_puthex(nbr / 16, hex, size);
    ft_putchar(hex[nbr % 16], size); // Print the current digit in hexadecimal
}

// Function to write a pointer address in hexadecimal format to standard output.
static void ft_putptr(unsigned long nbr, int *size)
{
    if (nbr > 15) // Recursive call to print each hexadecimal digit
        ft_putptr(nbr / 16, size);
    ft_puthex(nbr % 16 , "0123456789abcdef", size); // Convert address to hexadecimal
}

// Function to determine which conversion to apply based on the format specifier.
static void ft_all_print(char c, va_list args, int *size)
{
    if (c == '%') // If format is '%%', print a literal '%'
        ft_putchar('%', size);
    else if (c == 'c') // If format is 'c', print a character
        ft_putchar(va_arg(args, int), size);
    else if (c == 'd' || c == 'i') // If format is 'd' or 'i', print an integer
        ft_putnbr(va_arg(args, int), size);
    else if (c == 'u') // If format is 'u', print an unsigned integer
        ft_putuni(va_arg(args, unsigned int), size);
    else if (c == 's') // If format is 's', print a string
        ft_putstr(va_arg(args, char *), size);
    else if (c == 'x') // If format is 'x', print a hexadecimal number (lowercase)
        ft_puthex(va_arg(args, unsigned int), "0123456789abcdef", size);
    else if (c == 'X') // If format is 'X', print a hexadecimal number (uppercase)
        ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF", size);
    else if (c == 'p') // If format is 'p', print a pointer address
    {
        ft_putstr("0x", size); // Add "0x" prefix for pointers
        ft_putptr(va_arg(args, unsigned long), size);
    }
}

// Custom printf function that handles a subset of printf format specifiers.
static int ft_printf(char *format, ... )
{
    va_list args;
    int size;
    int i;

    size = 0;
    if (!format) // If format is null, return 0
        return (size);
    va_start(args, format); // Initialize argument list
    i = 0;
    while (format[i]) // Loop through each character in the format string
    {
        if (format[i] == '%' && format[i + 1] == '\0') // If there's a '%' at the end, stop
            return (size);
        else if (format[i] == '%' && format[i + 1] != '\0') // If there's a format specifier
            ft_all_print(format[i++ + 1], args, &size); // Print according to format
        else
            ft_putchar(format[i], &size); // Print regular characters
        i++;
    }
    va_end(args); // End argument list
    return (size); // Return the number of characters printed
}

int main(void)
{
    int len1;
    int len2;

    // Testing ft_printf and comparing it with the standard printf
    len1 = ft_printf("My Printf:     %% %c %s %d %i %u %x %X %p\n", 'S', "Hello", 1337, 42, 2024, 15, 15, &main);
    len2 = printf("Printf in c:   %% %c %s %d %i %u %x %X %p\n", 'S', "Hello", 1337, 42, 2024, 15, 15, &main);

    // Printing the result of each printf to compare lengths
    printf("\n%d\n%d\n", len1, len2);

    return (0);
}
