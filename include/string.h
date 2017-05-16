#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H

#include "types.h"

void memcpy(char *dest, const char *src, uint32_t len);

void memset(char *dest, uint32_t val, uint32_t len);

void bzero(char *dest, uint32_t len);

int strcmp(const char *str1, const char *str2);

char *strcpy(char *dest, const char *src);

uint32_t strlen(const char *str);

#endif