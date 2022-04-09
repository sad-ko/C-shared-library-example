all: build main libmal.plugin libspotify.plugin

build:
	@mkdir -p bin
	@mkdir -p bin/plugins
main: src/main.c
	gcc -g src/main.c -o bin/main
libmal.plugin: src/my_anime_list.c
	gcc -g src/my_anime_list.c -o bin/plugins/libmal.plugin -fPIC -shared
libspotify.plugin: src/spotify.c
	gcc -g src/spotify.c -o bin/plugins/libspotify.plugin -fPIC -shared