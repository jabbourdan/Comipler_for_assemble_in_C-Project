.entry LENGTH
    .extern W
MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
STR: .string "ab"
L1: inc K
jmp W
END: stop
LENGTH: .data 6,-9,15
K: .data 22
    .extern L3