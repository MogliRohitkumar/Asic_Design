# Asic_Design 
## LAB - 1
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
riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c
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












