#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#endif /* PY_SSIZE_T_CLEAN */

#include "Python.h"
#include "structmember.h"
/* #include "point.h" */

#include <Python.h>

// Forward declarations for the Fortran functions
extern void *c_new_point(double x, double y);
extern void c_delete_point(void **point);
extern double c_get_x(void *point);
extern void c_set_x(void *point, double x);
extern double c_get_y(void *point);
extern void c_set_y(void *point, double y);

// Destructor for the Python capsule
void point_capsule_destructor(PyObject *capsule) {
  void *point = PyCapsule_GetPointer(capsule, "point._Point");
  if (point) {
    c_delete_point(&point);
  }
}

// Point object definition
typedef struct {
  PyObject_HEAD PyObject *capsule; // Capsule containing the Point pointer
} PyPointObject;

// Deallocates the PyPointObject
static void PyPoint_dealloc(PyPointObject *self) {
  Py_XDECREF(
      self->capsule); // This will trigger the destructor if refcount reaches 0
  Py_TYPE(self)->tp_free((PyObject *)self);
}

// Creates a new PyPointObject
static PyObject *PyPoint_new(PyTypeObject *type, PyObject *args,
                             PyObject *kwds) {
  double x, y;
  if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
    return NULL;
  }

  PyPointObject *self = (PyPointObject *)type->tp_alloc(type, 0);
  if (self != NULL) {
    void *point = c_new_point(x, y);
    if (point == NULL) {
      Py_DECREF(self);
      return PyErr_NoMemory();
    }
    self->capsule =
        PyCapsule_New(point, "point._Point", point_capsule_destructor);
    if (self->capsule == NULL) {
      c_delete_point(
          &point); // Clean up Fortran point since capsule creation failed
      Py_DECREF(self);
      return NULL;
    }
  }
  return (PyObject *)self;
}

// Getter for the 'x' attribute
static PyObject *PyPoint_getx(PyPointObject *self, void *closure) {
  void *point = PyCapsule_GetPointer(self->capsule, "point._Point");
  double x = c_get_x(&point);
  return PyFloat_FromDouble(x);
}

// Setter for the 'x' attribute
static int PyPoint_setx(PyPointObject *self, PyObject *value, void *closure) {
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "Cannot delete the x attribute");
    return -1;
  }
  if (!PyFloat_Check(value)) {
    PyErr_SetString(PyExc_TypeError, "The x attribute value must be a float");
    return -1;
  }
  double x = PyFloat_AsDouble(value);
  void *point = PyCapsule_GetPointer(self->capsule, "point._Point");
  c_set_x(&point, x);
  return 0;
}

// Getter for the 'y' attribute
static PyObject *PyPoint_gety(PyPointObject *self, void *closure) {
  void *point = PyCapsule_GetPointer(self->capsule, "point._Point");
  double y = c_get_y(&point);
  return PyFloat_FromDouble(y);
}

// Setter for the 'y' attribute
static int PyPoint_sety(PyPointObject *self, PyObject *value, void *closure) {
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "Cannot delete the y attribute");
    return -1;
  }
  if (!PyFloat_Check(value)) {
    PyErr_SetString(PyExc_TypeError, "The y attribute value must be a float");
    return -1;
  }
  double y = PyFloat_AsDouble(value);
  void *point = PyCapsule_GetPointer(self->capsule, "point._Point");
  c_set_y(&point, y);
  return 0;
}

// Define the properties of the Point type
static PyGetSetDef PyPoint_getseters[] = {
    {"x", (getter)PyPoint_getx, (setter)PyPoint_setx, "x coordinate", NULL},
    {"y", (getter)PyPoint_gety, (setter)PyPoint_sety, "y coordinate", NULL},
    {NULL} /* Sentinel */
};

// Initializes the PyPointType object
static PyTypeObject PyPointType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "point.Point",
    .tp_doc = "Point objects",
    .tp_basicsize = sizeof(PyPointObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyPoint_new,
    .tp_dealloc = (destructor)PyPoint_dealloc,
    .tp_getset = PyPoint_getseters,
    // Additional fields can be filled in as needed
};

// Define the methods of the module if there are any
static PyMethodDef point_methods[] = {
    // Methods can be added here if needed
    {NULL, NULL, 0, NULL} /* Sentinel */
};

// Initializes the point module
static PyModuleDef pointmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "point",
    .m_doc = "Module that provides a Point object.",
    .m_size = -1,
    .m_methods = point_methods,
};

PyMODINIT_FUNC PyInit_point(void) {
  if (PyType_Ready(&PyPointType) < 0) {
    return NULL;
  }

  PyObject *m = PyModule_Create(&pointmodule);
  if (m == NULL) {
    return NULL;
  }

  Py_INCREF(&PyPointType);
  if (PyModule_AddObject(m, "Point", (PyObject *)&PyPointType) < 0) {
    Py_DECREF(&PyPointType);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
