#ifndef __KERNEL_MEMORY_MENAGEMENT_H_
#define __KERNEL_MEMORY_MENAGEMENT_H_
#include <stdint.h>
#include <stddef.h>
#define MEM_BASE ((uint32_t) 0x10000)
#define BLOCK_LITTLE_SIZE (0x20)
#define BLOCK_MID_SIZE (0x800)
#define BLOCK_LARGE_SIZE (0x1000)

#define LITTLE_BEGIN (0)
#define LITTLE_END (0x1000)

#define MID_BEGIN (0x1000)
#define MID_END (0xC000)

#define LARGE_BEGIN (0xC000)
#define LARGE_END (0xF000)
//TODO: critical important here
// enter and leave is workaround!
// should be replaced by interupt implementation.
void init_mm();
uint32_t mm_get_block_nth(int32_t nth);
uint32_t mm_malloc(int32_t size);
uint32_t mm_get_HEAD();
void mm_free(uint32_t , int32_t);
#endif