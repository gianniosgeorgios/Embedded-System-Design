.text
.align 4 /* code alignment */
.global strlen

.type strlen, %function

strlen:

    sub r0, r0, #1 	/* for first iteration of loop */
    mov r2, #0 	/* initialize counter to zero */

strlen_loop:
    ldrb r1, [r0, #1]!	/* load char from string */
    cmp r1, #0		/* if is null char (0), exit */
    beq exit
    add r2, r2, #1	/* counter++ */
    b strlen_loop

exit:
    mov r0, r2		/* return counter */
    bx lr

.data
