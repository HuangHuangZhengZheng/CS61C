# RISC-V Introduction

## Instruction Set Architecture (ISA)
![alt text](image.png)

## Assembly Variables 
each statement is called an **instruction**
### Registers
where are registers ?

![alt text](image-1.png)

32 general purpose registers (GPRs) are available in RISC-V architecture.(x0 - x31)

word: 32 bits (can be 64 bits in RV64)

x0: always 0
\# is the comment character

### no type casting in RISC-V assembly language
the registers have no type

## add/sub instructions

### syntax of instructions
![alt text](image-2.png)
```
add rd, rs1, rs2
sub rd, rs1, rs2 # d(rd) = e(rs1) - f(rs2), 注意顺序
```
![alt text](image-3.png)

## Immediate values（立即数）
```assembly
addi rd, rs1, 10 
```
没有`subi` ，加上相反数即可

### Register 0
![alt text](image-4.png)
