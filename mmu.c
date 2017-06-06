/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

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

}



void mmu_directorios() {

}

