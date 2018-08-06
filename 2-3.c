#include <stdio.h>
#include <ctype.h>       /* htoi() depends on ctype.h */
#include <math.h>        /* htoi() depends on math.h */
#include <string.h>     


#define MAXLINE 1000

int htoi(char s[], int len);

int htoi(char s[], int len)
{
	int i;
	int intValue = 0;
	int base10;
	
	for (i = 0; s[i] != '\0'; ++i) {
		if (isxdigit(s[i])) {
			if (isdigit(s[i])) 
				base10 = s[i] - '0';
			else 
				if (s[i] == 'a')
					base10 = 10;
				 else if (s[i] == 'b')
					base10 = 11;
				 else if (s[i] == 'c')
					base10 = 12;
				 else if (s[i] == 'd')
					base10 = 13;
				 else if (s[i] == 'e')
					base10 = 14;
				 else if (s[i] == 'f')
					base10 = 15;
				 else if (s[i] == 'A')
					base10 = 10;
				 else if (s[i] == 'B')
					base10 = 11;
				 else if (s[i] == 'C')
					base10 = 12;
				 else if (s[i] == 'D')
					base10 = 13;
				 else if (s[i] == 'E')
					base10 = 14;
				 else if (s[i] == 'F')
					base10 = 15;
		intValue += pow(16, len - 1) * base10;	
		--len;
		} else
			return -1;
	}
	return intValue;
}

int main(void)
{
	int len;
	int intValue;
	char xString[MAXLINE];

	printf("Enter a hexadecimal string: ");
	scanf("%s", &xString);

	len = strlen(xString);

	if ((intValue = htoi(xString, len)) >= 0)
		printf("%i\n", intValue);
	else
		printf("Invalid hexadecimal number\n");
	
	return 0;
}
