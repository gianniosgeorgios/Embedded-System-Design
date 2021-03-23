.text
.align 4 /* code alignment */
.global strcpy

.type strcpy, %function

strcpy:
    mov r3, r0 	/* save base address of dst string */
    sub r1, r1, #1

strcpy_loop:
    ldrb r2, [r1, #1]!	/* load a char from src string */
    strb r2, [r0], #1	/* store the char to dst string */
    cmp r2, #0		/* if char is null (0), exit */
    bne strcpy_loop

exit:
    mov r0, r3		/* return base address of dst string */
    bx lr
.data
