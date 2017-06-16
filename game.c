/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "screen.h"


jugador a= (jugador){0, 22, 1, "C", 0x40};

jugador b= (jugador){79,22,-1,"C", 0x12};


void handle_key_press(int scan_code) {
	
	switch(scan_code) {
		case 0x11 : {
			a.y= (a.y -1) % -45;
			if(a.y == 0) a.y = 44;
			//print_int(a.y, 0, 0, 0x07);
			break;
		}
		case 0x1f : {
			a.y= (a.y +1) % 45;
			//print_int(a.y, 0, 0, 0x07);
			break;
		}
		case 0x48 : {
			b.y= (b.y -1) % -45;
			if(b.y == 0) b.y = 44;
			//print("Handle 272", 0, 0, 0x07);
			break;	
		} 
		case 0x50 : {
			b.y= (b.y +1)  % 45;
			//print("Handle 280", 0, 0, 0x07);
			break;
		}

		case 0x20 : {
			//a.currentZombie= ;
			//print_int(a.y, 0, 0, 0x07);
			break;
		}
		case 0x1E : {
			//a.currentZombie= ;
			break;
		}
		case 0x4D : {
			break;	
		} 
		case 0x4B : {
			break;
		}
	}
	inicializarTablero();
	print_hex(scan_code, 3, 0, 0, 0x07);
} 

void print_player(jugador j) {
	print(j.currentZombie, j.x, j.y, j.color_attr);
}
void inicializarTablero() {
	paint_screen(0x70);
	print_color(0x40,0,1,0,VIDEO_FILS);
	print_color(0x10,VIDEO_COLS-1,VIDEO_COLS,0,VIDEO_FILS);
	print_color(0x60,0,VIDEO_COLS,0,1);
	print_color(0x60,0,VIDEO_COLS,VIDEO_FILS-5,VIDEO_FILS);
	print_color(0x40,VIDEO_COLS/2-5, VIDEO_COLS/2,VIDEO_FILS-5,VIDEO_FILS);
	print_color(0x10,VIDEO_COLS/2, VIDEO_COLS/2+5,VIDEO_FILS-5,VIDEO_FILS);
	print_player(a);
	print_player(b);
}	
void game_jugador_mover(unsigned int jugador, unsigned int value) {
}
void game_lanzar_zombi(unsigned int jugador) {
}
void game_move_current_zombi(direccion dir) {
}
