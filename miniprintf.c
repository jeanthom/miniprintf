#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

void miniprintf(const char *format, ...) {
	const char *hex_lower = "0123456789abcdef";
	const char *hex_upper = "0123456789ABCDEF";
	const char *char_lut;
	enum {
		PASSTHROUGH,
		FLAG,
		WIDTH,
		SPECIFIER
	} state = PASSTHROUGH;
	unsigned int val_unsigned;
	int digit, i, padding = 0;
	bool leading_zeros = false;
	va_list params;

	va_start(params, format);

	while (*format) {
		switch (state) {
		case PASSTHROUGH:
			if (*format == '%') {
				state = FLAG;
				break;
			}
			putchar(*format);
			break;

		case FLAG:
			if (*format == '%') {
				putchar('%');
				state = PASSTHROUGH;
			} else if (*format == '0') {
				leading_zeros = true;
				state = WIDTH;
			} else {
				goto _width;
			}
			break;

		_width:
		case WIDTH:
			if (*format >= '0' && *format <= '9') {
				if (padding == 0) {
					padding = *format - '0';
				} else {
					padding = padding * 10 + *format - '0';
				}
			} else {
				goto _specifier;
			}
			break;

		_specifier:
		case SPECIFIER:
			if (*format == 'x' || *format == 'X') {
				char_lut = (*format == 'x') ? hex_lower : hex_upper;

				val_unsigned = va_arg(params, unsigned int);
				for (i = sizeof(unsigned int)*2 - 1; i >= 0; i--) {
					digit = (val_unsigned >> 4*i) & 0xF;
					if (digit == 0) {
						if (leading_zeros && padding > i) {
							putchar('0');
						} else if (padding > i) {
							putchar(' ');
						}
					} else {
						leading_zeros = true;
						putchar(char_lut[digit]);
					}
				}
			}
			state = PASSTHROUGH;
			break;
		}

		format++;
	}

	va_end(params);
}

int main(void) {
	miniprintf("feedbebe (%%08x): %08x\n", 0xFEEDBEBE);
	miniprintf("FEEDBEBE (%%08X): %08X\n", 0xFEEDBEBE);
	miniprintf("0001 (%%04x): %04x\n", 1);
	miniprintf("01 (%%02x): %02x\n", 1);
	miniprintf(" 1 (%%2x): %2x\n", 1);
	return EXIT_SUCCESS;
}
