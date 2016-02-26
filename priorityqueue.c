#include "priorityqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upHeap(PriorityQueue* pq, int i) {
  void* node = pq->heap[i];
  void* parent = pq->heap[i/2];
  
  if (i/2 != 0 && pq->comparator(node, parent) < 0) {
    pq->heap[i] = parent;
    pq->heap[i/2] = node;
    upHeap(pq, i/2);
  }
}

void downHeap(PriorityQueue* pq, int i) {
  void *node = NULL;
  void *leftChild = NULL;
  void *rightChild = NULL;
  int swapIndex;
  
  node = pq->heap[i];
  if (node) {
    if (i*2 <= pq->size) {
      leftChild = pq->heap[2*i];
    }

    if (i*2+1 <= pq->size) {
      rightChild = pq->heap[2*i+1];
    }

    if (leftChild && rightChild) {
      if (pq->comparator(node, leftChild) > 0 || pq->comparator(node, rightChild) > 0) {
	swapIndex = pq->comparator(leftChild, rightChild) < 0 ? i*2 : i*2+1;
	pq->heap[i] = pq->heap[swapIndex];
	pq->heap[swapIndex] = node;
	downHeap(pq, swapIndex);
      }
    } else if (leftChild && pq->comparator(node, leftChild) > 0) {
      pq->heap[i] = leftChild;
      pq->heap[i*2] = node;
      downHeap(pq, i*2);
    } else if (rightChild && pq->comparator(node, rightChild) > 0) {
      pq->heap[i] = rightChild;
      pq->heap[i*2+1] = node;
      downHeap(pq, i*2+1);
    }
  }
}

void insert(PriorityQueue* pq, void* data) {
  if (pq->size == pq->max) {
    pq->max = 2 * pq->max;
    void** new_heap = calloc(pq->max+1, sizeof(void*));
    memcpy(new_heap, pq->heap, (pq->size + 1) * sizeof(void*)); 
    free(pq->heap);
    pq->heap = new_heap;
  }
 
  pq->size++;

  pq->heap[pq->size] = data;
  upHeap(pq, pq->size);
  
}

void* removeMin(PriorityQueue* pq) {
  void* node;
  
  if (pq->size > 0) {
    node = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size];
    pq->heap[pq->size] = 0;
    pq->size--;
    downHeap(pq, 1);
  }

  return node;
  
}

void destroyPQ(PriorityQueue* pq) {
  int i = 1;
  for (i = 1; i <= pq->size; i++) {
    free(pq->heap[i]);
  }
  
  free(pq->heap);
  free(pq);
}

PriorityQueue* makePQ(int max, int (*comparator)(const void*, const void*)) {
  PriorityQueue* pq = malloc(sizeof *pq);
  pq->heap = calloc(max + 1, sizeof(void*));
  pq->size = 0;
  pq->max = max;
  pq->comparator = comparator;
  return pq;
}


