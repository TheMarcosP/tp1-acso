.text
mov X1, 0x1000
lsl X1, X1, 16
adds X1, X1, 0x2
mov X10, 0x1234
lsl X10, X10, 20
adds X10, X10, 0xabc
lsl X10, X10, 20
adds X10, X10, 0xabc
lsl X10, X10, 8
adds X10, X10, 0xabc
stur X10, [X1, 0x0]
mov X5, 0xaabb
sturh W5, [X1, -1]
ldur X13, [X1, 0x0]
ldur X14, [X1, 0x4]
ldurb W15, [X1, 0x6]
HLT 0
