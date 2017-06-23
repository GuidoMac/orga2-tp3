; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

extern GDT_DESC
extern IDT_DESC
extern idt_inicializar
extern video_cols
extern video_fils
extern clean_screen
extern paint_screen
extern print
extern print_color
extern resetear_pic
extern habilitar_pic
extern mmu_inicializar_dir_kernel
extern mmu_inicializar
extern mmu_directorios
extern mmu_proxima_pagina_fisica_libre
extern mmu_mappear_pagina
extern mmu_desmappear_pagina
extern tss_inicializar
extern tss_inicializar_idle
extern tss_inicializar_zombi
extern inicializarTablero
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

nombre_equipo db        'No nos gusta adasdada...'
nombre_equipo_len equ   $ - nombre_equipo

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
    ; CS_0 Indice 8, TI 0, RPL 0,    0000000001000/000 en hexa = 0x0040
    ; DS_0 Indice 9 , TI 0, RPL 0,   0000000001001/000 en hexa = 0x0048  -> Este es el de data, hay que mover ds ahi
    ; CS_3 Indice 10 , TI 0, RPL 3,  0000000001010/011 en hexa = 0x0053
    ; DS_3 Indice 11 , TI 0, RPL 3,  0000000001011/011 en hexa = 0x005B
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
    ;call mmu_directorios
    ; Habilitar paginacion
    mov eax, 0x27000
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; Inicializar tss
    call tss_inicializar
    ;call tss_zombies
    ;call mapear_tss_zombies
    ; Inicializar tss de la tarea Idle
    call tss_inicializar_idle
    
    call tss_inicializar_zombi
    
    ; Inicializar el scheduler

    ; Inicializar la IDT
    call idt_inicializar
    ; Cargar IDT
    lidt [IDT_DESC]

    ; Configurar controlador de interrupciones
      call resetear_pic
      call habilitar_pic

      sti



    ; Cargar tarea inicial
    ; Indice 13 , TI 0, RPL 0,  0000000001101/000 en hexa = 0x0068 -> tss_inicial
    
    mov ax, 0x68
    ltr ax

    ; Habilitar interrupciones
    ;int 13
    ;xchg bx, bx
    ;sti
    ;INICIALIZACION DE PANTALLA

    push 0x70
    call paint_screen ;PINTAMOS LA PANTALLA DE VERDE
    
    call inicializarTablero

    ;IMPRIMOS EL NOMBRE DEL EQUIPO
    call video_cols ; eax <- VIDEO_COLS
    sub eax, nombre_equipo_len ; calculamos el offset a derecha del texto a imprimir
    sub eax, 5
    imprimir_texto_mp nombre_equipo, nombre_equipo_len, 0x05, 0, eax ; imprimos el texto con fondo verde y letra magenta

    ;PROBAR MMU
    ;call mmu_inicializar
    call mmu_proxima_pagina_fisica_libre
    ;xchg bx, bx
    push 0x55123
    push 0x27000
    push 0x400000
    call mmu_mappear_pagina
    ;xchg bx, bx
    ;SI HACES INFO TAB
    ;DEBERIA HABER UN RENGLON QUE DICE 0x00400000-0x00400fff -> 0x000000055000-0x000000055fff
    push 0x27000
    push 0x400000
    call mmu_desmappear_pagina
    ;xchg bx, bx
    ;SI HACES INFO TAB
    ;NO DEBERIA HABER UN RENGLON QUE DICE 0x00400000-0x00400fff -> 0x000000055000-0x000000055fff


    ; Saltar a la primera tarea: Idle
    ; Indice 14 , TI 0, RPL 0,  0000000001110/000 en hexa = 0x0070 -> tss_idle
    ;jmp 0x70:0 ;saltando a idle
    ; Indice 16 , TI 0, RPL 0,  0000000010000/011 en hexa = 0x0103 -> tss_zombi1_A
    xchg bx, bx
    jmp 0x103:0 ;saltando a la tarea zombie 1 a
    
    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
