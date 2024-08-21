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





