# Asic_Design 
## LAB - 1
### Objective
* Calculating the sum of numbers from 1 to n using GCC compiler and RISC-V 64-bit architecture
* Comparing O1 and Ofast optimization

### Part-1(GCC compiler)
* Create .c file using nano text editor
#### Command
```c
nano sum1ton.c 
```
![Screenshot 2024-08-07 182350](https://github.com/user-attachments/assets/5f927c5e-3919-45e4-8a33-0b55a5df7f6f)

* Code of C program which calculates the sum of numbers from 1 to n 
```c
#include <stdio.h>

int main() {
    int i, sum = 0, n=69;
    for(int i = 1; i <= n; ++i)
    {
        sum += i;
    }

    printf("The sum of numbers from 1 to %d = %d\n", n, sum);
    return 0;
}
```
* Running the C program using gcc compiler
#### Command
```c
gcc sum1ton.c
./a.out
```
![Screenshot 2024-08-07 114912](https://github.com/user-attachments/assets/40ae6bef-cda0-44ae-bd08-c0a3c37d23ba)
* Output of the C program that processes numbers from 1 to 69
![Screenshot 2024-08-07 115123](https://github.com/user-attachments/assets/5a0a6997-000d-4f62-9a64-7cf593c693c1)
* Result of the C program after changing the value of n to 96
![Screenshot 2024-08-07 115510](https://github.com/user-attachments/assets/517c6af6-c981-4e76-af81-2aad5ac42f13)

### Part-2(RISC-V 64bit)
**Using basic level O1** 
* This command compiles a C source file (sum1ton.c) for the 64-bit RISC-V architecture, generating an object file (sum1ton.o). It optimizes the code at the basic level ('O1')
#### Command
```c
riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c
```
![Screenshot 2024-08-07 115843](https://github.com/user-attachments/assets/d0cbe810-0482-4e28-bcca-4a044a251482)
* The command will display the assembly language representation of the code contained in sum1ton.o. This helps debug the code.
* The addition 'less' command is used to interactively browse the potentially lengthy disassembly output of sum1ton.o.
#### Command
```c
riscv64-unknown-elf-gcc-objdump -d sum1ton.o
riscv64-unknown-elf-gcc-objdump -d sum1ton.o | less
```
![Screenshot 2024-08-07 120249](https://github.com/user-attachments/assets/3db61ddd-a61a-4595-aebe-8dc4ae187c3c)
* Search the main function using '/main' command
  #### Command
```c
/main
```
![Screenshot 2024-08-07 120355](https://github.com/user-attachments/assets/76c1b21d-2e1f-461d-a216-db83c1766f59)

**Using Ofast**
* Executing the same commands with optimization levels O1 through Ofast as well.

![Screenshot 2024-08-07 120950](https://github.com/user-attachments/assets/63d2f3a5-2cad-4c06-ad02-25d0e0a67fbb)

![Screenshot 2024-08-07 120940](https://github.com/user-attachments/assets/9382c43e-df1c-4620-9292-0af168b46677)

* O0: No optimization (default setting).
* O1: Basic optimization (minimal level).
* O2: More optimization (increases code performance and reduces code size).
* O3: Aggressive optimization (may increase compilation time and code size but maximizes performance).
* Os: Optimize for size (reduces the binary size).
* Ofast: Enables -O3 and makes other aggressive optimizations.

## Results
#### Number of instructions
O1 - Hex(101c0 - 10184) / 4  = 15
<br>
Ofast - Hex(100e0 - 100b0) / 4 = 12
<br> 
The number of instructions decreases with Ofast due to aggressive optimization, but this may lead to an increase in compilation time and code size.

## LAB - 2
### Objective

* To verify the GCC compiler and RISC-V 64bit output using spike RISC-V simulator
* Using the debug tool in the spike simulator to debug the code.

* Using the command of the previous lab
```c
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c
```
* A spike simulator is used to run the RISC-V 64-bit architecture. Use the command below.
```c
spike pk sum1ton.c
```
* This screenshot demonstrates that both the GCC compiler and RISC-V produce the same output.

![Screenshot 2024-08-07 205653](https://github.com/user-attachments/assets/676640e3-59c1-4e6e-8fdb-582e160c3b7f)

* The following command is used to debug the code with the Spike simulator.
```c
spike -d pk sum1ton.c
```
![2](https://github.com/user-attachments/assets/94744f80-3011-431c-b1f4-426090b922ed)

* The command tells the simulator to execute the program until the program counter reaches the address 0x100b0.
```c
until pc 0 100b0
```
![3](https://github.com/user-attachments/assets/638b5b02-a3aa-4041-b432-ed1f1a483661)

* The command checks the contents in the register a2
```c
reg 0 a2
```
* Checking the value of the a2 register before and after the instruction is executed.

![4](https://github.com/user-attachments/assets/cedbf998-feeb-46b4-8ad0-55da3f5fb3ce)

* lui a2, 0X1 command adds the registor a2 value by 0X1.

Debugging the addi sp, sp,-16 which reduces the sp pointer by 16
* Run the same commands as the above (same as we checked the lui command)

![5](https://github.com/user-attachments/assets/7a1c5df1-8a29-4c7d-a99c-98f5ad0c1aed)

* The sp pointer gets updated from 0X0000003ffffffb50 to 0X0000003ffffffb40.

## LAB - 3
### Objective
- Identifying different instruction types (R-type, I-type, S-type, B-type, U-type, and J-type) 
- Writing the 32-bit pattern code for each instruction.
### Instructions
```c
 ADD r5, r4, r5
 SUB r5, r5, r4
 AND r4, r5, r5
 OR r8, r4, r5
 XOR r8, r5, r4
 SLT r10, r2, r4
 ADDI r12, r3, 5
 SW r3, r1, 4
 SRL r16, r11, r2
 BNE r0, r1, 20
 BEQ r0, r0, 15
 LW r13, r11, 2
 SLL r15, r11, r2
```

### RISC-V base instruction formats
![image](https://github.com/user-attachments/assets/c6bb13de-b03f-477b-8c14-126a1e702cb9)

### Base instruction table
![image](https://github.com/user-attachments/assets/ef5b6763-6907-4293-971b-65a479538d97)


### All instructions 32 bit pattern and RISC-V instruction type
```c
 ADD r5, r4, r5
```
- All the arithmetic and logical operations are performed using **R-type** instruction format, hence this instruction belongs to the **R-type** instruction set.
- **r5** is the destination register that will hold the sum of values stored in the registers **r4** and **r5**.
- **Opcode for ADD = `0110011`**
  - **rd = r5 = `00101`**
  - **rs1 = r4 = `00100`**
  - **rs2 = r5 = `00101`**
  - **func3 = `000`**
  - **func7 = `0000000`**

**32 bits instruction** : `0000000_00101_00100_000_00101_0110011`

```c
 SUB r5, r5, r4
```
- All the arithmetic and logical operations are performed using **R-type** instruction format, hence this instruction belongs to the **R-type** instruction set.
- **r5** is the destination register that will hold the sum of values stored in the registers **r5** and **r4**.
- **Opcode for SUB = `0110011`**
  - **rd = r5 = `00101`**
  - **rs1 = r5 = `00101`**
  - **rs2 = r4 = `00100`**
  - **func3 = `000`**
  - **func7 = `0100000`**

**32 bits instruction** : `0100000_00100_00101_000_00101_0110011`
```c
 AND r4, r5, r5
```
- All the arithmetic and logical operations are performed using **R-type** instruction format, hence this instruction belongs to the **R-type** instruction set.
- **r4** is the destination register that will hold the sum of values stored in the registers **r5** and **r5**.
- **Opcode for AND = `0110011`**
  - **rd = r4 = `00100`**
  - **rs1 = r5 = `00101`**
  - **rs2 = r5 = `00101`**
  - **func3 = `111`**
  - **func7 = `0000000`**

**32 bits instruction** : `0000000_00101_00101_111_00100_0110011`
```c
 OR r8, r4, r5
```
- All the arithmetic and logical operations are performed using **R-type** instruction format, hence this instruction belongs to the **R-type** instruction set.
- **r8** is the destination register that will hold the sum of values stored in the registers **r4** and **r5**.
- **Opcode for OR = `0110011`**
  - **rd = r8 = `01000`**
  - **rs1 = r4 = `00100`**
  - **rs2 = r5 = `00101`**
  - **func3 = `110`**
  - **func7 = `0000000`**

**32 bits instruction** : `0000000_00101_00100_110_01000_0110011`
```c
 XOR r8, r5, r4
```
- All the arithmetic and logical operations are performed using **R-type** instruction format, hence this instruction belongs to the **R-type** instruction set.
- **r8** is the destination register that will hold the sum of values stored in the registers **r5** and **r4**.
- **Opcode for XOR = `0110011`**
  - **rd = r8 = `01000`**
  - **rs1 = r5 = `00101`**
  - **rs2 = r4 = `00100`**
  - **func3 = `100`**
  - **func7 = `0000000`**

**32 bits instruction** : `0000000_00100_00101_100_01000_0110011`
```c
 SLT r10, r2, r4
```
- All the arithmetic and logical operations are performed using **R-type** instruction format, hence this instruction belongs to the **R-type** instruction set.
- **r10** is the destination register that will hold the sum of values stored in the registers **r2** and **r4**.
- **Opcode for SLT = `0110011`**
  - **rd = r10 = `01010`**
  - **rs1 = r2 = `00010`**
  - **rs2 = r4 = `00100`**
  - **func3 = `010`**
  - **func7 = `0000000`**

**32 bits instruction** : `0000000_00100_00010_010_01010_0110011`
```c
 ADDI r12, r3, 5
```
- In this instruction ADD means Addition, I means Immediate, therefore ADDI means Addition with Immediate, hence this instruction belongs to **I-type** instruction set.
- **r12** is the destination register that will store the value of **r3** sum-up with the immediate value **5**.
- **Opcode for ADDI = `0010011`**
    - **rd = r12 = `01100`**
    - **rs1 = r4 = `00100`**
    - **imm[11:0] = 5 = `000000000101`**
    - **func3 = `000`**

**32 bits instruction** : `000000000101_00100_000_01100_0010011`
```c
 SW r3, r1, 4
```
- In this instruction SW means store word, hence this instruction belongs to **S-type** instruction set.
- **r3** is the source register. This instruction will store the value located in register **r3** at the address obtained by adding the immediate address **4** with the address located in register **r1**.
- **Opcode for SW = `0100011`**
    - **rs2 = r3 = `00011`**
    - **rs1 = r1 = `00001`**
    - **imm[11:0] = 4 = `000000000100`**
    - **func3 = `010`**

**32 bits instruction** : `0000000_00011_00001_010_00100_0100011`
```c
 SRL r16, r11, r2
```
- SRL means Logical Shift Right and since the operation is performed on registers, this instruction belongs to **R-type** instruction set.
- **r16** is the destination register that will hold the sum of values stored in the registers **r11** and **r2**.
- **Opcode for SRL = `0110011`**
  - **rd = r16 = `10000`**
  - **rs1 = r11 = `01011`**
  - **rs2 = r2 = `00010`**
  - **func3 = `101`**
  - **func7 = `0000000`**

**32 bits instruction** : `0000000_00010_01011_101_10000_0110011`

```c
 BNE r0, r1, 20
```
- BNE is a branching instruction (**B-type**) based on conditions. Here BNE specifies the condition that the value stored in **r0** != (is not equal to) the value stored in **r1**. If the condition becomes true, Program Counter will be updated by **PC + 20**, else **PC + 4** for next instruction.
- **Opcode for BNE = `1100011`**
  - **rs1 = r0 = `00000`**
  - **rs2 = r1 = `00001`**
  - **imm[12:1] = 20 = `000000010100`**
  - **func3 = `001`**

**32 bits instruction** : `0_000001_00001_00000_001_0100_0_1100011`
```c
 BEQ r0, r0, 15
```
- BEQ is a branching instruction (**B-type**) based on conditions. Here BEQ specifies the condition that the value stored in **r0** == (is equal to) the value stored in **r0**. If the condition becomes true, Program Counter will be updated by **PC + 15**, else **PC + 4** for next instruction.
- **Opcode for BEQ = `1100011`**
  - **rs1 = r0 = `00000`**
  - **rs2 = r0 = `00000`**
  - **imm[12:1] = `000000001111`**
  - **func3 = `000`**
  
**32 bits instruction : `0_000000_00000_00000_000_1111_0_1100011`**
```c
 LW r13, r11, 2
```
- LW stands for Load Word. Word is equal to 32 bits or 4 bytes. Since there is an immediate value given in the instruction which helps to calculate the address of memory from where we have to fetch the data, hence this instruction belongs to **I-type**.
- **r13** is the destination register that will hold the value fetched from the memory location calculated by using (address value stored in **r11** + immediate value)
- **Opcode for LW = `0000011`**
  - **rd = r13 = `01101`**
  - **rs1 = r11 = `01011`**
  - **imm[11:0] = `000000000010`**
  - **func3 = `010`**
  
**32 bits instruction : `000000000010_01011_010_01101_0000011`**
```c
 SLL r15, r11, r2
```
- SLL means Logical Shift Left and since the operation is performed on registers, this instruction belongs to **R-type** instruction set.
- **r15** is the destination register, in which the value stored in **r11** will be written after performing logical left shift based on the number stored in **r2**.
- **Opcode for SLL = `0110011`**
  - **rd = r15 = `01111`**
  - **rs1 = r11 = `01011`**
  - **rs2 = r2 = `00010`**
  - **func3 = `001`**
  - **func7 = `0000000`**
  
**32 bits instruction :`0000000_00010_01011_001_01111_0110011`**

### Summary table 

| Instruction     | Instruction Type | 32bit pattern   | Hexadecimal pattern |
|-----------------|------------------|-----------------|---------------------|
| ADD r5, r4, r5  | R-Type  | 0000000_00101_00100_000_00101_0110011  | 0x005202B3      |
| SUB r5, r5, r4  | R-Type   | 0100000_00100_00101_000_00101_0110011  | 0x404282B3      |
| AND r4, r5, r5  | R-Type   | 0000000_00101_00101_111_00100_0110011  | 0x0052F233     |
| OR r8, r4, r5  | R-Type   | 0000000_00101_00100_110_01000_0110011  | 0x00526433      |
| XOR r8, r5, r4  | R-Type   | 0000000_00100_00101_100_01000_0110011  | 0x0042C433      |
| SLT r10, r2, r4  | R-Type   | 0000000_00100_00010_010_01010_0110011  | 0x00412533      |
| ADDI r12, r3, 5  | I-Type   | 000000000101_00100_000_01100_0010011  | 0x00520613      |
| SW r3, r1, 4  | S-Type   | 0000000_00011_00001_010_00100_0100011  | 0x0030A223     |
| SRL r16, r11, r2  | R-Type   | 0000000_00010_01011_101_10000_0110011 | 0x0025D833      |
| BNE r0, r1, 20  | B-Type   | 0_000001_00001_00000_001_0100_0_1100011 | 0x02101463      |
| BEQ r0, r0, 15  | B-Type   | 0_000000_00000_00000_000_1111_0_1100011  | 0x00000F63      |
| LW r13, r11, 2  | I-Type   | 000000000010_01011_010_01101_0000011  | 0x0025A683      |
| SLL r15, r11, r2  | R-Type   | 0000000_00010_01011_001_01111_0110011  | 0x002597B3      |

### Hardcoded table based on the provided Verilog code

- In the Verilog code, the opcode varies for each instruction type, and different instructions have distinct func3 values.
- To differentiate between immediate operations and other arithmetic functions, func7 is used; otherwise, func7 is set to b'0.

| Instruction     | Hardcoded 32bit pattern | Hardcoded hexadecimal pattern| 32bit pattern   | Hexadecimal pattern |
|-----------------|-------------------------|------------------------------|---------------------|---------------|
| ADD r5, r4, r5  | 0000001_00101_00100_000_00101_0000000 | 0x02520280 | 0000000_00101_00100_000_00101_0110011  | 0x005202B3 |
| SUB r5, r5, r4  | 0000001_00100_00101_001_00101_0000000 | 0x02429280  | 0100000_00100_00101_000_00101_0110011  | 0x404282B3      |
| AND r4, r5, r5  | 0000001_00101_00101_010_00100_0000000 | 0x0252A200 |0000000_00101_00101_111_00100_0110011  | 0x0052F233     |
| OR r8, r4, r5  | 0000001_00101_00100_011_01000_0000000  | 0x02523400 |0000000_00101_00100_110_01000_0110011  | 0x00526433      |
| XOR r8, r5, r4  | 0000001_00100_00101_100_01000_0000000 | 0x0242C400 |0000000_00100_00101_100_01000_0110011  | 0x0042C433      |
| SLT r10, r2, r4  | 0000001_00100_00010_101_01010_0000000| 0x02415500 | 0000000_00100_00010_010_01010_0110011  | 0x00412533      |
| ADDI r12, r3, 5  | 000000000101_00100_000_01100_0000000 | 0x00520600 |000000000101_00100_000_01100_0010011  | 0x00520613      |
| SW r3, r1, 4  | 0000000_00011_00001_001_00100_0000001   | 0X00309201| 0000000_00011_00001_010_00100_0100011  | 0x0030A223     |
| LW r13, r11, 2  | 000000000010_01011_000_01101_0000001   | 0x0258681 |000000000010_01011_010_01101_0000011  | 0x0025A683      |
| BEQ r0, r0, 15  | 0_000000_00000_00000_000_1111_0_1100011   | 0X00f00002 |0_000000_00000_00000_000_1111_0_1100011  | 0x00000F63      |
| SRL r16, r11, r2  | 0000000_00010_01011_001_10000_0000011 |0x00259803  | 0000000_00010_01011_101_10000_0110011 | 0x0025D833      |
 
### Output waveform

```c
ADD r5, r4, r5
```
![image](https://github.com/user-attachments/assets/5631d19a-362a-4584-ac3d-065678364a37)
```c
SUB r5, r5, r4
```
![image](https://github.com/user-attachments/assets/f8bf4de8-a4e4-402a-8746-8329f596eb9e)

```c
AND r4, r5, r5
```
![image](https://github.com/user-attachments/assets/a5a029c2-05bc-40c2-9dc1-b6430b854909)

```c
OR r8, r4, r5
```
![image](https://github.com/user-attachments/assets/6057587b-6b55-4c8c-91fe-8b9898dfbc8c)

```c
XOR r8, r4, r4
```
- The given rv32i code is not working for **r5** register. I tried debugging it but couldn't identify the issue.
- It's working fine for register **r1**,**r2**,**r3**,**r4** and **r6** but it's overflowing for the other register values. 
  
![image](https://github.com/user-attachments/assets/0311dc5d-d219-423b-b791-2df7a9543227)

```c
SLT r10, r2, r4 
```
![image](https://github.com/user-attachments/assets/7d87cd88-eda7-4aec-96f7-d56067119146)

```c
ADDI r12, r3, 5  
```
![image](https://github.com/user-attachments/assets/d8c72191-5c44-49da-bb80-b41231d3db69)

```c
SW r3, r1, 4   
```
![image](https://github.com/user-attachments/assets/5bf759fc-efd1-4191-96ac-99afd260f1d5)

```c
BEQ r0, r0, 15   
```
![image](https://github.com/user-attachments/assets/2dbd02ae-9a44-49ee-aaf5-252a8355699d)

```c
ADD r14, r2, r2
```
![image](https://github.com/user-attachments/assets/7c94c1f3-32d0-4fef-89f5-11c4c0a14718)

- The BNE command isn't working when I run it on my local machine, and the code has numerous logical errors

