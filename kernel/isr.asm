section .text

global gdt_flush
global idt_load
global irq0
global irq1
global irq12

extern irq_handler
extern timer_handler
extern keyboard_handler
extern mouse_handler

gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

%macro IRQ_COMMON 0
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
%endmacro

%macro IRQ_COMMON_END 0
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
%endmacro

irq0:
    cli
    push byte 0
    push byte 32
    IRQ_COMMON
    call timer_handler
    IRQ_COMMON_END

irq1:
    cli
    push byte 0
    push byte 33
    IRQ_COMMON
    call keyboard_handler
    IRQ_COMMON_END

irq12:
    cli
    push byte 0
    push byte 44
    IRQ_COMMON
    call mouse_handler
    IRQ_COMMON_END
