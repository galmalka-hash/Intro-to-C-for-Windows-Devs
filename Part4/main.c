// Part4.cpp : This file contains the 'main' function for the fourth part.
//

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#include "ListHelpers.h"

#define PART4
#ifdef PART4

#define __cdecl CDECL

#define RTL_CONSTANT_STRINGA(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), (PSTR)s }
#define RTL_CONSTANT_STRINGW(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), (PWSTR)s }

#ifdef UNICODE
#define RTL_CONSTANT_STRING RTL_CONSTANT_STRINGW
#else
#define RTL_CONSTANT_STRING RTL_CONSTANT_STRINGA
#endif // UNICODE


typedef struct _UNICODE_STRING  // Struct tag convention is to start with underscore
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING ; // Struct name convention does not starts with underscore, and pointer type starts with 'P'

// #pragma pack (1) // Preprocess macro for padding struct with 1 byte (options are: 1, 2, 4, 8, 16)

typedef struct _STRING_EX
{
    USHORT Length;
    USHORT MaximumLength;
#ifdef UNICODE
    PWSTR Buffer;
#else
    PSTR Buffer;
#endif // UNICODE

} STRING_EX, * PSTRING_EX ;

typedef struct _PROCESS_INFO_EX
{
    DWORD ProcessId;
    LIST_ENTRY ProcessInfoLinks;
    UNICODE_STRING Name;
    HMODULE ImageBaseAddress;
    HANDLE CurrentThread;
} PROCESS_INFO_EX, * PPROCESS_INFO_EX ; 


/// <summary>
/// DumpStruct 
/// </summary>
/// <param name="ProcessName">pointer to STRING_EX object</param>
/// <returns>VOID</returns>
VOID
WINAPI
DumpStruct(
    _In_ PSTRING_EX ProcessName // _In_ is SAL macro that demends that the parameter passed to function wont be modified and wont be bull
);

INT
CDECL
main(VOID)
{
    DWORD dwStatus = ERROR_SUCCESS;

    STRING_EX Name; // Name members are uninitialized
    STRING_EX Name2 = { 0 }; // All name2 members are initialize to 0
    STRING_EX Name3; // Name3 members are uninitialized
    RtlSecureZeroMemory(&Name3, sizeof(STRING_EX)); // Set all members to 0

    PTSTR s = _T("Hello"); // TSTR set a string by the character set properties for the project at compile time

    STRING_EX Name4 = { .Buffer = s, .MaximumLength = sizeof(s), .Length = sizeof(s) - sizeof((s)[0]) }; // Initialize members by dot notation
    STRING_EX Name5 = { sizeof(s) - sizeof((s)[0]), sizeof(s),s }; // Initialize members by order of definition
    STRING_EX Name6 = RTL_CONSTANT_STRING( _T("hey hey hey") ); // Initialize using macro

    DumpStruct(&Name6);
    
    // DumpStruct(NULL); // Because we demanded the parameter to not be null after compiling this line should be annotated green

    BOOLEAN bIsEmpty = FALSE; // Empty list flag
    PLIST_ENTRY TempHeadList = NULL;
    PLIST_ENTRY Temp = NULL;
    PPROCESS_INFO_EX pProcInfo = NULL;

    TempHeadList = ( (PLIST_ENTRY) HeapAlloc( // Allocate using the windows api
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        sizeof(LIST_ENTRY))
        );
    
    if (!TempHeadList)
    {
        dwStatus = GetLastError();
        printf("Heap alloc failed with error: %lu \n", dwStatus);
        return dwStatus;
    }

    InitializeListHead(TempHeadList); // Set the list head using the helper function

    bIsEmpty = IsListEmpty(TempHeadList); // True only TempHeadList in the list

    pProcInfo = (PPROCESS_INFO_EX)HeapAlloc(
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        sizeof(PROCESS_INFO_EX)
    );

    if (!pProcInfo)
    {
        dwStatus = GetLastError();
        printf("HeapAlloc failed with error: %lu\n", dwStatus);
        return dwStatus;
    }

    UNICODE_STRING usProcName = RTL_CONSTANT_STRING( _T("explorer.exe") );

    pProcInfo->CurrentThread = GetCurrentThread();
    pProcInfo->Name = usProcName;

    InsertTailList(TempHeadList, &(pProcInfo->ProcessInfoLinks));

    bIsEmpty = IsListEmpty(&TempHeadList);

    return dwStatus;
}

#endif // PART4

_Use_decl_annotations_
VOID
WINAPI
DumpStruct(
    PSTRING_EX ProcessName
)
{
    printf("Name: %hZ \n", ProcessName); // hZ identifies the structure (string ex {length maxLength and buffer}) 
}