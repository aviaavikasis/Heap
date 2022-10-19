#include <assert.h>
#include <stdio.h>
#include "heap.h"


void HeapCreateAndDestroyTest(void);
void HeapPushTest(void);
void HeapPopTest(void);
void HeapPeekTest(void);
void HeapRemoveTest(void);
void HeapSizeTest(void);
void HeapIsEmptyTest(void);
void RoiTest(void);

int CompareInts(const void *avl_data, const void *user_data, void *params);
bool_ty NumsIsEqual(const void *ds_data, const void *user_data);

int main(void)
{
/*
	HeapCreateAndDestroyTest();
	HeapPushTest();
	HeapSizeTest();
	HeapIsEmptyTest();
	HeapPopTest();
	HeapPeekTest();
	HeapRemoveTest();
*/
	RoiTest();
	
	printf("\n->->->->->-> success!! <-<-<-<-<-<-\n\n");	
	return 0;
}



void HeapCreateAndDestroyTest(void)
{
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	HeapDestroy(heap);
}

void HeapPushTest(void)
{
	int i = 0;
	int arr[12] = {5,2,9,8,1,6,7,4,3,10,15,0};
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	for( ; i < 12 ; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	PrintHeap(heap);
	
	HeapDestroy(heap);
}

void HeapSizeTest(void)
{
	int i = 0;
	int arr[10] = {5,2,9,8,1,6,7,4,3,10};
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	assert(0 == HeapSize(heap));
	
	for( ; i < 10 ; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	assert(10 == HeapSize(heap));
	
	HeapDestroy(heap);
}

void HeapIsEmptyTest(void)
{
	int i = 0;
	int arr[10] = {5,2,9,8,1,6,7,4,3,10};
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	assert(TRUE == HeapIsEmpty(heap));
	
	for( ; i < 10 ; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	assert(FALSE == HeapIsEmpty(heap));
	
	HeapDestroy(heap);
}


void HeapPopTest(void)
{
	int i = 0;
	int arr[10] = {5,2,9,8,1,6,7,4,3,10};
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	assert(TRUE == HeapIsEmpty(heap));
	
	for( ; i < 10 ; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	for(i = 0; i < 9 ; ++i)
	{
		HeapPop(heap);
	}
	/*
	printf("\n\n");
	PrintHeap(heap);
	*/	
	HeapPop(heap);
	/*PrintHeap(heap);*/
	
	HeapDestroy(heap);

}


void HeapPeekTest(void)
{
	int i = 0;
	int arr[10] = {5,2,9,8,1,6,7,4,3,10};
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	for( ; i < 10 ; ++i)
	{
		HeapPush(heap, arr + i);
	}
	assert(1 == *(int*)HeapPeek(heap));
	
	HeapDestroy(heap);

}


void HeapRemoveTest(void)
{
	is_match_func is_match = &NumsIsEqual;
	int i = 0;
	int arr1[10] = {5,2,9,8,1,6,7,4,3,10};
	int arr2[10] = {5,2,9,8,1,6,7,4,3,10};
	
	cmp_func cmp = &CompareInts;
	heap_ty *heap = HeapCreate(cmp, NULL);
	
	for( ; i < 10 ; ++i)
	{
		HeapPush(heap, arr1 + i);
	}
	/*PrintHeap(heap);*/
	
	/*printf("\n\n\n");*/	
	
	for(i = 9 ; i >= 0 ; --i)
	{
		HeapRemove(heap, arr2 + i, is_match);
		assert(i == (int)HeapSize(heap));	
		/*PrintHeap(heap);*/
		/*printf("\n");*/		
	}
	

	HeapDestroy(heap);

}


void RoiTest(void)
{

 	int num1 = 100;
 	int num2 = 19;
 	int num3 = 36;
 	int num4 = 17;
 	int num5 = 3;
 	int num6 = 25;
 	int num7 = 1;
 	int num8 = 2;
 	int num9 = 7;
	heap_ty *pt = HeapCreate(CompareInts, NULL);
 	
 	assert(0 == HeapSize(pt));
 	assert(1 == HeapIsEmpty(pt));
 	
 	HeapPush(pt, &num1);
 	HeapPush(pt, &num2);
 	HeapPush(pt, &num3);
 	HeapPush(pt, &num4);
 	HeapPush(pt, &num5);
 	HeapPush(pt, &num6);
 	HeapPush(pt, &num7);
 	HeapPush(pt, &num8);
 	HeapPush(pt, &num9);
 	
 	assert(9 == HeapSize(pt));
 	assert(0 == HeapIsEmpty(pt));
 	assert(1 == *(int *)HeapPeek(pt));
	
 	PrintHeap(pt);
 	
 	HeapPop(pt);
 	PrintHeap(pt);
 	assert(8 == HeapSize(pt));
 	assert(0 == HeapIsEmpty(pt));
 	assert(2 == *(int *)HeapPeek(pt));
 	
 	PrintHeap(pt);
 	
 	assert(&num3 == HeapRemove(pt, &num3, NumsIsEqual));
 	assert(7 == HeapSize(pt));
 	assert(0 == HeapIsEmpty(pt));
 	PrintHeap(pt);
 	
 	HeapDestroy(pt);
 	
}




int CompareInts(const void *data1, const void *data2, void *params)
{	

	int *data1_address = NULL;
	int *data2_address = NULL;
	
	(void)params;
	
	assert(NULL != data1);
	assert(NULL != data2);

	data1_address = (void*)data1;
	data2_address = (void*)data2;
	
	assert(NULL != data1);
	assert(NULL != data2);
	return (**(int**)data1_address - **(int**)data2_address);
}


bool_ty NumsIsEqual(const void *ds_data, const void *user_data)
{
	assert(NULL != ds_data);
	assert(NULL != user_data);
	
	return !(**(int**)ds_data == **(int**)user_data);

}














