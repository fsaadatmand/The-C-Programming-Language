/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* concatenate t to end of s; s must be big enough */
void strCat(char *s, char *t)
{
  while (*s)             /* find end of s */
    ++s;

  while ((*s++ = *t++))  /* copy t */
    ;
}

int main(void)
{
  char string1[64] = { "test this " };
  char string2[] = { "function" };

  strCat(string1, string2);

  printf("%s\n", string1);
  
  return 0;
}
