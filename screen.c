/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}


void clean_screen() {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int f;
    for(f = 0; f < VIDEO_FILS; f++) {
        int c;
        for(c = 0; c < VIDEO_COLS; c++) {
            p[f][c].c = ' ';
            p[f][c].a = C_BG_BLACK;
        }
    }
}

void print_color(unsigned short color,  unsigned int x,  unsigned int xLim,  unsigned int y, unsigned int yLim){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int f;
    for(f = y; f < yLim; f++) {
        int c;
        for(c = x; c < xLim; c++) {
            p[f][c].c = ' ';
            p[f][c].a = color;
        }
    }
}

void paint_screen(unsigned short color) {
    print_color(color, 0,VIDEO_COLS, 0, VIDEO_FILS);
}

void print_interrupcion(unsigned int interrupcion) {
    clean_screen();
    paint_screen(0x40);
    int i;
    int j;
    for (i = 0; i < VIDEO_COLS; i+= 7)
    {
        for (j = 0; j < VIDEO_FILS; j++)
        {
            if(j%2 == 0 && i%2 ==0){
                print("Error", i , j, 0x8F);
                print_int(interrupcion, i + 6, j, 0x8F);
            } else {
                print("Error", i , j, 0x0F);
                print_int(interrupcion, i + 6, j, 0x0F);
            }
        }
       
    }
    
}


int video_cols() {
    return VIDEO_COLS;
}
int video_fils() {
    return VIDEO_FILS;
}




