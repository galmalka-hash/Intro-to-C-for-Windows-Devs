/* main.c : This file contains the 'main' function of the second webcast in the series.
*  We see how different data types represented in memory, how they can cause undefined behaviors.
*  Learn how to manipulate bits to represent as flags, and about the concept of pointers */

#include <Windows.h>
#include <stdio.h>
#include <string.h>

// Some macros to check, set, and clear certain bit in data
#define FlagOn( Flags, TheFlag )    ( (Flags) & (TheFlag) )
#define SetFlag( Flags, TheFlag )    ( (Flags) |= (TheFlag) )
#define ClearFlag( Flags, TheFlag )    ( (Flags) &= ~(TheFlag) )

// Flags to check on integer numbers
#define SIXTEEN 0x10
#define ODD_NUMBER 0x1

// Flags for page and memory management on windows for demonstration
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40

#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000

#define ARRAY_SIZE 3

INT 
main(VOID)
{

    // #define FIRST_PART
#ifdef FIRST_PART

    INT min = -1; // Hex value of -1 in 32 bit integer is 0xFFFFFFFF
    UINT max = UINT_MAX; // Maximum value that stored in 32 bit integer is also 0xFFFFFFFF = 4,294,967,296

    UINT nextClass = 770; // 0x302

    printf("is min == max? %s\n", min == max ? "YES" : "NO"); // Answer is yes because (int) -1 = 0xFFFFFFFF = 0xFFFFFFFF = 4,294,967,296
    printf("is max > min? %s\n", max > min ? "YES" : "NO"); // Answer is no because 0xFFFFFFFF is not greater than 0xFFFFFFFF

    printf("is %d a multiple of 16? %s\n", nextClass, FlagOn(nextClass, SixTeen) ? "YES" : "NO"); // Answer is no because 0x10 bits is not set in 0x302
    printf("is %d odd number? %s\n", nextClass, FlagOn(nextClass, OddNumber) ? "YES" : "NO"); // Answer is no because 0x1 bit is not set in 0x302

    SetFlag(nextClass, OddNumber); // Set the least significant bit on, so now nextClass is 0x303

    printf("is %d odd number? %s\n", nextClass, FlagOn(nextClass, OddNumber) ? "YES" : "NO"); // Answer is yes because 0x1 bit is set in 0x303

    ClearFlag(nextClass, OddNumber); // Clear the least significant bit on, so now nextClass is 0x303

    printf("ClearFlag(nextClass, OddNumber) = %i (0x%08x)\n", nextClass, nextClass);

    ULONG memory = MEM_COMMIT | MEM_RESERVE; // Set both memory commit and memory reserve flags on

    printf("is memory being commited? %s \n", FlagOn(memory, MEM_COMMIT) ? "YES" : "NO"); // Answer is yes because memory commit flag is on

#endif // FIRST_PART

    // #define SECOND_PART
#ifdef SECOND_PART

    INT classes[ARRAY_SIZE] = { 670 }; // This initializes the array as [670, 0, 0]

    printf("index 0: %i, index 1: %i, index 2: %d \n", classes[0], classes[1], classes[2]);

    CHAR cmd[] = "cmd.exe"; // Initialize char array with null terminator ['c', 'm', 'd', '.', 'e', 'x', 'e', '\0']

    SIZE_T cmdLen = strlen(cmd); // The size of cmd (not including the null terminator)

    printf("strlen(cmd) -> %I64i\n", cmdLen); // Prints 7

    cmd[3] = '\0'; // This will change the way string functions treats the char array, so that they think it ends on the 3 char

    printf("The string is: %s\n", cmd); // Prints cmd

    cmdLen = strlen(cmd); // Size of cmd is now 3
    printf("strlen(cmd) -> %I64i\n", cmdLen);

    SIZE_T cmdLenSizeOf = sizeof(cmd); // The size of the data type of cmd, which in this case is char* and equals 8 (8 bytes is the size of a pointer)
    printf("sizeof(cmd) -> %I64i\n", cmdLenSizeOf);

    CHAR k32[] = "kernel32.dll";
    CHAR kBase[] = "kernelbase.dll";
    CHAR ntdll[] = "ntdll.dll";

    printf("is k32 == kbase? %s\n", strcmp(k32, kBase) ? "NO" : "YES"); // strcmp will return -1 as k32 is lexicographic smaller than kbase
    printf("is ntdll == kbase? %s\n", strcmp(ntdll, kBase) ? "NO" : "YES"); // strcmp will return 1 as ntdll is lexicographic smaller than kbase
    printf("is ntdll == ntdll? %s\n", strcmp(ntdll, ntdll) ? "NO" : "YES"); // strcmp will return 0 as ntdll is lexicographic equales kbase

    printf("atoi('23') -> %i\n", atoi("23")); // atoi will return an integer value represented in the string

    PCHAR addressOfNames[ARRAY_SIZE] = { "GetProcAddress", "LoadLibraryA", "LoadLibraryW" }; // Initialize char pointer array that points to 3 strings
    PVOID addressOfFunctions[ARRAY_SIZE] = { &addressOfNames[0], &addressOfNames[1], &addressOfNames[2]};

#endif // SECOND_PART

    return ERROR_SUCCESS;
}
