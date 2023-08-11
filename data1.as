V2: .entry LENGTH
    .extern W
    .string "abcdef"
MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
prn -5
bne LOOP
sub @r1, @r4
    bne END
L1: inc K
bne LOOP
END: stop

LENGTH: .data 6,-9,15
K: .data 22