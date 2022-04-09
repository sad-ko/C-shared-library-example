/* ----------------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "plugins.h"
/* ----------------------------------------------------------------------------------- */
#define NAME "My Anime List"
/* ----------------------------------------------------------------------------------- */
char* get_info(const char* anime_name) {
	char* info;
	float rating;
	int episodes;
	size_t info_len;

	//""Buscando"" la data en su database
	srand(time(0));
	rating = ((float) rand() / RAND_MAX) * 10.0;
	episodes = rand() % (24 + 1 - 3) + 3;

	//Formateando la data
	calculate_string_size("Name: %s\nRating: %.2f\nEpisodes: %d\n", info_len, anime_name, rating, episodes);
	create_string(info, info_len);

	sprintf(info, "Name: %s\nRating: %.2f\nEpisodes: %d\n", anime_name, rating, episodes);

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