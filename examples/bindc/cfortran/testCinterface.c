/* Testing Headers */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <float.h>
/* Program Headers */
#include "vecf.h"

/* A test case to call Fortran */
static void c_calls_fortran(void **state) {
    cartesian avec = {3.0, 1.0, 2.6};
    unit_step(&avec);
    assert_float_equal(avec.x, 4.0, DBL_EPSILON);
    assert_float_equal(avec.y, 2.0, DBL_EPSILON);
    assert_float_equal(avec.z, 3.6, DBL_EPSILON);
}
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(c_calls_fortran),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
