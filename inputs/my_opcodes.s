.text
mov X1, 0x1000
lsl X1, X1, 16
mov X10, 0x2354
lsl X10, X10, 15
lsl X10, X10, 15
adds x10,x10, 13 
stur X10, [X1, 0x0]
HLT 0
