project('pyclass_bindc', 'c', 'fortran',
        version : '0.1',
        default_options : ['warning_level=2',
                           'buildtype=debug',
                           'debug=true',
                          ])

py_mod = import('python')
py3 = py_mod.find_installation('python3')
py3_dep = py3.dependency()
message(py3.path())
message(py3.get_install_dir())

# # Python Class Representation
# py3.extension_module('point',
#            'matrix.f90',
#            'cwrappers.f90',
#            'pointcapsule.c',
#            dependencies : py3_dep,
#            install : true)

test_array = [#
  ['Pure fortran test', 'ftest',
   [ 'ftest.f90', 'matrix.f90' ]],
  ['Fortran ISO_C_BINDING test', 'ftest_cwrap',
   [ 'f_cwrapper_test.f90', 'matrix.f90', 'cwrappers.f90' ]],
]
foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
          sources : test.get(2),
                 ),
      )
endforeach

# executable('ctestf',
#            'testc.c',
#            'matrix.f90',
#            'cwrappers.f90',
#            install : true)
