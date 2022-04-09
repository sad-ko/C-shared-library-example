/* ----------------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
#include "plugins.h"
/* ----------------------------------------------------------------------------------- */
#define PLUGINS_EXTENSION ".plugin"
#define PLUGINS_FOLDER 	  "./plugins/"
#define PLUGINS_CHECK(file) (file->d_type == DT_REG && \
	strcmp(strrchr(file->d_name, '.'), PLUGINS_EXTENSION) == 0)
/* ----------------------------------------------------------------------------------- */
char* get_from_plugin(const char* plugin_name, plugin_function what, const char* arg) {
	const char* error_msg;
	void* lib_handler = NULL;
	char* str = NULL;

	lib_info info_handler;
	lib_name name_handler;

	lib_handler = dlopen(plugin_name, RTLD_LAZY);
	if(!lib_handler) {
		fprintf(stderr, "[ERROR] - %s\n", dlerror());
		goto error;
	}

	switch(what) {
		case INFO:
			info_handler = dlsym(lib_handler, "get_info");
			break;
		
		case NAME:
			name_handler = dlsym(lib_handler, "get_name");
			break;
	}
	
	error_msg = dlerror();
	if(error_msg) {
		fprintf(stderr, "[ERROR] - %s: %s\n", what, error_msg);
		goto error;
	}

	switch(what) {
		case INFO:
			str = info_handler(arg);
			break;
		
		case NAME:
			str = name_handler();
			break;
	}

	dlclose(lib_handler);

	return str;

error:
	if(lib_handler) {
		dlclose(lib_handler);
	}
	return NULL;
}
/* ----------------------------------------------------------------------------------- */
size_t get_total_plugins() {
	DIR *dir;
	struct dirent *file;
	size_t files_amount = 0;

	dir = opendir("./plugins");
	if(dir) {
		while((file = readdir(dir)) != NULL) {
			if(PLUGINS_CHECK(file)) {
				files_amount++;
			}
		}
		closedir(dir);
	}

	return files_amount;
}
/* ----------------------------------------------------------------------------------- */
int get_plugins(char** plugins, size_t amount) {
	char* folder = PLUGINS_FOLDER;
	size_t f_size = strlen(folder);

	DIR *dir;
	struct dirent *file;

	dir = opendir(PLUGINS_FOLDER);
	if(!dir) {
		return 0;
	}

	for(size_t i = 0; (file = readdir(dir)) != NULL && i < amount; ) {
		if(PLUGINS_CHECK(file)) {
			size_t fn_size = strlen(file->d_name);

			plugins[i] = (char*) calloc(f_size + fn_size + 1, sizeof(char));
			if(!plugins[i]) return 0;

			strncpy(plugins[i], folder, f_size);
			strncat(plugins[i], file->d_name, fn_size);

			i++; //
		}
	}

	closedir(dir);
	return 1;
}
/* ----------------------------------------------------------------------------------- */
int print_menu(char** plugins, size_t amount) {
	puts("---------------------------------------");
	for(size_t i = 0; i < amount; i++) {
		char* plugin_name = get_from_plugin(plugins[i], NAME, NULL);
		if(!plugin_name) {
			return 0;
		}

		printf("%d - Get info from '%s'\n", i+1, plugin_name);
		free(plugin_name);
	}
	puts("0 - Exit");
	puts("---------------------------------------");
	return 1;
}
/* ----------------------------------------------------------------------------------- */
int main_loop(char** plugins, size_t amount) {
	int input = 0;
	char* info = NULL;

	while(print_menu(plugins, amount) && scanf("%d", &input) && input) {
		char name[255];

		if(input-1 >= amount) {
			break;
		}

		while(strncmp(fgets(name, 254, stdin), "\n", 1) == 0) {}
		name[strcspn(name,"\n")] = '\0';

		info = get_from_plugin(plugins[input - 1], INFO, name);

		if(!info) {
			char* plugin_name = get_from_plugin(plugins[input - 1], NAME, NULL);
			if(!plugin_name) {
				return 0;
			}
			fprintf(stderr, "[ERROR] - get_info from %s did not work as expected.\n", plugin_name);
			free(plugin_name);
			return 0;
		}

		puts("---------------------------------------");
		printf("%s", info);
		puts("---------------------------------------");

		free(info);
	}

	return 1;
}
/* ----------------------------------------------------------------------------------- */
int main() {
	char** plugins = NULL;
	size_t total_plugins = get_total_plugins();

	//init
	if(!total_plugins) {
		fprintf(stderr, "[ERROR] - No plugins to load.\n");
		goto error;
	}

	plugins = (char**) malloc(total_plugins * sizeof(char*));
	if(!plugins || !get_plugins(plugins, total_plugins)) {
		fprintf(stderr, "[ERROR] - Can't get list of plugins.\n");
		goto error;
	}

	//main
	if(!main_loop(plugins, total_plugins)) {
		goto error;
	}

	//clean
	for(size_t i = 0; i < total_plugins; i++) {
		free(plugins[i]);
	}
	free(plugins);

	return 0;

error:
	if(plugins) {
		for(size_t i = 0; i < total_plugins; i++) {
			free(plugins[i]);
		}
		free(plugins);
	}

	return 1;
}
/* ----------------------------------------------------------------------------------- */
