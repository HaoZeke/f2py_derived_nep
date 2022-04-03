project('f2py_nep_samples', 'c',
  version : '0.1',
  default_options : ['warning_level=2'])

add_languages('fortran')

py_mod = import('python')
py3 = py_mod.find_installation('python3')
py3_dep = py3.dependency()
message(py3.path())
message(py3.get_install_dir())

# Dictionary For Point

py3.extension_module('eucli',
           'vec.f90',
           'pydictderived.c',
           dependencies : py3_dep,
           install : true)

executable('fortbase',
          'vec.f90',
          'main.f90')

executable('cfort',
          'vecf.c',
          'vec.f90')
