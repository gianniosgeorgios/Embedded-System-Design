.text 
.align 4 /* code alignment */
.global main
.extern tcsetattr

find_max_frequency:
    push {r4}
    ldr r0, =inp_string /* input string */
    ldr r3, =freq_arr	/* array with frequencies (256 entries - all ascii characters) */
    mov r1, #0

read_inp_string:
    ldrb r2, [r0, r1] 	/* loads the character of the input string with offset r1 */
    cmp r2, #10 	/* the last useful char will be EOL */
    beq end_of_read
    ldrb r4, [r3, r2] 	/* loads the frequency value from the array with offset r2 (character that we read) */
    add r4, r4, #1 	/* increse the frequency seen the character */
    strb r4, [r3, r2] 	/* store the value */
    add r1, r1, #1 	/* move to the next char of our input string */
    b read_inp_string

end_of_read:
    mov r1, #0 		/* initiate r1 to first char with ascii code zero */
    mov r0, #0		/* initiate max value r0 to zero */
    ldr r3, =freq_arr 	/* load frequency array to r3 */

check_array_of_frequencies:
    cmp r1, #32 	/* ignore the empty char (space) with ascii code 32 */
    addeq r1, r1, #1
    ldrb r2, [r3, r1] 	/* Load value of array with offset r1*/ 
    cmp r0, r2 	/* r0 holds the max value (if we have equal we keep the first, so the char with the smaller ascii code) */
    movlt r4, r1 	/* if we find a better frequency, we save the char */
    movlt r0, r2 	/* and the value (frequency) */
    add r1, r1, #1 
    cmp r1, #256 	/* End, when we reach the end of the frequency array */
    beq end_of_check
    b check_array_of_frequencies

end_of_check:
    mov r1, r4
    pop {r4}
    bx lr

main:

open:
    ldr r0, =device 	/* device to open */
    ldr r1, =#258 	/* O_RDWR | O_NOCTTY */
    mov r7, #5 		/* num of open syscal is 5 */
    swi 0

    /* now r0 has the fd */
    mov r6, r0 		/* save fd to r6 */
    
termios_setup:
    mov r0, r6 		/* call tcsetattr to set the settings for our port */
    ldr r2, =options
    mov r1, #0
    bl tcsetattr

read:
    mov r0, r6		/* read from fd */
    ldr r1, =inp_string
    mov r2, #64
    mov r7, #3		/* num of read syscal is 3 */
    swi 0

    bl find_max_frequency
    
    /* r0 has the max frequency  */
    /* r1 has the character */

    sub r0, r0, #48	/* we subtract with the ascii code zero to find the actual number of frequency (char -> int) */
    ldr r3, =result
    strb r1, [r3]
    strb r0, [r3, #1]
    
write:
    mov r0, r6		/* write to fd */
    ldr r1, =result
    ldr r2, =len 
    mov r7, #4		/* num of write syscal is 4 */
    swi 0

close:
    mov r0, r6		/* close fd */
    mov r7, #6		/* num of close syscal is 6 */
    swi 0

exit:
    mov r0, #0		
    mov r7, #1		/* num of exit syscal is 1 */
    swi 0

.data
    options: .word 0x00000000 /* c_iflag */
             .word 0x00000004 /* c_oflag */
             .word 0x000008bd /* c_cflag */
             .word 0x00000a22 /* c_lflag */

    device: .ascii "/dev/ttyAMA0"
    
    inp_string: .asciz "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    
    freq_arr: .ascii "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    
    result: .ascii "0\0"
    
    len = . - result
