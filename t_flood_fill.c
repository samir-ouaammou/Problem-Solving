#include <stdio.h>
#include <stdlib.h>

void	ft_flood_fill(char **strs, int i, int j, char c)
{
	if (i < 0 || j < 0 || strs[i] == NULL || strs[i][j] == '\0')
		return ;
	if (strs[i][j] == c || strs[i][j] == '0')
		strs[i][j] = '*';
	else
		return ;
	ft_flood_fill(strs, i + 1, j, c);
	ft_flood_fill(strs, i - 1, j, c);
	ft_flood_fill(strs, i, j + 1, c);
	ft_flood_fill(strs, i, j - 1, c);
}
