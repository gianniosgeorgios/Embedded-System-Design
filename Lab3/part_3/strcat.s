.text
.align 4 /* code alignment */
.global strcat

.type strcat, %function

strcat:
    mov r3, r0 	/* save the base address of dst string */
    sub r0, r0, #1 	/* for the first iteration */
    sub r1, r1, #1 	/* for the first iteration */

traverse_dst_list:	/* want to find the end address of dst string */
    ldrb r2, [r0, #1]! /* load char from dst string */
    cmp r2, #0 	/* if char is null (0), exit loop*/
    bne traverse_dst_list

strcat_loop:
    ldrb r2, [r1, #1]!	/* load a char from src string */
    strb r2, [r0], #1	/* store the char in the end of the dst string */
    cmp r2, #0		/* if char is null (0), exit */
    bne strcat_loop

exit: 
    mov r0, r3		/* return the base address of dst string */
    bx lr

.data
