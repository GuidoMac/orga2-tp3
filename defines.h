/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define SIZE_W                  78
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 32

#define GDT_IDX_NULL_DESC       0
#define GDT_IDX_CODE0_DESC      8
#define GDT_IDX_DATA0_DESC      9
#define GDT_IDX_CODE3_DESC      10
#define GDT_IDX_DATA3_DESC      11
#define GDT_IDX_VIDEO_DESC      12
#define GDT_IDX_TAREA_INICIAL	13
#define GDT_IDX_TAREA_IDLE		14
#define GDT_IDX_TAREA_ZOMBI		15
#define GDT_IDX_TAREA_ZOMBI1_A	16
#define GDT_IDX_TAREA_ZOMBI2_A	17
#define GDT_IDX_TAREA_ZOMBI3_A	18
#define GDT_IDX_TAREA_ZOMBI4_A	19
#define GDT_IDX_TAREA_ZOMBI5_A	20
#define GDT_IDX_TAREA_ZOMBI6_A	21
#define GDT_IDX_TAREA_ZOMBI7_A	22
#define GDT_IDX_TAREA_ZOMBI8_A	23
#define GDT_IDX_TAREA_ZOMBI1_B	24
#define GDT_IDX_TAREA_ZOMBI2_B	25
#define GDT_IDX_TAREA_ZOMBI3_B	26
#define GDT_IDX_TAREA_ZOMBI4_B	27
#define GDT_IDX_TAREA_ZOMBI5_B	28
#define GDT_IDX_TAREA_ZOMBI6_B	29
#define GDT_IDX_TAREA_ZOMBI7_B	30
#define GDT_IDX_TAREA_ZOMBI8_B	31
/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

#endif  /* !__DEFINES_H__ */
