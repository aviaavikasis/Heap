/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Roi Ershko                              *
 * 1/08/2022                                         *
 * Description : imlementation of heap ADT           *
 *                                                   *
 *****************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <stdio.h>
#include "vector.h" /* vector functions */
#include "heap.h"   /* heap api */

#define HEAP_SIZE 100
#define WORD_SIZE sizeof(void*) 

struct heap
{
	vector_ty *vector;
	cmp_func cmp;
	void *params;
};


heap_ty *HeapCreate(cmp_func cmp, void *params)
{
	heap_ty *new_heap = NULL;
	assert(NULL != cmp);
	new_heap = (heap_ty*)malloc(sizeof(heap_ty));
	if(NULL == new_heap)
	{
		return NULL;
	}

	new_heap->vector = VectorCreate(HEAP_SIZE, WORD_SIZE);
	if(NULL == new_heap->vector)
	{
		free(new_heap);
		return NULL;
	}
	
	new_heap->cmp = cmp;
	new_heap->params = params;

	return new_heap;
}


void HeapDestroy(heap_ty *heap)
{
	assert(NULL != heap);
	
	VectorDestroy(heap->vector);
	heap->vector = NULL;
	free(heap);
	heap = NULL;
}


void *HeapPeek(const heap_ty *heap)
{
	assert(NULL != heap);
	return *(void**)VectorGetElement(heap->vector, 0);
}


size_t HeapSize(const heap_ty *heap)
{
	assert(NULL != heap);
	
	return VectorSize(heap->vector);
}


bool_ty HeapIsEmpty(const heap_ty *heap)
{
	assert(NULL != heap);
	
	return (0 == VectorIsEmpty(heap->vector)) ? TRUE : FALSE;
}


static int IsInOrder(vector_ty *vector,
					 size_t parent_index,
					  size_t child_index,
					 cmp_func cmp, void *params)
{	
	void **parent = NULL;
	void **child = NULL;
	assert(NULL != vector);
	assert(NULL != cmp);
	
	parent = VectorGetElement(vector, parent_index);
	child = VectorGetElement(vector, child_index);
	return (0 < cmp(child, parent, params));
}



static size_t GetParent(size_t index)
{
	return (index - 1) / 2;
}


static void HeapifyUp(heap_ty *heap)
{
	size_t index = 0;
	vector_ty *vector = NULL;
	assert(NULL != heap);
	vector = heap->vector;
	
	index = VectorSize(heap->vector) - 1;
	
	while(0 != index && 
	!IsInOrder(vector, GetParent(index), index, heap->cmp, heap->params))
	{
		UMSwap(VectorGetElement(vector, GetParent(index)),
		 VectorGetElement(vector, index), sizeof(void*));
		index = GetParent(index);
	}
}


status_ty HeapPush(heap_ty *heap, void *data)
{
	assert(NULL != heap);
	
	if(FAIL == VectorPushBack(heap->vector, &data))
	{
		return FAIL;
	}

	HeapifyUp(heap);
	return SUCCESS;
}


static void SwapElements(size_t index, void **right_child, vector_ty *vector)
{
	void **parent = NULL;
	
	assert(NULL != right_child);

	parent = VectorGetElement(vector, index);
	UMSwap(parent, right_child, sizeof(void*));
}

static int IndexIsBiggest(size_t index, vector_ty *vector, cmp_func cmp,
															    void *params)
{
	void **parent = NULL;
	void **left_child = NULL;
	void **right_child = NULL;
	
	assert(NULL != vector);
	
	parent = VectorGetElement(vector, index);
	if(index * 2 + 1 < VectorSize(vector))
	{
		left_child = VectorGetElement(vector, index * 2 + 1);	
	}
	
	if(index * 2 + 2 < VectorSize(vector))
	{
		right_child = VectorGetElement(vector, index * 2 + 2);	
	}
	
	if((NULL != right_child && 0 < cmp(parent, right_child, params))  ||
	 (NULL != left_child && 0 < cmp(parent, left_child, params)))
	 {
	 	return TRUE;
	 }
	 
	 return FALSE;

}


