
MAIN: cmp  LENGTH,60
LENGTH: .data 6,-9,15
    .extern W
    .string "abcdef"
LOOP: jmp L1
prn -5
bne LOOP
sub @r1, @r4
    bne END
L1: inc K
bne LOOP
END: stop

K: .data 22