; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

extern GDT_DESC
extern clean_screen
extern mmu_inicializar_dir_kernel
extern mmu_inicializar
extern mmu_directorios
global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font
    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


    ; Habilitar A20
    call habilitar_A20
    ; Cargar la GDT
    lgdt [GDT_DESC]
    ; Setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    ; Saltar a modo protegido
    ;xchg bx, bx
    jmp (8<<3):modoprotegido ; Aca seteo automaticamente el procesador el CS 
    


    BITS 32
    
    modoprotegido:
    
    ; Establecer selectores de segmentos
    xor eax, eax
    ; 0 a 1 va RPL (Requested Privileg Level) - 2 va (0 si es GDT - 1 si es LDT) - 3 a 15 Index
    ; Indice 8, TI 0, RPL 0,    0000000001000/000 en hexa = 0x0040
    ; Indice 9 , TI 0, RPL 0,   0000000001001/000 en hexa = 0x0048  -> Este es el de data, hay que mover ds ahi
    ; Indice 10 , TI 0, RPL 3,  0000000001010/011 en hexa = 
    ; Indice 11 , TI 0, RPL 3,  0000000001011/011 en hexa = 
    ; Indice 12 , TI 0, RPL 0,  0000000001100/000 en hexa = 0x0060 -> VIDEO
    mov ax, 0x48
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    mov ax, 0x60
    mov fs, ax
    ; Establecer la base de la pila
    mov esp, 0x27000
    mov ebp, 0x27000



    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0
    ; Inicializar pantalla
    call clean_screen
    ; Inicializar el manejador de memoria  

    call mmu_inicializar
    ; Inicializar el directorio de paginas
    call mmu_inicializar_dir_kernel
    
    ; Cargar directorio de paginas
    call mmu_directorios
    ; Habilitar paginacion
    
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT

    ; Cargar IDT

    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