static void HeapifyDown(heap_ty *heap)
{	
	vector_ty *vector = NULL;
	size_t index = 0;
	void **right_child = NULL;
	void **left_child = NULL;
	
	assert(NULL != heap);
	
	vector = heap->vector;
	
	while(((2 * index + 1) <= VectorSize(vector) - 1) && 
				IndexIsBiggest(index, vector, heap->cmp, heap->params))
	{
		
		left_child = VectorGetElement(vector, 2 * index + 1);
		
		if((2 * index + 2) <= VectorSize(vector) - 1)
		{
			right_child = VectorGetElement(vector, 2 * index + 2);
			
			if(0 < heap->cmp(left_child, right_child, heap->params))
			{
				SwapElements(index, right_child, vector);
				index = 2 * index + 2; 
			}
			else
			{
				SwapElements(index, left_child, vector);
				index = 2 * index + 1;
			} 	
		}
		else
		{
			SwapElements(index, left_child, vector);
			index = 2 * index + 1; 
		}			
	}
}


static void SetData(vector_ty *vector, size_t index, void *element)
{
	assert(NULL != vector);
	memcpy(VectorGetElement(vector, index), element, sizeof(void*));
}


void HeapPop(heap_ty *heap)
{
	vector_ty *vector = NULL;
	void **last_element = NULL;
	
	assert(NULL != heap);
	
	vector = heap->vector;
	
	if(1 == VectorSize(vector))
	{
		VectorPopBack(vector);
		return;		
	}
	
	last_element = VectorGetElement(vector, VectorSize(vector) - 1);
	VectorPopBack(vector);
	
	SetData(vector, 0, last_element);
	
	HeapifyDown(heap);
}


static void SubHeapHeapifyDown(vector_ty *vector,
									 size_t index,
									 cmp_func cmp,
									  void *params)
{
	void **right_child = NULL;
	void **left_child = NULL;
	
	assert(NULL != vector);
	
	while((2 * index + 1) <= VectorSize(vector) - 1 &&
			 IndexIsBiggest(index, vector, cmp, params))
	{
		
		left_child = VectorGetElement(vector, 2 * index + 1);
		
		if((2 * index + 2) <= VectorSize(vector) - 1)
		{
			right_child = VectorGetElement(vector, 2 * index + 2);
			
			if(0 < cmp(left_child, right_child, params))
			{
				SwapElements(index, right_child, vector);
				index = 2 * index + 2; 
	
			}
			else
			{
				SwapElements(index, left_child, vector);
				index = 2 * index + 1;
			} 	
		}
		else
		{
			SwapElements(index, left_child, vector);
			index = 2 * index + 1;
		}	
		
	}	
}


static void SubHeapPop(vector_ty *vector, size_t index, cmp_func cmp, void *params)
{
	void **last_element = NULL;
	assert(NULL != vector);
	assert(NULL != cmp);
	
	last_element = VectorGetElement(vector, VectorSize(vector) - 1);
	UMSwap(VectorGetElement(vector, index), last_element, sizeof(void*));
	VectorPopBack(vector);

	SubHeapHeapifyDown(vector, index, cmp, params);

}

static size_t FindElement(vector_ty *vector, const void *data, is_match_func is_match)
{
	size_t i = 0;
	assert(NULL != vector);
	assert(NULL != is_match);
	
	for(; i < VectorSize(vector) ; ++i)
	{
		if(TRUE == is_match(VectorGetElement(vector, i), &data))
		{
			return i;
		}	
	}
	return -1;
}

void *HeapRemove(heap_ty *heap, const void *data, is_match_func is_match)
{
	size_t find_index = 0;
	assert(NULL != heap);
	assert(NULL != is_match);
	
	if(1 == VectorSize(heap->vector))
	{
		VectorPopBack(heap->vector);
		return (void*)data;
	}
	
	find_index = FindElement(heap->vector, data, is_match);
	if(-1 != (int)find_index)
	{
		SubHeapPop(heap->vector, (size_t)find_index, heap->cmp, heap->params);
		return (void*)data;
	}
	return NULL;	
}


void PrintHeap(heap_ty *heap)
{
    size_t i = 0;
    size_t size = HeapSize(heap);
    
    printf("HEAP |");
    
    for( ; i < size ; ++i)
    {
        printf("%d |", **(int **)VectorGetElement(heap->vector, i));
    }
    
    printf("\n");
}












































