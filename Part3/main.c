// main.c : This file contains the 'main' function for the third webcast on the series. 
// In this webcast we'll discuss about pointers, functions, and loops

#include <stdio.h>
#include <Windows.h>

// #define PART3
#ifdef PART3

#define __cdecl CDECL // The standard call
#define COUNTOF_NAMES 4

DWORD
WINAPI
MyGetCurrentProcId(VOID);

FARPROC
WINAPI
MyGetProcAddress();

HANDLE
WINAPI
MyLoadLibraryA();

BOOL
WINAPI
MyEnumProcesses();

INT
CDECL
main(VOID)
{

// #define FIRST_PART
#ifdef FIRST_PART

    printf("[#] %s:%d This program was compiled on %s %s\n", __FUNCTION__, __LINE__, __DATE__, __TIME__);

    ULONG ulCourse = 670UL; // The "UL" postfix force the compiler to cast to unsigned long
    PULONG pCourse = &ulCourse;

    printf("[#] %s:%d the address of ulCourse is 0X%p\n", __FUNCTION__, __LINE__, pCourse);
    printf("[#] %s:%d after deref pCourse, the value is %lu\n", __FUNCTION__, __LINE__, *pCourse);

#endif // FIRST_PART

#define SECOND_PART
#ifdef SECOND_PART

    PCHAR AddressOfNames[COUNTOF_NAMES] = { "MyGetCurrentProcId",
                                            "MyGetProcAddress", 
                                            "MyLoadLibraryA", 
                                            "MyEnumProcesses"   };
    PVOID AddressOfFunctions[COUNTOF_NAMES] = { MyGetCurrentProcId,
                                                MyGetProcAddress,
                                                MyLoadLibraryA,
                                                MyEnumProcesses };
    ULONG AddressOfNameOrdinals[COUNTOF_NAMES] = { 0, 1, 2, 3 };

    for (ULONG i = 0UL; i < COUNTOF_NAMES; i++)
    {
        if (0 == strcmp("MyLoadLibraryA", AddressOfNames[i]))
        {
            printf("[+] %s:%d found the procedure ad index %lu\n", __FUNCTION__, __LINE__, i);
        }
    }

#endif // SECOND_PART

    return ERROR_SUCCESS;
}

DWORD
WINAPI
MyGetCurrentProcId(VOID)
{
    return ERROR_SUCCESS;
}

FARPROC
WINAPI
MyGetProcAddress()
{
    return NULL;
}

HANDLE
WINAPI
MyLoadLibraryA()
{
    return INVALID_HANDLE_VALUE;
}

BOOL
WINAPI
MyEnumProcesses()
{
    return TRUE;
}

#endif // PART3