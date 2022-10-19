/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Roi Ershko                              *
 * 1/08/2022                                         *
 * Description : imlementation of heap ADT           *
 *                                                   *
 *****************************************************/
#ifndef __ILRD_OL127_128_HEAP_H__
#define __ILRD_OL127_128_HEAP_H__

#include <stddef.h> /* size_t */
#include "utils.h"  /* utils */

typedef struct heap heap_ty;

/*
DESCRIPTION : create a new heap adt, this will be
min heap or max heap per the cmp function of user
PARAMETERS : copmpare function, params for compare 
function(void *)
RETURN : pointer to new heap
COMPLEXITY : time - O(1) , space - O(1) 
*/
heap_ty *HeapCreate(cmp_func cmp, void *params);

/*
DESCRIPTION : destroy exist heap
PARAMETERS : pointer to heap
RETURN : void
COMPLEXITY : time - O(1) , space - O(1) 
*/
void HeapDestroy(heap_ty *heap);

/*
DESCRIPTION : push new element to exist heap
PARAMETERS : pointer to heap, pointer to data
RETURN : SUCCESS or FAIL
COMPLEXITY : time - O(logn) , space - O(1) 
*/
status_ty HeapPush(heap_ty *heap, void *data);

/*
DESCRIPTION : remove the top element in heap
PARAMETERS : pointer to heap
RETURN : void
COMPLEXITY : time - O(logn) , space - O(1) 
*/
void HeapPop(heap_ty *heap);

/*
DESCRIPTION : return the top element in heap
PARAMETERS : pointer to heap
RETURN : void pointer
COMPLEXITY : time - O(1) , space - O(1) 
*/
void *HeapPeek(const heap_ty *heap);

/*
DESCRIPTION : remove specific element in heap
PARAMETERS : pointer to heap, pointer to data,
pointer to match function
RETURN : SUCCESS if the element found,
FAIL if not
COMPLEXITY : time - O(logn) , space - O(1) 
*/
void *HeapRemove(heap_ty *heap, const void *data, is_match_func is_match);

/*
DESCRIPTION : return num of elements in heap
PARAMETERS : pointer to heap, pointer to data,
pointer to match function
RETURN : SUCCESS if the element found,
FAIL if not
COMPLEXITY : time - O(1) , space - O(1) 
*/
size_t HeapSize(const heap_ty *heap);

/*
DESCRIPTION : check if heap is empty
PARAMETERS : pointer to heap
RETURN : TRUE or FALSE
COMPLEXITY : time - O(1) , space - O(1) 
*/
bool_ty HeapIsEmpty(const heap_ty *heap);

void PrintHeap(heap_ty *heap);

/*advanced*/
heap_ty *HeapHeapify(void *src_array, size_t array_size, cmp_func compare,
const void *params);

#endif /* __ILRD_OL127_128_HEAP_H__ */
