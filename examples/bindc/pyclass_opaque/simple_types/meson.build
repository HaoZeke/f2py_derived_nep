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

# Python Class Representation
py3.extension_module('point',
           'point.f90',
           'cwrappers.f90',
           # 'point.c',
           'pointcapsule.c',
           dependencies : py3_dep,
           install : true)

executable('ftest',
           'ftest.f90',
           'point.f90',
           install : true)

executable('ftest_cwrap',
           'f_cwrapper_test.f90',
           'point.f90',
           'cwrappers.f90',
           install : true)

executable('ctestf',
           'testc.c',
           'point.f90',
           'cwrappers.f90',
           install : true)
