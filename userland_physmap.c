#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

#define TZRAM_ADDR 0x10100000
#define SMRAM_ADDR 0xA0000
#define MAP_SIZE  0x1000  // Map one page (4 KiB)

int main(void) {
    int fd;
    void *map_base;
    volatile uint32_t *virt_addr;

    // Open /dev/mem with read-only access.
    fd = open("/dev/mem", O_RDONLY | O_SYNC);
    if (fd < 0) {
        perror("open /dev/mem failed");
        return EXIT_FAILURE;
    }

    // Map physical address into our process address space.
    map_base = mmap(NULL, MAP_SIZE, PROT_READ, MAP_SHARED, fd, TZRAM_ADDR);
    if (map_base == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return EXIT_FAILURE;
    }

    virt_addr = (volatile uint32_t *)map_base;

    // Read the value at the beginning of this memory region.
    uint32_t value = virt_addr[0];
    printf("Value at physical address 0x%08X: 0x%08X\n", TZRAM_ADDR, value);

    // Clean up.
    if (munmap(map_base, MAP_SIZE) == -1) {
        perror("munmap failed");
    }
    close(fd);
    
    return EXIT_SUCCESS;
}

