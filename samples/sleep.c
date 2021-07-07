int main(void)
{
	write(1, "executing\n", 10);
	sleep(2);
	write(1, "done\n", 5);
}
