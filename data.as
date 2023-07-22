MAIN: first
MAIN: second
L2: asdasad
MAIN: seconda

    2MAINada: jmp L1
mcro m1
     ADASDADASDASDASD AS DAS DA DSA
    sub @r1, @r4
    bne END
endmcro

mcro m3
adadasd
asdasda
endmcro


prn -5
mcro m1
sub @r2, @r4
    bne END
endmcro
bne LOOP
m1
L1: inc K
bne LOOP
END  : stop
STR: .string “abcdef”
LENGTH: .data 6,-9,15
K : .data 22
m1