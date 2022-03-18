==============================================================================
NEP 50 — Fortran Derived Type Support
==============================================================================

:title: Fortran Derived Type Support
:Author: Rohit Goswami <r95g10@gmail.com>
:Author: Melissa Mendonça <melissawm@gmail.com>
:Author: Pearu Peterson <pearu.peterson@gmail.com>
:Status: Draft
:Type: Standards Track
:Created: 18-03-2022
:NumPy-Version: 1.23

******************************************************************************
Abstract
******************************************************************************

F2PY has been embedded in NumPy since 2007. This has lead to its continued
maintenance (e.g. transitioning between Python major versions). Compatibility
with newer Fortran functionality beyond the Fortran 90 standard has not been
considered. Herein we discuss the implementation details for adding derived type
support into F2PY.

******************************************************************************
Motivation and scope
******************************************************************************

For almost two decades now, Fortran has supported the object oriented
programming paradigm through the standardization of derived types. These have
grown in scope, from being record types similar to C structures to being fully
fledged class instances with inheritance and type bound procedures (class
methods).

The Fortran standards committee defines interoperability between C structures
and simple derived types within the context of the ``bind`` attribute which
enforces common data representations between compatible co-processors (e.g.
``bind(c)``).

******************************************************************************
Backward compatibility
******************************************************************************

The Fortran 77 feature set of F2PY including the parser and binding rules are
considered to be complete and will not be changed. For the implementation of
derived types and newer features, the backwards compatibility rules follow that
of NumPy itself, each released feature is guaranteed to have the same observable
behavior (modulo bug-fixes) for at-least two releases.

******************************************************************************
Usage and impact
******************************************************************************


******************************************************************************
Definitions
******************************************************************************

******************************************************************************
Record Types
******************************************************************************


``bind(c)`` Compatible types
==============================================================================

.. note::

   These bindings have a reference implementation in `PR 20770`_

As defined by the Fortran 2003 standard, a derived type with the ``bind(c)``
attribute:

.. code-block:: fortran

   type, bind(c) :: cartesian
    real(c_float) :: x, y, z
   end type cartesian

is considered to be exactly equivalent to:

.. code-block:: c

    struct cartesian {
        float x, y, z;
    }

F2PY will ensure that this structure is equivalent to a Python dictionary:

.. code-block:: python

    a = {'x': 0, 'y': 1, 'z': 2}


******************************************************************************
Implementation
******************************************************************************

Code which conforms to the ``bind(c)`` specification of the Fortran 2003
standard is guaranteed to be wrapped unchanged through the CPython interface.

******************************************************************************
Alternatives
******************************************************************************

Wrapping the structures into a CPython class with an attribute for determining
if the underlying Fortran code is ``bind(c)`` compatible was considered but
dropped as it harder to reason about the underlying Fortran code.


******************************************************************************
References
******************************************************************************

.. _`PR 20770`: https://github.com/numpy/numpy/pull/20770

******************************************************************************
Copyright
******************************************************************************

This document has been placed in the public domain.
