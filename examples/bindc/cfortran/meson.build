project('cfortran_bindc', 'fortran', 'c',
        version : '0.1',
        default_options : ['warning_level=2',
                           'buildtype=debug',
                           'debug=true',
                          ])

# Library target
libcfderived = library('libcfderived',
                       sources : ['vec.f90',
                                 'vecf.h'])

# Pure Fortran usage
executable('fortbase',
           'main.f90',
           link_with : libcfderived,
          )

# Usage from C
executable('cfort',
           'main.c',
           link_with : libcfderived,
          )

# Tests
tc = executable('tc',
                 'testCinterface.c',
                 dependencies : dependency('cmocka'),
                 link_with : libcfderived,
                )
test('Test C calling Fortran', tc)
