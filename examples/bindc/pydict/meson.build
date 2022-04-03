project('pydict_bindc', 'c', 'fortran',
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

# Python Dictionary Representation
py3.extension_module('eucli',
           'vec.f90',
           'pydictderived.c',
           dependencies : py3_dep,
           install : true)
