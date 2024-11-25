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
spike pk sum1ton.o
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
    - **rs1 = r3 = `00011`**
    - **imm[11:0] = 5 = `000000000101`**
    - **func3 = `000`**

**32 bits instruction** : `000000000101_00011_000_01100_0010011`
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
| ADDI r12, r3, 5  | I-Type   | 000000000101_00011_000_01100_0010011  | 0x00518613      |
| SW r3, r1, 4  | S-Type   | 0000000_00011_00001_010_00100_0100011  | 0x0030A223     |
| SRL r16, r11, r2  | R-Type   | 0000000_00010_01011_101_10000_0110011 | 0x0025D833      |
| BNE r0, r1, 20  | B-Type   | 0_000001_00001_00000_001_0100_0_1100011 | 0x02101463      |
| BEQ r0, r0, 15  | B-Type   | 0_000000_00000_00000_000_1111_0_1100011  | 0x00000F63      |
| LW r13, r11, 2  | I-Type   | 000000000010_01011_010_01101_0000011  | 0x0025A683      |
| SLL r15, r11, r2  | R-Type   | 0000000_00010_01011_001_01111_0110011  | 0x002597B3      |

## LAB - 4
### Objective
- Using the RISC-V core Verilog netlist and testbench for a functional simulation experiment
- Plot the waveform in gtkwave

### Hardcoded table based on the provided Verilog code

- In the Verilog code, the opcode varies for each instruction type, and different instructions have distinct func3 values.
- To differentiate between immediate operations and other arithmetic functions, func7 is used; otherwise, func7 is set to b'0.

#### Hardcoded table for given instructions

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

#### Comparsion RISC-V ISA and  Hardcoded ISA 

| Operation           | Standard RISC-V ISA | Hardcoded ISA |
|---------------------|---------------------|---------------|
| ADD R6, R1, R2    | 0x00110333        | 0x02208300  |
| SUB R7, R1, R2    | 0x402083b3        | 0x02209380  |
| AND R8, R1, R3    | 0x0030f433        | 0x0230a400  |
| OR R9, R2, R5     | 0x005164b3        | 0x02513480  |
| XOR R10, R1, R4   | 0x0040c533        | 0x0240c500  |
| SLT R11, R2, R4   | 0x0045a0b3        | 0x02415580  |
| ADDI R12, R4, 5   | 0x004120b3        | 0x00520600  |
| SW R3, R1, 2      | 0x0030a123        | 0x00209181  |
| LW R13, R1, 2     | 0x0020a683        | 0x00208681  |
| BEQ R0, R0, 15    | 0x00000f63        | 0x00f00002  |
| ADD R14, R2, R2   | 0x00210733        | 0x00210700  |
 
### Output waveform

```c
ADD r5, r4, r5
```
<img width="604" alt="1" src="https://github.com/user-attachments/assets/f79e9479-3b4d-45f6-8ba5-2dde88c6536e">

```c
SUB r5, r5, r4
```
<img width="604" alt="2" src="https://github.com/user-attachments/assets/0cbc05a1-7c88-42a0-bffb-9af8d87e1d43">

```c
AND r4, r5, r5
```
<img width="604" alt="3" src="https://github.com/user-attachments/assets/2671958d-e773-4bf0-b44e-7bbdb5f59c37">

```c
OR r8, r4, r5
```
<img width="604" alt="4" src="https://github.com/user-attachments/assets/598930bd-4c56-474e-981d-3045f9b38e7f">


```c
XOR r8, r5, r4
```  
<img width="604" alt="5" src="https://github.com/user-attachments/assets/e4912603-89da-492a-a9d1-293080aff980">

```c
SLT r10, r2, r4 
```
<img width="604" alt="6" src="https://github.com/user-attachments/assets/6ede7353-e86e-4cda-93d8-cc783c35000f">


```c
ADDI r12, r3, 5  
```
<img width="604" alt="7" src="https://github.com/user-attachments/assets/0da68ed3-3edf-45b2-94dd-825384cd3d10">


```c
SW r3, r1, 4   
```
<img width="604" alt="8" src="https://github.com/user-attachments/assets/c501f6b7-ac99-4511-9258-c2b23e5e142a">

```c
LW r13, r11, 2  
```
<img width="604" alt="9" src="https://github.com/user-attachments/assets/7f34f4ac-30ee-42fd-955d-7cef799061b1">

```c
BEQ r0, r0, 15   
```
<img width="604" alt="10" src="https://github.com/user-attachments/assets/d9ee77f8-9be9-44e6-b73d-d6844e0d41c7">

```c
SRL r16, r11, r2
```
<img width="604" alt="11" src="https://github.com/user-attachments/assets/4b7d62ca-5c03-48c5-bcf2-877d908b323e">

### Final output

<img width="1000" alt="12" src="https://github.com/user-attachments/assets/36acfa08-5752-41ea-a06f-1178858b12f3">

## LAB - 5
### Objective
* Select an application, write the application code in C language, and compile it using GCC or RISC-V GCC.
### BMI calculator
* A BMI (Body Mass Index) calculator is a widely used tool to assess whether a person has a healthy body weight for a given height. By calculating the ratio of weight to height squared, BMI provides a quick estimate of body fat, allowing individuals to understand their weight category—underweight, normal weight, overweight, or obese—based on standardized classifications.
### C Code
* Code of C program that calculates a person's BMI using their height and weight.
```c
#include <stdio.h>

void calculateBMI(double weight, double height) {
    double bmi = weight / (height * height);
    printf("Your BMI is: %.2f\n", bmi);
    if (bmi < 18.5) {
        printf("You are underweight.\n");
    } else if (bmi < 24.9) {
        printf("You have a normal weight.\n");
    } else if (bmi < 29.9) {
        printf("You are overweight.\n");
    } else {
        printf("You are obese.\n");
    }
}

int main() {
    double weight, height;

    printf("Enter your weight in kilograms: ");
    scanf("%lf", &weight);
    printf("Enter your height in meters: ");
    scanf("%lf", &height);

    calculateBMI(weight, height);

    return 0;
}
```

