
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int func(t_list *lst)
{
	static t_list *t;
	t_list *b;

	printf("%p << t\n", t);
	printf("%p << b\n", b);
}

int main()
{
	t_list *lst;

	printf("%p << lst\n", lst);
	func(lst);
}
