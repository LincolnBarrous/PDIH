//Periféricos y Dispositivos Interfaz Humana
//Práctica2
//Antonio Jesús Ruiz Gómez
//Archivo: PongPong.c
//Recreamos el juego de PingPong.

//Inclusión de las librerías
#include <ncurses.h>
#include <unistd.h>

#define DELAY 80000 //Retardo para evitar rápidez de la pelota

int main(int argc, char *argv[])
{
	int fils, cols;
	int max_x, max_y;
	int pelota_x, pelota_y;
	bool parar = false;
	int pala1 = 3;		 //Pala jugador izda
	int pala2 = 3;		 //Pala jugador dcha
	int puntos1 = 0;	 //Puntos jugador izda
	int puntos2 = 0;	 //Puntos jugador dcha
	int next_x = 0;		 //siguiente paso de la pelota coordenada x
	int next_y = 0;		 //siguiente paso de la pelota coordenada y
	int directionx = -1; //-1 izquierda , 1 derecha
	int directiony = 1;  //-1 arriba, 1 abajo

	initscr();
	noecho();
	curs_set(FALSE);
	clear();
	refresh();

	//Instrucciones de Juego

	getmaxyx(stdscr, fils, cols);

	WINDOW *window = newwin(fils, cols, 0, 0);
	box(window, '|', '-');
	mvwprintw(window, 5, 5, "Este es el juego del PingPong");
	mvwprintw(window, 6, 5, "Jugador Izq mueve con 'w' y 's' y Jugador Drcha con 'p' y 'i' y 'k'");
	mvwprintw(window, 7, 5, "Pulsar tecla para comenzar");
	mvwprintw(window, 8, 5, "Pulsar 'e' para salir del juego");
	wrefresh(window);
	getch();

	nodelay(stdscr, 1);

	//Posicion de la pelota
	getmaxyx(stdscr, max_y, max_x);
	pelota_x = max_x / 2;
	pelota_y = max_y / 2;

	//Juego

	while (!parar)
	{
		clear();

		//Dibujamos la pelota y las palas
		mvprintw(pelota_y, pelota_x, "o");

		mvprintw(pala1, 0, "|");
		mvprintw(pala1 + 1, 0, "|");
		mvprintw(pala1 + 2, 0, "|");
		mvprintw(pala1 + 3, 0, "|");
		mvprintw(pala1 + 4, 0, "|");
		mvprintw(pala1 + 5, 0, "|");

		mvprintw(pala2, cols - 1, "|");
		mvprintw(pala2 + 1, cols - 1, "|");
		mvprintw(pala2 + 2, cols - 1, "|");
		mvprintw(pala2 + 3, cols - 1, "|");
		mvprintw(pala2 + 4, cols - 1, "|");
		mvprintw(pala2 + 5, cols - 1, "|");

		//Dibujamos linea divisoria
		mvvline(0, max_x / 2, ACS_VLINE, max_y);

		//Contadores
		mvprintw(2, max_x / 2 - 2, "%i | %i", puntos1, puntos2);

		refresh();
		usleep(DELAY);

		next_x = pelota_x + directionx;
		next_y = pelota_y + directiony;

		if (next_x >= max_x || next_x < 0){
			directionx *= -1;
		}
		else{
			pelota_x += directionx;
		}

		if (next_y >= max_y || next_y < 0){
			directiony *= -1;
		}
		else{
			pelota_y += directiony;
		}

		switch (getch())
		{
		case 'w':
			if (pala1 > 1){
				pala1--;
			}
			break;
		case 's':
			if (pala1 < cols - 8){
				pala1++;
			}
			break;
		case 'i':
			if (pala2 > 1){
				pala2--;
			}
			break;
		case 'k':
			if (pala2 < cols - 8){
				pala2++;
			}
			break;
		case 'e':
			parar = true;
			break;
		}
	}

	endwin();
	return 0;
}
