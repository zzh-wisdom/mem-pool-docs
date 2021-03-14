
int MemPoolCreate(uint64 size, Option *op, MemPool *mem_pool);
int MemPoolDestroy(MemPool *mem_pool);
int MemSegmentAlloc(MemPool *mem_pool, uint64 size, MemSegment *mem_seg);
int MemSegmentFree(MemSegment *mem_seg);
int MemSegmentWrite(MemSegment *mem_seg, char *data, uint64 size);
int MemSegmentWrite(MemSegment *mem_seg, char *data, uint64 size, uint64 offset);
int MemSegmentRead(MemSegment *mem_seg, char *data, uint64 size);
int MemSegmentRead(MemSegment *mem_seg, char *data, uint64 size, uint64 offset);


