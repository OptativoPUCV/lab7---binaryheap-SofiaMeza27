#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq)
{
    if(pq -> size == 0)
    {
      return NULL;
    }
    return (void *) pq -> heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority)
{
   if(pq -> size == pq -> capac)
   {
      pq -> capac = pq -> capac * 2 + 1;
      pq -> heapArray = (heapElem*)realloc(pq -> heapArray, sizeof(heapElem) * pq -> capac);
   }

   pq -> heapArray[pq -> size].data = data;
   pq -> heapArray[pq -> size].priority = priority;
   pq -> size++;

   int i = pq -> size - 1;
   int parent = (i - 1) / 2;

   while(i > 0 && pq->heapArray[i].priority > pq->heapArray[parent].priority)
   {
      heapElem temp = pq -> heapArray[i];
      pq -> heapArray[i] = pq -> heapArray[parent];
      pq -> heapArray[parent] = temp;
      i = parent;
      parent = (i - 1) / 2;

   }
}


void heap_pop(Heap* pq)
{
  if(pq -> size == 0)
  {
    return;
  }

  pq -> heapArray[0] = pq -> heapArray[pq -> size - 1];
  pq -> size--;

  int i = 0;
  int left_child;
  int right_child;
  int larguest;

  while(1)
  {
    left_child = 2 * i + 1;
    right_child = 2 * i + 2;
    larguest = i;

    if(left_child < pq -> size && pq -> heapArray[left_child].priority > pq -> heapArray[larguest].priority)
    {
      larguest = left_child;
    }

    if(right_child < pq -> size && pq -> heapArray[right_child].priority > pq -> heapArray[larguest].priority)
    {
      larguest = right_child;
    }

    if(larguest != i)
    {
      heapElem temp = pq -> heapArray[i];
      pq -> heapArray[i] = pq -> heapArray[larguest];
      pq -> heapArray[larguest] = temp;
      i = larguest;
    }
    else 
    {
      break;
    }
  }
}

Heap* createHeap()
{
   Heap* nuevo = (Heap *)malloc(sizeof(Heap));
   nuevo -> size = 0;
   nuevo -> capac = 3;
   nuevo -> heapArray = (heapElem *)calloc(nuevo -> capac, sizeof(heapElem));

   return nuevo;
}
