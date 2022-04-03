#include "vecf.h"

int main(int argc, char* argv[argc+1]) {
    puts("Making a struct");
    cartesian avec = {3.0, 1.0, 2.6};
    printf("%f %f %f", avec.x, avec.y, avec.z);
    unit_step(&avec);
    puts("After call, Fortran sent back");
    printf("%f %f %f", avec.x, avec.y, avec.z);
    return EXIT_SUCCESS;
}