![1](https://github.com/user-attachments/assets/25e2a141-41d2-40fe-9cd1-2df8d4e2c4fc)

### Part-1(GCC compiler)
* Running the C program using gcc compiler
#### Command
```c
gcc sum1ton.c
./a.out
```

![2](https://github.com/user-attachments/assets/3b8a8070-27c1-42d8-b212-33e1f4bd5295)

### Part-2(RISC-V 64bit)
* Using the O1 optimization level to compile for the RISC-V 64-bit architecture.
* A spike simulator is used to run the RISC-V 64-bit architecture.
#### Command
```c
riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c
spike pk sum1ton.o
```

![3](https://github.com/user-attachments/assets/c89c1869-f3fd-4e43-a6c7-4b63cebc5775)

## LAB - 6
### Objective
* The objective of this lab project is to build a 5-stage pipelined RISC-V processor by following the detailed lab lectures on the VSDIAT platform.
* A unique clock signal name should be used by appending your initials to the clock signal name. The project will be guided by the recordings available on Cell S1.

### Basic RISC-V CPU Micro-Architecture
* This section will detail the implementation of a simple 3-stage RISC-V core/CPU. The core operates through three primary stages: Fetch, Decode, and Execute.

![image](https://github.com/user-attachments/assets/98fe8e97-20ad-4f30-9ea2-4ea07a6e279c)

#### Program Counter
* The program counter increments by 4 to fetch the next instruction from memory, as illustrated in the image below. If a reset is triggered, the program counter will be initialized to zero, preparing it to fetch the next instruction.

![image](https://github.com/user-attachments/assets/d6cc376e-1549-46b5-88da-e1003eae9201)

#### Fetch Logic
* The program counter's output is used to fetch an instruction from the instruction memory. The instruction memory outputs a 32-bit instruction based on the provided input address. During the Fetch stage, the processor retrieves the instruction from the instruction memory at the address specified by the program counter.

![image](https://github.com/user-attachments/assets/61b8bb06-82e8-4090-96e9-0c74897d4855)

#### Decode Logic
* Below is the snapshot of the different instruction types (instr[6:2] determine instruction type: I, R, S, B, J, U)

![image](https://github.com/user-attachments/assets/c110516e-4088-4689-b748-3b98dfeea9ce)
* We have decoded the instruction based on all six types of the RISC-V instruction set.

![image](https://github.com/user-attachments/assets/1692d349-dbd7-4fda-a2df-24b48bb9bf44)

#### Immediate Decode Logic
* Below is the snapshot to determine the immediate value of different instructions
  
![image](https://github.com/user-attachments/assets/3aaa48ea-053d-4273-a267-5f0e1992258a)
* The instruction set includes an immediate field. To decode this field .
  
![image](https://github.com/user-attachments/assets/b0b69611-e4db-48c0-b26a-615ce09e0e29)

#### Decode Logic For Other Fields
* Only one instruction is passed on for decoding at a time. This instruction can belong to any one of the six instruction set types. Therefore, it is crucial to validate that it belongs to the correct category to prevent conflicts between different instruction set types.
  
![image](https://github.com/user-attachments/assets/3cd70f04-e20a-4066-bf26-65551ccebc0d)

#### Decode Individual Instructions
* Decoding the each instruction type in the following format.
  
![image](https://github.com/user-attachments/assets/7a851a9d-992b-4e20-87ed-f29b7de2ea4b)

#### Register File Read and Enable
* We read instructions from the instruction memory and store them in two register slots. After storing the instructions, we send them to the ALU for further processing.
  
![image](https://github.com/user-attachments/assets/4a2af94a-2b7c-4041-bb16-681f221da709)

#### ALU Block
* Depending on the decoded operation, the instruction is executed. If necessary, the Arithmetic and Logic Unit (ALU) is utilized. For branching instructions, the target branch address is computed separately before executing the instruction. The result is then stored back in the Register File, according to the destination register index. During the Execute stage, both operands perform the operation based on the opcode.
  
![image](https://github.com/user-attachments/assets/b77f4b24-bd6d-43d6-80a6-9cd7d4ef4cd8)

#### Register File Write and Enable
* After the ALU performs operations on the values stored in the registers, these values may need to be written back into the registers. This is accomplished using the register file write. We must also ensure that we do not write to the register if the destination is x0, as it is always intended to be zero.
  
![image](https://github.com/user-attachments/assets/e60d9546-2136-4fb5-920e-e5c1ec6ab713)

#### Branch Instructions
* Based on the control input, we may need to jump to a different address after a particular instruction, depending on a condition generated during runtime. This is where branch instructions come into play.
  
![image](https://github.com/user-attachments/assets/94c89c2a-fa88-4122-96de-7c14edd22a89)

#### Testbench
* To verify the correctness of the code, we use a testbench to check it during the first five cycles.
  
![image](https://github.com/user-attachments/assets/a9a082b8-2e0c-473a-8d27-5dae4bfc3a4c)

#### Results
* Block Diagram
  
![image](https://github.com/user-attachments/assets/3b7ad95b-253a-4ae1-a129-2ab3ced3b5eb)
* Waveform
    - Clock waveform named as clk_roh

    ![image](https://github.com/user-attachments/assets/14cd22e4-0021-45c3-bbf1-70d50196166d)

    - Reset waveform
  
    ![15](https://github.com/user-attachments/assets/209d4c7f-7708-41fd-9bfd-b387cea043a8)

    - Final Result waveform
  
    ![16](https://github.com/user-attachments/assets/bd307cb7-5e87-4bfa-9e84-4a2a148b8f85)

### Complete Pipelined RISC-V CPU Micro-architecture
* After pipelining is validated in simulations, support for Jump instructions is added.
* Additionally, Instruction Decode and ALU implementation for the RV32I Base Integer Instruction Set are incorporated.

#### Introducing Valid Signal for Pipelined Logic:
* Which introduces valid signals for pipelined logic, handles data hazards in the register file with bypassing, and corrects the branch target path:

```c
$start            = >>1$reset && !$reset;
$valid            = $reset ? 1'b0 : ($start || >>3$valid);
$valid_or_reset   = $valid || $reset;

$rs1_or_funct3_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
$rs2_valid           = $is_r_instr || $is_s_instr || $is_b_instr;
$rd_valid            = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
$funct7_valid        = $is_r_instr;
```

#### Handling Data Hazards in Register File with Bypassing:

```c
// Register file bypass logic - data forwarding from ALU to resolve RAW dependence
$src1_value[31:0] = $rs1_bypass ? >>1$result[31:0] : $rf_rd_data1[31:0];
$src2_value[31:0] = $rs2_bypass ? >>1$result[31:0] : $rf_rd_data2[31:0];
```

#### Correcting Branch Target Path:

```c
// Current instruction is valid if one of the previous 2 instructions were not (due to taken_branch, load, or jump)
$valid = ~(>>1$valid_taken_br || >>2$valid_taken_br || >>1$is_load || >>2$is_load || >>2$jump_valid || >>1$jump_valid);

// Determine if the current instruction is valid and if it is a taken branch
$valid_taken_br = $valid && $taken_br;

// Determine if the current instruction is valid and if it is a load
$valid_load = $valid && $is_load;

// Determine if the current instruction is valid and if it is a jump
$jump_valid = $valid && $is_jump;
$jal_valid  = $valid && $is_jal;
$jalr_valid = $valid && $is_jalr;
```

#### Final Check for Passed Condition:

```c
*passed = |cpu/xreg[14]>>5$value == (1+2+3+4+5+6+7+8+9+10);
```
* A screenshot of the code, waveform, and block diagram.
  
![image](https://github.com/user-attachments/assets/a8727117-94d3-4311-a92e-9a9f7b1981aa)

#### Results
* VIZ table:
    * You can see that the value of reg 10 and reg 14 will reach to 55 after 59 cycles.

![image](https://github.com/user-attachments/assets/9a5ac09b-79e2-4040-9c00-10c5d471a6fc)
* Block Diagram:

![image](https://github.com/user-attachments/assets/92b7861e-7c7d-4801-a356-e5d49aba3045)
* Waveform
    - Clock waveform named as clk_roh

    ![image](https://github.com/user-attachments/assets/a4cf2275-8b45-481f-9872-b06df6283d4b)

    - Reset waveform
    
    ![image](https://github.com/user-attachments/assets/6feea98c-43a1-4303-9b37-22550ca4fa4c)

    - Final Result waveform
    
    ![image](https://github.com/user-attachments/assets/44c08506-b829-4614-b345-47f5d7629b40)


## LAB - 7
### Objective
* Convert TLV to Verilog as explained in the video using Sandpiper.
* Write a testbench using sample testbench for rvmyth.
* Use iverilog to simulate and gtkwave to view the output waveforms. Plot below signals from gtkwave
  
#### Comparision of RISC-V architecture outputs of Iverilog GTKwave and Makerchip
* Run the following commands to set up a development environment for working with simulation and synthesis tools

```c
$ sudo apt install make python python3 python3-pip git iverilog gtkwave

$ cd ~

$ sudo apt-get install python3-venv

$ python3 -m venv .venv

$ source ~/.venv/bin/activate

$ pip3 install pyyaml click sandpiper-saas
```

![1](https://github.com/user-attachments/assets/7853fa2e-1f74-46d3-8e60-96295ae2e853)

* To install the required packages, run these commands in a virtual environment

```c
$ sudo apt install make python python3 python3-pip git iverilog gtkwave docker.io

$ sudo chmod 666 /var/run/docker.sock

$ cd ~

$ pip3 install pyyaml click sandpiper-saas
```

![2](https://github.com/user-attachments/assets/918bbe09-3c0c-4981-9634-94ff7f4754e0)

* Next, clone the following repository into your home directory and create a pre_synth_sim directory to store the output.
  
```c
$ cd ~

$ git clone https://github.com/manili/VSDBabySoC.git

$ cd /home/vsduser/VSDBabySoC

$ make pre_synth_sim
```

![3](https://github.com/user-attachments/assets/7130ccba-d3b2-4a44-a8b4-17b1649caf68)

* Convert the TVL file into Verilog using SandPiper-SaaS by modifying the TVL file

```c
$ sandpiper-saas -i ./src/module/rvmyth.tlv -o rvmyth.v --bestsv --noline -p verilog --outdir ./src/module/
```

![4](https://github.com/user-attachments/assets/29cdb6b9-9569-453e-8f5e-2be056859c26)

* To compile and simulate the RISC-V design, run the following code. The simulation results (e.g., pre_synth_sim.vcd) will be stored in the "output/pre_synth_sim directory."
  
```c
$ iverilog -o output/pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module
$ cd output
$ ./pre_synth_sim.out
```
![5](https://github.com/user-attachments/assets/751d9c82-e9e1-499c-a951-b48e863b81ff)

#### Results
* Waveform comparsion GTKWAVE and MAKERCHIP
    - Clock waveform named as clk_roh
    <p align="center">
      <img src="https://github.com/user-attachments/assets/79136bfb-c052-426e-9e0b-ab80d3d77494" alt="Image 6" height="300" width="45%"/>
      <img src="https://github.com/user-attachments/assets/a4cf2275-8b45-481f-9872-b06df6283d4b" alt="Image 7" height="300" width="45%"/>
    </p>

    - Reset waveform
    <p align="center">
      <img src="https://github.com/user-attachments/assets/058c7bf9-30fe-4576-8bc5-fe5fba794368" alt="Image 8" height="300" width="45%"/>
      <img src="https://github.com/user-attachments/assets/6feea98c-43a1-4303-9b37-22550ca4fa4c" alt="Image 9" height="300" width="45%"/>
    </p>

    - Final Result waveform
    <p align="center">
      <img src="https://github.com/user-attachments/assets/7be23ac6-4692-4f0c-8dc2-f84f27d77cdf" alt="Image 10" height="300" width="45%"/>
      <img src="https://github.com/user-attachments/assets/44c08506-b829-4614-b345-47f5d7629b40" alt="Image 11" height="300" width="45%"/>
    </p>

## LAB - 8
### Objective
* This task involves integrating and verifying the functionality of a custom RISC-V processor (rvmyth) within the BabySoC platform, using a set of specific tools for digital design and simulation.
* To generate DAC and PPL waveform for the RISC-V processor.

#### Phase-Locked Loop (PLL)
* A Phase-Locked Loop (PLL) is an electronic control system that generates an output signal whose phase is related to the phase of an input signal.
* It is commonly used in telecommunications, radio, and computing to synchronize signals, stabilize frequencies, and generate clocks for digital circuits.

#### Download and Prepare Project Files
* Download all files from BabySoc using below command.
```c
git clone https://github.com/manili/VSDBabySoC.git
```
![image](https://github.com/user-attachments/assets/5f8e6341-4aa9-4479-b39f-15a527a5f900)

#### Edit the Top-Level Verilog Code 
* I modified the top-level Verilog code for the vsdbabysoc to achieve the desired results.

![image](https://github.com/user-attachments/assets/90c276ea-4a78-4519-80c0-559ca9f0af5c)

#### Simulation procedure
* Run the following command to perform functional simulation
  
```c
cd BabySoC_Simulation
iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
./pre_synth_sim.out
gtkwave pre_synth_sim.vcd
```

![image](https://github.com/user-attachments/assets/489a5293-12b3-4d5e-b28d-a28c8dec5f4f)

#### Results
* Waveform
    - Clock waveform named as clk_roh along with PLL clock

    ![image](https://github.com/user-attachments/assets/50643349-fe78-43b3-b7d2-2fceb5034a4e)

    - Reset waveform
    
    ![image](https://github.com/user-attachments/assets/773c8556-518b-4a01-8f87-fa2e03abf2dd)

    - Final Result waveform (along with PLL output signal, rvmyth 10-bit output signal, DAC output analog waveform)
    
    ![image](https://github.com/user-attachments/assets/46833ea6-1021-4476-aea7-6fe218c30b8e)
  
    ![image](https://github.com/user-attachments/assets/3471cb30-23f7-41be-bc3c-adb880107aa5)

## LAB - 9
### Day 1:Introduction to Verilog RTL design and Synthesis
- In digital circuit design, the Register-Transfer Level (RTL) models data flow between hardware registers and logic operations using Hardware Description Languages (HDL). These high-level models are transformed into physical hardware designs.
- Simulation, using tools like Icarus Verilog (iverilog), verifies circuit designs by replicating device behavior. A test bench applies input stimuli (test vectors) to validate the design's functionality and ensure it meets specifications.

#### HOW SIMULATOR WORKS
- The simulator monitors input signals and evaluates the output whenever an input change occurs. If there is no change in the input, the output remains unevaluated, and the simulator does not update it.
![image](https://github.com/user-attachments/assets/5965d5c9-aace-4720-8fa8-175e1c6c731d)

Start by executing the following commands:
```c
mkdir ASIC
cd ASIC
git clone https://github.com/kunalg123/vsdflow.git
git clone https://github.com/kunalg123/sky130RTLDesignAndSynthesisWorkshop.git
cd sky130RTLDesignAndSynthesisWorkshop
```
![image](https://github.com/user-attachments/assets/d7a05c71-d492-4a50-825f-eb3d09ef2277)

![image](https://github.com/user-attachments/assets/1d7969ce-db59-43f3-a6c6-4c68a579b325)

- To simulate the Verilog code in 'good_mux.v', follow these steps: First, compile the design and testbench using the provided command, which checks for syntax errors and generates an executable 'a.out' if successful. Running 'a.out' produces a VCD file that logs input and output changes during simulation. Finally, use GTKWave to view and analyze the waveform data in the VCD file.

```c
iverilog good_mux.v tb_good_mux.v
./a.out
gtkwave tb_good_mux.vcd
```
![image](https://github.com/user-attachments/assets/a41cc102-2cf9-4972-a82e-b22f829d8887)

![image](https://github.com/user-attachments/assets/9c9e8627-3134-4e36-9353-c242804e490e)

#### good_mux.v Code
```c
module good_mux (input i0 , input i1 , input sel , output reg y);
  always @ (*)
    begin
      if(sel)
      y <= i1;
    else 
      y <= i0;
  end
endmodule
```
#### tb_good_mux.v Code
```c
`timescale 1ns / 1ps
module tb_good_mux;
  // Inputs
  reg i0,i1,sel;
  // Outputs
  wire y;
  
    // Instantiate the Unit Under Test (UUT)
  good_mux uut (
    .sel(sel),
    .i0(i0),
    .i1(i1),
    .y(y)
  );
  
  initial begin
  $dumpfile("tb_good_mux.vcd");
  $dumpvars(0,tb_good_mux);
  // Initialize Inputs
  sel = 0;
  i0 = 0;
  i1 = 0;
  #300 $finish;
  end
  
  always #75 sel = ~sel;
  always #10 i0 = ~i0;
  always #55 i1 = ~i1;
endmodule
```
#### Yosys SETUP
![image](https://github.com/user-attachments/assets/5f80e662-5c63-4f53-8e00-4799b2afd65e)

#### Logic Synthesis
- RTL design involves describing the required functionality in HDL.
- Synthesis translates the RTL design into a gate-level netlist, connecting gates as per the design.
- The Liberty (.lib) file contains logical modules, including various types of logic gates (e.g., AND, OR) with different input sizes and speed variants. Fast gates offer high performance but consume more area and power, while slower gates help with hold time but can reduce performance. Optimal gate selection during synthesis balances area, power, and timing constraints.

![image](https://github.com/user-attachments/assets/522de956-f124-495a-b927-58865f3ebd4a)

- Cell delay in a digital circuit is influenced by load capacitance—faster charging or discharging reduces delay. Wider transistors speed up this process by providing more current, but increase power consumption and area. Narrower transistors save area and power but increase cell delay. Thus, minimizing cell delay requires balancing area, power, and delay.
  
![image](https://github.com/user-attachments/assets/744bb8de-9287-4fe6-af9f-2898fbf39a23)

#### Yosys flow
```c
yosys
```
![image](https://github.com/user-attachments/assets/08d52fd6-1a27-48eb-b6af-ff6436215624)

```c
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
![image](https://github.com/user-attachments/assets/70f0dec7-224a-442c-ad8e-5ec3d69c0b66)

```c
read_verilog good_mux.v
```
![image](https://github.com/user-attachments/assets/06286ce4-05e1-4f01-b477-d5d7429b660f)

```c
synth -top good_mux
```
![image](https://github.com/user-attachments/assets/bd39936a-9fdf-4da9-a935-3cfaa28cffe1)

```c
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
![image](https://github.com/user-attachments/assets/6b8f5060-8dbc-4f81-a129-4b1a83d66cc5)

```c
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
![image](https://github.com/user-attachments/assets/1f33a43a-9b98-4ca9-91ac-7fba5b94d19d)

```c
show
```
![image](https://github.com/user-attachments/assets/cf652d9e-8984-4a11-a736-af41e19d9984)

```c
write_verilog good_mux_netlist.v
```
![image](https://github.com/user-attachments/assets/98a6c68c-dc9c-4a84-a82d-5eae67c3e08b)

```c
write_verilog -noattr good_mux_netlist.v
```
![image](https://github.com/user-attachments/assets/23752d05-9c28-4121-ae77-2a95387d2adf)

![image](https://github.com/user-attachments/assets/3783d482-1d7c-4174-b63c-82aece5b02d1)

### Day 2:Timing libs, hierarchical vs flat synthesis and efficient flop coding styles
- Execute the following commands to check the contents of the .lib file:
```c
cd ASIC/sky130RTLDesignAndSynthesisWorkshop/lib/
vim sky130_fd_sc_hd__tt_025C_1v80.lib
```
![image](https://github.com/user-attachments/assets/fead9ab8-2bfb-4dc8-8c30-c428cbc2c4eb)

#### Cell library
- A standard cell library is a collection of characterized logic gates that can be used to implement digital circuits. The Liberty (.lib) files contain PVT parameters (Process, Voltage, Temperature) that can significantly impact circuit performance. Variations in manufacturing, changes in voltage, and fluctuations in temperature all play a role in affecting how the circuit functions.

![image](https://github.com/user-attachments/assets/949ab029-1085-4909-a688-ce4fe23c22a8)

![image](https://github.com/user-attachments/assets/d4eaeaab-73c0-438d-a52f-8d0f208511d1)

![image](https://github.com/user-attachments/assets/7d635831-409d-4196-a786-cb27f2b02ab0)

We can observe that:
- and2_0 -- takes the least area, more delay and low power.
- and2_1 -- takes more area, less delay and high power.
- and2_2 -- takes the largest area, larger delay and highest power.

#### Hierarchial synthesis vs Flat synthesis
- Hierarchical synthesis breaks down a complex design into sub-modules, synthesizing each separately to produce gate-level netlists before integration. This approach improves organization, supports module reuse, and allows incremental changes without affecting the whole system.
- In contrast, flat synthesis treats the entire design as one unit, producing a single netlist without structural modularity. While it can optimize some designs, flat synthesis is harder to maintain, analyze, and modify.

#### Hierarchial synthesis
- Consider the verilog file multiple_modules.v which is given in the verilog_files directory
```c
module sub_module2 (input a, input b, output y);
    assign y = a | b;
endmodule

module sub_module1 (input a, input b, output y);
    assign y = a&b;
endmodule


module multiple_modules (input a, input b, input c , output y);
    wire net1;
    sub_module1 u1(.a(a),.b(b),.y(net1));  //net1 = a&b
    sub_module2 u2(.a(net1),.b(c),.y(y));  //y = net1|c ,ie y = a&b + c;
endmodule
```

- Run the follwing commands 
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_modules.v
synth -top multiple_modules
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show multiple_modules
write_verilog -noattr multiple_modules_hier.v
!vim multiple_modules_hier.v
```
##### Statistics
![image](https://github.com/user-attachments/assets/05968204-9b05-417d-ba52-023d76c8b102)

#### Schematics
![image](https://github.com/user-attachments/assets/efd0b193-a2f0-4cb9-acf0-c5486cadb8cb)

```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module multiple_modules(a, b, c, y);
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  wire net1;
  output y;
  wire y;
  sub_module1 u1 (
    .a(a),
    .b(b),
    .y(net1)
  );
  sub_module2 u2 (
    .a(net1),
    .b(c),
    .y(y)
  );
endmodule

module sub_module1(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule

module sub_module2(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__or2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule
```

#### Flat synthesis
- Run the follwing commands 
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_modules.v
synth -top multiple_modules
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
flatten
show
write_verilog -noattr multiple_modules_flat.v
!vim multiple_modules_flat.v
```
##### Statistics
![image](https://github.com/user-attachments/assets/1d46f9cc-2c96-45d7-92fb-26f8bbc1753a)

#### Schematics
![image](https://github.com/user-attachments/assets/7f22f3c3-3542-40da-ac4e-a86436aaedc6)

```c
  /* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module multiple_modules(a, b, c, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  wire _5_;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  wire net1;
  wire \u1.a ;
  wire \u1.b ;
  wire \u1.y ;
  wire \u2.a ;
  wire \u2.b ;
  wire \u2.y ;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _6_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  sky130_fd_sc_hd__or2_0 _7_ (
    .A(_4_),
    .B(_3_),
    .X(_5_)
  );
  assign _4_ = \u2.b ;
  assign _3_ = \u2.a ;
  assign \u2.y  = _5_;
  assign \u2.a  = net1;
  assign \u2.b  = c;
  assign y = \u2.y ;
  assign _1_ = \u1.b ;
  assign _0_ = \u1.a ;
  assign \u1.y  = _2_;
  assign \u1.a  = a;
  assign \u1.b  = b;
  assign net1 = \u1.y ;
endmodule
```

#### Sub Module Level Synthesis
- Run the follwing commands 
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
read_verilog multiple_modules.v 
synth -top sub_module
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
```
##### Statistics
![image](https://github.com/user-attachments/assets/1d46f9cc-2c96-45d7-92fb-26f8bbc1753a)

#### Schematics
![image](https://github.com/user-attachments/assets/bf12f41d-05f4-4585-815c-208b3d70924a)

#### Flop coding styles and optimization
- Flip-flops are essential in sequential logic circuits, storing intermediate values and preventing glitches. They ensure inputs to combinational circuits remain stable until the clock edge, enabling reliable system operation.

#### Asynchronous Reset Flip-Flop
- An asynchronous reset flip-flop immediately resets its output (q) when the reset signal is asserted, regardless of the clock state. This feature is useful for quick initialization, enabling rapid response to system condition changes.

#### Verilog Code 
```c
module dff_asyncres (
    input clk,
    input async_reset,
    input d,
    output reg q
);
always @(posedge clk or posedge async_reset) begin
    if (async_reset)
        q <= 1'b0;  // Reset output to 0 when async_reset is high
    else
        q <= d;     // On clock edge, capture the input data
end
endmodule
```

#### Run the following commands
```c
iverilog dff_asyncres.v tb_dff_asyncres.v
./a.out
gtkwave tb_dff_asyncres.vcd
```
#### GTK Wave
![image](https://github.com/user-attachments/assets/6a751916-b3e4-4a03-b5c2-36490c382a80)

#### Netlist generation
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_asyncres.v
synth -top dff_asyncres
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```
#### Statistics
![image](https://github.com/user-attachments/assets/7b0a0a8e-146e-4b1d-9678-e955d28b36c8)

#### Schematics
![image](https://github.com/user-attachments/assets/db48e2fc-edc1-47f2-b91b-622015c2d533)

#### Synchronous Reset Flip-Flop
-A synchronous reset flip-flop updates its output only on the clock's rising edge, with the reset occurring in sync with the clock signal. This ensures predictable behavior within each clock cycle.

#### Verilog Code 
```c
module dff_syncres (
    input clk,
    input sync_reset,
    input d,
    output reg q
);
always @(posedge clk) begin
    if (sync_reset)
        q <= 1'b0;  // Reset output to 0 during the clock edge if sync_reset is high
    else
        q <= d;     // Capture the input data on the clock edge
end
endmodule
```

#### Run the following commands
```c
iverilog dff_syncres.v tb_dff_syncres.v
./a.out
gtkwave tb_dff_syncres.vcd
```
#### GTK Wave
![image](https://github.com/user-attachments/assets/2778a96b-bd6b-4c81-862e-77e4a8d7a161)

#### Netlist generation
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_syncres.v
synth -top dff_syncres
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```
#### Statistics
![image](https://github.com/user-attachments/assets/2077adc5-6192-4097-9777-a57f3e319167)

#### Schematics
![image](https://github.com/user-attachments/assets/70d7d58e-6809-4c31-b1c7-dd374bcfd7f6)

#### Asynchronous Set Flip-Flop
-An asynchronous set flip-flop instantly drives its output (q) to a high state when the set signal is activated, responding immediately to changes in the set signal regardless of the clock.

#### Verilog Code 
```c
module dff_async_set (
    input clk,
    input async_set,
    input d,
    output reg q
);
always @(posedge clk or posedge async_set) begin
    if (async_set)
        q <= 1'b1;  // Set output to 1 when async_set is high
    else
        q <= d;     // Capture the input data on the clock edge
end
endmodule
```

#### Run the following commands
```c
iverilog dff_async_set.v tb_dff_async_set.v
./a.out
gtkwave tb_dff_async_set.vcd
```
#### GTK Wave
![image](https://github.com/user-attachments/assets/0448e9ad-0560-4e1b-93f2-b040de587b18)

#### Netlist generation
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_async_set.v
synth -top dff_async_set
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```
#### Statistics
![image](https://github.com/user-attachments/assets/99ea1ad6-4b3c-4606-9c8e-b03cde5ea0fd)


#### Schematics
![image](https://github.com/user-attachments/assets/49eecd80-e71c-42d0-a4fb-5fe0b826e7af)

#### Design Optimizations
Example: Multiplication by 2

#### Verilog code
```c
module mul2 (
    input [2:0] a,
    output [3:0] y
);
assign y = a * 2;  // Multiply input by 2
endmodule
```
#### Truth Table
|a2 | a1 | a0 | y3 | y2 | y1 | y0 |
|---|----|----|----|----|----|----|
| 0 | 0  | 0  | 0  | 0  | 0  | 0  |
| 0 | 0  | 1  | 0  | 0  | 1  | 0  |
| 0 | 1  | 0  | 0  | 1  | 0  | 0  |
| 0 | 1  | 1  | 0  | 1  | 1  | 0  |
| 1 | 0  | 0  | 1  | 0  | 0  | 0  |
| 1 | 0  | 1  | 1  | 0  | 1  | 0  |
| 1 | 1  | 0  | 1  | 1  | 0  | 0  |
| 1 | 1  | 1  | 1  | 1  | 1  | 0  |

#### Optimization Insight
- Multiplying a number by 2 can be done by left-shifting the input bits and appending a zero in the least significant bit (LSB), eliminating the need for extra hardware and simplifying the design while saving resources.

#### Run the following commands
```c
yosys
read_liberty -lib ../my_lib/lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog mult_2.v
synth -top mult2
abc -liberty ../my_lib/lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show 
write_verilog -noattr mult_2_net.v
!vim mult_2_net.v
```
#### Statistics
![image](https://github.com/user-attachments/assets/f29a5b68-cb18-4217-9715-34054ff1b708)

#### Schematics
![image](https://github.com/user-attachments/assets/40f17679-6330-4b5d-ad1e-07215f95b0fc)

#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module mul2(a, y);
  input [2:0] a;
  wire [2:0] a;
  output [3:0] y;
  wire [3:0] y;
  assign y = { a, 1'h0 };
endmodule
```
Example: Multiplication by 9

#### Verilog code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module mul2(a, y);
  input [2:0] a;
  wire [2:0] a;
  output [3:0] y;
  wire [3:0] y;
  assign y = { a, 1'h0 };
endmodule
```

#### Optimization Insight
- In this design the 3-bit input number "a" is multiplied by 9 i.e (a9) which can be re-written as (a8) + a . The term (a8) is nothing but a left shifting the number a by three bits. Consider that a = a2 a1 a0. (a8) results in a2 a1 a0 0 0 0. (a9)=(a8)+a = a2 a1 a0 a2 a1 a0 = aa(in 6 bit format). Hence in this case no hardware realization is required. The synthesized netlist of this design is shown below:

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog mult_8.v
synth -top mult8
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr mult_8_net.v
```
#### Statistics
![image](https://github.com/user-attachments/assets/ff96829c-19ab-41ed-a808-0c258eb1e550)

#### Schematics
![image](https://github.com/user-attachments/assets/f8f84fb4-15c2-4457-bb65-f138f52c8681)

#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module mult8(a, y);
  input [2:0] a;
  wire [2:0] a;
  output [5:0] y;
  wire [5:0] y;
  assign y = { a, a };
endmodule
```

### Day 3:Optimizing Combinational and Sequential Logic
- There are two types of optimisations: Combinational and Sequential optimisations. These optimisations are done inorder to achieve designs that are efficient in terms of area, power, and performance.

* Combinational Optimization
    * The techiniques used are:
        * Constant Propagation (Direct Optimisation)
        * Boolean Logic Optimisation (using K-Map or Quine McCluskey method)

#### Constant Propagation
![image](https://github.com/user-attachments/assets/5323a99c-97a9-4a8f-a1b4-fcac87df418c)

Example 1:
#### Verilog code:
```c
module opt_check (input a , input b , output y);
	assign y = a?b:0;
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check.v
synth -top opt_check
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/3b3fa9e3-bae7-48b8-8980-12bd7e3b9dd0)

#### Schematics
![image](https://github.com/user-attachments/assets/bad582ed-6069-4e61-a1d0-950065fa8192)

#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module opt_check(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule
```

Example 2:
#### Verilog code:
```c
module opt_check2 (input a , input b , output y);
	assign y = a?1:b;
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check2.v
synth -top opt_check2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check2_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/47d492c9-9e8d-4096-8c00-c20c00373db6)

#### Schematics
![image](https://github.com/user-attachments/assets/afc077fa-f3d9-4b26-a7d6-8587c464c991)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module opt_check2(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__or2_0 _3_ (
    .A(_0_),
    .B(_1_),
    .X(_2_)
  );
  assign _0_ = a;
  assign _1_ = b;
  assign y = _2_;
endmodule
```

Example 3:
#### Verilog code:
```c
module opt_check3 (input a , input b, input c , output y);
	assign y = a?(c?b:0):0;
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check3.v
synth -top opt_check3
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check3_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/14d869ec-12cd-4fbd-9f5a-c89d67e290d5)


#### Schematics
![image](https://github.com/user-attachments/assets/9ad64961-7322-4fef-af23-e6fdf6771f31)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module opt_check3(a, b, c, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  output y;
  wire y;
  sky130_fd_sc_hd__and3_1 _5_ (
    .A(_2_),
    .B(_3_),
    .C(_1_),
    .X(_4_)
  );
  assign _2_ = b;
  assign _3_ = c;
  assign _1_ = a;
  assign y = _4_;
endmodule
```

Example 4:
#### Verilog code:
```c
module opt_check4 (input a , input b, input c , output y);
	assign y = a?(c?b:0):0;
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog opt_check4.v
synth -top opt_check4
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr opt_check4_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/e0f71401-a776-4a23-9fdb-55a61c8afbcb)


#### Schematics
![image](https://github.com/user-attachments/assets/e31b000a-6a05-4659-98c0-e728cd20ea95)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module opt_check4(a, b, c, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  wire _5_;
  wire _6_;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  output y;
  wire y;
  sky130_fd_sc_hd__xnor2_1 _7_ (
    .A(_5_),
    .B(_3_),
    .Y(_6_)
  );
  assign _5_ = c;
  assign _3_ = a;
  assign _4_ = b;
  assign y = _6_;
endmodule
```

Example 5:
#### Verilog code:
```c
module sub_module1(input a , input b , output y);
 assign y = a & b;
endmodule

module sub_module2(input a , input b , output y);
 assign y = a^b;
endmodule

module multiple_module_opt(input a , input b , input c , input d , output y);
wire n1,n2,n3;

sub_module1 U1 (.a(a) , .b(1'b1) , .y(n1));
sub_module2 U2 (.a(n1), .b(1'b0) , .y(n2));
sub_module2 U3 (.a(b), .b(d) , .y(n3));

assign y = c | (b & n1); 

endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_module_opt.v
synth -top multiple_module_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
flatten
show
write_verilog -noattr multiple_module_opt_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/4e9cdc99-b2ad-448d-90cd-8b1a56ac238d)


#### Schematics
![image](https://github.com/user-attachments/assets/560dcd16-820c-4dfb-9028-355c007c6329)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module multiple_module_opt(a, b, c, d, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  wire _5_;
  wire _6_;
  wire _7_;
  wire \U1.a ;
  wire \U1.b ;
  wire \U1.y ;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  input d;
  wire d;
  wire n1;
  output y;
  wire y;
  sky130_fd_sc_hd__a21o_1 _8_ (
    .A1(_3_),
    .A2(_1_),
    .B1(_2_),
    .X(_4_)
  );
  sky130_fd_sc_hd__and2_0 _9_ (
    .A(_6_),
    .B(_5_),
    .X(_7_)
  );
  assign _3_ = n1;
  assign _1_ = b;
  assign _2_ = c;
  assign y = _4_;
  assign _6_ = \U1.b ;
  assign _5_ = \U1.a ;
  assign \U1.y  = _7_;
  assign \U1.a  = a;
  assign \U1.b  = 1'h1;
  assign n1 = \U1.y ;
endmodule
```
Example 6:
#### Verilog code:
```c
module sub_module(input a , input b , output y);
	assign y = a & b;
endmodule

module multiple_module_opt2(input a , input b , input c , input d , output y);
		wire n1,n2,n3;
	sub_module U1 (.a(a) , .b(1'b0) , .y(n1));
	sub_module U2 (.a(b), .b(c) , .y(n2));
	sub_module U3 (.a(n2), .b(d) , .y(n3));
	sub_module U4 (.a(n3), .b(n1) , .y(y));
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_module_opt2.v
synth -top multiple_module_opt2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
flatten
show
write_verilog -noattr multiple_module_opt2_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/9d17244c-8774-4587-aecb-4ac1a6cf4ceb)


#### Schematics
![image](https://github.com/user-attachments/assets/b9466bd5-3a48-479c-9481-40216b421bb8)


#### Netlist Code
```c
	/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module multiple_module_opt2(a, b, c, d, y);
  wire _00_;
  wire _01_;
  wire _02_;
  wire _03_;
  wire _04_;
  wire _05_;
  wire _06_;
  wire _07_;
  wire _08_;
  wire _09_;
  wire _10_;
  wire _11_;
  wire \U1.a ;
  wire \U1.b ;
  wire \U1.y ;
  wire \U2.a ;
  wire \U2.b ;
  wire \U2.y ;
  wire \U3.a ;
  wire \U3.b ;
  wire \U3.y ;
  wire \U4.a ;
  wire \U4.b ;
  wire \U4.y ;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  input d;
  wire d;
  wire n1;
  wire n2;
  wire n3;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _12_ (
    .A(_01_),
    .B(_00_),
    .X(_02_)
  );
  sky130_fd_sc_hd__and2_0 _13_ (
    .A(_04_),
    .B(_03_),
    .X(_05_)
  );
  sky130_fd_sc_hd__and2_0 _14_ (
    .A(_07_),
    .B(_06_),
    .X(_08_)
  );
  sky130_fd_sc_hd__and2_0 _15_ (
    .A(_10_),
    .B(_09_),
    .X(_11_)
  );
  assign _10_ = \U4.b ;
  assign _09_ = \U4.a ;
  assign \U4.y  = _11_;
  assign \U4.a  = n3;
  assign \U4.b  = n1;
  assign y = \U4.y ;
  assign _07_ = \U3.b ;
  assign _06_ = \U3.a ;
  assign \U3.y  = _08_;
  assign \U3.a  = n2;
  assign \U3.b  = d;
  assign n3 = \U3.y ;
  assign _04_ = \U2.b ;
  assign _03_ = \U2.a ;
  assign \U2.y  = _05_;
  assign \U2.a  = b;
  assign \U2.b  = c;
  assign n2 = \U2.y ;
  assign _01_ = \U1.b ;
  assign _00_ = \U1.a ;
  assign \U1.y  = _02_;
  assign \U1.a  = a;
  assign \U1.b  = 1'h0;
  assign n1 = \U1.y ;
endmodule
```

#### Sequential Logic Optimizations
Example 1:
#### Verilog code:
```c
module dff_const1(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b0;
	else
		q <= 1'b1;
end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const1.v
synth -top dff_const1
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const1_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/fd342a15-8455-4ab3-92e8-96b8ba2454bb)


#### Schematics
![image](https://github.com/user-attachments/assets/e0497568-0e08-44f3-9866-9fb5181e94ad)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module dff_const1(clk, reset, q);
  wire _0_;
  wire _1_;
  wire _2_;
  input clk;
  wire clk;
  output q;
  wire q;
  input reset;
  wire reset;
  sky130_fd_sc_hd__clkinv_1 _3_ (
    .A(_1_),
    .Y(_0_)
  );
  sky130_fd_sc_hd__dfrtp_1 _4_ (
    .CLK(clk),
    .D(1'h1),
    .Q(q),
    .RESET_B(_2_)
  );
  assign _1_ = reset;
  assign _2_ = _0_;
endmodule
```
#### Run the following commands
```c
iverilog dff_const1.v tb_dff_const1.v
./a.out
gtkwave tb_dff_const1.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/2ff48df9-d8dd-4b5c-86af-f697413efaaa)

Example 2:
#### Verilog code:
```c
module dff_const2(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b1;
	else
		q <= 1'b1;
end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const2.v
synth -top dff_const2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const2_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/e34a0027-9c56-43b3-8128-ce7e2a78bac0)


#### Schematics
![image](https://github.com/user-attachments/assets/f7e2cd79-4f67-4c13-9345-56139e12d3e7)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module dff_const2(clk, reset, q);
  input clk;
  wire clk;
  output q;
  wire q;
  input reset;
  wire reset;
  assign q = 1'h1;
endmodule
```
#### Run the following commands
```c
iverilog dff_const2.v tb_dff_const2.v
./a.out
gtkwave tb_dff_const2.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/bfcc6649-73bc-4772-aa42-2e7727516aca)

Example 3:
#### Verilog code:
```c
module dff_const3(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b0;
	end
	else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const3.v
synth -top dff_const3
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const3_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/d19d1d9d-a566-4c1d-adfb-b6ffb898aa77)


#### Schematics
![image](https://github.com/user-attachments/assets/7d58d9f6-5996-48a1-9b5e-f602c502ecae)



#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module dff_const3(clk, reset, q);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  input clk;
  wire clk;
  output q;
  wire q;
  wire q1;
  input reset;
  wire reset;
  sky130_fd_sc_hd__clkinv_1 _5_ (
    .A(_2_),
    .Y(_0_)
  );
  sky130_fd_sc_hd__clkinv_1 _6_ (
    .A(_2_),
    .Y(_1_)
  );
  sky130_fd_sc_hd__dfstp_2 _7_ (
    .CLK(clk),
    .D(q1),
    .Q(q),
    .SET_B(_3_)
  );
  sky130_fd_sc_hd__dfrtp_1 _8_ (
    .CLK(clk),
    .D(1'h1),
    .Q(q1),
    .RESET_B(_4_)
  );
  assign _2_ = reset;
  assign _3_ = _0_;
  assign _4_ = _1_;
endmodule

```
#### Run the following commands
```c
iverilog dff_const3.v tb_dff_const3.v
./a.out
gtkwave tb_dff_const3.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/9d87a65f-f53f-464a-8ffc-2af788d44d43)

Example 4:
#### Verilog code:
```c
module dff_const4(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b1;
	end
else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const4.v
synth -top dff_const4
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const4_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/bc664eb1-5bff-41aa-905e-b9e605179c9b)


#### Schematics
![image](https://github.com/user-attachments/assets/00a242ea-3a6d-4df2-b189-1d60bffa2e41)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module dff_const4(clk, reset, q);
  input clk;
  wire clk;
  output q;
  wire q;
  wire q1;
  input reset;
  wire reset;
  assign q = 1'h1;
  assign q1 = 1'h1;
endmodule
```
#### Run the following commands
```c
iverilog dff_const4.v tb_dff_const4.v
./a.out
gtkwave tb_dff_const4.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/b44cece1-2eda-4c10-9f97-19171db40912)

Example 5:
#### Verilog code:
```c
module dff_const5(input clk, input reset, output reg q);
    reg q1;
    always @(posedge clk, posedge reset) begin
        if (reset) begin
            q <= 1'b0;
            q1 <= 1'b0;
        end else begin
            q1 <= 1'b1;
            q <= q1;
        end
    end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const5.v
synth -top dff_const5
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const5_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/d97b0d68-c563-4ef1-a176-93d60d2b5c8b)


#### Schematics
![image](https://github.com/user-attachments/assets/a8f8d19a-e1c7-44cf-83d5-88f7b3819adc)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module dff_const5(clk, reset, q);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  input clk;
  wire clk;
  output q;
  wire q;
  wire q1;
  input reset;
  wire reset;
  sky130_fd_sc_hd__clkinv_1 _5_ (
    .A(_2_),
    .Y(_0_)
  );
  sky130_fd_sc_hd__clkinv_1 _6_ (
    .A(_2_),
    .Y(_1_)
  );
  sky130_fd_sc_hd__dfrtp_1 _7_ (
    .CLK(clk),
    .D(q1),
    .Q(q),
    .RESET_B(_3_)
  );
  sky130_fd_sc_hd__dfrtp_1 _8_ (
    .CLK(clk),
    .D(1'h1),
    .Q(q1),
    .RESET_B(_4_)
  );
  assign _2_ = reset;
  assign _3_ = _0_;
  assign _4_ = _1_;
endmodule
```
#### Run the following commands
```c
iverilog dff_const5.v tb_dff_const5.v
./a.out
gtkwave tb_dff_const5.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/c20de44d-cc0f-490f-bfe3-d5bdb3ef4704)

#### Optimizing Unused Outputs in Counters
Example 1:
#### Verilog code:
```c
module counter_opt(input clk, input reset, output q);
    reg [2:0] count;
    assign q = count[0];
    always @(posedge clk, posedge reset) begin
        if (reset)
            count <= 3'b000;
        else
            count <= count + 1;
    end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog counter_opt.v
synth -top counter_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr counter_opt_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/081a84c9-4365-46fd-9cd4-a683998106be)


#### Schematics
![image](https://github.com/user-attachments/assets/cd1affe1-950b-47ff-9abb-179907f89912)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module counter_opt(clk, reset, q);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire [2:0] _4_;
  wire _5_;
  input clk;
  wire clk;
  wire [2:0] count;
  output q;
  wire q;
  input reset;
  wire reset;
  sky130_fd_sc_hd__clkinv_1 _6_ (
    .A(_2_),
    .Y(_0_)
  );
  sky130_fd_sc_hd__clkinv_1 _7_ (
    .A(_3_),
    .Y(_1_)
  );
  sky130_fd_sc_hd__dfrtp_1 _8_ (
    .CLK(clk),
    .D(_4_[0]),
    .Q(count[0]),
    .RESET_B(_5_)
  );
  assign _4_[2:1] = count[2:1];
  assign q = count[0];
  assign _2_ = count[0];
  assign _4_[0] = _0_;
  assign _3_ = reset;
  assign _5_ = _1_;
endmodule
```
#### Run the following commands
```c
iverilog counter_opt.v tb_counter_opt.v
./a.out
gtkwave tb_counter_opt.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/17f3631a-c885-4374-b6cb-061017f136a4)


#### Modified counter logic

#### Verilog code:
```c
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = {count[2:0]==3'b100};
always @(posedge clk ,posedge reset)
begin
if(reset)
	count <= 3'b000;
else
	count <= count + 1;
end
endmodule
```

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog counter_opt.v
synth -top counter_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr counter_opt_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/f9a96c91-8f86-4ace-a753-c3697f8d800b)


#### Schematics
![image](https://github.com/user-attachments/assets/70bc5a6c-d0b7-4d73-9f75-1af7a3c598e2)



#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module counter_opt(clk, reset, q);
  wire _00_;
  wire _01_;
  wire _02_;
  wire _03_;
  wire _04_;
  wire _05_;
  wire _06_;
  wire _07_;
  wire _08_;
  wire _09_;
  wire _10_;
  wire _11_;
  wire _12_;
  wire _13_;
  wire [2:0] _14_;
  wire [2:0] _15_;
  wire _16_;
  wire _17_;
  wire _18_;
  input clk;
  wire clk;
  wire [2:0] count;
  output q;
  wire q;
  input reset;
  wire reset;
  sky130_fd_sc_hd__clkinv_1 _19_ (
    .A(_08_),
    .Y(_02_)
  );
  sky130_fd_sc_hd__clkinv_1 _20_ (
    .A(_13_),
    .Y(_05_)
  );
  sky130_fd_sc_hd__nor3b_1 _21_ (
    .A(_08_),
    .B(_09_),
    .C_N(_10_),
    .Y(_12_)
  );
  sky130_fd_sc_hd__nand2_1 _22_ (
    .A(_08_),
    .B(_09_),
    .Y(_11_)
  );
  sky130_fd_sc_hd__xor2_1 _23_ (
    .A(_08_),
    .B(_09_),
    .X(_03_)
  );
  sky130_fd_sc_hd__xnor2_1 _24_ (
    .A(_10_),
    .B(_11_),
    .Y(_04_)
  );
  sky130_fd_sc_hd__clkinv_1 _25_ (
    .A(_13_),
    .Y(_06_)
  );
  sky130_fd_sc_hd__clkinv_1 _26_ (
    .A(_13_),
    .Y(_07_)
  );
  sky130_fd_sc_hd__dfrtp_1 _27_ (
    .CLK(clk),
    .D(_14_[0]),
    .Q(count[0]),
    .RESET_B(_16_)
  );
  sky130_fd_sc_hd__dfrtp_1 _28_ (
    .CLK(clk),
    .D(_15_[1]),
    .Q(count[1]),
    .RESET_B(_17_)
  );
  sky130_fd_sc_hd__dfrtp_1 _29_ (
    .CLK(clk),
    .D(_15_[2]),
    .Q(count[2]),
    .RESET_B(_18_)
  );
  assign _15_[0] = _14_[0];
  assign _14_[2:1] = count[2:1];
  assign _08_ = count[0];
  assign _14_[0] = _02_;
  assign _09_ = count[1];
  assign _10_ = count[2];
  assign q = _12_;
  assign _15_[1] = _03_;
  assign _15_[2] = _04_;
  assign _13_ = reset;
  assign _16_ = _05_;
  assign _17_ = _06_;
  assign _18_ = _07_;
endmodule
```
#### Run the following commands
```c
iverilog counter_opt.v tb_counter_opt.v
./a.out
gtkwave tb_counter_opt.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/8179df55-1e88-4ec4-803a-63a9d273433c)

### Day 4: GLS, blocking vs non-blocking and Synthesis-Simulation mismatch.
- Gate Level Simulation (GLS) is essential for verifying digital circuits by simulating the synthesized netlist to check logical accuracy and timing using a testbench. It ensures the synthesis process hasn't introduced errors and confirms the design meets performance requirements.
- Sensitivity lists play a critical role in proper circuit behavior. Missing entries in a sensitivity list can lead to unintended latches. Additionally, blocking and non-blocking assignments in always blocks behave differently, and improper use of blocking assignments can create latches, causing discrepancies between synthesis and simulation. Careful review of sensitivity lists and assignment usage is necessary to avoid these issues.

![image](https://github.com/user-attachments/assets/3bc1f7fe-7306-4004-87f5-31750f670947)

Example 1:
#### Verilog code:
```c
module ternary_operator_mux (input i0 , input i1 , input sel , output y);
assign y = sel?i1:i0;
endmodule
```
#### Run the following commands
```c
iverilog ternary_operator_mux.v tb_ternary_operator_mux.v
./a.out
gtkwave tb_ternary_operator_mux.vcd
```
#### GTK Wave
![image](https://github.com/user-attachments/assets/cd348084-6e96-4249-ad17-a4d430dcb517)

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog ternary_operator_mux.v
synth -top ternary_operator_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr ternary_operator_mux_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/7e75e0c4-90f0-4e0d-a618-fa0ed559985a)


#### Schematics
![image](https://github.com/user-attachments/assets/65924ac7-2d21-426f-b62a-820122c1a867)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module ternary_operator_mux(i0, i1, sel, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  input i0;
  wire i0;
  input i1;
  wire i1;
  input sel;
  wire sel;
  output y;
  wire y;
  sky130_fd_sc_hd__mux2_1 _4_ (
    .A0(_0_),
    .A1(_1_),
    .S(_2_),
    .X(_3_)
  );
  assign _0_ = i0;
  assign _1_ = i1;
  assign _2_ = sel;
  assign y = _3_;
endmodule
```
#### Gate Level Simulation
#### Run the following commands
```c
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v ternary_operator_mux_net.v tb_ternary_operator_mux.v
./a.out
gtkwave tb_ternary_operator_mux.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/16c82b7b-6947-42fa-b135-6c039ff313eb)


Example 2:
#### Verilog code:
```c
module bad_mux (input i0, input i1, input sel, output reg y);
always @(sel)
begin
    if (sel)
        y <= i1;
    else
        y <= i0;
end
endmodule
```
#### Run the following commands
```c
iverilog bad_mux.v tb_bad_mux.v
./a.out
gtkwave tb_bad_mux.vcd
```
#### GTK Wave
![image](https://github.com/user-attachments/assets/5aec6e3c-5665-4ebe-881d-0e96d7215cdf)

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog bad_mux.v
synth -top bad_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr bad_mux_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/0e50b47b-33cf-4ff8-bb97-0fb46c1ffc14)



#### Schematics
![image](https://github.com/user-attachments/assets/d358634b-8be3-475e-8c47-5494347d9185)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module bad_mux(i0, i1, sel, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  input i0;
  wire i0;
  input i1;
  wire i1;
  input sel;
  wire sel;
  output y;
  wire y;
  sky130_fd_sc_hd__mux2_1 _4_ (
    .A0(_0_),
    .A1(_1_),
    .S(_2_),
    .X(_3_)
  );
  assign _0_ = i0;
  assign _1_ = i1;
  assign _2_ = sel;
  assign y = _3_;
endmodule
```
#### Gate Level Simulation
#### Run the following commands
```c
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v bad_mux_net.v tb_bad_mux.v
./a.out
gtkwave tb_bad_mux.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/5181b16b-c31b-497e-830b-4a73ef1dc176)

#### Investigation of Synthesis-Simulation Mismatches for Blocking Assignments
#### Verilog code:
```c
module blocking_caveat (input a, input b, input c, output reg d); 
reg x;
always @ (*)
begin
    d = x & c;
    x = a | b;
end
endmodule
```
#### Run the following commands
```c
iverilog blocking_caveat.v tb_blocking_caveat.v
./a.out
gtkwave tb_blocking_caveat.vcd
```
#### GTK Wave
![image](https://github.com/user-attachments/assets/c1b99550-8363-4326-9b69-531d08d4b1c3)

#### Run the following commands
```c
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog blocking_caveat.v
synth -top blocking_caveat
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr blocking_caveat_net.v
```

#### Statistics
![image](https://github.com/user-attachments/assets/9dc640ad-be1f-4c28-9869-f535019ea8d3)


#### Schematics
![image](https://github.com/user-attachments/assets/ba9929ca-551f-4e9f-83a5-9267f8f72831)


#### Netlist Code
```c
/* Generated by Yosys 0.44+60 (git sha1 c25448f1d, g++ 11.4.0-1ubuntu1~22.04 -fPIC -O3) */

module blocking_caveat(a, b, c, d);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  output d;
  wire d;
  sky130_fd_sc_hd__o21a_1 _5_ (
    .A1(_2_),
    .A2(_1_),
    .B1(_3_),
    .X(_4_)
  );
  assign _2_ = b;
  assign _1_ = a;
  assign _3_ = c;
  assign d = _4_;
endmodule
```
#### Gate Level Simulation
#### Run the following commands
```c
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v blocking_caveat_net.v tb_blocking_caveat.v
./a.out
gtkwave tb_blocking_caveat.vcd
```

#### GTK Wave
![image](https://github.com/user-attachments/assets/1261da81-d41e-4fcb-9150-541bb43d8970)

## LAB - 10
### Synthesizing RISC-V and comparing output with functional (RTL) simulation.
### Functional Simulations
- Run the following commands
```c
cd BabySoC_Simulation
iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
./pre_synth_sim.out
gtkwave pre_synth_sim.vcd
```
![image](https://github.com/user-attachments/assets/e2869824-0c5a-479e-ac61-7b46e87320cb)

-Results

![6](https://github.com/user-attachments/assets/2f1323f1-a563-4109-8627-25fd4f77edad)


![7](https://github.com/user-attachments/assets/9ff870c6-8616-4823-a34c-0a3943987aeb)


### Synthesis
#### Steps
- Now go the following Directory:
```c
  cd /home/rohitmogli/VLSI/sky130RTLDesignAndSynthesisWorkshop/src/module
```
- Run the following commands
```c
yosys
read_liberty -lib /home/rohitmogli/ASIC/sky130RTLDesignAndSynthesisWorkshop/lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
![image](https://github.com/user-attachments/assets/eb8e7e4d-d415-414b-bc65-b81e135226a1)

```c
read_verilog clk_gate.v
```
![image](https://github.com/user-attachments/assets/f3ddff63-fe9a-4466-bee9-2acd824ab13a)

```c
read_verilog rvmyth.v
```

![image](https://github.com/user-attachments/assets/6e9ed836-e6d3-4119-a0b5-9d32c945fb48)

```c
synth -top rvmyth
```

![image](https://github.com/user-attachments/assets/c117f7f5-798d-446f-b13b-1f8a35eedc6c)

```c
abc -liberty /home/rohitmogli/ASIC/sky130RTLDesignAndSynthesisWorkshop/lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```

![image](https://github.com/user-attachments/assets/31b71116-b57c-4694-9faf-307e1552ef91)

```c
write_verilog -noattr rvmyth_netlist.v
exit
```
![image](https://github.com/user-attachments/assets/7d54d30c-591a-46ba-9813-e8fb42fcdf48)
- Netlist

![image](https://github.com/user-attachments/assets/a23026e4-959c-4c31-a587-42352618f192)

- Realisation

![image](https://github.com/user-attachments/assets/b3f3fe33-caf7-4bd7-8fa5-fb62b1f7b548)


![2](https://github.com/user-attachments/assets/902dc284-73b4-4993-8539-07649a1e519c)


![3](https://github.com/user-attachments/assets/9954fa5c-d8a3-4674-b5c1-53a4749af4ca)


![4](https://github.com/user-attachments/assets/7ce46e25-5232-461e-a6c7-552d1ff3e2bf)


```c
iverilog /home/rohitmogli/ASIC/sky130RTLDesignAndSynthesisWorkshop/my_lib/verilog_model/primitives.v /home/rohitmogli/ASIC/sky130RTLDesignAndSynthesisWorkshop/my_lib/verilog_model/sky130_fd_sc_hd.v rvmyth.v testbench.v vsdbabysoc.v avsddac.v avsdpll.v clk_gate.v
./a.out
gtkwave dump.vcd
```
![image](https://github.com/user-attachments/assets/6e21a078-aee8-43cc-95d5-d3736930ce87)

- Results
  
![image](https://github.com/user-attachments/assets/0f0059ea-ce8a-4c5c-9c1b-8f416214bf95)

![image](https://github.com/user-attachments/assets/bacd45b4-3bc6-4784-b3b6-de1c9cfd58da)

## LAB - 11
### STA Using Clock Time Of 11.3ns
#### The contents of VSDBabySoc/src/sdc/vsdbabysoc_synthesis.sdc
```c
set PERIOD 11.3

set_units -time ns

create_clock [get_pins {pll/CLK}] -name clk -period $PERIOD
set_clock_uncertainty -setup  [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_transition [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_uncertainty -hold [expr $PERIOD * 0.08] [get_clocks clk]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_CP]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_VCO]
set_input_transition [expr $PERIOD * 0.08] [get_ports REF]
set_input_transition [expr $PERIOD * 0.08] [get_ports VCO_IN]
set_input_transition [expr $PERIOD * 0.08] [get_ports VREFH]
```
#### Run the following commands
```c
cd VSDBabySoc/src
sta
read_liberty -min ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -min ./lib/avsdpll.lib
read_liberty -min ./lib/avsddac.lib
read_liberty -max ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -max ./lib/avsdpll.lib
read_liberty -max ./lib/avsddac.lib
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
report_checks -path_delay min_max -format full_clock_expanded -digits 4
```
![image](https://github.com/user-attachments/assets/a1c3bcd8-d33f-4d95-becb-4c3213a6b0f4)

#### Setup time
![image](https://github.com/user-attachments/assets/c5de677f-e5da-4b58-a152-1832c6220d26)

#### Hold time
![image](https://github.com/user-attachments/assets/28b39051-6c36-495d-8872-da1becc2a102)


## LAB - 12
### STA comparison for various sky libraries :
#### Organize all the sky library files into a folder named timing_libs. Next, navigate to the VSDBabySoC/src directory and create a Tcl script named sta_across_pvt.tcl with the following content:
```c
set list_of_lib_files(1) "sky130_fd_sc_hd__ff_100C_1v65.lib"
set list_of_lib_files(2) "sky130_fd_sc_hd__ff_100C_1v95.lib"
set list_of_lib_files(3) "sky130_fd_sc_hd__ff_n40C_1v56.lib"
set list_of_lib_files(4) "sky130_fd_sc_hd__ff_n40C_1v65.lib"
set list_of_lib_files(5) "sky130_fd_sc_hd__ff_n40C_1v76.lib"
set list_of_lib_files(6) "sky130_fd_sc_hd__ff_n40C_1v95.lib"
set list_of_lib_files(7) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part1"
set list_of_lib_files(8) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part2"
set list_of_lib_files(9) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part3"
set list_of_lib_files(10) "sky130_fd_sc_hd__ss_100C_1v40.lib"
set list_of_lib_files(11) "sky130_fd_sc_hd__ss_100C_1v60.lib"
set list_of_lib_files(12) "sky130_fd_sc_hd__ss_n40C_1v28.lib"
set list_of_lib_files(13) "sky130_fd_sc_hd__ss_n40C_1v35.lib"
set list_of_lib_files(14) "sky130_fd_sc_hd__ss_n40C_1v40.lib"
set list_of_lib_files(15) "sky130_fd_sc_hd__ss_n40C_1v44.lib"
set list_of_lib_files(16) "sky130_fd_sc_hd__ss_n40C_1v60.lib"
set list_of_lib_files(17) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part1"
set list_of_lib_files(18) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part2"
set list_of_lib_files(19) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part3"
set list_of_lib_files(20) "sky130_fd_sc_hd__ss_n40C_1v76.lib"
set list_of_lib_files(21) "sky130_fd_sc_hd__tt_025C_1v80.lib"
set list_of_lib_files(22) "sky130_fd_sc_hd__tt_100C_1v80.lib"

for {set i 1} {$i <= [array size list_of_lib_files]} {incr i} {
read_liberty ./timing_libs/$list_of_lib_files($i)
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
check_setup -verbose
report_checks -path_delay min_max -fields {nets cap slew input_pins fanout} -digits {4} > ./sta_output/min_max_$list_of_lib_files($i).txt

}
```

![image](https://github.com/user-attachments/assets/70b2ab31-1d3c-4ac1-b108-0c4f7d1067e4)

![image](https://github.com/user-attachments/assets/e5cb8379-d9e2-48eb-82c5-3c3dcdd4295c)

#### Run the following commands:
```c
cd VSDBabySoC/src
sta
source sta_across_pvt.tcl
```

![image](https://github.com/user-attachments/assets/bdd8b6d8-9747-47bd-aeb1-bf5e0241624b)

#### Table

![image](https://github.com/user-attachments/assets/1f7f55bb-09a5-4cfa-ab6a-3ea0c2daa92c)

#### Graphs
- Worst Setup Slack
![image](https://github.com/user-attachments/assets/55f7e65d-bb56-4df6-8069-d67471e9b312)

- Worst Hold Slack
![image](https://github.com/user-attachments/assets/3f6cc9a2-8e80-4d97-891a-c555e68ca417)

#### Timing Reports
##### sky130_fd_sc_hd__ff_100C_1v65.lib.txt
![image](https://github.com/user-attachments/assets/e5b00726-c94b-4c23-93b6-9b718935b77a)

![image](https://github.com/user-attachments/assets/7210da38-5534-4932-840b-9cf7f3df9e07)

##### sky130_fd_sc_hd__ff_100C_1v95.lib.txt
![image](https://github.com/user-attachments/assets/4e922ef4-21e1-4b1f-aad4-acb6f280c42e)

![image](https://github.com/user-attachments/assets/ff05631d-7839-4087-869f-e02a4a54a324)

##### sky130_fd_sc_hd__ff_n40C_1v56.lib.txt
![image](https://github.com/user-attachments/assets/5a2f066e-fb95-4e45-92ec-23a18efefc62)

![image](https://github.com/user-attachments/assets/f909a2f2-2556-475b-822e-b7573e2bf15c)

##### sky130_fd_sc_hd__ff_n40C_1v65.lib.txt
![image](https://github.com/user-attachments/assets/909b997e-b645-49cb-a5d4-61a6cca5e616)

![image](https://github.com/user-attachments/assets/b518f92e-58c9-4818-b50d-334100c7bcc6)

##### sky130_fd_sc_hd__ff_n40C_1v76.lib.txt
![image](https://github.com/user-attachments/assets/60477af2-d437-4050-9d5e-c223aadaf06e)

![image](https://github.com/user-attachments/assets/b652141f-24e9-473a-98aa-dfa24d9dd91e)

##### sky130_fd_sc_hd__ff_n40C_1v95.lib.txt
![image](https://github.com/user-attachments/assets/4015473f-1648-4956-932f-3f3e7456e9fb)

![image](https://github.com/user-attachments/assets/111abbc3-10e5-41a7-9ae0-53cbd2506b45)

##### sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part1.txt
![image](https://github.com/user-attachments/assets/b1a7c7ad-44e2-40ee-ae3c-61147efb874b)

![image](https://github.com/user-attachments/assets/f3a4870d-952d-4f5d-8308-b620dd45a91f)

##### sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part2.txt
![image](https://github.com/user-attachments/assets/60c6cb34-b923-49ac-99d6-93380881013a)

![image](https://github.com/user-attachments/assets/f3a4870d-952d-4f5d-8308-b620dd45a91f)

##### sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part3.txt
![image](https://github.com/user-attachments/assets/60c6cb34-b923-49ac-99d6-93380881013a)

![image](https://github.com/user-attachments/assets/f3a4870d-952d-4f5d-8308-b620dd45a91f)

##### sky130_fd_sc_hd__ss_100C_1v40.lib.txt
![image](https://github.com/user-attachments/assets/44d0e29d-d12c-4b02-8272-52bb42bd9158)

![image](https://github.com/user-attachments/assets/63351068-d10c-4ea5-96a5-4b934cd013b4)

##### sky130_fd_sc_hd__ss_100C_1v60.lib.txt
![image](https://github.com/user-attachments/assets/2ba0ca40-8e8e-4a7f-81b3-e5a73831c9e6)

![image](https://github.com/user-attachments/assets/9c585a11-4c67-4bed-8d64-52bf29a91ffb)

##### sky130_fd_sc_hd__ss_n40C_1v28.lib.txt
![image](https://github.com/user-attachments/assets/b4a779c7-363a-43e9-a465-71cb3a0361ce)

![image](https://github.com/user-attachments/assets/e8c9a8a8-6a92-4eac-9907-a28219dd2889)

##### sky130_fd_sc_hd__ss_n40C_1v35.lib.txt
![image](https://github.com/user-attachments/assets/b8c620fa-ad74-435b-8b36-03baa617ebe0)

![image](https://github.com/user-attachments/assets/caf7929c-a3a8-47b7-a11d-e447ff76acd2)

##### sky130_fd_sc_hd__ss_n40C_1v40.lib.txt
![image](https://github.com/user-attachments/assets/4be0575f-15bb-43c6-b783-cb677af690ef)

![image](https://github.com/user-attachments/assets/5fcf84d5-d1e8-4f17-a7a4-0449790bd352)

##### sky130_fd_sc_hd__ss_n40C_1v44.lib.txt
![image](https://github.com/user-attachments/assets/448d1db0-cfaa-4725-af9c-14595b734e36)

![image](https://github.com/user-attachments/assets/a80041f9-5526-4184-bb9c-8b9699cd0c5c)

##### sky130_fd_sc_hd__ss_n40C_1v60.lib.txt
![image](https://github.com/user-attachments/assets/9f18ad34-a727-4a61-8574-cd948c73dc70)

![image](https://github.com/user-attachments/assets/5376bac1-2f40-4e81-a49c-8f14d95e1b28)

##### sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part1.txt
![image](https://github.com/user-attachments/assets/4358aa5a-da38-41a5-80d1-6f8ae703b98c)

![image](https://github.com/user-attachments/assets/e7180655-dfcc-4496-8057-88266b233182)

##### sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part2.txt
![image](https://github.com/user-attachments/assets/39a0cd20-d439-4245-a032-1c0867c00544)

![image](https://github.com/user-attachments/assets/d5b3ccd6-9748-4330-b8dc-6f42a907f1d5)

##### sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part3.txt
![image](https://github.com/user-attachments/assets/39a0cd20-d439-4245-a032-1c0867c00544)

![image](https://github.com/user-attachments/assets/d5b3ccd6-9748-4330-b8dc-6f42a907f1d5)

##### sky130_fd_sc_hd__ss_n40C_1v76.lib.txt
![image](https://github.com/user-attachments/assets/a21d71e6-c1e0-4aea-a8de-9e655bfc5fe4)

![image](https://github.com/user-attachments/assets/4a79e643-3996-4953-958f-cfafb2b8a999)

##### sky130_fd_sc_hd__tt_025C_1v80.lib.txt
![image](https://github.com/user-attachments/assets/0dd7d6f1-6f86-4206-8f61-bfbdfc7b7d0b)

![image](https://github.com/user-attachments/assets/f8a0ed38-ab01-4446-8dfd-808927419874)

##### sky130_fd_sc_hd__tt_100C_1v80.lib.txt
![image](https://github.com/user-attachments/assets/e14b3c4d-0941-4426-b35d-6466bd0a9c75)

![image](https://github.com/user-attachments/assets/95970273-1ed8-4637-a989-3c7c3531d941)

## LAB - 12
### Advanced Physical Design using OpenLane using Sky130 :
### DAY-1
#### Inception of open-source EDA, OpenLane and Sky130 PDK

**QFN-48 Package**: The QFN-48 is a compact leadless package with 48 connection pads around its perimeter, providing excellent thermal and electrical performance, ideal for high-density applications.

![Screenshot from 2024-11-11 14-32-57](https://github.com/user-attachments/assets/3f1237c7-c6a6-453f-9655-636f8778eb9c)

**Chip**: An integrated circuit (IC) on a silicon substrate with various functional blocks like memory, processors, and I/O, designed for specific electronics applications.

![Screenshot from 2024-11-11 14-33-11](https://github.com/user-attachments/assets/32a46c31-bde4-46b7-807a-5f09e7a42a82)

**Pads**: Small metallic contact points on a chip or package, used to connect internal circuitry with external connections, enabling signal transfer.

**Core**: The main processing unit of a chip, containing functional logic optimized for power and performance.

**Die**: The section of a silicon wafer containing an individual IC before packaging, hosting all the active circuitry of the chip.

![Screenshot from 2024-11-11 14-33-23](https://github.com/user-attachments/assets/ff797bc6-ea8e-4bd9-be22-e3cf8ce4df95)

**IPs (Intellectual Properties)**: Pre-designed functional modules, such as USB controllers or memory interfaces, licensed for reuse in various designs to save development time and costs.

![Screenshot from 2024-11-11 14-33-32](https://github.com/user-attachments/assets/4e0b10e5-eea2-4b68-a42c-3db071423e38)

---

#### Software to Hardware Execution Flow

When running an application on hardware, it first enters the system software layer, which translates it to binary form. Key components here include the Operating System (OS), Compiler, and Assembler.

1. **OS**: Breaks down application functions written in high-level languages (e.g., C, Java) and passes them to a compiler.
2. **Compiler**: Translates functions into hardware-specific low-level instructions.
3. **Assembler**: Converts these instructions into binary code, which the hardware can execute.

![Screenshot from 2024-11-11 14-33-50](https://github.com/user-attachments/assets/0f07a5f9-9ce0-457e-a7af-1caffa64f809)

For instance, take a stopwatch app running on a RISC-V core. The OS generates a function in C, which is sent to the compiler. The compiler produces RISC-V-specific instructions adapted to the architecture. These instructions are then processed by the assembler, converting them to binary code. This binary code is then integrated into the chip layout, allowing the hardware to execute the intended functionality.

![Screenshot from 2024-11-11 14-34-04](https://github.com/user-attachments/assets/1d9b1e0e-1170-4709-98b9-3f2f71f28098)

For the above stopwatch the below figure shows the input and output of the compiler and assembler.

![Screenshot from 2024-11-11 14-34-16](https://github.com/user-attachments/assets/205f26fb-62b5-40d4-8bf2-ef96fc9ff711)

The compiler produces instructions specific to the architecture, and the assembler converts these into corresponding binary patterns. To execute them on hardware, an RTL (written in a Hardware Description Language) interprets and implements the instructions. This RTL design is then synthesized into a netlist, represented by interconnected logic gates. Finally, the netlist undergoes physical design implementation, preparing it for chip fabrication.

![Screenshot from 2024-11-11 14-34-28](https://github.com/user-attachments/assets/f4df4c33-62e9-4a78-9f14-98282aa9c2a2)

---

#### Components of ASIC Design

- **RTL IPs**: Verified circuit blocks (adders, flip-flops) in HDL, used to accelerate complex designs.
- **EDA Tools**: Automates ASIC tasks like synthesis, optimization, and timing analysis, ensuring performance meets requirements.
- **PDK Data**: Semiconductor foundry files defining the manufacturing process, ensuring ASIC designs are fabrication-ready.

![Screenshot from 2024-11-11 14-34-40](https://github.com/user-attachments/assets/610fc21f-8262-4d4b-b868-01a9d84b40ca)

---

#### Simplified RTL to GDSII Flow

![Screenshot from 2024-11-11 14-34-49](https://github.com/user-attachments/assets/9d8d2664-476d-4cd6-b5b3-7e0aed241a2f)

1. **RTL Design**: Describes circuit function using HDLs like Verilog or VHDL.
2. **RTL Synthesis**: Converts RTL to a gate-level netlist with optimized cells.
3. **Floor and Power Planning**: Lays out major components, power grid, and I/O.
4. **Placement**: Allocates cells to minimize wirelength and signal delay.
5. **Clock Tree Synthesis (CTS)**: Distributes clock signals uniformly to reduce skew.
6. **Routing**: Connects components while meeting design rules.
7. **Sign-off**: Final verification, confirming design readiness for fabrication.
8. **GDSII Generation**: Creates the layout for chip production.

---

#### OpenLane ASIC Flow Overview

![Screenshot from 2024-11-11 14-34-58](https://github.com/user-attachments/assets/414fbce3-7665-4375-9123-42a11f41ccec)

1. **RTL Synthesis and Technology Mapping**: Uses Yosys and ABC.
2. **Static Timing Analysis**: Uses OpenSTA.
3. **Floor Planning**: Utilizes init_fp, ioPlacer, pdn, tapcell.
4. **Placement**: Managed by RePLace, Resizer, OpenPhySyn, and OpenDP.
5. **Clock Tree Synthesis**: Uses TritonCTS.
6. **Fill Insertion**: Uses OpenDP.
7. **Routing**: Uses FastRoute/CU-GR (global) and TritonRoute/DR-CU (detailed).
8. **SPEF Extraction**: OpenRCX for parasitic data.
9. **GDSII Output**: Uses Magic and KLayout.
10. **Design Rule Checks**: Magic and KLayout.
11. **Layout vs. Schematic Check**: Uses Netgen.
12. **Antenna Checks**: Handled by Magic.

---
#### OpenLane Directory Structure

```
├── OpenLane             -> Main directory to invoke tools (run docker first)
│   ├── designs          -> Holds all design files for the flow
│   │   ├── picorv32a    -> Example design used in workshops or tutorials
│   │   ├── ...          -> Additional designs
├── pdks                 -> Stores PDK-related files, supporting open-source tools
│   ├── skywater-pdk     -> Contains the Skywater 130nm PDK
│   ├── open-pdks        -> Scripts to adapt commercial PDKs for open-source tools
│   ├── sky130A          -> Variant of PDK with open-source compatibility
│   │   ├── libs.ref     -> Node-specific files (e.g., timing libraries, cell LEF files)
│   │   ├── libs.tech    -> Tool-specific files for KLayout, Netgen, Magic, etc.
```

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
```
![image](https://github.com/user-attachments/assets/841409d6-3de4-4056-8fba-467edc380dcf)

```
cd designs/picorv32a/runs/13-11_15-22/results/synthesis/
gedit picorv32a.synthesis.v
```
![image](https://github.com/user-attachments/assets/139e6608-613c-42ca-b1e5-bfa8c4860b36)

![image](https://github.com/user-attachments/assets/e5c61c70-d807-4cd6-827b-03d1957921fb)

```
cd ../..
cd reports/synthesis
gedit 1-yosys_4.stat.rpt
```
![image](https://github.com/user-attachments/assets/bb04839e-3462-4b3d-81b1-8b1403f9eb33)

![image](https://github.com/user-attachments/assets/b206ccc7-84a8-495e-b89c-937f3130b3ae)

```

28. Printing statistics.

=== picorv32a ===

   Number of wires:              14596
   Number of wire bits:          14978
   Number of public wires:        1565
   Number of public wire bits:    1947
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:              14876
     sky130_fd_sc_hd__a2111o_2       1
     sky130_fd_sc_hd__a211o_2       35
     sky130_fd_sc_hd__a211oi_2      60
     sky130_fd_sc_hd__a21bo_2      149
     sky130_fd_sc_hd__a21boi_2       8
     sky130_fd_sc_hd__a21o_2        57
     sky130_fd_sc_hd__a21oi_2      244
     sky130_fd_sc_hd__a221o_2       86
     sky130_fd_sc_hd__a22o_2      1013
     sky130_fd_sc_hd__a2bb2o_2    1748
     sky130_fd_sc_hd__a2bb2oi_2     81
     sky130_fd_sc_hd__a311o_2        2
     sky130_fd_sc_hd__a31o_2        49
     sky130_fd_sc_hd__a31oi_2        7
     sky130_fd_sc_hd__a32o_2        46
     sky130_fd_sc_hd__a41o_2         1
     sky130_fd_sc_hd__and2_2       157
     sky130_fd_sc_hd__and3_2        58
     sky130_fd_sc_hd__and4_2       345
     sky130_fd_sc_hd__and4b_2        1
     sky130_fd_sc_hd__buf_1       1656
     sky130_fd_sc_hd__buf_2          8
     sky130_fd_sc_hd__conb_1        42
     sky130_fd_sc_hd__dfxtp_2     1613
     sky130_fd_sc_hd__inv_2       1615
     sky130_fd_sc_hd__mux2_1      1224
     sky130_fd_sc_hd__mux2_2         2
     sky130_fd_sc_hd__mux4_1       221
     sky130_fd_sc_hd__nand2_2       78
     sky130_fd_sc_hd__nor2_2       524
     sky130_fd_sc_hd__nor2b_2        1
     sky130_fd_sc_hd__nor3_2        42
     sky130_fd_sc_hd__nor4_2         1
     sky130_fd_sc_hd__o2111a_2       2
     sky130_fd_sc_hd__o211a_2       69
     sky130_fd_sc_hd__o211ai_2       6
     sky130_fd_sc_hd__o21a_2        54
     sky130_fd_sc_hd__o21ai_2      141
     sky130_fd_sc_hd__o21ba_2      209
     sky130_fd_sc_hd__o21bai_2       1
     sky130_fd_sc_hd__o221a_2      204
     sky130_fd_sc_hd__o221ai_2       7
     sky130_fd_sc_hd__o22a_2      1312
     sky130_fd_sc_hd__o22ai_2       59
     sky130_fd_sc_hd__o2bb2a_2     119
     sky130_fd_sc_hd__o2bb2ai_2     92
     sky130_fd_sc_hd__o311a_2        8
     sky130_fd_sc_hd__o31a_2        19
     sky130_fd_sc_hd__o31ai_2        1
     sky130_fd_sc_hd__o32a_2       109
     sky130_fd_sc_hd__o41a_2         2
     sky130_fd_sc_hd__or2_2       1088
     sky130_fd_sc_hd__or2b_2        25
     sky130_fd_sc_hd__or3_2         68
     sky130_fd_sc_hd__or3b_2         5
     sky130_fd_sc_hd__or4_2         93
     sky130_fd_sc_hd__or4b_2         6
     sky130_fd_sc_hd__or4bb_2        2

   Chip area for module '\picorv32a': 147712.918400

```

```
Flop ratio = Number of D Flip flops = 1613  = 0.1084
             ______________________   _____
             Total Number of cells    14876
```
### DAY-2
#### Good floorplan vs bad floorplan and introduction to library cells

#### Utilization Factor
The utilization factor is an essential metric that compares the area occupied by the circuit (netlist) to the total core area of the chip. A higher utilization means more of the chip's area is being used effectively, but over-utilization can cause issues with routing and space for other necessary components.

In ideal scenarios, we'd aim for a utilization factor of 1 (100%), but in reality, a range of **0.5 to 0.6** is preferred to account for buffer zones, routing channels, and the flexibility for adjustments.

##### Utilization Factor Formula:
$$
\text{Utilization Factor} = \frac{\text{Area Occupied by Netlist}}{\text{Total Core Area}}
$$

#### Aspect Ratio
The aspect ratio describes the shape of the chip, calculated as the height-to-width ratio. An **aspect ratio of 1** gives a square shape, while other values result in a rectangular layout. Factors like functionality, packaging, and manufacturing constraints determine the ideal aspect ratio.

##### Aspect Ratio Formula:
$$
\text{Aspect Ratio} = \frac{\text{Height}}{\text{Width}}
$$

#### Pre-Placed Cells
Pre-placed cells are essential functional blocks like memory units, custom processors, and analog circuits, manually positioned in fixed locations during the floorplanning stage. These blocks are critical to the chip's operation and cannot be moved during the placement and routing phases to ensure their functionality remains intact.

#### Decoupling Capacitors
- Purpose: These capacitors are placed near logic circuits to smooth out power supply fluctuations during high-speed switching.
- Benefits:
  - Minimize voltage fluctuations
  - Reduce electromagnetic interference (EMI)
  - Ensure reliable power delivery, especially to sensitive circuits

#### Power Planning
In a well-designed IC, power planning ensures that **VDD and VSS** are distributed evenly across the chip using a power mesh. The goal is to provide a stable power supply, minimize voltage drops, and optimize the overall power efficiency of the design. More power and ground points help reduce the likelihood of instability.

#### Pin Placement
The placement of I/O pins is crucial for the chip’s overall performance. A careful pin distribution minimizes signal integrity issues and heat buildup, which contributes to the chip’s stability and manufacturability.

---

### Floorplanning with OpenLANE

#### Set Up OpenLANE
First, navigate to the OpenLANE directory and initiate the interactive session:
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```

#### Run OpenLANE Flow
To prepare the design (`picorv32a`) and begin the floorplanning process, execute the following commands:
```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
```
![image](https://github.com/user-attachments/assets/e80d9a96-460a-4313-bcc0-0aba6aeb5eba)

![image](https://github.com/user-attachments/assets/ca1a2f85-5a4d-412b-97f6-dabaf6853819)

Then, in a new terminal, access the floorplan file as follows:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/floorplan
gedit picorv32a.floorplan.def
```
![image](https://github.com/user-attachments/assets/a068eee2-106a-47e4-af2c-1bb0061c5077)

According to the floorplan definitions:
- 1000 Unit Distance = 1 Micron
- Die width in unit distance = 660685−0 = 660685
- Die height in unit distance = 671405−0 = 671405
- Width in microns = 660685 / 1000 = 660.685 Microns
- Height in microns = 671405 / 1000 = 671.405 Microns
- Die area in microns² = 660.685 × 671.405 = 443587.212425 Microns²

#### View the floorplan in Magic:

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/floorplan/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.floorplan.def &
```

![image](https://github.com/user-attachments/assets/745e4104-67be-45a8-8e98-df32055d0fd8)


#### Decap and Tap Cells:
- Decap cells and tap cells are placed to manage power delivery and maintain electrical connectivity across the chip.

![image](https://github.com/user-attachments/assets/32e50637-dccb-4e8b-90c0-b39ce5a02fbf)

#### Unplaced Standard Cells at Origin

![image](https://github.com/user-attachments/assets/4ecd284b-438f-418a-bc84-8cc86f043f2c)

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
run_placement
```

![image](https://github.com/user-attachments/assets/693754d6-b32f-401f-a7d4-0f405f42bba4)

#### View the placement in Magic with:
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &
```
![image](https://github.com/user-attachments/assets/d7750375-76aa-4848-b354-a80b0080672e)

![image](https://github.com/user-attachments/assets/31d6150a-5c61-4346-aeda-971baf0ea096)

### Cell Design and Characterization Flow
#### Library Cells
- A library contains cells that define different functionalities, sizes, and thresholds. It is crucial for creating the building blocks of an IC.

#### Design Flow:
Inputs: PDKs, SPICE models, DRC, LVS, and user-defined specifications.
Steps:
- Circuit design
- Layout design
- Parasitic extraction
- Characterization (timing, noise, and power)
Outputs:
CDL (Circuit Description Language), LEF, GDSII, SPICE netlist, and various characterization files like .lib for timing, noise, and power.

### Standard Cell Characterization Flow
#### Steps in Characterization:
- Load Models and Tech Files: These provide process-specific details.
- Extract Spice Netlist: Extract the circuit netlist for analysis.
- Characterization with GUNA: Using characterization software like GUNA, the following models are generated:
	* Timing Models
 	* Power Models
  	* Noise Models

### Timing Parameters
| Timing Parameter         | Value         |
|------------------------------|--------------------|
| Slew Low Rise Threshold  | 20%                |
| Slew High Rise Threshold  | 80%                |
| Slew Low Fall Threshold   | 20%                |
| Slew High Fall Threshold  | 80%                |
| Input Rise Threshold      | 50%                |
| Input Fall Threshold      | 50%                |
| Output Rise Threshold     | 50%                |
| Output Fall Threshold     | 50%                |

### Propagation Delay:
Propagation delay is the time it takes for an input signal to propagate and affect the output signal.

$$
\text{Rise Delay} = \text{time(out-fall-thr)} - \text{time(in-rise-thr)}
$$

### Transition Time:
Transition time is the time taken for a signal to change between logic levels. This is typically measured between 10% and 90% or 20% and 80% of the signal’s swing.

$$
\text{Fall Transition Time} = \text{time(slew-high-fall-thr)} - \text{time(slew-low-fall-thr)}
$$

$$
\text{Rise Transition Time} = \text{time(slew-high-rise-thr)} - \text{time(slew-low-rise-thr)}
$$

### DAY-3
#### Design library cell using Magic Layout and ngspice characterization

#### CMOS Inverter NGSPICE Simulations

#### SPICE Deck for a CMOS Inverter Simulation

1. **Netlist Creation**: Define a netlist for the CMOS inverter circuit, labeling nodes clearly (e.g., `input`, `output`, `ground`, and `supply`) for easier identification during SPICE simulation.

2. **Device Sizing**: Define the Width-to-Length (W/L) ratios for the PMOS and NMOS transistors. Typically, the PMOS width is 2x to 3x the NMOS width for balanced drive strength.

3. **Voltage Levels**: Set gate and supply voltages in multiples of the transistor length.

4. **Node Naming**: Assign names (e.g., `VDD`, `GND`, `IN`, `OUT`) to nodes around each component in the SPICE netlist for easier reference.

   <img width="953" alt="Screenshot 2024-11-12 at 11 23 10 PM" src="https://github.com/user-attachments/assets/cbd5664c-8342-4f0c-9cc9-1320c3d1ca68">


5. **Simulation Commands**: For transient analysis, use:
   ``` 
   source [filename].cir 
   run 
   setplot 
   dc1 
   plot out vs in 
   ```

   <img width="938" alt="Screenshot 2024-11-12 at 11 23 32 PM" src="https://github.com/user-attachments/assets/4339530d-407c-4be8-a2de-ecdac84d3523">

#### Simulation and Analysis

- **Switching Threshold (Vm)**: Vm is the input voltage at which the inverter output switches between logic levels. For equal PMOS/NMOS sizes, Vm is around VDD/2. Adjusting PMOS or NMOS sizes shifts Vm higher or lower.

- **SPICE Command for Threshold Calculation**:
   ``` 
   Vin in 0 2.5 
   .op 
   .dc Vin 0 2.5 0.05 
   ```

    <img width="950" alt="Screenshot 2024-11-12 at 11 23 49 PM" src="https://github.com/user-attachments/assets/09eb989c-2a66-4225-b15a-2ded2d9299ee">


- **Transient Analysis for Propagation Delay**: SPICE command for pulse input:
   ``` 
   Vin in 0 0 pulse 0 2.5 0 10p 10p 1n 2n 
   .op 
   .tran 10p 4n 
   ```

    <img width="884" alt="Screenshot 2024-11-12 at 11 28 02 PM" src="https://github.com/user-attachments/assets/4f45f9d0-43ab-494e-8e18-c775f27509ae">

#### Cloning the Custom Inverter Layout

1. Clone the inverter:
   ``` 
   cd Desktop/work/tools/openlane_working_dir/openlane 
   git clone https://github.com/nickson-jose/vsdstdcelldesign 
   cd vsdstdcelldesign 
   cp /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech . 
   magic -T sky130A.tech sky130_inv.mag & 
   ```
![image](https://github.com/user-attachments/assets/c36565c9-520a-4f81-83a5-921e84ba350c)
2. Inverter Layout and CMOS Fabrication Process
#### CMOS Fabrication Process (16-Mask Method)
The CMOS fabrication process is a series of precise, photolithographic and chemical steps to create integrated circuits on a silicon wafer. This process includes multiple layers and utilizes 16 photomasks to define and protect specific areas of the wafer at various stages. Each step in this process is carefully controlled to ensure that the resulting chips are reliable and functionally correct.

- Substrate Preparation: Start with a cleaned, polished silicon wafer as the base.
- N-Well Formation: Form N-well regions in the p-type substrate using ion implantation with phosphorus.
- P-Well Formation: Create P-well regions in n-type areas by implanting boron.
- Gate Oxide Deposition: Deposit a thin silicon dioxide layer as insulation between the gate and channel.
- Polysilicon Deposition: Apply a polysilicon layer to serve as the gate electrode.
- Polysilicon Masking and Etching: Mask and etch to shape polysilicon into gate structures.
- N-Well Masking and Implantation: Define and implant N-well areas with phosphorus.
- P-Well Masking and Implantation: Define and implant P-well areas with boron.
- Source/Drain Implantation: Form source/drain regions by implanting dopants (e.g., arsenic for NMOS, boron for PMOS).
- Gate Formation: Use a mask to define and etch the gate structure.
- Source/Drain Masking and Etching: Etch to expose source/drain areas for further processing.
- Contact/Via Formation: Etch holes to access source, drain, and gate regions for connections.
- Metal Deposition: Deposit metal (e.g., aluminum or copper) to form interconnections.
- Metal Masking and Etching: Mask and etch metal to create interconnect patterns.
- Passivation Layer Deposition: Apply a protective silicon dioxide or nitride layer over the wafer.
- Final Testing and Packaging: Test the wafer, separate functioning chips, and package for deployment.

#### Identification of Transistors in the Inverter
- In the Magic layout viewer, hover over the required transistor and press **S** to select it. In the Magic terminal, type **what** to get information about the component type.

#### NMOS Transistor:
![image](https://github.com/user-attachments/assets/fa61ca31-19ad-47f1-abe7-7e6c46f30777)

#### PMOS Transistor:
![image](https://github.com/user-attachments/assets/44554937-bda5-4638-b315-28de530ce517)

#### Output Node - Y: ss
![image](https://github.com/user-attachments/assets/035a63cd-9702-471a-9c89-b79af16eba9e)

3. SPICE Extraction in Magic
Run SPICE Extraction Commands: In Magic’s tkcon window:

```
extract all
ext2spice cthresh 0 rthresh 0
ext2spice
```
![image](https://github.com/user-attachments/assets/ba1ac73f-ac55-43f4-9cd3-0c12ef78fc41)

View SPICE File: The extracted SPICE file (sky130_inv.spice) contains transistor models and capacitances.

![image](https://github.com/user-attachments/assets/13bead44-f814-4bc4-b4e6-67f41c1d29b8)

4. Transient Response Analysis
It is 0.01 microns. This has to accordingly updated in the spice file.
```
* SPICE3 file created from sky130_inv.ext - technology: sky130A

.option scale=0.01u

.include ./libs/pshort.lib
.include ./libs/nshort.lib

// .subckt sky130_inv A Y VPWR VGND

M1000 Y A VGND VGND nshort_model.0 w=35 l=23
+  ad=1.44n pd=0.152m as=1.37n ps=0.148m
M1001 Y A VPWR VPWR pshort_model.0 w=37 l=23
+  ad=1.44n pd=0.152m as=1.52n ps=0.156m

VDD VPWR 0 3.3V
VSS VGND 0 0V
Va A VGND PULSE(0V 3.3V 0 0.1ns 0.1ns 2ns 4ns)

C0 VPWR Y 0.117f
C1 A Y 0.0754f
C2 A VPWR 0.0774f
C3 Y VGND 2f
C4 A VGND 0.45f
C5 VPWR VGND 0.781f
// .ends


.tran 1n 20n
.control
run
.endc
.end
```
Run the modified file in ngspice:

```
ngspice sky130_inv.spice
```
![image](https://github.com/user-attachments/assets/52764b2b-9128-4032-99b1-3945cb2a8ab0)

### Plot the Waveform:

```
plot y vs time a
```
![image](https://github.com/user-attachments/assets/7655e404-9876-4541-bf83-933eebef316e)

|Parameter           |Calculation
|------------------------------|--------------------|
| Rise Time  |  2.17897 ns - 2.12091 ns = 0.05776 ns    | 
| Fall Time  | 4.06296 ns - 4.02074 ns = 0.04222 ns               |
| Cell Rise Delay   |    2.20654 ns - 2.15001 ns = 0.05653 ns            |
| Cell Fall Delay  |     4.07532 ns - 4.05 ns = 0.02532 ns         |

5. DRC Rules in Magic
- Download DRC Tests:
```
cd ~
wget http://opencircuitdesign.com/open_pdks/archive/drc_tests.tgz
tar xfz drc_tests.tgz
cd drc_tests
gvim .magicrc
```
![image](https://github.com/user-attachments/assets/aff28136-82e9-4afc-9464-c6f7f8bbaaa4)

![image](https://github.com/user-attachments/assets/9249d5f9-fdf7-4de5-ab65-4874a9b84cfb)
- Here we can observe that there is a drc error. To fix this add the following commands to the sky130A.tech file.
```
spacing npres allpolynonres 480 touching_illegal \
	"poly.resistor spacing to allpolynonres < %d (poly.9)"

spacing xhrpoly,uhrpoly,xpc allpolynonres 480 touching_illegal \
	"xhrpoly/uhrpoly resistor spacing to allpolynonres < %d (poly.9)"
```
![image](https://github.com/user-attachments/assets/9e5ff832-5ffa-4370-bbc9-189ebad1fd47)

![image](https://github.com/user-attachments/assets/c08720b5-5442-4237-972e-960c4c425049)

- Load and Check:
```
tech load sky130A.tech
drc check
drc why
```
<img width="805" alt="Screenshot 2024-11-13 at 12 38 16 AM" src="https://github.com/user-attachments/assets/ddccab54-9579-42a6-80e2-a4b74dc21eea">

### DAY-4
#### Pre-layout timing analysis and importance of good clock tree

Commands to extract `tracks.info` file:

```
cd Desktop/work/tools/openlane_working_dir/openlane/vsdstdcelldesign
cd ../../pdks/sky130A/libs.tech/openlane/sky130_fd_sc_hd/
less tracks.info
```
![image](https://github.com/user-attachments/assets/fa517bc3-f794-404f-bc0c-0ba726451998)

Commands to set grid for tkcon window as tracks of locali layer use the following command

```
grid 0.46um 0.34um 0.23um 0.17um
```
![image](https://github.com/user-attachments/assets/3cd2f6d4-d450-49bd-ba31-5267a4395f26)

Now, save it by giving a custon mae

```
save sky130_rohinv.mag
```
![image](https://github.com/user-attachments/assets/d88694f2-1341-4fb6-bd95-7ade716c8bcd)

Now, open it by using the following commands:

```
magic -T sky130A.tech sky130_rohinv.mag &
```

![image](https://github.com/user-attachments/assets/d7829fd9-6b8d-4d08-ad87-1293c02e4f95)

Now, type the following command in tkcon window:

```
lef write
```

![image](https://github.com/user-attachments/assets/018f1492-844b-43ed-88ac-2d5318370150)

Modify config.tcl:

```
# Design
set ::env(DESIGN_NAME) "picorv32a"

set ::env(VERILOG_FILES) "./designs/picorv32a/src/picorv32a.v"
set ::env(SDC_FILE) "./designs/picorv32a/src/picorv32a.sdc"

set ::env(CLOCK_PERIOD) "5.000"
set ::env(CLOCK_PORT) "clk"

set ::env(CLOCK_NET) $::env(CLOCK_PORT)

set ::env(LIB_SYNTH) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"
set ::env(LIB_FASTEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib"
set ::env(LIB_SLOWEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib"
set ::env(LIB_TYPICAL) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"

set ::env(EXTRA_LEFS) [glob $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/src/*.lef]

set filename $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/$::env(PDK)_$::env(STD_CELL_LIBRARY)_config.tcl
if { [file exists $filename] == 1 } {
  source $filename
}
```

Now, run openlane flow synthesis:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
run_synthesis
```
![image](https://github.com/user-attachments/assets/8ae3ee05-fef2-420b-8daa-a13a75d7a21b)

![image](https://github.com/user-attachments/assets/85e158b2-c4a6-42ee-a9b1-2c71ef348c34)

![image](https://github.com/user-attachments/assets/701ff79a-84d4-44b5-831d-57b3d6ef4c1b)

**Delay Tables**

Delay plays a crucial role in cell timing, impacted by input transition and output load. Cells of the same type can have different delays depending on wire length due to resistance and capacitance variations. To manage this, "delay tables" are created, using 2D arrays with input slew and load capacitance for each buffer size as timing models. Algorithms compute buffer delays from these tables, interpolating where exact data isn’t available to estimate delays accurately, preserving signal integrity across varying load conditions.

![image](https://github.com/user-attachments/assets/095a59e1-158c-4870-88e3-b73cb3a3692c)

Fixing slack:

```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a -tag 13-11_08-51 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
echo $::env(SYNTH_STRATEGY)
set ::env(SYNTH_STRATEGY) "DELAY 3"
echo $::env(SYNTH_BUFFERING
echo $::env(SYNTH_SIZING)
set ::env(SYNTH_SIZING) 1
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```
![image](https://github.com/user-attachments/assets/a16a7739-b90d-415d-8f8c-d16cf2409fe2)

![image](https://github.com/user-attachments/assets/d060fcda-9060-48d5-a47f-5507f14ed03f)

Now, run floorplan

```
run_floorplan
```

![image](https://github.com/user-attachments/assets/cba8b810-8bfb-4983-8ffb-657d0ee5f297)

Since we are facing unexpected un-explainable error while using run_floorplan command, we can instead use the following set of commands available based on information from `Desktop/work/tools/openlane_working_dir/openlane/scripts/tcl_commands/floorplan.tcl` and also based on Floorplan Commands section in `Desktop/work/tools/openlane_working_dir/openlane/docs/source/OpenLANE_commands.md`

```
init_floorplan
place_io
tap_decap_or
```

Now, do placement

```
run_placement
```
![image](https://github.com/user-attachments/assets/b2c685fa-baf7-4afa-b42a-ea3281bcccb5)

![image](https://github.com/user-attachments/assets/9acfbc1f-c767-481e-956d-2dd8900b1922)

![image](https://github.com/user-attachments/assets/1f540ed3-b6d8-4e88-8a11-6085a4e21a32)

Now, open a new terminal and run the below commands to load placement def in magic

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &

```

Custom inverter inserted in placement def

Now, open a new terminal and run the below commands to load placement def in magic

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &

```

Custom inverter inserted in placement def

![image](https://github.com/user-attachments/assets/0a831743-7445-4673-bd61-204875075ded)

![image](https://github.com/user-attachments/assets/8a82b2d0-2d17-432c-a299-fd98917a4b6f)


**Timing analysis with ideal clocks using openSTA**

Pre-layout STA will include effects of clock buffers and net-delay due to RC parasitics (wire delay will be derived from PDK library wire model).

![image](https://github.com/user-attachments/assets/a74af227-70dd-4812-930d-b6e9e787a27f)

Since we are getting 0 wns after improved timing run, we will be doing the timing analysis on initial run of synthesis which has lots of violations and no parameters added to improve timing.

Commands to invoke the OpenLANE flow include new lef and perform synthesis:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9set
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
run_synthesis
```
Go, to `Desktop/work/tools/openlane_working_dir/openlane` and create a file `pre_sta.conf`. The contents of the file are:

```
set_cmd_units -time ns -capacitance pF -current mA -voltage V -resistance kOhm -distance um
read_liberty -max /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib
read_liberty -min /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib
read_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/synthesis/picorv32a.synthesis.v
link_design picorv32a
read_sdc /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/my_base.sdc
report_checks -path_delay min_max -fields {slew trans net cap input_pin}
report_tns
report_wns
```

Contents of `my_base.sdc`:

```
set ::env(CLOCK_PORT) clk
set ::env(CLOCK_PERIOD) 12.000
set ::env(SYNTH_DRIVING_CELL) sky130_fd_sc_hd__inv_8
set ::env(SYNTH_DRIVING_CELL_PIN) Y
set ::env(SYNTH_CAP_LOAD) 17.65
create_clock [get_ports $::env(CLOCK_PORT)]  -name $::env(CLOCK_PORT)  -period $::env(CLOCK_PERIOD)
set IO_PCT  0.2
set input_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
set output_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
puts "\[INFO\]: Setting output delay to: $output_delay_value"
puts "\[INFO\]: Setting input delay to: $input_delay_value"


set clk_indx [lsearch [all_inputs] [get_port $::env(CLOCK_PORT)]]
#set rst_indx [lsearch [all_inputs] [get_port resetn]]
set all_inputs_wo_clk [lreplace [all_inputs] $clk_indx $clk_indx]
#set all_inputs_wo_clk_rst [lreplace $all_inputs_wo_clk $rst_indx $rst_indx]
set all_inputs_wo_clk_rst $all_inputs_wo_clk


# correct resetn
set_input_delay $input_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] $all_inputs_wo_clk_rst
#set_input_delay 0.0 -clock [get_clocks $::env(CLOCK_PORT)] {resetn}
set_output_delay $output_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] [all_outputs]

# TODO set this as parameter
set_driving_cell -lib_cell $::env(SYNTH_DRIVING_CELL) -pin $::env(SYNTH_DRIVING_CELL_PIN) [all_inputs]
set cap_load [expr $::env(SYNTH_CAP_LOAD) / 1000.0]
puts "\[INFO\]: Setting load to: $cap_load"
set_load  $cap_load [all_outputs]

# correct resetn
set_input_delay $input_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] $all_inputs_wo_clk_rst
#set_input_delay 0.0 -clock [get_clocks $::env(CLOCK_PORT)] {resetn}
set_output_delay $output_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] [all_outputs]

# TODO set this as parameter
set_driving_cell -lib_cell $::env(SYNTH_DRIVING_CELL) -pin $::env(SYNTH_DRIVING_CELL_PIN) [all_inputs]
set cap_load [expr $::env(SYNTH_CAP_LOAD) / 1000.0]
puts "\[INFO\]: Setting load to: $cap_load"
set_load  $cap_load [all_outputs]
```

Commands to run STA:

```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```

![Screenshot from 2024-11-13 18-36-30](https://github.com/user-attachments/assets/f8c6ead2-098a-4922-bead-6c07a11ec03e)

![Screenshot from 2024-11-13 18-36-35](https://github.com/user-attachments/assets/5e5a72ee-60fd-4c71-afed-8abeec4d8f37)

We now try to optimise synthesis.

Go to new terminal and run the follwoing commands:

```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 13-11_15-36 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
set ::env(SYNTH_MAX_FANOUT) 4
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```

![image](https://github.com/user-attachments/assets/8d57a5eb-7671-4e79-9821-98880b38c846)

Commands to run STA:
```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```
![image](https://github.com/user-attachments/assets/4a8e225d-0873-4161-86be-d548a2304db2)

![image](https://github.com/user-attachments/assets/b89aa127-fec6-4f20-a269-db70873dd9f5)

![image](https://github.com/user-attachments/assets/f5efdf07-c1e0-45ab-a6d2-fdb7bac19fe7)

### Basic Timing ECO (Engineering Change Order)
In this ECO, a NOR gate with a drive strength of 2 was driving five fanouts, causing a timing issue. Adjustments were made to improve timing by replacing the cell:

```
report_net -connections _13111_
replace_cell _16171_ sky130_fd_sc_hd__nor3_2
report_checks -fields {net cap slew input_pins} -digits 4
```
![image](https://github.com/user-attachments/assets/f7514979-333b-4f9e-91cd-ab726086ee52)

### Clock Tree Synthesis (CTS) and Signal Integrity
CTS organizes the clock distribution network for optimal timing across the design. Techniques vary by design requirements:

- Balanced Tree CTS: Binary-like structure for minimal clock skew.
- H-Tree CTS: H-shaped structure, good for large designs.
- Star CTS: Centralized clock distribution, reducing skew.
- Global-Local CTS: Combines star and tree for scalable distribution.
- Mesh CTS: Uses a grid pattern, balancing simplicity and skew.
- Adaptive CTS: Adjusts dynamically, ideal for complex design

![image](https://github.com/user-attachments/assets/615cdb4f-b0ba-4e2d-8915-dcb8eaa26674)

Crosstalk and Clock Net Shielding

- Crosstalk: Signal interference due to electromagnetic coupling. Mitigated by optimized layout and shielding.
- Clock Net Shielding: Prevents glitches by isolating clock nets with shields tied to power or ground. Shielding reduces interference and maintains signal integrity.

### Inserting Updated Netlist in PnR Flow

Replace the synthesis netlist with the updated one, making a backup first:
```bash
	cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_21-09/results/synthesis/
	cp picorv32a.synthesis.v picorv32a.synthesis_old.v
	write_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-36/results/synthesis/picorv32a.synthesis.v
```
### Running CTS and Post-CTS Timing Analysis
```
 cd Desktop/work/tools/openlane_working_dir/openlane
 docker
 ./flow.tcl -interactive
 prep -design picorv32a -tag 13-11_21-09 -overwrite
 set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
 add_lefs -src $lefs
 set ::env(SYNTH_STRATEGY) "DELAY 3"
 set ::env(SYNTH_SIZING) 1
 run_synthesis
 init_floorplan
 place_io
 tap_decap_or
 run_placement
 run_cts
```

![image](https://github.com/user-attachments/assets/1106f18d-abcc-4216-9120-9c9d5ceec605)


![image](https://github.com/user-attachments/assets/082d1723-d2c2-4eb2-afb2-edb664adf338)

### Setup Real Clocks in STA

```
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/13-11_21-09/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/13-11_21-09/results/cts/picorv32a.cts.def
write_db pico_cts.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_21-09/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit
```
![image](https://github.com/user-attachments/assets/a16cf49c-06fb-4cd6-91bf-1c0f4806cffe)

![image](https://github.com/user-attachments/assets/aa59a816-6647-4c87-bced-ede861eaf6d7)

### Clock Buffer List Modification

```
 echo $::env(CTS_CLK_BUFFER_LIST)
 set ::env(CTS_CLK_BUFFER_LIST) [lreplace $::env(CTS_CLK_BUFFER_LIST) 0 0]
 echo $::env(CTS_CLK_BUFFER_LIST)
 echo $::env(CURRENT_DEF)
 set ::env(CURRENT_DEF) /openLANE_flow/designs/picorv32a/runs/13-11_21-09/results/placement/picorv32a.placement.def
 run_cts
 echo $::env(CTS_CLK_BUFFER_LIST)
 openroad
 read_lef /openLANE_flow/designs/picorv32a/runs/13-11_21-09/tmp/merged.lef
 read_def /openLANE_flow/designs/picorv32a/runs/13-11_21-09/results/cts/picorv32a.cts.def
 write_db pico_cts1.db
 read_db pico_cts.db
 read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_21-09/results/synthesis/picorv32a.synthesis_cts.v
 read_liberty $::env(LIB_SYNTH_COMPLETE)
 link_design picorv32a
 read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
 set_propagated_clock [all_clocks]
 report_checks -path_delay min_max -fields {slew transd net cap input_pins} -format full_clock_expanded -digits 4
 report_clock_skew -hold
 report_clock_skew -setup
 exit
 echo $::env(CTS_CLK_BUFFER_LIST)
 set ::env(CTS_CLK_BUFFER_LIST) [linsert $::env(CTS_CLK_BUFFER_LIST) 0 sky130_fd_sc_hd__clkbuf_1]
 echo $::env(CTS_CLK_BUFFER_LIST)
```

![image](https://github.com/user-attachments/assets/f8e5f570-7257-4d5f-bbe4-87a12a1a7dcf)

![image](https://github.com/user-attachments/assets/80528a36-d61d-4736-89d1-4ec6a2494845)

![image](https://github.com/user-attachments/assets/fa2d619d-8be8-4cf8-9a52-e7aafc160f37)

### DAY-5
#### Final steps for RTL2GDS using tritonRoute and openSTA

#### Perform generation of Power Distribution Network (PDN) and explore the PDN layout.
```

cd Desktop/work/tools/openlane_working_dir/openlane
docker

./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_STRATEGY) "DELAY 3"
set ::env(SYNTH_SIZING) 1
run_synthesis
init_floorplan
place_io
tap_decap_or
run_placement
run_cts
gen_pdn

```
![image](https://github.com/user-attachments/assets/58d4adc5-1a8a-4c04-927b-795bf4ce86a6)

![image](https://github.com/user-attachments/assets/0a5d1cba-4e67-467a-b779-97cd7330070e)

![image](https://github.com/user-attachments/assets/39f394c6-5cb4-476e-8b03-04e58e469c20)

![image](https://github.com/user-attachments/assets/c1ae2d86-25dc-49c8-b172-a2e13052fdcc)

![image](https://github.com/user-attachments/assets/0a816c54-bd79-4a11-8e1b-04bf00323479)

### Perfrom detailed routing using TritonRoute and explore the routed layout.
```
echo $::env(CURRENT_DEF)
echo $::env(ROUTING_STRATEGY)
run_routing
```
![image](https://github.com/user-attachments/assets/e2d883e8-cfb2-4a57-878e-852efb7368ac)

![image](https://github.com/user-attachments/assets/46172b7a-9575-4a38-9bf2-7a02a678a9dd)
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_22-20/results/routing/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.def &
```
![image](https://github.com/user-attachments/assets/bfb51adc-5b69-4e64-bc02-adc4e6d7082e)

![image](https://github.com/user-attachments/assets/0dfeef56-eeed-40c0-abb1-511ee55159ec)

![image](https://github.com/user-attachments/assets/60b6dbd4-3c8c-4bbb-8510-5c3671c19a88)

##### TritonRoute's Routing Features:

1. **Intra-layer Routing**: Within a single metal layer, routing is done in parallel.
2. **Inter-layer Routing**: Conducted sequentially across layers, ensuring alignment with LEF-defined directions (e.g., met1 horizontal, met2 vertical).
3. **Route Guides**: Global route guides provide an initial path outline, aiding TritonRoute in detailed routing with minimized conflicts and enhanced connectivity.
4. **Inter-guide Connectivity**: TritonRoute maintains signal flow across adjacent guides, reducing gaps for improved design continuity.


![image](https://github.com/user-attachments/assets/19fcc3e8-3c51-4fb0-a56e-b5e677d0097f)

![image](https://github.com/user-attachments/assets/8e9f3c3d-d1bd-4b00-9292-7b45fa06c42c)

![image](https://github.com/user-attachments/assets/d939afa4-cc41-4f08-a15e-8f7b809b6adc)

![image](https://github.com/user-attachments/assets/a0b77e6a-6cf5-45de-9116-182cbe37a091)

![image](https://github.com/user-attachments/assets/45964f31-b0e5-4539-990f-09370dffe7ec)

##### Routing Topology Algorithms

Routing topology algorithms define connection paths between pins, optimizing for minimal path cost and connectivity efficiency.

![image](https://github.com/user-attachments/assets/15c75c7f-a8b6-47a0-9dd0-529f5af242c1)

---

#### SPEF Extraction for Parasitic Analysis

For Post-Route parasitic extraction using SPEF, navigate to the `spef_extractor` directory and run:

```bash
cd Desktop/work/tools/openlane_working_dir/openlane/scripts/spef_extractor
python3 main.py -l /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_22-20/tmp/merged.lef -d /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_22-20/results/routing/picorv32a.def
```

![image](https://github.com/user-attachments/assets/3a2b87d6-7c71-4ef6-9570-78e2b61c2422)


This extracts parasitics to aid in timing analysis.

---

#### Post-Route Timing Analysis with OpenSTA

To perform timing analysis on the routed design with extracted parasitics, use the following sequence in OpenSTA:

```bash
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/13-11_22-20/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/13-11_22-20/results/routing/picorv32a.def
write_db pico_route.db
read_db pico_route.db
read_verilog /openLANE_flow/designs/picorv32a/runs/13-11_22-20/results/synthesis/picorv32a.synthesis_preroute.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
read_spef /openLANE_flow/designs/picorv32a/runs/13-11_22-20/results/routing/picorv32a.spef
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit
```
![Untitled](https://github.com/user-attachments/assets/65ebae68-2ba2-40bb-b249-f2d0c759c8ea)

![image](https://github.com/user-attachments/assets/f298fa3c-f3a0-4c72-8bd5-1049e76e7c4c)

![image](https://github.com/user-attachments/assets/bcc7463e-9ab7-4fcd-89e2-de6608351181)

LAB-13
Installing and setting up ORFS
```
git clone --recursive https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts
cd OpenROAD-flow-scripts
sudo ./setup.sh
```
```
./build_openroad.sh --local
```
Verify Installation
```
source ./env.sh
yosys -help
openroad -help
cd flow
make
```
![image](https://github.com/user-attachments/assets/ddfb3cc4-8492-44bf-86c4-e83f3380487b)

![image](https://github.com/user-attachments/assets/1e61da98-8054-406a-be18-80cd13332ae4)

```
make gui_final
```

![image](https://github.com/user-attachments/assets/aa79fe5d-a0de-48b1-9a0b-a532e0751fcb)

ORFS Directory Structure and File formats

![image](https://github.com/user-attachments/assets/857e969a-0935-4c2c-9730-5393c4865a1a)

```
├── OpenROAD-flow-scripts             
│   ├── docker           -> It has Docker based installation, run scripts and all saved here
│   ├── docs             -> Documentation for OpenROAD or its flow scripts.  
│   ├── flow             -> Files related to run RTL to GDS flow  
|   ├── jenkins          -> It contains the regression test designed for each build update
│   ├── tools            -> It contains all the required tools to run RTL to GDS flow
│   ├── etc              -> Has the dependency installer script and other things
│   ├── setup_env.sh     -> Its the source file to source all our OpenROAD rules to run the RTL to GDS flow
```
Now, go to flow directory

![image](https://github.com/user-attachments/assets/ee70b00a-70d3-448b-882f-23bf2b31cc2c)

```
├── flow           
│   ├── design           -> It has built-in examples from RTL to GDS flow across different technology nodes
│   ├── makefile         -> The automated flow runs through makefile setup
│   ├── platform         -> It has different technology note libraries, lef files, GDS etc 
|   ├── tutorials        
│   ├── util            
│   ├── scripts             
```
Automated RTL2GDS Flow for VSDBabySoC:

Initial Steps:

We need to create a directory vsdbabysoc inside OpenROAD-flow-scripts/flow/designs/sky130hd
Now copy the folders gds, include, lef and lib from the VSDBabySoC folder in your system into this directory.
The gds folder would contain the files avsddac.gds and avsdpll.gds
The include folder would contain the files sandpiper.vh, sandpiper_gen.vh, sp_default.vh and sp_verilog.vh
The gds folder would contain the files avsddac.lef and avsdpll.lef
The lib folder would contain the files avsddac.lib and avsdpll.lib
Now copy the constraints file(vsdbabysoc_synthesis.sdc) from the VSDBabySoC folder in your system into this directory.
Now copy the files(macro.cfg and pin_order.cfg) from the VSDBabySoC folder in your system into this directory.
Now, create a macro.cfg file whose contents are shown below:

Now go to terminal and run the following commands:

```
cd OpenROAD-flow-scripts
source env.sh
cd flow
```

Commands for synthesis:

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk synth
```

![image](https://github.com/user-attachments/assets/14861458-31f3-4062-9486-01dc7d4ef288)

![image](https://github.com/user-attachments/assets/dd317914-081d-4003-bd0a-822e030e6bde)

Synthesis netlist:

![image](https://github.com/user-attachments/assets/b36c1310-81c3-44eb-bfea-2af973524727)

Synthesis log:

![image](https://github.com/user-attachments/assets/afee84cd-a688-411c-bee0-e790105a99a9)

Synthesis Check:

![image](https://github.com/user-attachments/assets/c4b2255b-2bfd-44dc-bf0a-21c26ec82785)

Synthesis Stats:

![image](https://github.com/user-attachments/assets/60ca54e7-f7b9-4b47-9207-711e92a81082)

![image](https://github.com/user-attachments/assets/1011900e-7786-4ffa-aa8d-ef97558a3fcc)

Commands for floorplan:
```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk floorplan
```

![image](https://github.com/user-attachments/assets/45b4e082-0122-487a-8bac-34944f69ce16)

![image](https://github.com/user-attachments/assets/dd9407ba-f4d2-4062-a1c8-66a3f870122e)

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk gui_floorplan
```

![image](https://github.com/user-attachments/assets/e34cebb8-dab4-4b07-8c33-1e32fd97e6d3)

![image](https://github.com/user-attachments/assets/34a8eea0-dfa1-409a-bc94-c9a3d53a112d)

![image](https://github.com/user-attachments/assets/1118fd92-f7b8-4c30-9ca2-47f20f2990c4)

Commands for Placement:
```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk place
```

![image](https://github.com/user-attachments/assets/516d6a28-919c-40b4-ba10-f094d3cfb557)

![image](https://github.com/user-attachments/assets/be35cf09-67e8-4fea-a413-095ebe53cee6)

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk gui_place
```
![image](https://github.com/user-attachments/assets/4b715d24-e002-469d-8b4d-6ffd1e7e7f27)

![image](https://github.com/user-attachments/assets/2e15ccdf-bb6b-46ef-91cc-5c95e188c7a7)

![image](https://github.com/user-attachments/assets/9abf38aa-6cbf-4e0a-88d9-05072739eeec)

![image](https://github.com/user-attachments/assets/d06e5634-6a21-416d-90d9-fad7f3740a69)

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk cts
```
![image](https://github.com/user-attachments/assets/a4442e3d-cc67-4178-a38e-4bd661ec2512)

![image](https://github.com/user-attachments/assets/0f1d306c-684d-4d5a-bd6d-0e154a90ce56)

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk gui_cts
```

![image](https://github.com/user-attachments/assets/74382b46-f85b-4b47-afc3-86a7290b7a2e)

![image](https://github.com/user-attachments/assets/f06ec2a7-5b71-4b59-86f9-155a6e365511)

![image](https://github.com/user-attachments/assets/2970c680-3116-4940-9427-749cc4076cf2)

Final CTS report:

```
==========================================================================
cts final report_tns
--------------------------------------------------------------------------
tns -0.43

==========================================================================
cts final report_wns
--------------------------------------------------------------------------
wns -0.05

==========================================================================
cts final report_worst_slack
--------------------------------------------------------------------------
worst slack -0.05

==========================================================================
cts final report_clock_skew
--------------------------------------------------------------------------
Clock core_clock
   0.07 source latency dpath.a_reg.out[15]$DFFE_PP/CK ^
  -0.07 target latency dpath.b_reg.out[9]$DFFE_PP/CK ^
   0.00 CRPR
--------------
   0.00 setup skew


==========================================================================
cts final report_checks -path_delay min
--------------------------------------------------------------------------
Startpoint: req_val (input port clocked by core_clock)
Endpoint: ctrl.state.out[0]$DFF_P
          (rising edge-triggered flip-flop clocked by core_clock)
Path Group: core_clock
Path Type: min

Fanout     Cap    Slew   Delay    Time   Description
-----------------------------------------------------------------------------
                          0.00    0.00   clock core_clock (rise edge)
                          0.00    0.00   clock network delay (propagated)
                          0.09    0.09 ^ input external delay
     1    1.37    0.00    0.00    0.09 ^ req_val (in)
                                         req_val (net)
                  0.00    0.00    0.09 ^ input33/A (BUF_X1)
     2    3.87    0.01    0.02    0.12 ^ input33/Z (BUF_X1)
                                         net33 (net)
                  0.01    0.00    0.12 ^ 521/B2 (OAI21_X1)
     1    1.40    0.01    0.02    0.13 v 521/ZN (OAI21_X1)
                                         000 (net)
                  0.01    0.00    0.13 v ctrl.state.out[0]$DFF_P/D (DFF_X1)
                                  0.13   data arrival time

                          0.00    0.00   clock core_clock (rise edge)
                          0.00    0.00   clock source latency
     1    5.05    0.00    0.00    0.00 ^ clk (in)
                                         clk (net)
                  0.00    0.00    0.00 ^ clkbuf_0_clk/A (CLKBUF_X3)
     4    9.70    0.01    0.03    0.03 ^ clkbuf_0_clk/Z (CLKBUF_X3)
                                         clknet_0_clk (net)
                  0.01    0.00    0.03 ^ clkbuf_2_0__f_clk/A (CLKBUF_X3)
    11   14.16    0.01    0.04    0.07 ^ clkbuf_2_0__f_clk/Z (CLKBUF_X3)
                                         clknet_2_0__leaf_clk (net)
                  0.01    0.00    0.07 ^ ctrl.state.out[0]$DFF_P/CK (DFF_X1)
                          0.00    0.07   clock reconvergence pessimism
                          0.00    0.08   library hold time
                                  0.08   data required time
-----------------------------------------------------------------------------
                                  0.08   data required time
                                 -0.13   data arrival time
-----------------------------------------------------------------------------
                                  0.06   slack (MET)



==========================================================================
cts final report_checks -path_delay max
--------------------------------------------------------------------------
Startpoint: dpath.a_reg.out[12]$DFFE_PP
            (rising edge-triggered flip-flop clocked by core_clock)
Endpoint: resp_msg[15] (output port clocked by core_clock)
Path Group: core_clock
Path Type: max

Fanout     Cap    Slew   Delay    Time   Description
-----------------------------------------------------------------------------
                          0.00    0.00   clock core_clock (rise edge)
                          0.00    0.00   clock source latency
     1    5.05    0.00    0.00    0.00 ^ clk (in)
                                         clk (net)
                  0.00    0.00    0.00 ^ clkbuf_0_clk/A (CLKBUF_X3)
     4    9.70    0.01    0.03    0.03 ^ clkbuf_0_clk/Z (CLKBUF_X3)
                                         clknet_0_clk (net)
                  0.01    0.00    0.03 ^ clkbuf_2_1__f_clk/A (CLKBUF_X3)
    12   14.87    0.01    0.04    0.07 ^ clkbuf_2_1__f_clk/Z (CLKBUF_X3)
                                         clknet_2_1__leaf_clk (net)
                  0.01    0.00    0.07 ^ dpath.a_reg.out[12]$DFFE_PP/CK (DFF_X1)
     3    8.06    0.02    0.10    0.18 ^ dpath.a_reg.out[12]$DFFE_PP/Q (DFF_X1)
                                         dpath.a_lt_b$in0[12] (net)
                  0.02    0.00    0.18 ^ 580/A (INV_X2)
     2    4.89    0.01    0.01    0.19 v 580/ZN (INV_X2)
                                         125 (net)
                  0.01    0.00    0.19 v 581/A1 (NOR2_X2)
     3   10.22    0.03    0.04    0.23 ^ 581/ZN (NOR2_X2)
                                         126 (net)
                  0.03    0.00    0.23 ^ 583/A2 (NOR2_X4)
     4    6.86    0.01    0.01    0.24 v 583/ZN (NOR2_X4)
                                         128 (net)
                  0.01    0.00    0.24 v 730/A (INV_X1)
     2    5.07    0.01    0.02    0.26 ^ 730/ZN (INV_X1)
                                         270 (net)
                  0.01    0.00    0.26 ^ 740/A1 (NOR2_X2)
     3    4.26    0.01    0.01    0.27 v 740/ZN (NOR2_X2)
                                         278 (net)
                  0.01    0.00    0.27 v 790/A1 (AND2_X1)
     2    2.54    0.01    0.03    0.30 v 790/ZN (AND2_X1)
                                         324 (net)
                  0.01    0.00    0.30 v 791/A1 (AND2_X1)
     1    1.65    0.01    0.03    0.33 v 791/ZN (AND2_X1)
                                         325 (net)
                  0.01    0.00    0.33 v 792/A2 (NAND2_X1)
     2    3.64    0.01    0.02    0.35 ^ 792/ZN (NAND2_X1)
                                         326 (net)
                  0.01    0.00    0.35 ^ 798/A1 (NAND2_X1)
     1    1.58    0.01    0.01    0.36 v 798/ZN (NAND2_X1)
                                         332 (net)
                  0.01    0.00    0.36 v 799/A1 (NAND2_X1)
     1    1.76    0.01    0.01    0.38 ^ 799/ZN (NAND2_X1)
                                         333 (net)
                  0.01    0.00    0.38 ^ 801/A1 (NAND2_X1)
     2    3.05    0.01    0.02    0.39 v 801/ZN (NAND2_X1)
                                         net43 (net)
                  0.01    0.00    0.39 v output43/A (BUF_X1)
     1    0.18    0.00    0.02    0.42 v output43/Z (BUF_X1)
                                         resp_msg[15] (net)
                  0.00    0.00    0.42 v resp_msg[15] (out)
                                  0.42   data arrival time

                          0.46    0.46   clock core_clock (rise edge)
                          0.00    0.46   clock network delay (propagated)
                          0.00    0.46   clock reconvergence pessimism
                         -0.09    0.37   output external delay
                                  0.37   data required time
-----------------------------------------------------------------------------
                                  0.37   data required time
                                 -0.42   data arrival time
-----------------------------------------------------------------------------
                                 -0.05   slack (VIOLATED)



==========================================================================
cts final report_checks -unconstrained
--------------------------------------------------------------------------
Startpoint: dpath.a_reg.out[12]$DFFE_PP
            (rising edge-triggered flip-flop clocked by core_clock)
Endpoint: resp_msg[15] (output port clocked by core_clock)
Path Group: core_clock
Path Type: max

Fanout     Cap    Slew   Delay    Time   Description
-----------------------------------------------------------------------------
                          0.00    0.00   clock core_clock (rise edge)
                          0.00    0.00   clock source latency
     1    5.05    0.00    0.00    0.00 ^ clk (in)
                                         clk (net)
                  0.00    0.00    0.00 ^ clkbuf_0_clk/A (CLKBUF_X3)
     4    9.70    0.01    0.03    0.03 ^ clkbuf_0_clk/Z (CLKBUF_X3)
                                         clknet_0_clk (net)
                  0.01    0.00    0.03 ^ clkbuf_2_1__f_clk/A (CLKBUF_X3)
    12   14.87    0.01    0.04    0.07 ^ clkbuf_2_1__f_clk/Z (CLKBUF_X3)
                                         clknet_2_1__leaf_clk (net)
                  0.01    0.00    0.07 ^ dpath.a_reg.out[12]$DFFE_PP/CK (DFF_X1)
     3    8.06    0.02    0.10    0.18 ^ dpath.a_reg.out[12]$DFFE_PP/Q (DFF_X1)
                                         dpath.a_lt_b$in0[12] (net)
                  0.02    0.00    0.18 ^ 580/A (INV_X2)
     2    4.89    0.01    0.01    0.19 v 580/ZN (INV_X2)
                                         125 (net)
                  0.01    0.00    0.19 v 581/A1 (NOR2_X2)
     3   10.22    0.03    0.04    0.23 ^ 581/ZN (NOR2_X2)
                                         126 (net)
                  0.03    0.00    0.23 ^ 583/A2 (NOR2_X4)
     4    6.86    0.01    0.01    0.24 v 583/ZN (NOR2_X4)
                                         128 (net)
                  0.01    0.00    0.24 v 730/A (INV_X1)
     2    5.07    0.01    0.02    0.26 ^ 730/ZN (INV_X1)
                                         270 (net)
                  0.01    0.00    0.26 ^ 740/A1 (NOR2_X2)
     3    4.26    0.01    0.01    0.27 v 740/ZN (NOR2_X2)
                                         278 (net)
                  0.01    0.00    0.27 v 790/A1 (AND2_X1)
     2    2.54    0.01    0.03    0.30 v 790/ZN (AND2_X1)
                                         324 (net)
                  0.01    0.00    0.30 v 791/A1 (AND2_X1)
     1    1.65    0.01    0.03    0.33 v 791/ZN (AND2_X1)
                                         325 (net)
                  0.01    0.00    0.33 v 792/A2 (NAND2_X1)
     2    3.64    0.01    0.02    0.35 ^ 792/ZN (NAND2_X1)
                                         326 (net)
                  0.01    0.00    0.35 ^ 798/A1 (NAND2_X1)
     1    1.58    0.01    0.01    0.36 v 798/ZN (NAND2_X1)
                                         332 (net)
                  0.01    0.00    0.36 v 799/A1 (NAND2_X1)
     1    1.76    0.01    0.01    0.38 ^ 799/ZN (NAND2_X1)
                                         333 (net)
                  0.01    0.00    0.38 ^ 801/A1 (NAND2_X1)
     2    3.05    0.01    0.02    0.39 v 801/ZN (NAND2_X1)
                                         net43 (net)
                  0.01    0.00    0.39 v output43/A (BUF_X1)
     1    0.18    0.00    0.02    0.42 v output43/Z (BUF_X1)
                                         resp_msg[15] (net)
                  0.00    0.00    0.42 v resp_msg[15] (out)
                                  0.42   data arrival time

                          0.46    0.46   clock core_clock (rise edge)
                          0.00    0.46   clock network delay (propagated)
                          0.00    0.46   clock reconvergence pessimism
                         -0.09    0.37   output external delay
                                  0.37   data required time
-----------------------------------------------------------------------------
                                  0.37   data required time
                                 -0.42   data arrival time
-----------------------------------------------------------------------------
                                 -0.05   slack (VIOLATED)



==========================================================================
cts final report_check_types -max_slew -max_cap -max_fanout -violators
--------------------------------------------------------------------------

==========================================================================
cts final max_slew_check_slack
--------------------------------------------------------------------------
0.15255571901798248

==========================================================================
cts final max_slew_check_limit
--------------------------------------------------------------------------
0.1985349953174591

==========================================================================
cts final max_slew_check_slack_limit
--------------------------------------------------------------------------
0.7684

==========================================================================
cts final max_fanout_check_slack
--------------------------------------------------------------------------
1.0000000150474662e+30

==========================================================================
cts final max_fanout_check_limit
--------------------------------------------------------------------------
1.0000000150474662e+30

==========================================================================
cts final max_capacitance_check_slack
--------------------------------------------------------------------------
16.691926956176758

==========================================================================
cts final max_capacitance_check_limit
--------------------------------------------------------------------------
20.904499053955078

==========================================================================
cts final max_capacitance_check_slack_limit
--------------------------------------------------------------------------
0.7985

==========================================================================
cts final max_slew_violation_count
--------------------------------------------------------------------------
max slew violation count 0

==========================================================================
cts final max_fanout_violation_count
--------------------------------------------------------------------------
max fanout violation count 0

==========================================================================
cts final max_cap_violation_count
--------------------------------------------------------------------------
max cap violation count 0

==========================================================================
cts final setup_violation_count
--------------------------------------------------------------------------
setup violation count 26

==========================================================================
cts final hold_violation_count
--------------------------------------------------------------------------
hold violation count 0

==========================================================================
cts final report_checks -path_delay max reg to reg
--------------------------------------------------------------------------
Startpoint: dpath.a_reg.out[7]$DFFE_PP
            (rising edge-triggered flip-flop clocked by core_clock)
Endpoint: dpath.a_reg.out[7]$DFFE_PP
          (rising edge-triggered flip-flop clocked by core_clock)
Path Group: core_clock
Path Type: max

  Delay    Time   Description
---------------------------------------------------------
   0.00    0.00   clock core_clock (rise edge)
   0.00    0.00   clock source latency
   0.00    0.00 ^ clk (in)
   0.03    0.03 ^ clkbuf_0_clk/Z (CLKBUF_X3)
   0.04    0.07 ^ clkbuf_2_3__f_clk/Z (CLKBUF_X3)
   0.00    0.07 ^ dpath.a_reg.out[7]$DFFE_PP/CK (DFF_X1)
   0.09    0.16 v dpath.a_reg.out[7]$DFFE_PP/Q (DFF_X1)
   0.02    0.19 v rebuffer16/Z (BUF_X2)
   0.02    0.21 v rebuffer15/Z (BUF_X1)
   0.02    0.23 v rebuffer14/Z (BUF_X1)
   0.02    0.25 v rebuffer13/Z (BUF_X1)
   0.02    0.28 v rebuffer12/Z (BUF_X1)
   0.02    0.30 v rebuffer11/Z (BUF_X1)
   0.02    0.32 v rebuffer10/Z (BUF_X1)
   0.02    0.35 v rebuffer9/Z (BUF_X2)
   0.02    0.37 v rebuffer8/Z (BUF_X2)
   0.02    0.39 v rebuffer7/Z (BUF_X2)
   0.02    0.41 v rebuffer6/Z (BUF_X2)
   0.02    0.43 v rebuffer5/Z (BUF_X2)
   0.02    0.46 v rebuffer4/Z (BUF_X2)
   0.03    0.48 v 860/ZN (AND2_X4)
   0.03    0.51 ^ 861/ZN (AOI21_X4)
   0.01    0.53 v 862/ZN (NAND2_X1)
   0.00    0.53 v dpath.a_reg.out[7]$DFFE_PP/D (DFF_X1)
           0.53   data arrival time

   0.46    0.46   clock core_clock (rise edge)
   0.00    0.46   clock source latency
   0.00    0.46 ^ clk (in)
   0.03    0.49 ^ clkbuf_0_clk/Z (CLKBUF_X3)
   0.04    0.53 ^ clkbuf_2_3__f_clk/Z (CLKBUF_X3)
   0.00    0.53 ^ dpath.a_reg.out[7]$DFFE_PP/CK (DFF_X1)
   0.00    0.53   clock reconvergence pessimism
  -0.03    0.50   library setup time
           0.50   data required time
---------------------------------------------------------
           0.50   data required time
          -0.53   data arrival time
---------------------------------------------------------
          -0.03   slack (VIOLATED)



==========================================================================
cts final report_checks -path_delay min reg to reg
--------------------------------------------------------------------------
Startpoint: ctrl.state.out[1]$DFF_P
            (rising edge-triggered flip-flop clocked by core_clock)
Endpoint: ctrl.state.out[1]$DFF_P
          (rising edge-triggered flip-flop clocked by core_clock)
Path Group: core_clock
Path Type: min

  Delay    Time   Description
---------------------------------------------------------
   0.00    0.00   clock core_clock (rise edge)
   0.00    0.00   clock source latency
   0.00    0.00 ^ clk (in)
   0.03    0.03 ^ clkbuf_0_clk/Z (CLKBUF_X3)
   0.04    0.07 ^ clkbuf_2_0__f_clk/Z (CLKBUF_X3)
   0.00    0.07 ^ ctrl.state.out[1]$DFF_P/CK (DFF_X1)
   0.09    0.16 v ctrl.state.out[1]$DFF_P/Q (DFF_X1)
   0.02    0.17 ^ 522/ZN (NAND2_X1)
   0.01    0.19 v 524/ZN (OAI21_X1)
   0.00    0.19 v ctrl.state.out[1]$DFF_P/D (DFF_X1)
           0.19   data arrival time

   0.00    0.00   clock core_clock (rise edge)
   0.00    0.00   clock source latency
   0.00    0.00 ^ clk (in)
   0.03    0.03 ^ clkbuf_0_clk/Z (CLKBUF_X3)
   0.04    0.07 ^ clkbuf_2_0__f_clk/Z (CLKBUF_X3)
   0.00    0.07 ^ ctrl.state.out[1]$DFF_P/CK (DFF_X1)
   0.00    0.07   clock reconvergence pessimism
   0.00    0.08   library hold time
           0.08   data required time
---------------------------------------------------------
           0.08   data required time
          -0.19   data arrival time
---------------------------------------------------------
           0.11   slack (MET)



==========================================================================
cts final critical path target clock latency max path
--------------------------------------------------------------------------
0.0718

==========================================================================
cts final critical path target clock latency min path
--------------------------------------------------------------------------
0.0717

==========================================================================
cts final critical path source clock latency min path
--------------------------------------------------------------------------
0.0000

==========================================================================
cts final critical path delay
--------------------------------------------------------------------------
0.4165

==========================================================================
cts final critical path slack
--------------------------------------------------------------------------
-0.0485

==========================================================================
cts final slack div critical path delay
--------------------------------------------------------------------------
-11.644658

==========================================================================
cts final report_power
--------------------------------------------------------------------------
Group                  Internal  Switching    Leakage      Total
                          Power      Power      Power      Power (Watts)
----------------------------------------------------------------
Sequential             4.81e-04   8.46e-05   2.80e-06   5.69e-04  19.3%
Combinational          1.01e-03   1.03e-03   1.81e-05   2.06e-03  69.8%
Clock                  1.43e-04   1.78e-04   2.50e-07   3.22e-04  10.9%
Macro                  0.00e+00   0.00e+00   0.00e+00   0.00e+00   0.0%
Pad                    0.00e+00   0.00e+00   0.00e+00   0.00e+00   0.0%
----------------------------------------------------------------
Total                  1.63e-03   1.30e-03   2.11e-05   2.95e-03 100.0%
                          55.3%      44.0%       0.7%
```

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk route
```

![image](https://github.com/user-attachments/assets/2a1ef3ee-8f9c-4a7c-af82-a6f89264723a)

![image](https://github.com/user-attachments/assets/16664dae-255e-4c75-9fce-5f7f435882b5)
