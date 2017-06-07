/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
unsigned int proxima_pagina_libre;

void mmu_inicializar_dir_kernel() {

//	unsigned int* pepe =  (int*)(0x27000) 

//pepe[0] = 0x00028003;




	//directorio-> crear lista de tablas
	//crear lista de paginas
	pde_t* pde = (pde_t*) 0x27000;
	int i;
	pde[0].base = 0x28; // Base
	pde[0].rw = 1; // Read/Write
	pde[0].p = 1;  // Present
	pde[0].us = 0;
	pde[0].pwt = 0;
	pde[0].pcd = 0;
	pde[0].a = 0;
	pde[0].ign = 0;
	pde[0].ps = 0;
	for(i = 1; i < 0x1000; i++) {
		pde[i].base = 0; // Base
		pde[i].p = 0;
		pde[i].rw = 0; // Read/Write
		pde[i].us = 0;
		pde[i].pwt = 0;
		pde[i].pcd = 0;
		pde[i].a = 0;
		pde[i].ign = 0;
		pde[i].ps = 0;
	}

	pte_t* pte = (pte_t*)(pde[0].base << 12);
	//pte_t* pte = (pte_t*) 0x28000;

	for(i = 0; i < 0x1000; i++) {
		pte[i].base = i;
		pte[i].p = 1;
		pte[i].rw = 1;
		pte[i].us = 0;
		pte[i].pwt = 0;
		pte[i].pcd = 0;
		pte[i].a = 0;
		pte[i].d = 0;
		pte[i].pat = 0;
		pte[i].g = 0;
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

void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica) {
	pde_t* pd = (pde_t*) dir_pd;
	// TO-DO: MACRO
	unsigned int indice_directorio = PDE_INDEX(virtual);
	unsigned int indice_tabla = PTE_INDEX(virtual);
	if(pd[indice_directorio].base == 0) {
		pte_t pte[0x1000];
		
		pd[indice_directorio].base = (int)(&pte[0])  >> 12;
		pd[indice_directorio].p = 1;
		int i;
		for(i = 0; i < 0x1000; i++) {
			pte[i].base = 0;
			pte[i].p = 0;
			pte[i].rw = 0;
			pte[i].us = 0;
			pte[i].pwt = 0;
			pte[i].pcd = 0;
			pte[i].a = 0;
			pte[i].d = 0;
			pte[i].pat = 0;
			pte[i].g = 0;
		}
	}
	pte_t* pte = (pte_t*)(pd[indice_directorio].base << 12);
	pte[indice_tabla].base = fisica >> 12;
	pte[indice_tabla].p = 1;
	pte[indice_tabla].rw = 1;
	pte[indice_tabla].us = 0;
	pte[indice_tabla].pwt = 0;
	pte[indice_tabla].pcd = 0;
	pte[indice_tabla].a = 0;
	pte[indice_tabla].d = 0;
	pte[indice_tabla].pat = 0;
	pte[indice_tabla].g = 0;
}

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

