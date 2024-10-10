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




