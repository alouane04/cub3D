#include "cube3D.h"

void	init_input(t_input	*input)
{
	input->no = NULL;
	input->so = NULL;
	input->ea = NULL;
	input->we = NULL;
	input->f = NULL;
	input->c = NULL;
	input->map = NULL;
}

int	*stock_rgb(char *str)
{
	int 	*i_rgb;
	char 	**c_rgb;
	int		i;

	i = 0;
	c_rgb = check_rgb(str);
	if(!c_rgb)
		return (NULL);
	i_rgb = malloc(sizeof(int) * 3);
	if(!i_rgb)
		return (ft_free(c_rgb), NULL);
	while(c_rgb[i])
	{
		i_rgb[i] = ft_atoi(c_rgb[i]);
		if(i_rgb[i]< 0 || i_rgb[i] > 255)
			return(ft_free(c_rgb), free(i_rgb), NULL);
		i++;
	}
	return (ft_free(c_rgb), i_rgb);
}

void	stock_lst(int fd, char *str, t_list *lst)
{
	char	*str1;

	str1 = get_next_line(fd);

	// write(2, str, 5);
	// write(2, "\n", 1);
	ft_lstadd_back(&lst, ft_lstnew(str));
	// if (lst->content)
	// 	write(2, lst->content, 5);
	check_if_map(fd, str1, lst);
}

int	get_biggest_line(t_list *lst)
{
	int	i;
	//char	*str;

	//str = lst->content;
	//if (!str)
	//	write(2, "test\n", 5);
	write(2, "9alwa\n", 7);
	i = ft_strlen((char*)lst->content);
	while (lst)
	{
		if (i < (int)ft_strlen((char*)lst->content))
			i = ft_strlen(lst->content);
		lst = lst->next;
	}
	return (i);
}

char	*stock_line(char const *s, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

void	stock_map(t_list *lst, t_input *input)
{
	int len;
	int i;

	i = 0;
	input->map = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!input->map)
		return ;
	len = get_biggest_line(lst);
	while (lst)
	{
		input->map[i] = stock_line(lst->content, len);
		i++;
		lst = lst->next;
	}
}

int	stock_input(int fd, t_input *input)
{
	char	*str;
	t_list	*lst;

	lst = NULL;
	while(1)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		//printf("%s\n", str);
		if (check_line(str, input))
		{
			if (!check_if_map(fd, str, lst))
			{
				//write(2, "koo\n", 4);
				//if(!lst->content)
					//write(2, "ok\n", 3);
				stock_map(lst, input);
				break ;
			}
			else
			{
				return (free(str), ft_putendl_fd("Error invalid map", 2), 1);
			}
		}
		free(str);
	}
	if (check_if_empty(input) || str)
		return (free(str), ft_putendl_fd("Error invalid map", 2), 1);
	return (free(str), 0);
}