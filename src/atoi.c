#include <ctype.h>

#define MINUS -1
#define PLUS 1

int atoi(const char *str) {
  int i, ret_number;
  for (i = 0; isspace(str[i]); i++)
    ;
  int sign = (str[i] == '-') ? MINUS : PLUS;
  if (str[i] == '+' || str[i] == '-')
    i++;
  for (ret_number = 0; isdigit(str[i]); i++) {
    ret_number = 10 * ret_number + (str[i] - '0');
  }
  if (sign == MINUS)
    ret_number *= MINUS;
  return ret_number;
}
