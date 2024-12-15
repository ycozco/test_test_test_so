ENTRY(_start)

SECTIONS
{
    . = 0x00100000; /* Dirección base del kernel */

    .multiboot :
    {
        *(.multiboot) /* Encabezado Multiboot */
    }

    .text :
    {
        *(.text)      /* Código del kernel */
        *(.text.*)
    }

    .rodata :
    {
        *(.rodata)    /* Datos de solo lectura */
        *(.rodata.*)
    }

    .data :
    {
        *(.data)      /* Datos inicializados */
        *(.data.*)
    }

    .bss :
    {
        *(.bss)       /* Datos no inicializados */
        *(.bss.*)
    }
}
