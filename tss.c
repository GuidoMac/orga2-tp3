/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;

tss tss_zombi;

tss tss_zombisA[CANT_ZOMBIS];
tss tss_zombisB[CANT_ZOMBIS];

void tss_inicializar() {
    //asumimos que tss_inical arranca todo en 0;
    tss_inicial = (tss) {0};
    gdt[GDT_IDX_TAREA_INICIAL].base_0_15 = (unsigned short) (int)&tss_inicial;
    gdt[GDT_IDX_TAREA_INICIAL].base_23_16 = (unsigned char) ((int)&tss_inicial >> 16); 
    gdt[GDT_IDX_TAREA_INICIAL].base_31_24 = (unsigned char) ((int)&tss_inicial >> 24);  
}

void tss_inicializar_zombi() {

    tss_zombi.ptl = 0;
    tss_zombi.unused0 = 0;
    tss_zombi.esp0 = 0;
    tss_zombi.ss0 = 0;
    tss_zombi.unused1 = 0;
    tss_zombi.esp1 = 0;
    tss_zombi.ss1 = 0;
    tss_zombi.unused2 = 0;
    tss_zombi.esp2 = 0;
    tss_zombi.ss2 = 0;
    tss_zombi.unused3 = 0;
    tss_zombi.eip = 0x00010000;
    tss_zombi.eflags = 0x00000202;
    tss_zombi.eax = 0;
    tss_zombi.ecx = 0;
    tss_zombi.edx = 0;
    tss_zombi.ebx = 0;

    //unsigned int pila = mmu_proxima_pagina_fisica_libre();
    tss_zombi.esp = 0x11000;
    tss_zombi.ebp = 0x11000;

    tss_zombi.esi = 0;
    tss_zombi.edi = 0;
    tss_zombi.es = 0x48;
    tss_zombi.unused4 = 0;
    tss_zombi.cs = 0x40;
    tss_zombi.unused5 = 0;
    tss_zombi.ss = 0x48;
    tss_zombi.unused6 = 0;
    tss_zombi.ds = 0x48;
    tss_zombi.unused7 = 0;
    tss_zombi.fs = 0x60;
    tss_zombi.unused8 = 0;
    tss_zombi.gs = 0x48;
    tss_zombi.unused9 = 0;
    tss_zombi.ldt = 0;
    tss_zombi.unused10 = 0;
    tss_zombi.dtrap = 0;
    tss_zombi.iomap = 0xffff;

    tss_zombi.cr3 = (unsigned int) mmu_inicializar_dir_zombi(0,0);

    gdt[GDT_IDX_TAREA_ZOMBI].base_0_15 = (unsigned short) (int)&tss_zombi;
    gdt[GDT_IDX_TAREA_ZOMBI].base_23_16 = (unsigned char) ((int)&tss_zombi >> 16); 
    gdt[GDT_IDX_TAREA_ZOMBI].base_31_24 = (unsigned char) ((int)&tss_zombi >> 24);  
}

void tss_inicializar_idle() {
	tss_idle.ptl = 0;
    tss_idle.unused0 = 0;
    tss_idle.esp0 = 0;
    tss_idle.ss0 = 0;
    tss_idle.unused1 = 0;
    tss_idle.esp1 = 0;
    tss_idle.ss1 = 0;
    tss_idle.unused2 = 0;
    tss_idle.esp2 = 0;
    tss_idle.ss2 = 0;
    tss_idle.unused3 = 0;
    tss_idle.cr3 = 0x27000;
    tss_idle.eip = 0x16000;
    tss_idle.eflags = 0x00000202;
    tss_idle.eax = 0;
    tss_idle.ecx = 0;
    tss_idle.edx = 0;
    tss_idle.ebx = 0;
    tss_idle.esp = 0x27000;
    tss_idle.ebp = 0x27000;
    tss_idle.esi = 0;
    tss_idle.edi = 0;
    tss_idle.es = 0x48;
    tss_idle.unused4 = 0;
    tss_idle.cs = 0x40;
    tss_idle.unused5 = 0;
    tss_idle.ss = 0x48;
    tss_idle.unused6 = 0;
    tss_idle.ds = 0x48;
    tss_idle.unused7 = 0;
    tss_idle.fs = 0x60;
    tss_idle.unused8 = 0;
    tss_idle.gs = 0x48;
    tss_idle.unused9 = 0;
    tss_idle.ldt = 0;
    tss_idle.unused10 = 0;
    tss_idle.dtrap = 0;
    tss_idle.iomap = 0xffff;

    gdt[GDT_IDX_TAREA_IDLE].base_0_15 = (unsigned short) (int)&tss_idle;
    gdt[GDT_IDX_TAREA_IDLE].base_23_16 = (unsigned char) ((int)&tss_idle >> 16); 
    gdt[GDT_IDX_TAREA_IDLE].base_31_24 = (unsigned char) ((int)&tss_idle >> 24);  

}