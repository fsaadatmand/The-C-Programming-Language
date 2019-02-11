/*
 * Exercise 5-4. Write the function strend(s, t), which returns 1 if string t
 * occurs at the end of the string s, and zero otherwise.
 * By Faisal Saadatmand
 */

#include <stdio.h>

/* strend: returns 1 if t occurs at the end of s, and zero otherwise */
int strend (char *s, char *t)
{
  int t_len;

  while (*++s)          /* find end of s */
    ;

  t_len = 0;
  while (*t++)          /* find end of t */
    ++t_len;            /* find length of t */

  ++t_len;              /* account for '\0' */

  while (*s-- == *t--)
    --t_len;

  if (t_len == 0)
    return 1;
  else
    return 0;
}

int main(void)
{
  char string1[] = { "this is a string" };
  char string2[] = { "string" };

  printf("%i\n", strend(string1, string2));
  return 0;
}
