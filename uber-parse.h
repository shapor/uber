#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#ifndef _PARSE_H
#define _PARSE_H 1

enum state_en {
	NEXT_STATE,
	INT_STATE,
	INT_NUM_STATE,
	SKIP_CHARS_STATE,
	LOOP_STATE,
	STRING_STATE,
	INSTRING_STATE,
	END_STATE,
};

#define STRING_MAX 1024
#define MAX_PARSE_STRINGS 100
#define MAX_PARSE_INTS 255
#define MAX_STEPS 255
#define MAX_SKIPCHARS 255

typedef struct parse_config parse_config_t;
typedef struct parse_data parse_data_t;

struct parse_config {
	int num_steps;
	int state_steps[MAX_STEPS];
	char skip_chars[MAX_SKIPCHARS];
	char skip_chars_count[MAX_SKIPCHARS];
	char string_term_chars[MAX_PARSE_STRINGS];
	void (*callback)(parse_data_t*);
};

struct parse_data {
	int fd;
	parse_config_t *config;
	int int_data[MAX_PARSE_STRINGS];
	char *string_data[MAX_PARSE_STRINGS];
	unsigned long string_hashes[MAX_PARSE_STRINGS];
};

int update_data_from_fd(parse_data_t *d);

#if 0
#define rol(i, by) \
i = (i << by) | (i >> ((sizeof(i) << 3) - by))
#else
#define rol(i,by) \
	__asm__ ( \
		"rolq %b1,%q0"\
		:"+g" (i) \
		:"Jc" (by) ) 
#endif
#endif // _PARSE_H
