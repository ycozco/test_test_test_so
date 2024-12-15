bits 16
org 0x7c00

global _start
_start:
    mov ah, 0x0e    ; Función de mostrar caracteres en pantalla
    mov al, 'H'
    int 0x10
    mov al, 'i'
    int 0x10

    cli             ; Deshabilitar interrupciones
    hlt             ; Detener CPU

times 510-($-$$) db 0 ; Llenar con ceros hasta los 512 bytes
dw 0xaa55            ; Firma de arranque
