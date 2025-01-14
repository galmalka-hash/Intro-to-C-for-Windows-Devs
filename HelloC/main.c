// main.c : This file contains the 'main' function for the first lab.

#include <Windows.h>
#include <stdio.h>

INT
main(VOID)
{

	INT max = 0x7FFFFFFF;
	UINT min = 0x1;
	DWORD big = 1 << 12;
	
	printf("INT max (hex)[%x] (dec)[%d] \n", max, max);
	printf("UINT min (hex)[%x] (dec)[%d] \n", min, min);
	printf("DWORD big (hex)[%x] (dec)[%d] \n", big, big);

	max += min;

	printf("INT max + UINT min (hex)[%x] (signed)[%d] (unsigned)[%u] \n", max, max, max);

	ULONGLONG l = 0xDeadBeefCafeBabe;
	INT ip = 2130706433;
	UINT ip2 = 0x7F000001;
}