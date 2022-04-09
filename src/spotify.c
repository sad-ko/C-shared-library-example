/* ----------------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "plugins.h"
/* ----------------------------------------------------------------------------------- */
#define NAME "Spotify"
/* ----------------------------------------------------------------------------------- */
char* get_info(const char* song_name) {
	char* info;
	int minutes;
	int seconds;
	size_t info_len;

	//""Buscando"" la data en su database
	srand(time(0));
	minutes = rand() % (60 + 1 - 1) + 1;
	seconds = rand() % (60 + 1 - 1) + 1;

	//Formateando la data
	calculate_string_size("Name: %s\nDuration: %d:%d\n", info_len, song_name, minutes, seconds);
	create_string(info, info_len);

	sprintf(info, "Name: %s\nDuration: %d:%d\n", song_name, minutes, seconds);

	return info;
}
/* ----------------------------------------------------------------------------------- */
char* get_name() {
	char *name;
	size_t name_size = strlen(NAME);

	create_string(name, name_size);
	strncpy(name, NAME, name_size);

	return name;
}
/* ----------------------------------------------------------------------------------- */