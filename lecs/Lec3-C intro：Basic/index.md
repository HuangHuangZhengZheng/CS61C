+++
title = 'Lec3-C intro：Basic'
date = 2024-10-05T14:01:35+08:00
draft = false
categories = ['UCB-CS61C']
+++
# C intro: Basic
## Compile vs Interpret
Java 是先编译后解释器解释 C 是编译完成后直接运行，不需要解释器

## Syntax
```C
    int8_t a = 10;
    int64_t b = 20;
    int16_t c = a + b;
    uint32_t d = a - b;
```

```C
typedef uint8_t Byte;
typedef struct {
    Byte a;
    int b;
} MyStruct;

MyStruct myStruct = {10, 20};
```
