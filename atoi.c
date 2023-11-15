#include "shell.h"

int interactive(info_t *info) {
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int is_delim(char c, char *delim) {
	while (*delim) {
	if (*delim++ == c) {
	return (1);
		}
	}
	return (0);
}

int _isalpha(int c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int _atoi(char *s) {
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] && flag != 2; i++) {
	if (s[i] == '-') {
		sign *= -1;
	}

	if (s[i] >= '0' && s[i] <= '9') {
		flag = 1;
		result = result * 10 + (s[i] - '0');
	} else if (flag == 1) {
		flag = 2;
		}
	}

	output = (sign == -1) ? -result : result;

	return (output);
}

