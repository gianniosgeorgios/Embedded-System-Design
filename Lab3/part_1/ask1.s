.text 
.global main


convert_string:
    push {r0, r1, r2, r3, lr}
    sub r1, r1, #1 /* subtract one from r1 for the loop to function correctly at first iteration*/
/* we can't have 0 input characters, so we don't care about this case */

convert_string_loop:     
    ldrb r0, [r1, #1]!
    cmp r0, #57 /* 9 in ascii */
    bgt not_number
    cmp r0, #48 /* 0 in ascii */
    bge is_number
    b store_byte

not_number:
    cmp r0, #65 /* ASCII for A */
    blt store_byte
    cmp r0, #90 /* ASCII for Z */
    bgt is_small_letter
    b is_capital_letter


is_capital_letter:
    add r0, #32 /* Transform to small by adding 32 */
    b store_byte

is_small_letter:
    cmp r0, #97 /* a in ascii */
    blt store_byte
    cmp r0, #122 /* z in ascii */
    bgt store_byte
    sub r0, #32 /* remove 32 to transform to capital */
    b store_byte

is_number:
    sub r0, #48 /* remove acii 0 to get actual number */
    add r0, #5 /* add 5 */
    cmp r0, #10 /* if number over 10, remove 10 */
    subge r0, #10
    add r0, #48 /* add ascii back */

store_byte:
    strb r0, [r1]
    subs r3, r3, #1 /* Loop iterator*/
    bne convert_string_loop 
    
end_of_convertion:
    pop {r0, r1, r2, r3, lr}
    bx lr
    
main:
    ldr r1, =output_string /* second argument -> memory location of output string */
    mov r2, #len /* third argument -> number of bytes */
    mov r0, #1 /* first argument -> stdout */
    mov r7, #4 /* number of write syscall */
    swi 0    
    
    ldr r1, =inp_str /* second argument -> memory where input string will be stored */
    mov r2, #32 /* third argument -> number of bytes to be read */    
    mov r0, #0 /* first argument -> stdin */
    mov r7, #3 /* number of read syscall */
    swi 0
    
    /* read returns to r0 how many bytes have been read */

    /* Check if we get quit code */
    cmp r0, #2 /* First check the length - 2 characters ('q\n' or 'Q\n') */
    bne continue
    ldrb r3, [r1]
    cmp r3, #81 /* Compare with Q */
    beq exit
    cmp r3, #113 /* Compare with q */
    beq exit

continue:

    mov r3, r0 /* store the value of length of the result */
    bl convert_string  
    
    /* if length of string is 32bytes and last char not EOL, add EOL char in the end (33 bytes in the end) */
    cmp r3, #32
    bne print_result
    ldrb r6, [r1, #31]
    cmp r6, #10
    beq print_result

    add r3, r3, #1
    mov r6, #10   
    strb r6, [r1, #32]

print_result:
    ldr r1, =output_string_2 /* second argument -> memory location of output string */
    mov r2, #len_2 /* second argument ->  number of bytes */
    mov r0, #1 /* first argument -> stdout */
    mov r7, #4 /* number of system call */
    swi 0

    /* Print changed input */
    ldr r1, =inp_str /*  second argument -> memory where output string (converted) is stored */
    mov r2, r3 /* third argument -> number of bytes print */
    mov r0, #1 /* first argument -> stdout */
    mov r7, #4 /* number of system call */
    swi 0   

    cmp r3, #32
    blt main 
    ldrb r6, [r1, #31]
    cmp r6, #10
    beq main

greater_than_standard_lenth:
    /* Read so as to clear any leftover input */
    ldr r1, =inp_str /* second argument -> memory where input string will be stored */
    mov r2, #32 /* third argument -> number of bytes to be read */    
    mov r0, #0 /* first argument -> stdin */
    mov r7, #3 /* number of read syscall */
    swi 0
    
    cmp r0, #32 /* First check the length. If less than 32 then all the input is cleared */
    bne main
    ldrb r6, [r1, #31]
    cmp r6, #10
    bne greater_than_standard_lenth

    b main

exit:
    mov r0, #0 /* exit status 0 */
    mov r7, #1 /* number of exit syscall */
    swi 0

.data
    output_string: .ascii "Input a string of up to 32 chars long: " /* location of output string in memory */
    len = . - output_string /* length of output_string is the current memory indicated by (.) minus the memory location of the first element of string */
    output_string_2: .ascii "Result is: "
    len_2 = . - output_string_2
    inp_str: .ascii "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" /* pre-allocate 33 bytes for input string, initialize them with null character '/0'*/
