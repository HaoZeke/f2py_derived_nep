#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#endif /* PY_SSIZE_T_CLEAN */

#include "Python.h"

// Fortran-C stuff
#include "vecf.h"

// Python-C stuff

static PyObject* eucli_unitinc(PyObject* self, PyObject* args) {
    cartesian a;
    PyObject* dict;
    PyArg_ParseTuple(args, "O", &dict);
    PyObject* vals = PyDict_Values(dict);
    a.x = PyFloat_AsDouble(PyList_GetItem(vals,0));
    a.y = PyFloat_AsDouble(PyList_GetItem(vals,1));
    a.z = PyFloat_AsDouble(PyList_GetItem(vals,2));
    // Call Fortran on it
    unit_step(&a);
    //
    PyObject* ret = Py_BuildValue("{s:f,s:f,s:f}",
                         "x", a.x,
                         "y", a.y,
                         "z", a.z);
    return ret;
}

static PyMethodDef EucliMethods[] = {
    {"unitinc", (PyCFunction)eucli_unitinc, METH_VARARGS,
     "Add 1 to the axes of a point"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef eucli_module = {
   PyModuleDef_HEAD_INIT,
   "eucli",
   "blah",
   -1,
   EucliMethods
};

PyMODINIT_FUNC PyInit_eucli(void)
{
    PyObject *m;
    m = PyModule_Create(&eucli_module);
    if (!m) {
        return NULL;
    }

    return m;
}
