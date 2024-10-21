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

## LAB - 8
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
