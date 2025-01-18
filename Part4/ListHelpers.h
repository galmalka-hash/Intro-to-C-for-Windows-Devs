#pragma once

#include <Windows.h>

/// <summary>
/// The InitializeListHead routine initializes a LIST_ENTRY structure that represents the head of a doubly linked list
/// </summary>
/// <param name="ListHead">Pointer to a LIST_ENTRY structure that serves as the list header</param>
FORCEINLINE
VOID 
InitializeListHead(
	_Out_ PLIST_ENTRY ListHead
)
{
	ListHead->Flink = ListHead->Blink = ListHead;
	return;
}

/// <summary>
/// The IsListEmpty routine indicates whether a doubly linked list of LIST_ENTRY structures is empty
/// </summary>
/// <param name="ListHead">Pointer to a LIST_ENTRY structure that represents the head of the list</param>
/// <returns>IsListEmpty returns TRUE if there are currently no entries in the list and FALSE otherwise</returns>
_Must_inspect_result_
BOOLEAN
CFORCEINLINE
IsListEmpty(
	_In_ const LIST_ENTRY* ListHead
)
{
	return (BOOLEAN)(ListHead->Flink == ListHead);
}

/// <summary>
/// The InsertTailList routine inserts an entry at the tail of a doubly linked list of LIST_ENTRY structures
/// </summary>
/// <param name="ListHead">Pointer to the LIST_ENTRY structure that represents the head of the list</param>
/// <param name="Entry">Pointer to a LIST_ENTRY structure that represents the entry to be inserted in the list</param>
FORCEINLINE
VOID
InsertTailList(
	_Inout_ PLIST_ENTRY ListHead, // _Inout_ macro means parameter that read from, read and written to
	_Inout_ PLIST_ENTRY Entry
)
{
	PLIST_ENTRY Blink;

	Blink = ListHead->Blink;
	Entry->Flink = ListHead;
	Blink->Flink = Entry;
	ListHead->Blink = Entry;
	return;
}