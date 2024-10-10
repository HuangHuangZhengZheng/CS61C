# Compiling, Assembling, Linking and Loading

CALL

## Interpretation and Translation
### Interpretation
![alt text](image.png)

有一个解释器（是一个程序）

![alt text](image-1.png)
### Translation
翻译为低级的语言针对hardware更快操作

![alt text](image-2.png)
![alt text](image-3.png)
## Compiler
CS164 :thinking:

![alt text](image-4.png)

这么看来pseudo code确实存在？

## Assembler
![alt text](image-5.png)

### Directives
![alt text](image-6.png)


### Replacements
把pseudo code翻译成真实的RISC-V指令

### Producing real machine code
让.o文件确定终值

- 简单case：直接用.o文件
- Forward reference problem：确定标签位置，然后再用.o文件
- PC 相对寻址
![alt text](image-7.png)








