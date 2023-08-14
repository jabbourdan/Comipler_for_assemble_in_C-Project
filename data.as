 .string "abcdef"
prn -5
Data: jmp LENGTH
.data -9,9
.entry LENGTH
.extern K2


LENGTH: .string "data"
bne LOOP
sub @r1, @r4
    bne END
L1: inc K
bne LOOP
END: stop
W: .data 1,2
K: .data 22