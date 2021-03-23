.text
.align 4 /* code alignment */
.global strcmp

.type strcmp, %function

strcmp:
    push {r4} 		/* Save r4 for recovery according to conventions */
    mov r4, #0 	/* initialize result to zero */
    sub r1, r1, #1 	/* for the first iteration */
    sub r0, r0, #1 	/* for the first iteration */

strcmp_loop:
    ldrb r2, [r0, #1]! /* load char from string1 */
    ldrb r3, [r1, #1]! /* load char from string2 */
    cmp r2, r3 	/* compare chars */
    beq equal		/* if equal, go to equal */
    blt negative 	/* calculate -1 */
    movgt r4, #1 	/* if char_of_string1 > char_of_string2, then return 1 */ 
    b exit

negative:
    mvn r4, #1 	/* calculate 1s complement of one */
    add r4, r4, #1 	/* add one for 2s complemet of one */
    b exit

equal:
    cmp r2, #0 	/* if they are equal and one of the two is null, then both are null */
    bne strcmp_loop	/* if they are not null, check next chars */
    mov r4, #0 	/* else we reach the end of the strings and return 0 */
    b exit

exit:
    mov r0, r4
    pop {r4}
    bx lr


.data
