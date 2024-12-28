#include <stdio.h>
#include <stddef.h> // For offsetof

struct person
{
    char name[50];
    int age;
};

struct family
{
    struct person *fa;
    struct person *mo;
    int number_of_sons;
    int family_id;
} f;

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

int main(void)
{
    struct person father = {"John Doe", 45};
    struct person mother = {"Jane Doe", 43};

    // Fill and initialize `f`
    f.fa = &father;
    f.mo = &mother;
    f.number_of_sons = 2;
    f.family_id = 101;

    // Pointer to a member of the structure
    int *fam_id_ptr = &f.family_id;
    struct family *fam_ptr;

    // Retrieve the containing structure using `container_of`
    fam_ptr = container_of(fam_id_ptr, struct family, family_id);

    // Output the results
    printf("Address of the `family` structure: %p\n", (void *)&f);
    printf("Address retrieved using `container_of`: %p\n", (void *)fam_ptr);

    // Verify by accessing other members
    printf("Number of sons in the family: %d\n", fam_ptr->number_of_sons);
    printf("Father's name: %s\n", fam_ptr->fa->name);

    return 0;
}

