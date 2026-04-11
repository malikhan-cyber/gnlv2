#include <stdio.h>

void print_buffer(char *s)        // alleen lezen
{
	int i;
	i = 0;
	while(s[i])
		i++;
	printf("de lengte van buffer is: %d", i);
}

void modify_chars(char *s)      // inhoud wijzigen, pointer blijft zelfde
{
	char *nieuwe_buffer = "ik hoop dat ik het uiteindelijk snap";
	s = nieuwe_buffer;
	printf("%s\n", s);
}

void replace_buffer(char **s)     // pointer vervangen
{
	printf("%s\n", s);
}

void getnextline(void)
{
	static char *buffer;
	buffer = "ik ben mijn pointer kennis aan het verbeteren";
	void print_buffer(char *buffer);        // alleen lezen
	void replace_buffer(char **buffer);     // pointer vervangen
	void modify_chars(char *buffer);        // inhoud wijzigen, pointer blijft zelfde
}
