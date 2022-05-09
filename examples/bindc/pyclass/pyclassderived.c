#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#endif /* PY_SSIZE_T_CLEAN */

#include "Python.h"
#include "structmember.h"

// Fortran-C stuff
#include "vecf.h"

// Python-C stuff

// CPython compatible declaration
typedef struct {
  PyObject_HEAD        /* Do not move */
  // Make this a pointer to a cart
      cartesian ccart; /* totally interoperable */
  // Maybe wrap arrays with ndarray
  // Check bind(c) for arrays
} pycart;

// Almost everything in the class must be static
static void pycart_dealloc(pycart *self) {
  // Also free the pointer here
  Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *pycart_new(PyTypeObject *type, PyObject *args,
                            PyObject *kwds) {
  // Allocate and create the cartesian object here
  pycart *self;
  self = (pycart *)type->tp_alloc(type, 0);
  if (self != NULL) {
    // TODO: Error handling
    self->ccart.x = 0;
    self->ccart.y = 0;
    self->ccart.z = 0;
  }
  return (PyObject *)self;
}

static int pycart_init(pycart *self, PyObject *args, PyObject *kwds) {
  static char *kwlist[] = {"x", "y", "x", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ddd", kwlist, &self->ccart.x,
                                   &self->ccart.y, &self->ccart.z))
    return -1;
  return 0;
}

static PyMemberDef pycart_members[] = {
    {"x", T_DOUBLE, offsetof(pycart, ccart.x), 0, "x coordinate"},
    {"y", T_DOUBLE, offsetof(pycart, ccart.y), 0, "y coordinate"},
    {"z", T_DOUBLE, offsetof(pycart, ccart.z), 0, "z coordinate"},
    {NULL} /* Sentinel */
};

static PyObject *pycart_repr(pycart *self) {
  char x[50], y[50], z[50];
  sprintf(x, "%f", self->ccart.x);
  sprintf(y, "%f", self->ccart.y);
  sprintf(z, "%f", self->ccart.z);
  PyObject *repr = PyUnicode_FromFormat("pycart(x: %s, y: %s, z: %s)", x, y, z);
  return repr;
}

static PyObject *pycart_unitstep(pycart *self) {
  // Call Fortran on the internal representation
  unit_step(&self->ccart);
  Py_RETURN_NONE;
}

static PyMethodDef pycart_methods[] = {
    {"unitstep", (PyCFunction)pycart_unitstep, METH_NOARGS,
     "Modify the class members with the Fortran unit_step function"},
    {NULL} /* Sentinel */
};

// Definition of type
static PyTypeObject t_pycart = {
    PyVarObject_HEAD_INIT(NULL, 0) /* tp_head */
        .tp_name = "pycart.pycart",
    .tp_doc = PyDoc_STR("One coordinate (x, y, z)"),
    .tp_basicsize = sizeof(pycart),
    .tp_itemsize = 0,
    .tp_dealloc = pycart_dealloc,
    .tp_repr = pycart_repr,
    .tp_getattro = PyObject_GenericGetAttr,
    .tp_setattro = PyObject_GenericSetAttr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = pycart_members,
    .tp_methods = pycart_methods,
    .tp_init = pycart_init,          /* tp_init */
    .tp_alloc = PyType_GenericAlloc, /* tp_alloc */
    .tp_new = PyType_GenericNew,     /* tp_new */
    .tp_free = PyObject_Del,         /* tp_free */
    // Add an attribute to show this is from Fortran
};

static char pycart_docs[] = "pycart: data type with x,y,z elements\n";

static PyModuleDef pycartmodule = {PyModuleDef_HEAD_INIT, .m_name = "pycart",
                                   .m_doc = pycart_docs, .m_size = -1};

PyMODINIT_FUNC PyInit_pycart(void) {
  PyObject *this_module;
  if (PyType_Ready(&t_pycart))
    return NULL;
  this_module = PyModule_Create(&pycartmodule);
  if (this_module == NULL) {
    return NULL;
  }
  Py_INCREF(&t_pycart);
  if (PyModule_AddObject(this_module, "pycart", (PyObject *)&t_pycart) < 0) {
    Py_DECREF(&t_pycart);
    Py_DECREF(this_module);
    return NULL;
  }
  return this_module;
}
