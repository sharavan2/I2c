#include <stdio.h>
#include <stddef.h> // For offsetof

struct sample
{
    int mem1;
    char mem2;
    int mem3;
};

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

int main(void)
{
    struct sample sample1;

    printf("Address of Structure sample1 (Normal Method) = %p\n", (void *)&sample1);
    printf("Address of Structure sample1 (container_of Method) = %p\n", (void*)container_of(&sample1.mem1, struct sample, mem1));
    printf("Address of Structure sample1 (container_of Method) = %p\n", (void*)container_of(&sample1.mem2, struct sample, mem2));
    printf("Address of Structure sample1 (container_of Method) = %p\n", (void*)container_of(&sample1.mem3, struct sample, mem3));

    return 0;
}

