%module(directors="1") simbody

// TODO only use the necessary headers.
%{
#define SWIG_FILE_WITH_INIT
#include <Bindings/OpenSimHeaders.h>
%}
%{
using namespace OpenSim;
using namespace SimTK;

%}


%include "preliminaries_python.i"


// Relay exceptions to the target language.
// This causes substantial code bloat and possibly hurts performance.
// Without these try-catch block, a SimTK or OpenSim exception causes the
// program to crash.
%include "exception.i"
%exception {
    try {
        $action
    } catch (const std::exception& e) {
        std::string str("std::exception in '$fulldecl': ");
        std::string what(e.what());
        SWIG_exception(SWIG_RuntimeError, (str + what).c_str());
    }
}

// Typemaps
// ========
// Allow passing python objects into OpenSim functions. For example,
// pass a list of 3 float's into a function that takes a Vec3 as an argument.
/*
TODO disabling these for now as the typemaps remove the ability to pass
arguments using the C++ types. For example, with these typemaps,
Model::setGravity() can no longer take a Vec3. We can revisit typemaps if we
can keep the ability to use the original argument types.
These typemaps work, though.
%typemap(in) SimTK::Vec3 {
    SimTK::Vec3 v;
    if (!PySequence_Check($input)) {
        PyErr_SetString(PyExc_ValueError, "Expected a sequence.");
        return NULL;
    }
    if (PySequence_Length($input) != v.size()) {
        PyErr_SetString(PyExc_ValueError,
                "Size mismatch. Expected 3 elements.");
        return NULL;
    }
    for (int i = 0; i < v.size(); ++i) {
        PyObject* o = PySequence_GetItem($input, i);
        if (PyNumber_Check(o)) {
            v[i] = PyFloat_AsDouble(o);
        } else {
            PyErr_SetString(PyExc_ValueError,
                "Sequence elements must be numbers.");
            return NULL;
        }
    }
    $1 = &v;
};
%typemap(in) const SimTK::Vec3& {
    SimTK::Vec3 v;
    if (!PySequence_Check($input)) {
        PyErr_SetString(PyExc_ValueError, "Expected a sequence.");
        return NULL;
    }
    if (PySequence_Length($input) != v.size()) {
        PyErr_SetString(PyExc_ValueError,
                "Size mismatch. Expected 3 elements.");
        return NULL;
    }
    for (int i = 0; i < v.size(); ++i) {
        PyObject* o = PySequence_GetItem($input, i);
        if (PyNumber_Check(o)) {
            v[i] = PyFloat_AsDouble(o);
        } else {
            PyErr_SetString(PyExc_ValueError,
                "Sequence elements must be numbers.");
            return NULL;
        }
    }
    $1 = &v;
};
// This is how one would apply a generic typemap to specific arguments:
//%apply const SimTK::Vec3& INPUT { const SimTK::Vec3& aGrav };
*/

// Pythonic operators
// ==================
// Extend the template Vec class; these methods will apply for all template
// parameters. This extend block must appear before the %template call in
// simbody.i.
%extend SimTK::Vec {
    std::string __str__() const {
        return $self->toString();
    }
    int __len__() const {
        return $self->size();
    }
};

%extend SimTK::Vector_ {
    std::string __str__() const {
        return $self->toString();
    }
    int __len__() const {
        return $self->size();
    }
};

%include <Bindings/preliminaries.i>
%include <Bindings/simbody.i>

// Pythonic operators
// ==================
%extend SimTK::Vec<3> {
     double __getitem__(int i) const {
        SimTK_INDEXCHECK_ALWAYS(i, $self->size(), "Vec3.__getitem__()");
        return $self->operator[](i);
    }
    void __setitem__(int i, double value) {
        SimTK_INDEXCHECK_ALWAYS(i, $self->size(), "Vec3.__setitem__()");
        $self->operator[](i) = value;
    }
    //SimTK::Vec<3> __add__(const SimTK::Vec<3>& v) const {
    //    return *($self) + v;
    //}
};
%extend SimTK::Vector_<double> {
    double __getitem__(int i) const {
        SimTK_INDEXCHECK_ALWAYS(i, $self->size(), "Vector.__getitem__()");
        return $self->operator[](i);
    }
    void __setitem__(int i, double value) {
        SimTK_INDEXCHECK_ALWAYS(i, $self->size(), "Vector.__setitem__()");
        $self->operator[](i) = value;
    }
};
