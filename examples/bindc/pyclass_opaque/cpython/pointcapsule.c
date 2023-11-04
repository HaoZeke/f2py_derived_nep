#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#endif /* PY_SSIZE_T_CLEAN */

#include "Python.h"
#include "structmember.h"
#include "point.h"

#include <Python.h>

/* Destructor for the Python capsule */
void point_capsule_destructor(PyObject* capsule) {
    Point* p = (Point*) PyCapsule_GetPointer(capsule, "point._Point");
    destroy_point(p);
}

// Python wrapper for the Point class
typedef struct {
    PyObject_HEAD
    PyObject* capsule; // Capsule containing the Point pointer
} PyPoint;

// Methods of the Point class
static void PyPoint_dealloc(PyPoint* self) {
    /* Decrement the reference count of the capsule */
    Py_XDECREF(self->capsule);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyPoint_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyPoint* self;

    self = (PyPoint*)type->tp_alloc(type, 0);
    if (self != NULL) {
        double x, y;
        if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
            Py_DECREF(self);
            return NULL;
        }
        Point* p = create_point(x, y);
        self->capsule = PyCapsule_New(p, "point._Point", point_capsule_destructor);
        if (self->capsule == NULL) {
            Py_DECREF(self);
            return NULL;
        }
    }

    return (PyObject*)self;
}

// Getter for x
static PyObject* PyPoint_getx(PyPoint* self, void* closure) {
    Point* p = (Point*) PyCapsule_GetPointer(self->capsule, "point._Point");
    if (!p) {
        PyErr_SetString(PyExc_RuntimeError, "The point is invalid.");
        return NULL;
    }
    double x = get_x(p);
    return PyFloat_FromDouble(x);
}

// Setter for x
static int PyPoint_setx(PyPoint* self, PyObject* value, void* closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the x attribute");
        return -1;
    }
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The x attribute value must be a float");
        return -1;
    }
    Point* p = (Point*) PyCapsule_GetPointer(self->capsule, "point._Point");
    if (!p) {
        PyErr_SetString(PyExc_RuntimeError, "The point is invalid.");
        return -1;
    }
    double x = PyFloat_AsDouble(value);
    set_x(p, x);
    return 0;
}

// Getter for y
static PyObject* PyPoint_gety(PyPoint* self, void* closure) {
    Point* p = (Point*) PyCapsule_GetPointer(self->capsule, "point._Point");
    if (!p) {
        PyErr_SetString(PyExc_RuntimeError, "The point is invalid.");
        return NULL;
    }
    double y = get_y(p);
    return PyFloat_FromDouble(y);
}

// Setter for y
static int PyPoint_sety(PyPoint* self, PyObject* value, void* closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the y attribute");
        return -1;
    }
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The y attribute value must be a float");
        return -1;
    }
    Point* p = (Point*) PyCapsule_GetPointer(self->capsule, "point._Point");
    if (!p) {
        PyErr_SetString(PyExc_RuntimeError, "The point is invalid.");
        return -1;
    }
    double y = PyFloat_AsDouble(value);
    set_y(p, y);
    return 0;
}


// Define getters and setters
static PyGetSetDef PyPoint_getsetters[] = {
    {"x", (getter)PyPoint_getx, (setter)PyPoint_setx, "x coordinate", NULL},
    {"y", (getter)PyPoint_gety, (setter)PyPoint_sety, "y coordinate", NULL},
    {NULL}  /* Sentinel */
};

// Define the Python type object for Point
static PyTypeObject PyPointType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "point.Point",             /* tp_name */
    .tp_basicsize = sizeof(PyPoint),           /* tp_basicsize */
    .tp_dealloc = (destructor)PyPoint_dealloc, /* tp_dealloc */
    .tp_flags = Py_TPFLAGS_DEFAULT,        /* tp_flags */
    .tp_doc = "Point objects",           /* tp_doc */
    .tp_getset = PyPoint_getsetters,        /* tp_getset */
    .tp_new = PyPoint_new               /* tp_new */
};

// Module method definitions
static PyMethodDef point_methods[] = {
    // Method definitions would go here, if there are any global functions
    {NULL, NULL, 0, NULL}  /* Sentinel */
};

// Module definition
static struct PyModuleDef pointmodule = {
    PyModuleDef_HEAD_INIT,
    "point",   /* name of module */
    "Module that provides a Point object.",  /* module documentation, may be NULL */
    -1,        /* size of per-interpreter state of the module */
    point_methods
};

// Module initialization function
PyMODINIT_FUNC PyInit_point(void) {
    PyObject* m;

    if (PyType_Ready(&PyPointType) < 0)
        return NULL;

    m = PyModule_Create(&pointmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyPointType);
    if (PyModule_AddObject(m, "Point", (PyObject *)&PyPointType) < 0) {
        Py_DECREF(&PyPointType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
