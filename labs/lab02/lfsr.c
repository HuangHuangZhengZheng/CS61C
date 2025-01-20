#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *x) {
    /* YOUR CODE HERE */
    // 计算新位：位置 0、2、3 和 5 的异或
    uint16_t new_bit = ((*x >> 0) & 1) ^ 
                       ((*x >> 2) & 1) ^ 
                       ((*x >> 3) & 1) ^ 
                       ((*x >> 5) & 1); // Xor 迭代一下

    // 将寄存器内容右移一位，并将新位插入到左侧
    *x = (*x >> 1) | (new_bit << 15);
}

