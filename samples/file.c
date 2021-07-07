#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

struct s_demo
{
	short	low_pass_vcf;
	short	filter_coupler;
	short	reverb;
	short	sequential;
};

int	main(void)
{
	struct s_demo	a;
	int				b;

	a.low_pass_vcf = 2;
	((b = 1 * 2) && printf("hello\n"));
}
