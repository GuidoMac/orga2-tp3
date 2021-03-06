/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [GDT_IDX_CODE0_DESC] = (gdt_entry) {
        (unsigned short)    0x4c0c,         /* limit[0:15]  */ //Preguntar.
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [GDT_IDX_DATA0_DESC] = (gdt_entry) {
        (unsigned short)    0x4c0c,         /* limit[0:15]  */ //Preguntar.
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [GDT_IDX_CODE3_DESC] = (gdt_entry) {
        (unsigned short)    0x4c0c,         /* limit[0:15]  */ //Preguntar.
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [GDT_IDX_DATA3_DESC] = (gdt_entry) {
        (unsigned short)    0x4c0c,         /* limit[0:15]  */ //Preguntar.
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    [GDT_IDX_VIDEO_DESC] = (gdt_entry) {
        (unsigned short)    0x2000,         /* limit[0:15]  */ // CHEQUEAR SI ES 2000 O 1000 PORQUE EN EL PDF PARECE QUE DEBERIA SER 2000.
        (unsigned short)    0x8000,         /* base[0:15]   */
        (unsigned char)     0x0B,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x02,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    [GDT_IDX_TAREA_INICIAL] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // CHEQUEAR SI ES 2000 O 1000 PORQUE EN EL PDF PARECE QUE DEBERIA SER 2000.
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. ARCHIVO TSS.C
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    [GDT_IDX_TAREA_IDLE] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. ARCHIVO TSS.C
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */ //Level 0 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI1_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI2_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI3_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI4_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },
    [GDT_IDX_TAREA_ZOMBI5_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI6_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI7_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI8_A] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI1_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI2_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI3_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI4_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },
    [GDT_IDX_TAREA_ZOMBI5_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI6_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI7_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

    [GDT_IDX_TAREA_ZOMBI8_B] = (gdt_entry) {
        (unsigned short)    0x0067,         /* limit[0:15]  */ // LA TAREA OCUPA UNA PAGINA DE 4K !! SINO NO ANDA
        (unsigned short)    0x0000,         /* base[0:15]   */ //SE CARGAN EN RUNTIME. Atendiendo la interrupcion de teclado
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */ //Level 3 Privilege Level
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */ //Available for system software - 0
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0X00,           /* base[31:24]  */
    },

};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};
