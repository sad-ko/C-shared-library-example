if [ $# -eq 0 ]; then
	make
	cd bin
	echo "-----------------------------"
	echo "PROGRAM START"
	echo "-----------------------------"
	./main
elif [ $1 == "-v" ]; then
	make
	cd bin
	echo "-----------------------------"
	echo "PROGRAM START - with Valgrind"
	echo "-----------------------------"
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./main
elif [ $1 == "-h" ]; then
	echo "-v - Runs compiled program with valgrind."
	echo "[NO ARGUMENTS] - Runs compiled programs as is."
else
	echo "[ERROR] - $1 is an invalid option."
	echo "./run.sh -h for more information."
	exit 1
fi