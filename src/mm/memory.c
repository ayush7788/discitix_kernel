#include "mm/memory.h"
#include "klibc/string.h"
#include "devices/terminal.h"

uint32_t memory_bytes = 0;

char *memory_type_names[6] = {"UNKOWN",
                            "MULTIBOOT_MEMORY_AVAILABLE",
                            "MULTIBOOT_MEMORY_RESERVED",
                            "MULTIBOOT_MEMORY_ACPI_RECLAIMABLE",
                            "MULTIBOOT_MEMORY_NVS",
                            "MULTIBOOT_MEMORY_BADRAM"};

void print_memory(multiboot_info_t* mbootptr){
    calculate_mem(mbootptr);
    info("Memory Map Loaded");
    kprintf("\tTotal RAM: %U MB\n", memory_bytes/1024/1024);
}

void calculate_mem(multiboot_info_t* mbootptr){
    multiboot_memory_map_t *entry = (multiboot_memory_map_t*)mbootptr->mmap_addr;
    uint32_t mem_limit = mbootptr->mmap_addr + mbootptr->mmap_length;
    while((uint32_t)entry < mem_limit){
        //kprintf("Memory map found: size: %U\n", entry->addr + entry->len);
        if(entry->type == MULTIBOOT_MEMORY_AVAILABLE)
            memory_bytes += (entry->addr + entry->len);
        entry = (multiboot_memory_map_t*)((uint32_t)entry + entry->size + sizeof(uint32_t));
    }
    //kprintf("\nMemory in bytes: %U\nMemory in KBs: %U\nMemory in MBs: %U", memory_bytes, memory_bytes/1024, memory_bytes/1024/1024);
}