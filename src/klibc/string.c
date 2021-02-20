#include "klibc/string.h"
#include "devices/terminal.h"
#include "devices/kbd.h"

uint32_t dgcount(int num){
    uint32_t count = 0;
    if(num == 0){
        return 1;
    }
    while(num > 0){
        count++;
        num = num/10;
    }
    return count;
}

void itoa(int num, char *dest){
    int dcount = dgcount(num);
    int index = dcount -1;
    char x;
    if(num == 0 && dcount == 1){
        dest[0] = '0';
        dest[1] = '\0';
    }
    else{
        while(num != 0){
            x = num % 10;
            dest[index] = x + '0';
            index--;
            num = num/10;
        }
        dest[dcount] = '\0';
    }
}

int strlen(const char* str) {
	int len = 0;
	while (str[len])
		len++;
	return len;
}

uint16_t *memsetw(uint16_t *dest, uint16_t val, size_t count)
{
    uint16_t *temp = dest;

    while(count--){
        *temp++ = val;
    }

    return dest;
}

uint8_t *memcpy(uint8_t *dest, const uint8_t *src, size_t n)
{
    uint8_t *d = dest;
    const uint8_t *s = src;

    while(n--){
        *d++=*s++;
    }

    return dest;
}

void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

char *strrev(char *s){
	int start = 0;
	int end = strlen(s) - 1;
	char swap;

	while(start < end){
		swap = s[start];
		s[start] = s[end];
		s[end] = swap;

		start++;
		end--;
	}

	return s;
}

char *strcpy(char *dst, const char *src){
    char c;
    char *p = dst;

    while ((c = *src++)){
        *p++ = c;
    }

    *p = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2){
    while (*s1 == *s2){
        if (*s1 == '\0'){
            return 0;
        }

        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}


char *strcat(char *d, const char *s){
	strcpy(d + strlen(d), s);
	return d;
}

const char *strchr(const char *s, char ch){
	while(*s) {
		if(*s == ch)
			return s;
		s++;
	}
	return 0;
}

char *strtok(char *s, const char *delim)
{
	static char *oldword = 0;
	char *word;

	if(!s)
		s = oldword;

	while(*s && strchr(delim, *s))
		s++;

	if(!*s) {
		oldword = s;
		return 0;
	}

	word = s;
	while(*s && !strchr(delim, *s))
		s++;

	if(*s) {
		*s = 0;
		oldword = s + 1;
	} else {
		oldword = s;
	}

	return word;
}


// printing functions

void putc(char ch){
    terminal_putchar(ch);
}

void puts(const char *str){
    terminal_putstr(str);
}

void kprintf(char *str, ...){
    int integer;
    char character;
    char *string;
    va_list arg;
    va_start(arg, str);
    while(*str!=0){
        if(*str == '%'){
            ++str;
            switch(*str){
                case 'c':
                    character = va_arg(arg, int);
                    putc(character);
                    break;
                case 'd':
                    integer = va_arg(arg, int);
                    char temp[] = "";
                    itoa(integer, temp);
                    puts(temp);
                    break;
                case 's':
                    string = va_arg(arg, char *);
                    puts(string);
                    break;
                default:
                    putc(*str);
                    break;
            }
        }
        else{
            putc(*str);
        }
        ++str;
    }
    va_end(arg);
}

void gets(){
    char c;
    while(1){
        c = keyboard_read();
        if(c == '\n'){
            //putc('\n');
            return;
        }
       
            //putc(c);
    }
}