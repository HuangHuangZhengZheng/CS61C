.globl factorial

.data
n: .word 7 # input argument

.text
main:
    la t0, n          # Load address of n into t0
    lw a0, 0(t0)     # Load the value of n into a0
    jal ra, factorial # Call factorial function

    addi a1, a0, 0   # Move the result to a1 for printing
    addi a0, x0, 1   # Prepare to print result (syscall number for print integer)
    ecall             # Print Result

    addi a1, x0, '\n' # Prepare to print newline character
    addi a0, x0, 11   # Syscall number for print character
    ecall             # Print newline

    addi a0, x0, 10   # Prepare to exit (syscall number for exit)
    ecall             # Exit

factorial: # 递归的时候注意使用stack而不是t / a寄存器
    addi sp, sp, -16   # Allocate stack space
    sw ra, 12(sp)      # Save return address
    sw a0, 8(sp)       # Save n (argument)

    li t0, 1           # Load immediate value 1 into t0 (base case)
    beq a0, t0, base_case   # If n == 1 , go to base_case

    addi a0, a0, -1     # Decrement n by 1
    jal ra, factorial   # Recursive call: factorial(n-1)

    lw t1, 8(sp)       # Load original n from stack
    mul a0, a0, t1     # Multiply result by n (original value)

base_case:
    lw ra, 12(sp)      # Restore return address
    addi sp, sp, 16    # Deallocate stack space
    ret                 # Return from function


