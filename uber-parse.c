#include <stdlib.h> // malloc()
#include <time.h>

#include "uber-parse.h"

/* assume fd is pointing at the beginning of the data to parse and load in to p->{string,int}_data */
int update_data_from_fd(parse_data_t *d) {
	int step=0;
	parse_config_t *c = d->config;
	int i, state = c->state_steps[0];
	char current_char;
	char buf[BUFSIZ * 3];
	char *buf1 = &buf[BUFSIZ];
	char *buf2 = &buf[BUFSIZ * 2];
	char *bp = buf1, *obp = buf2;
	int br;

	/* to support integer type */
	int int_tmp;
	int num_ints = 0;

	/* to support string type */
	int num_strings = 0;
	char term_char = c->string_term_chars[0];

	/* to support hashing the strings */
	unsigned long *string_hashes = d->string_hashes;
	unsigned long hash = 0;

	/* to support skip chars */
	int cur_skip = 0;
	int skipped = 0;

	while ((br = read(d->fd, bp, BUFSIZ))) {
		for(i=0;i<br;i++) {
			current_char = bp[i];
			//printf("char: %c, state: %i, curskip: %i\n", current_char, state, cur_skip);
			switch(state) {
			case INT_STATE:
				switch (current_char) {
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						int_tmp = current_char - '0';
						state = INT_NUM_STATE;
					default: break;
				}
				break;

			case INT_NUM_STATE:
				switch (current_char) {
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						int_tmp = (int_tmp * 10) + (current_char - '0');
						break;
					default:
						d->int_data[num_ints++] = int_tmp;
						state = NEXT_STATE;
				}
				break;

			case STRING_STATE:
				d->string_data[num_strings] = &bp[i];
				state = INSTRING_STATE;

			case INSTRING_STATE:
				if (current_char == term_char) {
					bp[i] = '\0';
					string_hashes[num_strings++] = hash;
					hash = 0;
					term_char = c->string_term_chars[num_strings];
					state = NEXT_STATE;
				}
				hash ^= current_char;
				//rol(hash, 1);
				break;

			case SKIP_CHARS_STATE:
				if (current_char == c->skip_chars[cur_skip]) {
					//printf("	%c == %c, skipped: %i, looking for %i\n", current_char, c->skip_chars[cur_skip], skipped, c->skip_chars_count[cur_skip]);
					skipped++;
					if (c->skip_chars_count[cur_skip] == skipped) {
						// TODO: handle overflow
						cur_skip++;
						state=NEXT_STATE;
						//printf("state now %i, curskip: %i\n", state, cur_skip);
						skipped = 0;
					}
				}
				break;
			default: break;
			}
			if (state == NEXT_STATE) {
				step++;
				if (step == c->num_steps) { // done!
					i = br + 1;
					break;
				}
				state = c->state_steps[step];
				switch(state) {
				case LOOP_STATE:
				case END_STATE:
					c->callback(d);
					if (state == END_STATE)
						return 0;
					step = 0;
					state = c->state_steps[0];
					num_strings = 0;
					num_ints = 0;
					cur_skip = 0;
					term_char = c->string_term_chars[0];
					break;
				case SKIP_CHARS_STATE:
					skipped = 0;
					break;
				case STRING_STATE:
					d->string_data[num_strings] = NULL;
					break;
				default: break;
				}
			}
		}
		if (i > br)
			break;
		/* swap buffers */
		if (bp == buf1) {
			bp = buf2;
			obp = buf1;
		} else {
			if (state == INSTRING_STATE) {
				int strlen = (char *)&bp[i] - d->string_data[num_strings];
				memcpy(obp - strlen, bp + BUFSIZ - strlen, strlen);
				d->string_data[num_strings] = obp - strlen;
			}
			bp = buf1;
			obp = buf2;
		}
	}
	return 0;
}
