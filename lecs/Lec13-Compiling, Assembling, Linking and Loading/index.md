+++
title = 'Lec13-Compiling, Assembling, Linking and Loading'
date = 2024-10-15T10:12:14+08:00
draft = false
categories = ['UCB-CS61C']
+++
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
让.o文件确定终值 ==> object file

- 简单case：直接用.o文件
- Forward reference problem：确定标签位置，然后再用.o文件
- PC 相对寻址
![alt text](image-7.png)


### Symbol Table and Relocation Table
- symbol Table
![alt text](image-8.png)

- label Table
![alt text](image-9.png)

汇编器层面不知道static 之类的东西，所以需要暂时做个记号等待link处理

### Object File Format
![alt text](image-10.png)


## Linker
what happen?
![alt text](image-11.png)

4 types of addressing

![alt text](image-12.png)

which instructions must be linked?
- J-format: j / jal
- L-, S-format: there is a `gp` !

### Resolving reference

![alt text](image-13.png)

然后在"user" symbol table中找到对应的地址，然后替换掉原来的符号

接着在library files同样操作

最后输出：*executable file*，containing text and data (plus header)==> 存储在 **磁盘** 上面

### static and dynamic linking

![alt text](image-14.png)

现在我知道`.dll` 文件是什么了:yum:

动态link通常在机器码级别进行，而不是汇编器级别

## Loader

什么是loader？ -- CS162 OS先导课程 :triumph:

![alt text](image-15.png)

Loader的作用：

![alt text](image-16.png)

注意最后一行start-up routine的program's arguments 正是和 `argc` & `argv` 相关的 :open_mouth:

## EXAMPLE hello world !
```c
#include <stdio.h>

int main() {
    printf("Hello, %s\n", "world");
    return 0;
}
```

`.s` file:

![alt text](image-17.png)

`.o` file:

只有字符存储在`.o`文件中！

![alt text](image-18.png)

`.out` file:

红色的字符被补充了

![alt text](image-19.png)









