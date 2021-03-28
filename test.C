/*
int MemPoolCreate(uint64 size, Option *op, MemPool *mem_pool);
int MemPoolDestroy(MemPool *mem_pool);
int MemSegmentAlloc(MemPool *mem_pool, uint64 size, MemSegment *mem_seg);
int MemSegmentFree(MemSegment *mem_seg);
int MemSegmentWrite(MemSegment *mem_seg, char *data, uint64 size);
int MemSegmentWrite(MemSegment *mem_seg, char *data, uint64 size, uint64 offset);
int MemSegmentRead(MemSegment *mem_seg, char *data, uint64 size);
int MemSegmentRead(MemSegment *mem_seg, char *data, uint64 size, uint64 offset);
*/
#include<stdio.h>
#include <stdint.h>

#define _toid_struct 

struct PMEMoid{
    int pid;
    int off;
};

#define TOID(type)\
union _toid_##type##_toid

#define TOID_DECLARE(type, type_num)\
typedef uint8_t _toid_##type##_toid_id[(type_num)];\
TOID(type)\
{\
    PMEMoid oid;\
    type *_type;\
    _toid_##type##_toid_id *_id;\
}

struct car {
    int price;
};

TOID_DECLARE(struct car, 1);

car_toid_id a={1};

int main() {
    printf("a is %d\n", a[0]);
    return 0;
}

	