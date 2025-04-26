# Combinational Logic Block

## ALU

a simple ALU is just reusing `mux`s, :wink:

## adder/subtractor

write out the truth table. then you will recognize that it is just a reusing `xor` and `and` gates :laughing:, of course, these gates can be multi-input & multi-output

and there is a definition of `maj` circ:

$$
MAJ(a_i, b_i, c_i) = a_ib_i + a_ic_i + b_ic_i
$$

### overflow?

unsigned: the output of the *serial* adders is high......
signed: 

$$
\begin{array}{ccc}
  & c_1 &  \\
  & a_1 & a_0 \\
\sum & b_1 & b_0 \\
\hline
c_2 & s_1 & s_0 \\
\end{array}
$$
only when $c_2 + c_1 = 1$ will there be an overflow, i.e., overflow = $c_n$ XOR $c_{n-1}$ 

### subtraction

$a-b = a+(-b)$

using flip and add one to invert the bits of b, then add a to the result :thinking:


------
till now, Lec 14~17 over!