.section .multiboot
.align 4
.long 0x1BADB002        /* Identificador de Multiboot */
.long 0x00              /* Flags (sin requisitos adicionales) */
.long -(0x1BADB002)     /* Suma de verificación */

/* Punto de entrada del kernel */
.section .text
.global _start
.extern main
_start:
    call main           /* Llamar a la función main() en el kernel */
    cli                 /* Deshabilitar interrupciones */
loop:
    hlt                 /* Detener la CPU */
    jmp loop            /* Mantenerse en bucle */
