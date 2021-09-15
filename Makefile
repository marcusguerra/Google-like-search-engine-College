main: main.c
	gcc -Wno-format -o main-bin main.c dicionario.c indice_invertido.c listaencadeada.c patricia.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
