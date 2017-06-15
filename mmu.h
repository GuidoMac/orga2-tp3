/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

#define INICIO_PAGINAS_LIBRES 0x100000;
#define PAGE_SIZE 0x1000;
#define PDE_INDEX(virtual) (virtual >> 22)
#define PTE_INDEX(virtual) ((virtual << 10) >> 22)
#define PG_READ_WRITE 0x00000002
#define PG_USER 0x00000004
#define PG_PRESENT 0x00000001

typedef struct pde_t {
	unsigned char   p:1;
    unsigned char   rw:1;
    unsigned char   us:1;
    unsigned char   pwt:1;
    unsigned char   pcd:1;
    unsigned char   a:1;
    unsigned char   ign:1;
    unsigned char   ps:1;
    unsigned char	igns:4;
    unsigned int 	base:20;
    
} __attribute__((__packed__)) pde_t;

typedef struct pte_t {
	unsigned char   p:1;
	unsigned char   rw:1;
    unsigned char   us:1;
    unsigned char  	pwt:1;
    unsigned char   pcd:1;
    unsigned char   a:1;
    unsigned char   d:1;
    unsigned char   pat:1;
    unsigned char   g:1;
    unsigned char	igns:3;
    unsigned int 	base:20;
    
} __attribute__((__packed__)) pte_t;




void mmu_inicializar_dir_kernel();

void mmu_inicializar();

void mmu_directorios();

unsigned int mmu_proxima_pagina_fisica_libre();

void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica, unsigned short r_w, unsigned short u_s);

void mmu_desmappear_pagina(unsigned int virtual, unsigned int dir_pd);

pde_t * mmu_inicializar_dir_zombi(unsigned int posJug, unsigned int jugador);

#endif	/* !__MMU_H__ */




