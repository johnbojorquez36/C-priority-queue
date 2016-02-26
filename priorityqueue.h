#ifndef __PQUEUE_H
#define __PQUEUE_H

typedef struct PriorityQueue {
  void **heap;
  int size;
  int max;
  int (*comparator)(const void*, const void*);
} PriorityQueue;

PriorityQueue* makePQ(int max, int (*comparator)(const void*, const void*));
void destroyPQ(PriorityQueue* pq);
void insert(PriorityQueue* pq, void* data);
void* removeMin(PriorityQueue* pq);

#endif
