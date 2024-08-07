# Asic_Design 
## LAB - 1
### Part-1(GCC compiler)
* Create .c file using leafpad text editor
#### Command
```c
leafpad sum1ton.c &
```
![Screenshot 2024-08-07 144016](https://github.com/user-attachments/assets/db98f086-c854-4483-ae81-d0d9d83d7fd3)


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
![Screenshot 2024-08-07 120950](https://github.com/user-attachments/assets/63d2f3a5-2cad-4c06-ad02-25d0e0a67fbb)
![Screenshot 2024-08-07 120940](https://github.com/user-attachments/assets/9382c43e-df1c-4620-9292-0af168b46677)
