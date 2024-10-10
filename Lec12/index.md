# RISC-V Instruction Formats II

## B-Format Layout
branch/分支 ==> if-else, while, for

encode Label: 

![alt text](image.png)



PC寻址, 用imm field来表示偏移量  

![alt text](image-1.png)

![alt text](image-2.png)

实际上 RV compressed instruction format! 16bit 压缩指令格式，偏移量不再是4的倍数，而是2的倍数（所以imm 二进制结尾一定是0）

理论layout
![alt text](image-3.png)

解释一下如何从指令解析出立即数的数值

![alt text](image-4.png)

B-type "|" 意思是专门分出一块区域来存一位数字

![alt text](image-5.png)


## Long Immediate， U-Format Layout

I, B, S imm的12位扩展到long，找个地方放下剩下的20位

![alt text](image-6.png)

注意这里不直接使用branch指令跳转，而是采用jump直接来做

地方来了：同时来了两个新的指令`lui` & `auipc`
![alt text](image-7.png)

### Corner case
有符号扩展带过来的，1开头的符号扩展

![alt text](image-8.png)

用+1来避免这个问题

![alt text](image-9.png)

补充 `auipc` 指令
![alt text](image-10.png)


## J-Format Layout

只有jal，因为jalr是I-type的

![alt text](image-11.png)

使用示例

![alt text](image-12.png)

jalr
![alt text](image-13.png)

使用示例

![alt text](image-14.png)

留一个[reference](https://www.cse.cuhk.edu.hk/~byu/CENG3420/2023Spring/doc/RV32-reference-1.pdf)



