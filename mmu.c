/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
unsigned int proxima_pagina_libre;


pde_t * mmu_inicializar_dir_zombi(unsigned int posJug, unsigned int jugador) {
	pde_t * pde = (pde_t *) mmu_proxima_pagina_fisica_libre();
	int i;

	for(i=0;i*0x1000<0x400000;i++) {
		mmu_mappear_pagina(i*0x1000,(unsigned int)pde,i*0x1000, 0, 0);
	}

	/*
	Funcion para 'ubicarlo en el mapa'
	*/

/*	if(jugador == 0){ //Jugador A

	} else { // Jugador B
		//algo
	}*/
	return pde;
}

void mmu_inicializar_dir_kernel() {

	pde_t * pde = (pde_t*) 0x27000;
	int i;
	for(i = 0; i < 1024 ; i++) {
		pde[i].p = 0;
	}
	int ReadWrite = 1;
	int UserSuper = 1;

	//crea la primer entrada del directorio de tabla de paginas con una tabla de paginas en la direccion 0x28000
	//la crea con privilegios de kernel y de lectura
	pde[0].base = 0x28000 >> 12;
	pde[0].rw = ReadWrite;
	pde[0].p = 1;  // Present
	pde[0].us = UserSuper;
	pde[0].pwt = 0;
	pde[0].pcd = 0;
	pde[0].a = 0;
	pde[0].ign = 0;
	pde[0].ps = 0;

	//Hace identity mapping entre 0x0 y 0x003FFFFF (Kernel + Area Libre)

	for(i = 0;i*0x1000<0x0400000; i++) {
		mmu_mappear_pagina(i*0x1000,(unsigned int)pde,i*0x1000, ReadWrite, UserSuper);
	}

}


void mmu_inicializar() {
	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	return pagina_libre;
}


void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica, unsigned short r_w, unsigned short u_s) {
	//descomponer la direccion virtual en los 3 indices
	//con la dir_pd y el indice, obtener el dir_td
	//si el dir_td no existe, crearlo y setear el dir_pd para que conozca el nuevo dir_td
	//con el dir_td y el indice, obtener el dir_pe
	//completar el dir_pe con la dir fisica de parametro. salvo los ultimos 12 bits. fisica << 12;
	//dir_pd = direccion del page directory
	//dir_td = direccion del page table
	//dir_pe = direccion del page table entry
	pde_t * pd_table = (pde_t*) dir_pd;
	unsigned int idx_pd_entry = PDE_INDEX(virtual);
	unsigned int idx_pt_entry = PTE_INDEX(virtual);
	pde_t pd_entry = pd_table[idx_pd_entry];
	//pd_enty es el descriptor de la pagina que contiene la tabla de descriptores de paginas
	if (pd_entry.p == 0) { 
		//Si no esta presente en memoria. Es decir que no hay una pagina que contenga el directorio de paginas
		//Hay que crearlo.
		pte_t * p_table = (pte_t*) mmu_proxima_pagina_fisica_libre();
		int i;
		for(i = 0; i < 1024 ; i++) {
			p_table[i].p = 0;
		}
		//creo la pagina con la tabla de paginas con todas las paginas no presentes.

		pd_entry.base = (unsigned int)p_table >> 12;
		pd_entry.p = 1; //present = 1 => tabla de paginas en memoria 
		pd_entry.ps = 0; //page_size = 0 => paginas de 4KB
		pd_entry.a = 0;; //accessed = 0 => no fue accedida
		pd_entry.pcd = 0; // page cache disabled = 0 // Cacha Habilitado
		pd_entry.pwt = 0; // page write through = 0 // Escribe Cache y Memoria en el mismo write
		pd_entry.us = u_s; //recibe el parametro para saber si la pagina sera de usuario o kernel
		pd_entry.rw = r_w; //recibe el parametro para saber si la pagina sera de escritura o lectura
	}
	pte_t * p_table = (pte_t*) ((unsigned int)(pd_entry.base << 12)); //recupero la tabla de paginas
	p_table[idx_pt_entry].base = fisica >> 12; //le asigno los 20bits de la pagina fisica a acceder
	p_table[idx_pt_entry].p = 1; //seteo en presente el p_table[idx_pt_entry]
	p_table[idx_pt_entry].pat = 0; //no quiero PAT
	p_table[idx_pt_entry].g = 0; //no es global
	p_table[idx_pt_entry].d = 0; // no esta dirty
	p_table[idx_pt_entry].a = 0; // no fue accedida
	p_table[idx_pt_entry].us = u_s; 
	p_table[idx_pt_entry].rw = r_w;
}

/*
void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica) {
	pde_t* pd = (pde_t*) dir_pd;
	// TO-DO: MACRO
	unsigned int indice_directorio = PDE_INDEX(virtual);
	unsigned int indice_tabla = PTE_INDEX(virtual);
	if (pd[indice_directorio].p == 0) {
		pd[indice_directorio].base = mmu_proxima_pagina_fisica_libre() >> 12;
		pd[indice_directorio].p = 1;
	}
	pte_t* pte = (pte_t*)(pd[indice_directorio].base << 12);
	pte[indice_tabla].base  = fisica >> 12;	
	
}
*/
void mmu_desmappear_pagina(unsigned int virtual, unsigned int dir_pd) {
	pde_t* pd = (pde_t*) dir_pd;
	unsigned int indice_directorio = PDE_INDEX(virtual);
	unsigned int indice_tabla = PTE_INDEX(virtual);
	pte_t* pte = (pte_t*)(pd[indice_directorio].base << 12);
	pte[indice_tabla].base = 0;
	pte[indice_tabla].p = 0;
	pte[indice_tabla].rw = 0;
	pte[indice_tabla].us = 0;
	pte[indice_tabla].pwt = 0;
	pte[indice_tabla].pcd = 0;
	pte[indice_tabla].a = 0;
	pte[indice_tabla].d = 0;
	pte[indice_tabla].pat = 0;
	pte[indice_tabla].g = 0;
}


void mmu_directorios() {

}

