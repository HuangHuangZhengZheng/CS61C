.data # 标志着数据段的开始。在这个部分，程序可以定义和初始化变量。数据段通常用于存储静态数据，如常量、数组和结构体等
.word 2, 4, 6, 8 # 用于在数据段中分配内存并初始化整数值。在大多数架构中，.word通常表示一个32位（4字节）的整数。使用这个指令可以创建一个整数数组或单个整数变量
n: .word 9 # 

.text
main:
    add t0, x0, x0
    addi t1, x0, 1
    la t3, n # 分解为多个指令
    lw t3, 0(t3)
fib:
    beq t3, x0, finish
    add t2, t1, t0
    mv t0, t1
    mv t1, t2
    addi t3, t3, -1
    j fib
finish:
    addi a0, x0, 1 # return 1
    addi a1, t0, 0
    ecall # print integer ecall
    addi a0, x0, 10
    ecall # terminate ecall
