#define PY_SSIZE_T_CLEAN
#ifndef CYTHON_USE_PYLONG_INTERNALS
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 0
#else
#include "pyconfig.h"
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 1
#else
#define CYTHON_USE_PYLONG_INTERNALS 0
#endif
#endif
#endif
#include <Python/Python.h>
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03020000)
    #error Cython requires Python 2.6+ or Python 3.2+.
#else
#define CYTHON_ABI "0_22"
#include <stddef.h>
#ifndef offsetof
#define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
#define CYTHON_COMPILING_IN_PYPY 1
#define CYTHON_COMPILING_IN_CPYTHON 0
#else
#define CYTHON_COMPILING_IN_PYPY 0
#define CYTHON_COMPILING_IN_CPYTHON 1
#endif
#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
#define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyType_Type
#endif
#if PY_MAJOR_VERSION >= 3
  #define Py_TPFLAGS_CHECKTYPES 0
  #define Py_TPFLAGS_HAVE_INDEX 0
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#if PY_VERSION_HEX < 0x030400a1 && !defined(Py_TPFLAGS_HAVE_FINALIZE)
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ? \
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
#else
  #define CYTHON_PEP393_ENABLED 0
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
  #define __Pyx_PyFrozenSet_Size(s)         PyObject_Size(s)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ? \
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
  #define __Pyx_PyFrozenSet_Size(s)         PySet_Size(s)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#ifndef CYTHON_INLINE
  #if defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  /* Initialize NaN. The sign is irrelevant, an exponent with all bits 1 and
   a nonzero mantissa means NaN. If the first bit in the mantissa is 1, it is
   a quiet NaN. */
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#define __Pyx_void_to_None(void_result) (void_result, Py_INCREF(Py_None), Py_None)
#ifdef __cplusplus
template<typename T>
void __Pyx_call_destructor(T* x) {
    x->~T();
}
template<typename T>
class __Pyx_FakeReference {
  public:
    __Pyx_FakeReference() : ptr(NULL) { }
    __Pyx_FakeReference(T& ref) : ptr(&ref) { }
    T *operator->() { return ptr; }
    operator T&() { return *ptr; }
  private:
    T *ptr;
};
#endif


#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#define __PYX_HAVE__parser
#define __PYX_HAVE_API__parser
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif

#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
typedef struct {PyObject **p; char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (    \
    (sizeof(type) < sizeof(Py_ssize_t))  ||             \
    (sizeof(type) > sizeof(Py_ssize_t) &&               \
          likely(v < (type)PY_SSIZE_T_MAX ||            \
                 v == (type)PY_SSIZE_T_MAX)  &&         \
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||       \
                                v == (type)PY_SSIZE_T_MIN)))  ||  \
    (sizeof(type) == sizeof(Py_ssize_t) &&              \
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||        \
                               v == (type)PY_SSIZE_T_MAX)))  )
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_Owned_Py_None(b) (Py_INCREF(Py_None), Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? (Py_INCREF(Py_True), Py_True) : (Py_INCREF(Py_False), Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_COMPILING_IN_CPYTHON
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "parser.py",
};

/*--- Type declarations ---*/

/* --- Runtime support code (head) --- */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          if (acquire_gil) { \
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure(); \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
              PyGILState_Release(__pyx_gilstate_save); \
          } else { \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext() \
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {                            \
        PyObject *tmp = (PyObject *) r;                         \
        r = v; __Pyx_XDECREF(tmp);                              \
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {                             \
        PyObject *tmp = (PyObject *) r;                         \
        r = v; __Pyx_DECREF(tmp);                               \
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

static PyObject *__Pyx_GetBuiltinName(PyObject *name);

static CYTHON_INLINE int __Pyx_PySequence_Contains(PyObject* item, PyObject* seq, int eq) {
    int result = PySequence_Contains(seq, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

#if PY_MAJOR_VERSION < 3
#define __Pyx_PyString_Join __Pyx_PyBytes_Join
#define __Pyx_PyBaseString_Join(s, v) (PyUnicode_CheckExact(s) ? PyUnicode_Join(s, v) : __Pyx_PyBytes_Join(s, v))
#else
#define __Pyx_PyString_Join PyUnicode_Join
#define __Pyx_PyBaseString_Join PyUnicode_Join
#endif
#if CYTHON_COMPILING_IN_CPYTHON
    #if PY_MAJOR_VERSION < 3
    #define __Pyx_PyBytes_Join _PyString_Join
    #else
    #define __Pyx_PyBytes_Join _PyBytes_Join
    #endif
#else
static CYTHON_INLINE PyObject* __Pyx_PyBytes_Join(PyObject* sep, PyObject* values);
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE int __Pyx_PyList_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len) & likely(len > (L->allocated >> 1))) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        Py_SIZE(list) = len+1;
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_PyList_Append(L,x) PyList_Append(L,x)
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

static PyObject* __Pyx_PyObject_CallMethod0(PyObject* obj, PyObject* method_name);

#define __Pyx_PyObject_Pop(L) (PyList_CheckExact(L) ? \
    __Pyx_PyList_Pop(L) : __Pyx__PyObject_Pop(L))
static CYTHON_INLINE PyObject* __Pyx_PyList_Pop(PyObject* L);
static CYTHON_INLINE PyObject* __Pyx__PyObject_Pop(PyObject* L);

static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type);

#define __Pyx_CyFunction_USED 1
#include "structmember.h"
#define __Pyx_CYFUNCTION_STATICMETHOD  0x01
#define __Pyx_CYFUNCTION_CLASSMETHOD   0x02
#define __Pyx_CYFUNCTION_CCLASS        0x04
#define __Pyx_CyFunction_GetClosure(f) \
    (((__pyx_CyFunctionObject *) (f))->func_closure)
#define __Pyx_CyFunction_GetClassObj(f) \
    (((__pyx_CyFunctionObject *) (f))->func_classobj)
#define __Pyx_CyFunction_Defaults(type, f) \
    ((type *)(((__pyx_CyFunctionObject *) (f))->defaults))
#define __Pyx_CyFunction_SetDefaultsGetter(f, g) \
    ((__pyx_CyFunctionObject *) (f))->defaults_getter = (g)
typedef struct {
    PyCFunctionObject func;
#if PY_VERSION_HEX < 0x030500A0
    PyObject *func_weakreflist;
#endif
    PyObject *func_dict;
    PyObject *func_name;
    PyObject *func_qualname;
    PyObject *func_doc;
    PyObject *func_globals;
    PyObject *func_code;
    PyObject *func_closure;
    PyObject *func_classobj;
    void *defaults;
    int defaults_pyobjects;
    int flags;
    PyObject *defaults_tuple;
    PyObject *defaults_kwdict;
    PyObject *(*defaults_getter)(PyObject *);
    PyObject *func_annotations;
} __pyx_CyFunctionObject;
static PyTypeObject *__pyx_CyFunctionType = 0;
#define __Pyx_CyFunction_NewEx(ml, flags, qualname, self, module, globals, code) \
    __Pyx_CyFunction_New(__pyx_CyFunctionType, ml, flags, qualname, self, module, globals, code)
static PyObject *__Pyx_CyFunction_New(PyTypeObject *, PyMethodDef *ml,
                                      int flags, PyObject* qualname,
                                      PyObject *self,
                                      PyObject *module, PyObject *globals,
                                      PyObject* code);
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *m,
                                                         size_t size,
                                                         int pyobjects);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *m,
                                                            PyObject *tuple);
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *m,
                                                             PyObject *dict);
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *m,
                                                              PyObject *dict);
static int __Pyx_CyFunction_init(void);

#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck) \
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ? \
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) : \
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) : \
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck) \
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ? \
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) : \
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck) \
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ? \
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) : \
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

typedef struct {
    int code_line;
    PyCodeObject* code_object;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

static int __Pyx_Print(PyObject*, PyObject *, int);
#if CYTHON_COMPILING_IN_PYPY || PY_MAJOR_VERSION >= 3
static PyObject* __pyx_print = 0;
static PyObject* __pyx_print_kwargs = 0;
#endif

static int __Pyx_PrintOne(PyObject* stream, PyObject *o);

static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

static int __Pyx_check_binary_version(void);

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);


/* Module declarations from 'parser' */
#define __Pyx_MODULE_NAME "parser"
int __pyx_module_is_main_parser = 0;

/* Implementation of 'parser' */
static PyObject *__pyx_builtin_open;
static PyObject *__pyx_builtin_enumerate;
static PyObject *__pyx_pf_6parser_match_quote(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_str); /* proto */
static PyObject *__pyx_pf_6parser_2minify(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x); /* proto */
static PyObject *__pyx_pf_6parser_4parse_nml(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_file); /* proto */
static char __pyx_k_[] = "'";
static char __pyx_k_a[] = "a";
static char __pyx_k_b[] = "b";
static char __pyx_k_r[] = "r";
static char __pyx_k_s[] = "\\s";
static char __pyx_k_x[] = "x";
static char __pyx_k_z[] = "z";
static char __pyx_k__2[] = "\"";
static char __pyx_k__3[] = "\n";
static char __pyx_k__4[] = "\t";
static char __pyx_k__5[] = "";
static char __pyx_k__6[] = "$";
static char __pyx_k__7[] = "<";
static char __pyx_k__8[] = "@";
static char __pyx_k__9[] = ">";
static char __pyx_k_ac[] = "ac";
static char __pyx_k_ce[] = "ce";
static char __pyx_k_iq[] = "iq";
static char __pyx_k_re[] = "re";
static char __pyx_k_ws[] = "ws";
static char __pyx_k__10[] = "(";
static char __pyx_k__11[] = " ";
static char __pyx_k__12[] = ":";
static char __pyx_k__13[] = "=\"";
static char __pyx_k__14[] = ",";
static char __pyx_k__15[] = ")";
static char __pyx_k__16[] = "\">";
static char __pyx_k__17[] = "%";
static char __pyx_k__18[] = "#";
static char __pyx_k__19[] = "<!--";
static char __pyx_k__20[] = "-->";
static char __pyx_k_ac2[] = "ac2";
static char __pyx_k_cfs[] = "cfs";
static char __pyx_k_css[] = "css";
static char __pyx_k_end[] = "end";
static char __pyx_k_pop[] = "pop";
static char __pyx_k_s_2[] = "</%s>";
static char __pyx_k_str[] = "str";
static char __pyx_k_sys[] = "sys";
static char __pyx_k_ws2[] = "ws2";
static char __pyx_k_argc[] = "argc";
static char __pyx_k_argv[] = "argv";
static char __pyx_k_body[] = "body";
static char __pyx_k_file[] = "file";
static char __pyx_k_head[] = "head";
static char __pyx_k_html[] = "</html>";
static char __pyx_k_join[] = "join";
static char __pyx_k_main[] = "__main__";
static char __pyx_k_open[] = "open";
static char __pyx_k_read[] = "read";
static char __pyx_k_test[] = "__test__";
static char __pyx_k_match[] = "match";
static char __pyx_k_print[] = "print";
static char __pyx_k_buffer[] = "buffer";
static char __pyx_k_import[] = "__import__";
static char __pyx_k_minify[] = "minify";
static char __pyx_k_parser[] = "parser";
static char __pyx_k_tokens[] = "tokens";
static char __pyx_k_enumerate[] = "enumerate";
static char __pyx_k_parse_nml[] = "parse_nml";
static char __pyx_k_match_quote[] = "match_quote";
static char __pyx_k_1mUsage_0m_s_file[] = "\033[1mUsage:\033[0m %s [file]";
static char __pyx_k_DOCTYPE_html_html[] = "<!DOCTYPE html><html>";
static char __pyx_k_Users_nsandman09_Documents_code[] = "/Users/nsandman09/Documents/code/nml/parser.py";
static PyObject *__pyx_kp_s_;
static PyObject *__pyx_kp_s_1mUsage_0m_s_file;
static PyObject *__pyx_kp_s_DOCTYPE_html_html;
static PyObject *__pyx_kp_s_Users_nsandman09_Documents_code;
static PyObject *__pyx_kp_s__10;
static PyObject *__pyx_kp_s__11;
static PyObject *__pyx_kp_s__12;
static PyObject *__pyx_kp_s__13;
static PyObject *__pyx_kp_s__14;
static PyObject *__pyx_kp_s__15;
static PyObject *__pyx_kp_s__16;
static PyObject *__pyx_kp_s__17;
static PyObject *__pyx_kp_s__18;
static PyObject *__pyx_kp_s__19;
static PyObject *__pyx_kp_s__2;
static PyObject *__pyx_kp_s__20;
static PyObject *__pyx_kp_s__3;
static PyObject *__pyx_kp_s__4;
static PyObject *__pyx_kp_s__5;
static PyObject *__pyx_kp_s__6;
static PyObject *__pyx_kp_s__7;
static PyObject *__pyx_kp_s__8;
static PyObject *__pyx_kp_s__9;
static PyObject *__pyx_n_s_a;
static PyObject *__pyx_n_s_ac;
static PyObject *__pyx_n_s_ac2;
static PyObject *__pyx_n_s_argc;
static PyObject *__pyx_n_s_argv;
static PyObject *__pyx_n_s_b;
static PyObject *__pyx_n_s_body;
static PyObject *__pyx_n_s_buffer;
static PyObject *__pyx_n_s_ce;
static PyObject *__pyx_n_s_cfs;
static PyObject *__pyx_n_s_css;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_enumerate;
static PyObject *__pyx_n_s_file;
static PyObject *__pyx_n_s_head;
static PyObject *__pyx_kp_s_html;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_iq;
static PyObject *__pyx_n_s_join;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_match;
static PyObject *__pyx_n_s_match_quote;
static PyObject *__pyx_n_s_minify;
static PyObject *__pyx_n_s_open;
static PyObject *__pyx_n_s_parse_nml;
static PyObject *__pyx_n_s_parser;
static PyObject *__pyx_n_s_pop;
static PyObject *__pyx_n_s_print;
static PyObject *__pyx_n_s_r;
static PyObject *__pyx_n_s_re;
static PyObject *__pyx_n_s_read;
static PyObject *__pyx_kp_s_s;
static PyObject *__pyx_kp_s_s_2;
static PyObject *__pyx_n_s_str;
static PyObject *__pyx_n_s_sys;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_tokens;
static PyObject *__pyx_n_s_ws;
static PyObject *__pyx_n_s_ws2;
static PyObject *__pyx_n_s_x;
static PyObject *__pyx_n_s_z;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_tuple__21;
static PyObject *__pyx_tuple__23;
static PyObject *__pyx_tuple__25;
static PyObject *__pyx_codeobj__22;
static PyObject *__pyx_codeobj__24;
static PyObject *__pyx_codeobj__26;

/* "parser.py":27
 * # than if a is '"' or a is "'" (especially since the second one looks
 * # kind of ugly)
 * def match_quote(str):             # <<<<<<<<<<<<<<
 * 	if str is "'" or str is '"':
 * 		return True
 */

/* Python wrapper */
static PyObject *__pyx_pw_6parser_1match_quote(PyObject *__pyx_self, PyObject *__pyx_v_str); /*proto*/
static PyMethodDef __pyx_mdef_6parser_1match_quote = {"match_quote", (PyCFunction)__pyx_pw_6parser_1match_quote, METH_O, 0};
static PyObject *__pyx_pw_6parser_1match_quote(PyObject *__pyx_self, PyObject *__pyx_v_str) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("match_quote (wrapper)", 0);
  __pyx_r = __pyx_pf_6parser_match_quote(__pyx_self, ((PyObject *)__pyx_v_str));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_6parser_match_quote(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_str) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  __Pyx_RefNannySetupContext("match_quote", 0);

  /* "parser.py":28
 * # kind of ugly)
 * def match_quote(str):
 * 	if str is "'" or str is '"':             # <<<<<<<<<<<<<<
 * 		return True
 * 	else:
 */
  __pyx_t_2 = (__pyx_v_str == __pyx_kp_s_);
  __pyx_t_3 = (__pyx_t_2 != 0);
  if (!__pyx_t_3) {
  } else {
    __pyx_t_1 = __pyx_t_3;
    goto __pyx_L4_bool_binop_done;
  }
  __pyx_t_3 = (__pyx_v_str == __pyx_kp_s__2);
  __pyx_t_2 = (__pyx_t_3 != 0);
  __pyx_t_1 = __pyx_t_2;
  __pyx_L4_bool_binop_done:;
  if (__pyx_t_1) {

    /* "parser.py":29
 * def match_quote(str):
 * 	if str is "'" or str is '"':
 * 		return True             # <<<<<<<<<<<<<<
 * 	else:
 * 		return False
 */
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(Py_True);
    __pyx_r = Py_True;
    goto __pyx_L0;
  }
  /*else*/ {

    /* "parser.py":31
 * 		return True
 * 	else:
 * 		return False             # <<<<<<<<<<<<<<
 * 
 * def minify(x):
 */
    __Pyx_XDECREF(__pyx_r);
    __Pyx_INCREF(Py_False);
    __pyx_r = Py_False;
    goto __pyx_L0;
  }

  /* "parser.py":27
 * # than if a is '"' or a is "'" (especially since the second one looks
 * # kind of ugly)
 * def match_quote(str):             # <<<<<<<<<<<<<<
 * 	if str is "'" or str is '"':
 * 		return True
 */

  /* function exit code */
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "parser.py":33
 * 		return False
 * 
 * def minify(x):             # <<<<<<<<<<<<<<
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):
 */

/* Python wrapper */
static PyObject *__pyx_pw_6parser_3minify(PyObject *__pyx_self, PyObject *__pyx_v_x); /*proto*/
static PyMethodDef __pyx_mdef_6parser_3minify = {"minify", (PyCFunction)__pyx_pw_6parser_3minify, METH_O, 0};
static PyObject *__pyx_pw_6parser_3minify(PyObject *__pyx_self, PyObject *__pyx_v_x) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("minify (wrapper)", 0);
  __pyx_r = __pyx_pf_6parser_2minify(__pyx_self, ((PyObject *)__pyx_v_x));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_6parser_2minify(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_x) {
  PyObject *__pyx_v_a = NULL;
  PyObject *__pyx_v_b = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  PyObject *(*__pyx_t_4)(PyObject *);
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_t_7;
  int __pyx_t_8;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("minify", 0);

  /* "parser.py":35
 * def minify(x):
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):             # <<<<<<<<<<<<<<
 * 		if "\n" in b or "\t" in b:
 * 			del x[a]
 */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_t_1 = __pyx_int_0;
  if (likely(PyList_CheckExact(__pyx_v_x)) || PyTuple_CheckExact(__pyx_v_x)) {
    __pyx_t_2 = __pyx_v_x; __Pyx_INCREF(__pyx_t_2); __pyx_t_3 = 0;
    __pyx_t_4 = NULL;
  } else {
    __pyx_t_3 = -1; __pyx_t_2 = PyObject_GetIter(__pyx_v_x); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_4 = Py_TYPE(__pyx_t_2)->tp_iternext; if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  for (;;) {
    if (likely(!__pyx_t_4)) {
      if (likely(PyList_CheckExact(__pyx_t_2))) {
        if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_2)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_5 = PyList_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_5); __pyx_t_3++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #endif
      } else {
        if (__pyx_t_3 >= PyTuple_GET_SIZE(__pyx_t_2)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_5 = PyTuple_GET_ITEM(__pyx_t_2, __pyx_t_3); __Pyx_INCREF(__pyx_t_5); __pyx_t_3++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #else
        __pyx_t_5 = PySequence_ITEM(__pyx_t_2, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #endif
      }
    } else {
      __pyx_t_5 = __pyx_t_4(__pyx_t_2);
      if (unlikely(!__pyx_t_5)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_5);
    }
    __Pyx_XDECREF_SET(__pyx_v_b, __pyx_t_5);
    __pyx_t_5 = 0;
    __Pyx_INCREF(__pyx_t_1);
    __Pyx_XDECREF_SET(__pyx_v_a, __pyx_t_1);
    __pyx_t_5 = PyNumber_Add(__pyx_t_1, __pyx_int_1); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_DECREF(__pyx_t_1);
    __pyx_t_1 = __pyx_t_5;
    __pyx_t_5 = 0;

    /* "parser.py":36
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):
 * 		if "\n" in b or "\t" in b:             # <<<<<<<<<<<<<<
 * 			del x[a]
 * 	return "".join(x)
 */
    __pyx_t_7 = (__Pyx_PySequence_Contains(__pyx_kp_s__3, __pyx_v_b, Py_EQ)); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 36; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (!__pyx_t_8) {
    } else {
      __pyx_t_6 = __pyx_t_8;
      goto __pyx_L6_bool_binop_done;
    }
    __pyx_t_8 = (__Pyx_PySequence_Contains(__pyx_kp_s__4, __pyx_v_b, Py_EQ)); if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 36; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_7 = (__pyx_t_8 != 0);
    __pyx_t_6 = __pyx_t_7;
    __pyx_L6_bool_binop_done:;
    if (__pyx_t_6) {

      /* "parser.py":37
 * 	for (a, b) in enumerate(x):
 * 		if "\n" in b or "\t" in b:
 * 			del x[a]             # <<<<<<<<<<<<<<
 * 	return "".join(x)
 * 
 */
      if (PyObject_DelItem(__pyx_v_x, __pyx_v_a) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 37; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L5;
    }
    __pyx_L5:;

    /* "parser.py":35
 * def minify(x):
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):             # <<<<<<<<<<<<<<
 * 		if "\n" in b or "\t" in b:
 * 			del x[a]
 */
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "parser.py":38
 * 		if "\n" in b or "\t" in b:
 * 			del x[a]
 * 	return "".join(x)             # <<<<<<<<<<<<<<
 * 
 * # It takes one argument, which is a file object. For some reason, passing argv[1]
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_PyString_Join(__pyx_kp_s__5, __pyx_v_x); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 38; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  /* "parser.py":33
 * 		return False
 * 
 * def minify(x):             # <<<<<<<<<<<<<<
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("parser.minify", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_a);
  __Pyx_XDECREF(__pyx_v_b);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "parser.py":42
 * # It takes one argument, which is a file object. For some reason, passing argv[1]
 * # as the file name caused an error.
 * def parse_nml(file):             # <<<<<<<<<<<<<<
 * 	tokens = str()
 * 	# "buffer" is, predictably, the buffer that actually holds the output. It's
 */

/* Python wrapper */
static PyObject *__pyx_pw_6parser_5parse_nml(PyObject *__pyx_self, PyObject *__pyx_v_file); /*proto*/
static PyMethodDef __pyx_mdef_6parser_5parse_nml = {"parse_nml", (PyCFunction)__pyx_pw_6parser_5parse_nml, METH_O, 0};
static PyObject *__pyx_pw_6parser_5parse_nml(PyObject *__pyx_self, PyObject *__pyx_v_file) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("parse_nml (wrapper)", 0);
  __pyx_r = __pyx_pf_6parser_4parse_nml(__pyx_self, ((PyObject *)__pyx_v_file));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_6parser_4parse_nml(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_file) {
  PyObject *__pyx_v_tokens = NULL;
  PyObject *__pyx_v_buffer = NULL;
  PyObject *__pyx_v_open = NULL;
  int __pyx_v_ws;
  int __pyx_v_ws2;
  int __pyx_v_ac;
  int __pyx_v_ac2;
  int __pyx_v_cfs;
  int __pyx_v_iq;
  int __pyx_v_ce;
  CYTHON_UNUSED int __pyx_v_css;
  PyObject *__pyx_v_a = NULL;
  PyObject *__pyx_v_z = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  Py_ssize_t __pyx_t_5;
  PyObject *(*__pyx_t_6)(PyObject *);
  int __pyx_t_7;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  Py_ssize_t __pyx_t_10;
  PyObject *__pyx_t_11 = NULL;
  int __pyx_t_12;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("parse_nml", 0);

  /* "parser.py":43
 * # as the file name caused an error.
 * def parse_nml(file):
 * 	tokens = str()             # <<<<<<<<<<<<<<
 * 	# "buffer" is, predictably, the buffer that actually holds the output. It's
 * 	# an array because Python strings are non-mutable; so, in order to modify it
 */
  __pyx_t_1 = __Pyx_PyObject_Call(((PyObject *)((PyObject*)(&PyString_Type))), __pyx_empty_tuple, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 43; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_tokens = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "parser.py":47
 * 	# an array because Python strings are non-mutable; so, in order to modify it
 * 	# as it's being parsed, it has to be a list.
 * 	buffer = []             # <<<<<<<<<<<<<<
 * 	open = ["head", "body"]
 * 	# Close tag on whitespace?
 */
  __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_buffer = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "parser.py":48
 * 	# as it's being parsed, it has to be a list.
 * 	buffer = []
 * 	open = ["head", "body"]             # <<<<<<<<<<<<<<
 * 	# Close tag on whitespace?
 * 	ws = False
 */
  __pyx_t_1 = PyList_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_head);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_head);
  __Pyx_GIVEREF(__pyx_n_s_head);
  __Pyx_INCREF(__pyx_n_s_body);
  PyList_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_body);
  __Pyx_GIVEREF(__pyx_n_s_body);
  __pyx_v_open = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "parser.py":50
 * 	open = ["head", "body"]
 * 	# Close tag on whitespace?
 * 	ws = False             # <<<<<<<<<<<<<<
 * 	# Same as ws, but for "@" tags.
 * 	ws2 = False
 */
  __pyx_v_ws = 0;

  /* "parser.py":52
 * 	ws = False
 * 	# Same as ws, but for "@" tags.
 * 	ws2 = False             # <<<<<<<<<<<<<<
 * 	# Are we doing item attributes now?
 * 	ac = False
 */
  __pyx_v_ws2 = 0;

  /* "parser.py":54
 * 	ws2 = False
 * 	# Are we doing item attributes now?
 * 	ac = False             # <<<<<<<<<<<<<<
 * 	ac2 = False
 * 	# Check for space. Used for attributes (space after ":")
 */
  __pyx_v_ac = 0;

  /* "parser.py":55
 * 	# Are we doing item attributes now?
 * 	ac = False
 * 	ac2 = False             # <<<<<<<<<<<<<<
 * 	# Check for space. Used for attributes (space after ":")
 * 	cfs = False
 */
  __pyx_v_ac2 = 0;

  /* "parser.py":57
 * 	ac2 = False
 * 	# Check for space. Used for attributes (space after ":")
 * 	cfs = False             # <<<<<<<<<<<<<<
 * 	# Ignore quotes
 * 	iq = True
 */
  __pyx_v_cfs = 0;

  /* "parser.py":59
 * 	cfs = False
 * 	# Ignore quotes
 * 	iq = True             # <<<<<<<<<<<<<<
 * 	# End comment on newline
 * 	ce = False
 */
  __pyx_v_iq = 1;

  /* "parser.py":61
 * 	iq = True
 * 	# End comment on newline
 * 	ce = False             # <<<<<<<<<<<<<<
 * 	css = False
 * 	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!
 */
  __pyx_v_ce = 0;

  /* "parser.py":62
 * 	# End comment on newline
 * 	ce = False
 * 	css = False             # <<<<<<<<<<<<<<
 * 	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!
 * 	for a in file.read():
 */
  __pyx_v_css = 0;

  /* "parser.py":63
 * 	ce = False
 * 	css = False
 * 	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!             # <<<<<<<<<<<<<<
 * 	for a in file.read():
 * 		if a is "$":
 */
  __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s_DOCTYPE_html_html); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 63; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  /* "parser.py":64
 * 	css = False
 * 	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!
 * 	for a in file.read():             # <<<<<<<<<<<<<<
 * 		if a is "$":
 * 			# Replace "$" with "<" and set the ws flag.
 */
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_file, __pyx_n_s_read); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && likely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_4 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_4)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_4);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (__pyx_t_4) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_4); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (likely(PyList_CheckExact(__pyx_t_1)) || PyTuple_CheckExact(__pyx_t_1)) {
    __pyx_t_3 = __pyx_t_1; __Pyx_INCREF(__pyx_t_3); __pyx_t_5 = 0;
    __pyx_t_6 = NULL;
  } else {
    __pyx_t_5 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_t_1); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_6 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  for (;;) {
    if (likely(!__pyx_t_6)) {
      if (likely(PyList_CheckExact(__pyx_t_3))) {
        if (__pyx_t_5 >= PyList_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_5); __Pyx_INCREF(__pyx_t_1); __pyx_t_5++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #endif
      } else {
        if (__pyx_t_5 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_5); __Pyx_INCREF(__pyx_t_1); __pyx_t_5++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #else
        __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_5); __pyx_t_5++; if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #endif
      }
    } else {
      __pyx_t_1 = __pyx_t_6(__pyx_t_3);
      if (unlikely(!__pyx_t_1)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_1);
    }
    __Pyx_XDECREF_SET(__pyx_v_a, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "parser.py":65
 * 	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!
 * 	for a in file.read():
 * 		if a is "$":             # <<<<<<<<<<<<<<
 * 			# Replace "$" with "<" and set the ws flag.
 * 			buffer.append("<")
 */
    __pyx_t_7 = (__pyx_v_a == __pyx_kp_s__6);
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (__pyx_t_8) {

      /* "parser.py":67
 * 		if a is "$":
 * 			# Replace "$" with "<" and set the ws flag.
 * 			buffer.append("<")             # <<<<<<<<<<<<<<
 * 			ws = True
 * 		elif a is "@":
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__7); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":68
 * 			# Replace "$" with "<" and set the ws flag.
 * 			buffer.append("<")
 * 			ws = True             # <<<<<<<<<<<<<<
 * 		elif a is "@":
 * 			# Replace "@" with "<" and set the ws2 flag.
 */
      __pyx_v_ws = 1;
      goto __pyx_L5;
    }

    /* "parser.py":69
 * 			buffer.append("<")
 * 			ws = True
 * 		elif a is "@":             # <<<<<<<<<<<<<<
 * 			# Replace "@" with "<" and set the ws2 flag.
 * 			buffer.append("<")
 */
    __pyx_t_8 = (__pyx_v_a == __pyx_kp_s__8);
    __pyx_t_7 = (__pyx_t_8 != 0);
    if (__pyx_t_7) {

      /* "parser.py":71
 * 		elif a is "@":
 * 			# Replace "@" with "<" and set the ws2 flag.
 * 			buffer.append("<")             # <<<<<<<<<<<<<<
 * 			ws2 = True
 * 		elif ws and match("\s", a):
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__7); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":72
 * 			# Replace "@" with "<" and set the ws2 flag.
 * 			buffer.append("<")
 * 			ws2 = True             # <<<<<<<<<<<<<<
 * 		elif ws and match("\s", a):
 * 			# The space after a $tag should actually be a ">".
 */
      __pyx_v_ws2 = 1;
      goto __pyx_L5;
    }

    /* "parser.py":73
 * 			buffer.append("<")
 * 			ws2 = True
 * 		elif ws and match("\s", a):             # <<<<<<<<<<<<<<
 * 			# The space after a $tag should actually be a ">".
 * 			# ($div should be <div>)
 */
    __pyx_t_8 = (__pyx_v_ws != 0);
    if (__pyx_t_8) {
    } else {
      __pyx_t_7 = __pyx_t_8;
      goto __pyx_L6_bool_binop_done;
    }
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_match); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_9 = NULL;
    __pyx_t_10 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_10 = 1;
      }
    }
    __pyx_t_11 = PyTuple_New(2+__pyx_t_10); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_11);
    if (__pyx_t_9) {
      PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_9); __Pyx_GIVEREF(__pyx_t_9); __pyx_t_9 = NULL;
    }
    __Pyx_INCREF(__pyx_kp_s_s);
    PyTuple_SET_ITEM(__pyx_t_11, 0+__pyx_t_10, __pyx_kp_s_s);
    __Pyx_GIVEREF(__pyx_kp_s_s);
    __Pyx_INCREF(__pyx_v_a);
    PyTuple_SET_ITEM(__pyx_t_11, 1+__pyx_t_10, __pyx_v_a);
    __Pyx_GIVEREF(__pyx_v_a);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_11, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_7 = __pyx_t_8;
    __pyx_L6_bool_binop_done:;
    if (__pyx_t_7) {

      /* "parser.py":76
 * 			# The space after a $tag should actually be a ">".
 * 			# ($div should be <div>)
 * 			buffer.append(">")             # <<<<<<<<<<<<<<
 * 			open.append(tokens)
 * 			ws = False
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__9); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 76; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":77
 * 			# ($div should be <div>)
 * 			buffer.append(">")
 * 			open.append(tokens)             # <<<<<<<<<<<<<<
 * 			ws = False
 * 			tokens = ""
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_open, __pyx_v_tokens); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 77; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":78
 * 			buffer.append(">")
 * 			open.append(tokens)
 * 			ws = False             # <<<<<<<<<<<<<<
 * 			tokens = ""
 * 		elif ws2 and iq and match("\s", a):
 */
      __pyx_v_ws = 0;

      /* "parser.py":79
 * 			open.append(tokens)
 * 			ws = False
 * 			tokens = ""             # <<<<<<<<<<<<<<
 * 		elif ws2 and iq and match("\s", a):
 * 			# The space between an @tag and its value should actually be a ">".
 */
      __Pyx_INCREF(__pyx_kp_s__5);
      __Pyx_DECREF_SET(__pyx_v_tokens, __pyx_kp_s__5);
      goto __pyx_L5;
    }

    /* "parser.py":80
 * 			ws = False
 * 			tokens = ""
 * 		elif ws2 and iq and match("\s", a):             # <<<<<<<<<<<<<<
 * 			# The space between an @tag and its value should actually be a ">".
 * 			# (@h1 "Hi" should be <h1>Hi</h1>)
 */
    __pyx_t_8 = (__pyx_v_ws2 != 0);
    if (__pyx_t_8) {
    } else {
      __pyx_t_7 = __pyx_t_8;
      goto __pyx_L8_bool_binop_done;
    }
    __pyx_t_8 = (__pyx_v_iq != 0);
    if (__pyx_t_8) {
    } else {
      __pyx_t_7 = __pyx_t_8;
      goto __pyx_L8_bool_binop_done;
    }
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_match); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 80; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_11 = NULL;
    __pyx_t_10 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_11)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_11);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_10 = 1;
      }
    }
    __pyx_t_9 = PyTuple_New(2+__pyx_t_10); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 80; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_11) {
      PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_11); __Pyx_GIVEREF(__pyx_t_11); __pyx_t_11 = NULL;
    }
    __Pyx_INCREF(__pyx_kp_s_s);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_10, __pyx_kp_s_s);
    __Pyx_GIVEREF(__pyx_kp_s_s);
    __Pyx_INCREF(__pyx_v_a);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_10, __pyx_v_a);
    __Pyx_GIVEREF(__pyx_v_a);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 80; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 80; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_7 = __pyx_t_8;
    __pyx_L8_bool_binop_done:;
    if (__pyx_t_7) {

      /* "parser.py":83
 * 			# The space between an @tag and its value should actually be a ">".
 * 			# (@h1 "Hi" should be <h1>Hi</h1>)
 * 			buffer.append(">")             # <<<<<<<<<<<<<<
 * 			ws2 = False
 * 		elif a is "(":
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__9); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 83; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":84
 * 			# (@h1 "Hi" should be <h1>Hi</h1>)
 * 			buffer.append(">")
 * 			ws2 = False             # <<<<<<<<<<<<<<
 * 		elif a is "(":
 * 			# From now until we see a "(", everything is an attribute.
 */
      __pyx_v_ws2 = 0;
      goto __pyx_L5;
    }

    /* "parser.py":85
 * 			buffer.append(">")
 * 			ws2 = False
 * 		elif a is "(":             # <<<<<<<<<<<<<<
 * 			# From now until we see a "(", everything is an attribute.
 * 			ac = True
 */
    __pyx_t_7 = (__pyx_v_a == __pyx_kp_s__10);
    __pyx_t_8 = (__pyx_t_7 != 0);
    if (__pyx_t_8) {

      /* "parser.py":87
 * 		elif a is "(":
 * 			# From now until we see a "(", everything is an attribute.
 * 			ac = True             # <<<<<<<<<<<<<<
 * 		elif ac:
 * 			z = len(buffer) - 1
 */
      __pyx_v_ac = 1;
      goto __pyx_L5;
    }

    /* "parser.py":88
 * 			# From now until we see a "(", everything is an attribute.
 * 			ac = True
 * 		elif ac:             # <<<<<<<<<<<<<<
 * 			z = len(buffer) - 1
 * 			# Replace the last ">" with the first character of the attribute
 */
    __pyx_t_8 = (__pyx_v_ac != 0);
    if (__pyx_t_8) {

      /* "parser.py":89
 * 			ac = True
 * 		elif ac:
 * 			z = len(buffer) - 1             # <<<<<<<<<<<<<<
 * 			# Replace the last ">" with the first character of the attribute
 * 			buffer[z] = a
 */
      __pyx_t_10 = PyList_GET_SIZE(__pyx_v_buffer); if (unlikely(__pyx_t_10 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_1 = PyInt_FromSsize_t((__pyx_t_10 - 1)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_v_z = __pyx_t_1;
      __pyx_t_1 = 0;

      /* "parser.py":91
 * 			z = len(buffer) - 1
 * 			# Replace the last ">" with the first character of the attribute
 * 			buffer[z] = a             # <<<<<<<<<<<<<<
 * 			# Insert a space between the tag name and the first attribute
 * 			buffer.insert(z, " ")
 */
      if (unlikely(PyObject_SetItem(__pyx_v_buffer, __pyx_v_z, __pyx_v_a) < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":93
 * 			buffer[z] = a
 * 			# Insert a space between the tag name and the first attribute
 * 			buffer.insert(z, " ")             # <<<<<<<<<<<<<<
 * 			ac = False
 * 			ac2 = True
 */
      __pyx_t_10 = __Pyx_PyIndex_AsSsize_t(__pyx_v_z); if (unlikely((__pyx_t_10 == (Py_ssize_t)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_2 = PyList_Insert(__pyx_v_buffer, __pyx_t_10, __pyx_kp_s__11); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":94
 * 			# Insert a space between the tag name and the first attribute
 * 			buffer.insert(z, " ")
 * 			ac = False             # <<<<<<<<<<<<<<
 * 			ac2 = True
 * 			del z			# Delete "z" to save memory
 */
      __pyx_v_ac = 0;

      /* "parser.py":95
 * 			buffer.insert(z, " ")
 * 			ac = False
 * 			ac2 = True             # <<<<<<<<<<<<<<
 * 			del z			# Delete "z" to save memory
 * 		elif match_quote(a):
 */
      __pyx_v_ac2 = 1;

      /* "parser.py":96
 * 			ac = False
 * 			ac2 = True
 * 			del z			# Delete "z" to save memory             # <<<<<<<<<<<<<<
 * 		elif match_quote(a):
 * 			if not iq:
 */
      __Pyx_DECREF(__pyx_v_z);
      __pyx_v_z = NULL;
      goto __pyx_L5;
    }

    /* "parser.py":97
 * 			ac2 = True
 * 			del z			# Delete "z" to save memory
 * 		elif match_quote(a):             # <<<<<<<<<<<<<<
 * 			if not iq:
 * 				# If we're not supposed to ignore quotes (read: we have a pair open),
 */
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_match_quote); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_9 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_9)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_9);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
      }
    }
    if (!__pyx_t_9) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_a); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_11);
      PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_9); __Pyx_GIVEREF(__pyx_t_9); __pyx_t_9 = NULL;
      __Pyx_INCREF(__pyx_v_a);
      PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_v_a);
      __Pyx_GIVEREF(__pyx_v_a);
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_11, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
    }
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    if (__pyx_t_8) {

      /* "parser.py":98
 * 			del z			# Delete "z" to save memory
 * 		elif match_quote(a):
 * 			if not iq:             # <<<<<<<<<<<<<<
 * 				# If we're not supposed to ignore quotes (read: we have a pair open),
 * 				# replace the next quote we find with a closing tag for the open @tag.
 */
      __pyx_t_8 = ((!(__pyx_v_iq != 0)) != 0);
      if (__pyx_t_8) {

        /* "parser.py":101
 * 				# If we're not supposed to ignore quotes (read: we have a pair open),
 * 				# replace the next quote we find with a closing tag for the open @tag.
 * 				buffer.append("</%s>" % tokens)             # <<<<<<<<<<<<<<
 * 				tokens = ""
 * 				ws2 = False
 */
        __pyx_t_1 = __Pyx_PyString_Format(__pyx_kp_s_s_2, __pyx_v_tokens); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 101; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_t_1); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 101; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

        /* "parser.py":102
 * 				# replace the next quote we find with a closing tag for the open @tag.
 * 				buffer.append("</%s>" % tokens)
 * 				tokens = ""             # <<<<<<<<<<<<<<
 * 				ws2 = False
 * 			iq = not iq				# Toggle the flag to ignore quotes
 */
        __Pyx_INCREF(__pyx_kp_s__5);
        __Pyx_DECREF_SET(__pyx_v_tokens, __pyx_kp_s__5);

        /* "parser.py":103
 * 				buffer.append("</%s>" % tokens)
 * 				tokens = ""
 * 				ws2 = False             # <<<<<<<<<<<<<<
 * 			iq = not iq				# Toggle the flag to ignore quotes
 * 		elif ac2 and a is ":":
 */
        __pyx_v_ws2 = 0;
        goto __pyx_L11;
      }
      __pyx_L11:;

      /* "parser.py":104
 * 				tokens = ""
 * 				ws2 = False
 * 			iq = not iq				# Toggle the flag to ignore quotes             # <<<<<<<<<<<<<<
 * 		elif ac2 and a is ":":
 * 			# In NML, attribute syntax is name: value. In HTML, it's name="value".
 */
      __pyx_v_iq = (!(__pyx_v_iq != 0));
      goto __pyx_L5;
    }

    /* "parser.py":105
 * 				ws2 = False
 * 			iq = not iq				# Toggle the flag to ignore quotes
 * 		elif ac2 and a is ":":             # <<<<<<<<<<<<<<
 * 			# In NML, attribute syntax is name: value. In HTML, it's name="value".
 * 			# So, replace the colon with '="' and ignore the next character (ONLY if it's a space!)
 */
    __pyx_t_7 = (__pyx_v_ac2 != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_8 = __pyx_t_7;
      goto __pyx_L12_bool_binop_done;
    }
    __pyx_t_7 = (__pyx_v_a == __pyx_kp_s__12);
    __pyx_t_12 = (__pyx_t_7 != 0);
    __pyx_t_8 = __pyx_t_12;
    __pyx_L12_bool_binop_done:;
    if (__pyx_t_8) {

      /* "parser.py":108
 * 			# In NML, attribute syntax is name: value. In HTML, it's name="value".
 * 			# So, replace the colon with '="' and ignore the next character (ONLY if it's a space!)
 * 			buffer.append('="')             # <<<<<<<<<<<<<<
 * 			cfs = True
 * 		elif cfs and match("\s", a):
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__13); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 108; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":109
 * 			# So, replace the colon with '="' and ignore the next character (ONLY if it's a space!)
 * 			buffer.append('="')
 * 			cfs = True             # <<<<<<<<<<<<<<
 * 		elif cfs and match("\s", a):
 * 			cfs = False
 */
      __pyx_v_cfs = 1;
      goto __pyx_L5;
    }

    /* "parser.py":110
 * 			buffer.append('="')
 * 			cfs = True
 * 		elif cfs and match("\s", a):             # <<<<<<<<<<<<<<
 * 			cfs = False
 * 		elif ac2 and a is "," and iq:
 */
    __pyx_t_12 = (__pyx_v_cfs != 0);
    if (__pyx_t_12) {
    } else {
      __pyx_t_8 = __pyx_t_12;
      goto __pyx_L14_bool_binop_done;
    }
    __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_match); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_11 = NULL;
    __pyx_t_10 = 0;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
      __pyx_t_11 = PyMethod_GET_SELF(__pyx_t_4);
      if (likely(__pyx_t_11)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
        __Pyx_INCREF(__pyx_t_11);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_4, function);
        __pyx_t_10 = 1;
      }
    }
    __pyx_t_9 = PyTuple_New(2+__pyx_t_10); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_9);
    if (__pyx_t_11) {
      PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_11); __Pyx_GIVEREF(__pyx_t_11); __pyx_t_11 = NULL;
    }
    __Pyx_INCREF(__pyx_kp_s_s);
    PyTuple_SET_ITEM(__pyx_t_9, 0+__pyx_t_10, __pyx_kp_s_s);
    __Pyx_GIVEREF(__pyx_kp_s_s);
    __Pyx_INCREF(__pyx_v_a);
    PyTuple_SET_ITEM(__pyx_t_9, 1+__pyx_t_10, __pyx_v_a);
    __Pyx_GIVEREF(__pyx_v_a);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_9, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_12 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_8 = __pyx_t_12;
    __pyx_L14_bool_binop_done:;
    if (__pyx_t_8) {

      /* "parser.py":111
 * 			cfs = True
 * 		elif cfs and match("\s", a):
 * 			cfs = False             # <<<<<<<<<<<<<<
 * 		elif ac2 and a is "," and iq:
 * 			# Commas separate attributes when there are two or more of them.
 */
      __pyx_v_cfs = 0;
      goto __pyx_L5;
    }

    /* "parser.py":112
 * 		elif cfs and match("\s", a):
 * 			cfs = False
 * 		elif ac2 and a is "," and iq:             # <<<<<<<<<<<<<<
 * 			# Commas separate attributes when there are two or more of them.
 * 			# So close the quotes if we're starting a new attribute.
 */
    __pyx_t_12 = (__pyx_v_ac2 != 0);
    if (__pyx_t_12) {
    } else {
      __pyx_t_8 = __pyx_t_12;
      goto __pyx_L16_bool_binop_done;
    }
    __pyx_t_12 = (__pyx_v_a == __pyx_kp_s__14);
    __pyx_t_7 = (__pyx_t_12 != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_8 = __pyx_t_7;
      goto __pyx_L16_bool_binop_done;
    }
    __pyx_t_7 = (__pyx_v_iq != 0);
    __pyx_t_8 = __pyx_t_7;
    __pyx_L16_bool_binop_done:;
    if (__pyx_t_8) {

      /* "parser.py":115
 * 			# Commas separate attributes when there are two or more of them.
 * 			# So close the quotes if we're starting a new attribute.
 * 			buffer.append('"')             # <<<<<<<<<<<<<<
 * 		elif ac2 and a is ")":
 * 			buffer.append('">')	# Close quotes for the last attribute when attributes are closed
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__2); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 115; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L5;
    }

    /* "parser.py":116
 * 			# So close the quotes if we're starting a new attribute.
 * 			buffer.append('"')
 * 		elif ac2 and a is ")":             # <<<<<<<<<<<<<<
 * 			buffer.append('">')	# Close quotes for the last attribute when attributes are closed
 * 		elif a is "%":
 */
    __pyx_t_7 = (__pyx_v_ac2 != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_8 = __pyx_t_7;
      goto __pyx_L19_bool_binop_done;
    }
    __pyx_t_7 = (__pyx_v_a == __pyx_kp_s__15);
    __pyx_t_12 = (__pyx_t_7 != 0);
    __pyx_t_8 = __pyx_t_12;
    __pyx_L19_bool_binop_done:;
    if (__pyx_t_8) {

      /* "parser.py":117
 * 			buffer.append('"')
 * 		elif ac2 and a is ")":
 * 			buffer.append('">')	# Close quotes for the last attribute when attributes are closed             # <<<<<<<<<<<<<<
 * 		elif a is "%":
 * 			buffer.append("</%s>" % open.pop())
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__16); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      goto __pyx_L5;
    }

    /* "parser.py":118
 * 		elif ac2 and a is ")":
 * 			buffer.append('">')	# Close quotes for the last attribute when attributes are closed
 * 		elif a is "%":             # <<<<<<<<<<<<<<
 * 			buffer.append("</%s>" % open.pop())
 * 		elif a is "#":
 */
    __pyx_t_8 = (__pyx_v_a == __pyx_kp_s__17);
    __pyx_t_12 = (__pyx_t_8 != 0);
    if (__pyx_t_12) {

      /* "parser.py":119
 * 			buffer.append('">')	# Close quotes for the last attribute when attributes are closed
 * 		elif a is "%":
 * 			buffer.append("</%s>" % open.pop())             # <<<<<<<<<<<<<<
 * 		elif a is "#":
 * 			# Replace a "#" with "<!--" (The start of an HTML comment)
 */
      __pyx_t_1 = __Pyx_PyList_Pop(__pyx_v_open); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_4 = __Pyx_PyString_Format(__pyx_kp_s_s_2, __pyx_t_1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_t_4); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      goto __pyx_L5;
    }

    /* "parser.py":120
 * 		elif a is "%":
 * 			buffer.append("</%s>" % open.pop())
 * 		elif a is "#":             # <<<<<<<<<<<<<<
 * 			# Replace a "#" with "<!--" (The start of an HTML comment)
 * 			# OR, if --comment-strip is specified, delete it
 */
    __pyx_t_12 = (__pyx_v_a == __pyx_kp_s__18);
    __pyx_t_8 = (__pyx_t_12 != 0);
    if (__pyx_t_8) {

      /* "parser.py":123
 * 			# Replace a "#" with "<!--" (The start of an HTML comment)
 * 			# OR, if --comment-strip is specified, delete it
 * 			buffer.append("<!--")             # <<<<<<<<<<<<<<
 * 			ce = True
 * 		elif ce and "\n" in a:
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__19); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":124
 * 			# OR, if --comment-strip is specified, delete it
 * 			buffer.append("<!--")
 * 			ce = True             # <<<<<<<<<<<<<<
 * 		elif ce and "\n" in a:
 * 			buffer.append("-->")
 */
      __pyx_v_ce = 1;
      goto __pyx_L5;
    }

    /* "parser.py":125
 * 			buffer.append("<!--")
 * 			ce = True
 * 		elif ce and "\n" in a:             # <<<<<<<<<<<<<<
 * 			buffer.append("-->")
 * 			ce = False
 */
    __pyx_t_12 = (__pyx_v_ce != 0);
    if (__pyx_t_12) {
    } else {
      __pyx_t_8 = __pyx_t_12;
      goto __pyx_L21_bool_binop_done;
    }
    __pyx_t_12 = (__Pyx_PySequence_Contains(__pyx_kp_s__3, __pyx_v_a, Py_EQ)); if (unlikely(__pyx_t_12 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_7 = (__pyx_t_12 != 0);
    __pyx_t_8 = __pyx_t_7;
    __pyx_L21_bool_binop_done:;
    if (__pyx_t_8) {

      /* "parser.py":126
 * 			ce = True
 * 		elif ce and "\n" in a:
 * 			buffer.append("-->")             # <<<<<<<<<<<<<<
 * 			ce = False
 * 		else:
 */
      __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_kp_s__20); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 126; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

      /* "parser.py":127
 * 		elif ce and "\n" in a:
 * 			buffer.append("-->")
 * 			ce = False             # <<<<<<<<<<<<<<
 * 		else:
 * 			# If the whitespace isn't marked as significant through the
 */
      __pyx_v_ce = 0;
      goto __pyx_L5;
    }
    /*else*/ {

      /* "parser.py":131
 * 			# If the whitespace isn't marked as significant through the
 * 			# use of the "ws" flag, don't add it to the buffer!
 * 			if not ws or not match("\s", a): buffer.append(a)             # <<<<<<<<<<<<<<
 * 		# Don't add "$" or "@" to the tag name, otherwise you'd get </$body> or </@h1>
 * 		if (ws or ws2) and a is not "$" and a is not "@": tokens += a
 */
      __pyx_t_7 = ((!(__pyx_v_ws != 0)) != 0);
      if (!__pyx_t_7) {
      } else {
        __pyx_t_8 = __pyx_t_7;
        goto __pyx_L24_bool_binop_done;
      }
      __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_match); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 131; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_9 = NULL;
      __pyx_t_10 = 0;
      if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_1))) {
        __pyx_t_9 = PyMethod_GET_SELF(__pyx_t_1);
        if (likely(__pyx_t_9)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
          __Pyx_INCREF(__pyx_t_9);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_1, function);
          __pyx_t_10 = 1;
        }
      }
      __pyx_t_11 = PyTuple_New(2+__pyx_t_10); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 131; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_11);
      if (__pyx_t_9) {
        PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_9); __Pyx_GIVEREF(__pyx_t_9); __pyx_t_9 = NULL;
      }
      __Pyx_INCREF(__pyx_kp_s_s);
      PyTuple_SET_ITEM(__pyx_t_11, 0+__pyx_t_10, __pyx_kp_s_s);
      __Pyx_GIVEREF(__pyx_kp_s_s);
      __Pyx_INCREF(__pyx_v_a);
      PyTuple_SET_ITEM(__pyx_t_11, 1+__pyx_t_10, __pyx_v_a);
      __Pyx_GIVEREF(__pyx_v_a);
      __pyx_t_4 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_11, NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 131; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_7 = __Pyx_PyObject_IsTrue(__pyx_t_4); if (unlikely(__pyx_t_7 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 131; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
      __pyx_t_12 = ((!__pyx_t_7) != 0);
      __pyx_t_8 = __pyx_t_12;
      __pyx_L24_bool_binop_done:;
      if (__pyx_t_8) {
        __pyx_t_2 = __Pyx_PyList_Append(__pyx_v_buffer, __pyx_v_a); if (unlikely(__pyx_t_2 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 131; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        goto __pyx_L23;
      }
      __pyx_L23:;
    }
    __pyx_L5:;

    /* "parser.py":133
 * 			if not ws or not match("\s", a): buffer.append(a)
 * 		# Don't add "$" or "@" to the tag name, otherwise you'd get </$body> or </@h1>
 * 		if (ws or ws2) and a is not "$" and a is not "@": tokens += a             # <<<<<<<<<<<<<<
 * 	return (minify(buffer) + "</html>")		# Make "buffer" a string and close the "html" tag from the beginning
 * 	file.close()
 */
    __pyx_t_12 = (__pyx_v_ws != 0);
    if (!__pyx_t_12) {
    } else {
      goto __pyx_L28_next_and;
    }
    __pyx_t_12 = (__pyx_v_ws2 != 0);
    if (__pyx_t_12) {
    } else {
      __pyx_t_8 = __pyx_t_12;
      goto __pyx_L27_bool_binop_done;
    }
    __pyx_L28_next_and:;
    __pyx_t_12 = (__pyx_v_a != __pyx_kp_s__6);
    __pyx_t_7 = (__pyx_t_12 != 0);
    if (__pyx_t_7) {
    } else {
      __pyx_t_8 = __pyx_t_7;
      goto __pyx_L27_bool_binop_done;
    }
    __pyx_t_7 = (__pyx_v_a != __pyx_kp_s__8);
    __pyx_t_12 = (__pyx_t_7 != 0);
    __pyx_t_8 = __pyx_t_12;
    __pyx_L27_bool_binop_done:;
    if (__pyx_t_8) {
      __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_v_tokens, __pyx_v_a); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 133; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_4);
      __Pyx_DECREF_SET(__pyx_v_tokens, __pyx_t_4);
      __pyx_t_4 = 0;
      goto __pyx_L26;
    }
    __pyx_L26:;

    /* "parser.py":64
 * 	css = False
 * 	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!
 * 	for a in file.read():             # <<<<<<<<<<<<<<
 * 		if a is "$":
 * 			# Replace "$" with "<" and set the ws flag.
 */
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "parser.py":134
 * 		# Don't add "$" or "@" to the tag name, otherwise you'd get </$body> or </@h1>
 * 		if (ws or ws2) and a is not "$" and a is not "@": tokens += a
 * 	return (minify(buffer) + "</html>")		# Make "buffer" a string and close the "html" tag from the beginning             # <<<<<<<<<<<<<<
 * 	file.close()
 * 
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_4 = __Pyx_GetModuleGlobalName(__pyx_n_s_minify); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_1 = NULL;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_4))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_4);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_4);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_4, function);
    }
  }
  if (!__pyx_t_1) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_4, __pyx_v_buffer); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
  } else {
    __pyx_t_11 = PyTuple_New(1+1); if (unlikely(!__pyx_t_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_11);
    PyTuple_SET_ITEM(__pyx_t_11, 0, __pyx_t_1); __Pyx_GIVEREF(__pyx_t_1); __pyx_t_1 = NULL;
    __Pyx_INCREF(__pyx_v_buffer);
    PyTuple_SET_ITEM(__pyx_t_11, 0+1, __pyx_v_buffer);
    __Pyx_GIVEREF(__pyx_v_buffer);
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_4, __pyx_t_11, NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyNumber_Add(__pyx_t_3, __pyx_kp_s_html); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_r = __pyx_t_4;
  __pyx_t_4 = 0;
  goto __pyx_L0;

  /* "parser.py":42
 * # It takes one argument, which is a file object. For some reason, passing argv[1]
 * # as the file name caused an error.
 * def parse_nml(file):             # <<<<<<<<<<<<<<
 * 	tokens = str()
 * 	# "buffer" is, predictably, the buffer that actually holds the output. It's
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_11);
  __Pyx_AddTraceback("parser.parse_nml", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_tokens);
  __Pyx_XDECREF(__pyx_v_buffer);
  __Pyx_XDECREF(__pyx_v_open);
  __Pyx_XDECREF(__pyx_v_a);
  __Pyx_XDECREF(__pyx_v_z);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    "parser",
    0, /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_kp_s_, __pyx_k_, sizeof(__pyx_k_), 0, 0, 1, 0},
  {&__pyx_kp_s_1mUsage_0m_s_file, __pyx_k_1mUsage_0m_s_file, sizeof(__pyx_k_1mUsage_0m_s_file), 0, 0, 1, 0},
  {&__pyx_kp_s_DOCTYPE_html_html, __pyx_k_DOCTYPE_html_html, sizeof(__pyx_k_DOCTYPE_html_html), 0, 0, 1, 0},
  {&__pyx_kp_s_Users_nsandman09_Documents_code, __pyx_k_Users_nsandman09_Documents_code, sizeof(__pyx_k_Users_nsandman09_Documents_code), 0, 0, 1, 0},
  {&__pyx_kp_s__10, __pyx_k__10, sizeof(__pyx_k__10), 0, 0, 1, 0},
  {&__pyx_kp_s__11, __pyx_k__11, sizeof(__pyx_k__11), 0, 0, 1, 0},
  {&__pyx_kp_s__12, __pyx_k__12, sizeof(__pyx_k__12), 0, 0, 1, 0},
  {&__pyx_kp_s__13, __pyx_k__13, sizeof(__pyx_k__13), 0, 0, 1, 0},
  {&__pyx_kp_s__14, __pyx_k__14, sizeof(__pyx_k__14), 0, 0, 1, 0},
  {&__pyx_kp_s__15, __pyx_k__15, sizeof(__pyx_k__15), 0, 0, 1, 0},
  {&__pyx_kp_s__16, __pyx_k__16, sizeof(__pyx_k__16), 0, 0, 1, 0},
  {&__pyx_kp_s__17, __pyx_k__17, sizeof(__pyx_k__17), 0, 0, 1, 0},
  {&__pyx_kp_s__18, __pyx_k__18, sizeof(__pyx_k__18), 0, 0, 1, 0},
  {&__pyx_kp_s__19, __pyx_k__19, sizeof(__pyx_k__19), 0, 0, 1, 0},
  {&__pyx_kp_s__2, __pyx_k__2, sizeof(__pyx_k__2), 0, 0, 1, 0},
  {&__pyx_kp_s__20, __pyx_k__20, sizeof(__pyx_k__20), 0, 0, 1, 0},
  {&__pyx_kp_s__3, __pyx_k__3, sizeof(__pyx_k__3), 0, 0, 1, 0},
  {&__pyx_kp_s__4, __pyx_k__4, sizeof(__pyx_k__4), 0, 0, 1, 0},
  {&__pyx_kp_s__5, __pyx_k__5, sizeof(__pyx_k__5), 0, 0, 1, 0},
  {&__pyx_kp_s__6, __pyx_k__6, sizeof(__pyx_k__6), 0, 0, 1, 0},
  {&__pyx_kp_s__7, __pyx_k__7, sizeof(__pyx_k__7), 0, 0, 1, 0},
  {&__pyx_kp_s__8, __pyx_k__8, sizeof(__pyx_k__8), 0, 0, 1, 0},
  {&__pyx_kp_s__9, __pyx_k__9, sizeof(__pyx_k__9), 0, 0, 1, 0},
  {&__pyx_n_s_a, __pyx_k_a, sizeof(__pyx_k_a), 0, 0, 1, 1},
  {&__pyx_n_s_ac, __pyx_k_ac, sizeof(__pyx_k_ac), 0, 0, 1, 1},
  {&__pyx_n_s_ac2, __pyx_k_ac2, sizeof(__pyx_k_ac2), 0, 0, 1, 1},
  {&__pyx_n_s_argc, __pyx_k_argc, sizeof(__pyx_k_argc), 0, 0, 1, 1},
  {&__pyx_n_s_argv, __pyx_k_argv, sizeof(__pyx_k_argv), 0, 0, 1, 1},
  {&__pyx_n_s_b, __pyx_k_b, sizeof(__pyx_k_b), 0, 0, 1, 1},
  {&__pyx_n_s_body, __pyx_k_body, sizeof(__pyx_k_body), 0, 0, 1, 1},
  {&__pyx_n_s_buffer, __pyx_k_buffer, sizeof(__pyx_k_buffer), 0, 0, 1, 1},
  {&__pyx_n_s_ce, __pyx_k_ce, sizeof(__pyx_k_ce), 0, 0, 1, 1},
  {&__pyx_n_s_cfs, __pyx_k_cfs, sizeof(__pyx_k_cfs), 0, 0, 1, 1},
  {&__pyx_n_s_css, __pyx_k_css, sizeof(__pyx_k_css), 0, 0, 1, 1},
  {&__pyx_n_s_end, __pyx_k_end, sizeof(__pyx_k_end), 0, 0, 1, 1},
  {&__pyx_n_s_enumerate, __pyx_k_enumerate, sizeof(__pyx_k_enumerate), 0, 0, 1, 1},
  {&__pyx_n_s_file, __pyx_k_file, sizeof(__pyx_k_file), 0, 0, 1, 1},
  {&__pyx_n_s_head, __pyx_k_head, sizeof(__pyx_k_head), 0, 0, 1, 1},
  {&__pyx_kp_s_html, __pyx_k_html, sizeof(__pyx_k_html), 0, 0, 1, 0},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_iq, __pyx_k_iq, sizeof(__pyx_k_iq), 0, 0, 1, 1},
  {&__pyx_n_s_join, __pyx_k_join, sizeof(__pyx_k_join), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_match, __pyx_k_match, sizeof(__pyx_k_match), 0, 0, 1, 1},
  {&__pyx_n_s_match_quote, __pyx_k_match_quote, sizeof(__pyx_k_match_quote), 0, 0, 1, 1},
  {&__pyx_n_s_minify, __pyx_k_minify, sizeof(__pyx_k_minify), 0, 0, 1, 1},
  {&__pyx_n_s_open, __pyx_k_open, sizeof(__pyx_k_open), 0, 0, 1, 1},
  {&__pyx_n_s_parse_nml, __pyx_k_parse_nml, sizeof(__pyx_k_parse_nml), 0, 0, 1, 1},
  {&__pyx_n_s_parser, __pyx_k_parser, sizeof(__pyx_k_parser), 0, 0, 1, 1},
  {&__pyx_n_s_pop, __pyx_k_pop, sizeof(__pyx_k_pop), 0, 0, 1, 1},
  {&__pyx_n_s_print, __pyx_k_print, sizeof(__pyx_k_print), 0, 0, 1, 1},
  {&__pyx_n_s_r, __pyx_k_r, sizeof(__pyx_k_r), 0, 0, 1, 1},
  {&__pyx_n_s_re, __pyx_k_re, sizeof(__pyx_k_re), 0, 0, 1, 1},
  {&__pyx_n_s_read, __pyx_k_read, sizeof(__pyx_k_read), 0, 0, 1, 1},
  {&__pyx_kp_s_s, __pyx_k_s, sizeof(__pyx_k_s), 0, 0, 1, 0},
  {&__pyx_kp_s_s_2, __pyx_k_s_2, sizeof(__pyx_k_s_2), 0, 0, 1, 0},
  {&__pyx_n_s_str, __pyx_k_str, sizeof(__pyx_k_str), 0, 0, 1, 1},
  {&__pyx_n_s_sys, __pyx_k_sys, sizeof(__pyx_k_sys), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_tokens, __pyx_k_tokens, sizeof(__pyx_k_tokens), 0, 0, 1, 1},
  {&__pyx_n_s_ws, __pyx_k_ws, sizeof(__pyx_k_ws), 0, 0, 1, 1},
  {&__pyx_n_s_ws2, __pyx_k_ws2, sizeof(__pyx_k_ws2), 0, 0, 1, 1},
  {&__pyx_n_s_x, __pyx_k_x, sizeof(__pyx_k_x), 0, 0, 1, 1},
  {&__pyx_n_s_z, __pyx_k_z, sizeof(__pyx_k_z), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_open = __Pyx_GetBuiltinName(__pyx_n_s_open); if (!__pyx_builtin_open) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_builtin_enumerate = __Pyx_GetBuiltinName(__pyx_n_s_enumerate); if (!__pyx_builtin_enumerate) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "parser.py":27
 * # than if a is '"' or a is "'" (especially since the second one looks
 * # kind of ugly)
 * def match_quote(str):             # <<<<<<<<<<<<<<
 * 	if str is "'" or str is '"':
 * 		return True
 */
  __pyx_tuple__21 = PyTuple_Pack(1, __pyx_n_s_str); if (unlikely(!__pyx_tuple__21)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_tuple__21);
  __Pyx_GIVEREF(__pyx_tuple__21);
  __pyx_codeobj__22 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__21, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_Users_nsandman09_Documents_code, __pyx_n_s_match_quote, 27, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__22)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  /* "parser.py":33
 * 		return False
 * 
 * def minify(x):             # <<<<<<<<<<<<<<
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):
 */
  __pyx_tuple__23 = PyTuple_Pack(3, __pyx_n_s_x, __pyx_n_s_a, __pyx_n_s_b); if (unlikely(!__pyx_tuple__23)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_tuple__23);
  __Pyx_GIVEREF(__pyx_tuple__23);
  __pyx_codeobj__24 = (PyObject*)__Pyx_PyCode_New(1, 0, 3, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__23, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_Users_nsandman09_Documents_code, __pyx_n_s_minify, 33, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__24)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}

  /* "parser.py":42
 * # It takes one argument, which is a file object. For some reason, passing argv[1]
 * # as the file name caused an error.
 * def parse_nml(file):             # <<<<<<<<<<<<<<
 * 	tokens = str()
 * 	# "buffer" is, predictably, the buffer that actually holds the output. It's
 */
  __pyx_tuple__25 = PyTuple_Pack(14, __pyx_n_s_file, __pyx_n_s_tokens, __pyx_n_s_buffer, __pyx_n_s_open, __pyx_n_s_ws, __pyx_n_s_ws2, __pyx_n_s_ac, __pyx_n_s_ac2, __pyx_n_s_cfs, __pyx_n_s_iq, __pyx_n_s_ce, __pyx_n_s_css, __pyx_n_s_a, __pyx_n_s_z); if (unlikely(!__pyx_tuple__25)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 42; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_tuple__25);
  __Pyx_GIVEREF(__pyx_tuple__25);
  __pyx_codeobj__26 = (PyObject*)__Pyx_PyCode_New(1, 0, 14, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__25, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_Users_nsandman09_Documents_code, __pyx_n_s_parse_nml, 42, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__26)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 42; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initparser(void); /*proto*/
PyMODINIT_FUNC initparser(void)
#else
PyMODINIT_FUNC PyInit_parser(void); /*proto*/
PyMODINIT_FUNC PyInit_parser(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  Py_ssize_t __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_parser(void)", 0);
  if ( __Pyx_check_binary_version() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #ifdef __Pyx_CyFunction_USED
  if (__Pyx_CyFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("parser", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  /*--- Initialize various global constants etc. ---*/
  if (unlikely(__Pyx_InitGlobals() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  if (__pyx_module_is_main_parser) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (!PyDict_GetItemString(modules, "parser")) {
      if (unlikely(PyDict_SetItemString(modules, "parser", __pyx_m) < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
  }
  #endif
  /*--- Builtin init code ---*/
  if (unlikely(__Pyx_InitCachedBuiltins() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  /*--- Constants init code ---*/
  if (unlikely(__Pyx_InitCachedConstants() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  /*--- Global init code ---*/
  /*--- Variable export code ---*/
  /*--- Function export code ---*/
  /*--- Type init code ---*/
  /*--- Type import code ---*/
  /*--- Variable import code ---*/
  /*--- Function import code ---*/
  /*--- Execution code ---*/

  /* "parser.py":19
 * # -n
 * 
 * from sys import argv             # <<<<<<<<<<<<<<
 * from re import match
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_argv);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_argv);
  __Pyx_GIVEREF(__pyx_n_s_argv);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_sys, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_argv); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_argv, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 19; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "parser.py":20
 * 
 * from sys import argv
 * from re import match             # <<<<<<<<<<<<<<
 * 
 * argc = len(argv)
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_match);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_match);
  __Pyx_GIVEREF(__pyx_n_s_match);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_re, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_match); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_match, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "parser.py":22
 * from re import match
 * 
 * argc = len(argv)             # <<<<<<<<<<<<<<
 * 
 * # Pretty self explanatory. I'd just rather type "if match_quote(a)"
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_argv); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = PyObject_Length(__pyx_t_1); if (unlikely(__pyx_t_3 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyInt_FromSsize_t(__pyx_t_3); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_argc, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "parser.py":27
 * # than if a is '"' or a is "'" (especially since the second one looks
 * # kind of ugly)
 * def match_quote(str):             # <<<<<<<<<<<<<<
 * 	if str is "'" or str is '"':
 * 		return True
 */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_6parser_1match_quote, 0, __pyx_n_s_match_quote, NULL, __pyx_n_s_parser, __pyx_d, ((PyObject *)__pyx_codeobj__22)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_match_quote, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "parser.py":33
 * 		return False
 * 
 * def minify(x):             # <<<<<<<<<<<<<<
 * 	# Delete unnecessary spaces in order to decrease file size (and memory used)
 * 	for (a, b) in enumerate(x):
 */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_6parser_3minify, 0, __pyx_n_s_minify, NULL, __pyx_n_s_parser, __pyx_d, ((PyObject *)__pyx_codeobj__24)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_minify, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 33; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "parser.py":42
 * # It takes one argument, which is a file object. For some reason, passing argv[1]
 * # as the file name caused an error.
 * def parse_nml(file):             # <<<<<<<<<<<<<<
 * 	tokens = str()
 * 	# "buffer" is, predictably, the buffer that actually holds the output. It's
 */
  __pyx_t_1 = __Pyx_CyFunction_NewEx(&__pyx_mdef_6parser_5parse_nml, 0, __pyx_n_s_parse_nml, NULL, __pyx_n_s_parser, __pyx_d, ((PyObject *)__pyx_codeobj__26)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 42; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_parse_nml, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 42; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "parser.py":137
 * 	file.close()
 * 
 * if argc is 2:             # <<<<<<<<<<<<<<
 * 	# If there's only one argument, print the parsed file to stdout.
 * 	print parse_nml(open(argv[1], "r"))
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_argc); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 137; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_4 = (__pyx_t_1 == __pyx_int_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_5 = (__pyx_t_4 != 0);
  if (__pyx_t_5) {

    /* "parser.py":139
 * if argc is 2:
 * 	# If there's only one argument, print the parsed file to stdout.
 * 	print parse_nml(open(argv[1], "r"))             # <<<<<<<<<<<<<<
 * else:
 * 	# Print the help message
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_parse_nml); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_argv); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_7 = __Pyx_GetItemInt(__pyx_t_6, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(__pyx_t_7 == NULL)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = PyTuple_New(2); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_7);
    __Pyx_GIVEREF(__pyx_t_7);
    __Pyx_INCREF(__pyx_n_s_r);
    PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_n_s_r);
    __Pyx_GIVEREF(__pyx_n_s_r);
    __pyx_t_7 = 0;
    __pyx_t_7 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_6, NULL); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = NULL;
    if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_6) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_7); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      __pyx_t_8 = PyTuple_New(1+1); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_8);
      PyTuple_SET_ITEM(__pyx_t_8, 0, __pyx_t_6); __Pyx_GIVEREF(__pyx_t_6); __pyx_t_6 = NULL;
      PyTuple_SET_ITEM(__pyx_t_8, 0+1, __pyx_t_7);
      __Pyx_GIVEREF(__pyx_t_7);
      __pyx_t_7 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_8, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (__Pyx_PrintOne(0, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    goto __pyx_L2;
  }
  /*else*/ {

    /* "parser.py":142
 * else:
 * 	# Print the help message
 * 	print "\033[1mUsage:\033[0m %s [file]" % argv[0]             # <<<<<<<<<<<<<<
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_argv); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(__pyx_t_2 == NULL)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyString_Format(__pyx_kp_s_1mUsage_0m_s_file, __pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (__Pyx_PrintOne(0, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __pyx_L2:;

  /* "parser.py":1
 * #!/usr/bin/env python             # <<<<<<<<<<<<<<
 * #coding=utf-8
 * 
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init parser", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init parser");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}

/* --- Runtime support code --- */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

#if !CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyBytes_Join(PyObject* sep, PyObject* values) {
    return PyObject_CallMethodObjArgs(sep, __pyx_n_s_join, values, NULL);
}
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg) {
    PyObject *self, *result;
    PyCFunction cfunc;
    cfunc = PyCFunction_GET_FUNCTION(func);
    self = PyCFunction_GET_SELF(func);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = cfunc(self, arg);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_New(1);
    if (unlikely(!args)) return NULL;
    Py_INCREF(arg);
    PyTuple_SET_ITEM(args, 0, arg);
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
            return __Pyx_PyObject_CallMethO(func, arg);
        }
    }
    return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject* args = PyTuple_Pack(1, arg);
    return (likely(args)) ? __Pyx_PyObject_Call(func, args, NULL) : NULL;
}
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func) {
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
            return __Pyx_PyObject_CallMethO(func, NULL);
        }
    }
    return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
    PyObject *result;
#if CYTHON_COMPILING_IN_CPYTHON
    result = PyDict_GetItem(__pyx_d, name);
    if (likely(result)) {
        Py_INCREF(result);
    } else {
#else
    result = PyObject_GetItem(__pyx_d, name);
    if (!result) {
        PyErr_Clear();
#endif
        result = __Pyx_GetBuiltinName(name);
    }
    return result;
}

static PyObject* __Pyx_PyObject_CallMethod0(PyObject* obj, PyObject* method_name) {
    PyObject *method, *result = NULL;
    method = __Pyx_PyObject_GetAttrStr(obj, method_name);
    if (unlikely(!method)) goto bad;
#if CYTHON_COMPILING_IN_CPYTHON
    if (likely(PyMethod_Check(method))) {
        PyObject *self = PyMethod_GET_SELF(method);
        if (likely(self)) {
            PyObject *function = PyMethod_GET_FUNCTION(method);
            result = __Pyx_PyObject_CallOneArg(function, self);
            Py_DECREF(method);
            return result;
        }
    }
#endif
    result = __Pyx_PyObject_CallNoArg(method);
    Py_DECREF(method);
bad:
    return result;
}

static CYTHON_INLINE PyObject* __Pyx__PyObject_Pop(PyObject* L) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (Py_TYPE(L) == &PySet_Type) {
        return PySet_Pop(L);
    }
#endif
    return __Pyx_PyObject_CallMethod0(L, __pyx_n_s_pop);
}
static CYTHON_INLINE PyObject* __Pyx_PyList_Pop(PyObject* L) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (likely(PyList_GET_SIZE(L) > (((PyListObject*)L)->allocated >> 1))) {
        Py_SIZE(L) -= 1;
        return PyList_GET_ITEM(L, PyList_GET_SIZE(L));
    }
#endif
    return __Pyx_PyObject_CallMethod0(L, __pyx_n_s_pop);
}

static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

static PyTypeObject* __Pyx_FetchCommonType(PyTypeObject* type) {
    PyObject* fake_module;
    PyTypeObject* cached_type = NULL;
    fake_module = PyImport_AddModule((char*) "_cython_" CYTHON_ABI);
    if (!fake_module) return NULL;
    Py_INCREF(fake_module);
    cached_type = (PyTypeObject*) PyObject_GetAttrString(fake_module, type->tp_name);
    if (cached_type) {
        if (!PyType_Check((PyObject*)cached_type)) {
            PyErr_Format(PyExc_TypeError,
                "Shared Cython type %.200s is not a type object",
                type->tp_name);
            goto bad;
        }
        if (cached_type->tp_basicsize != type->tp_basicsize) {
            PyErr_Format(PyExc_TypeError,
                "Shared Cython type %.200s has the wrong size, try recompiling",
                type->tp_name);
            goto bad;
        }
    } else {
        if (!PyErr_ExceptionMatches(PyExc_AttributeError)) goto bad;
        PyErr_Clear();
        if (PyType_Ready(type) < 0) goto bad;
        if (PyObject_SetAttrString(fake_module, type->tp_name, (PyObject*) type) < 0)
            goto bad;
        Py_INCREF(type);
        cached_type = type;
    }
done:
    Py_DECREF(fake_module);
    return cached_type;
bad:
    Py_XDECREF(cached_type);
    cached_type = NULL;
    goto done;
}

static PyObject *
__Pyx_CyFunction_get_doc(__pyx_CyFunctionObject *op, CYTHON_UNUSED void *closure)
{
    if (unlikely(op->func_doc == NULL)) {
        if (op->func.m_ml->ml_doc) {
#if PY_MAJOR_VERSION >= 3
            op->func_doc = PyUnicode_FromString(op->func.m_ml->ml_doc);
#else
            op->func_doc = PyString_FromString(op->func.m_ml->ml_doc);
#endif
            if (unlikely(op->func_doc == NULL))
                return NULL;
        } else {
            Py_INCREF(Py_None);
            return Py_None;
        }
    }
    Py_INCREF(op->func_doc);
    return op->func_doc;
}
static int
__Pyx_CyFunction_set_doc(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp = op->func_doc;
    if (value == NULL) {
        value = Py_None;
    }
    Py_INCREF(value);
    op->func_doc = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_name(__pyx_CyFunctionObject *op)
{
    if (unlikely(op->func_name == NULL)) {
#if PY_MAJOR_VERSION >= 3
        op->func_name = PyUnicode_InternFromString(op->func.m_ml->ml_name);
#else
        op->func_name = PyString_InternFromString(op->func.m_ml->ml_name);
#endif
        if (unlikely(op->func_name == NULL))
            return NULL;
    }
    Py_INCREF(op->func_name);
    return op->func_name;
}
static int
__Pyx_CyFunction_set_name(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (unlikely(value == NULL || !PyUnicode_Check(value))) {
#else
    if (unlikely(value == NULL || !PyString_Check(value))) {
#endif
        PyErr_SetString(PyExc_TypeError,
                        "__name__ must be set to a string object");
        return -1;
    }
    tmp = op->func_name;
    Py_INCREF(value);
    op->func_name = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_qualname(__pyx_CyFunctionObject *op)
{
    Py_INCREF(op->func_qualname);
    return op->func_qualname;
}
static int
__Pyx_CyFunction_set_qualname(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
#if PY_MAJOR_VERSION >= 3
    if (unlikely(value == NULL || !PyUnicode_Check(value))) {
#else
    if (unlikely(value == NULL || !PyString_Check(value))) {
#endif
        PyErr_SetString(PyExc_TypeError,
                        "__qualname__ must be set to a string object");
        return -1;
    }
    tmp = op->func_qualname;
    Py_INCREF(value);
    op->func_qualname = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_self(__pyx_CyFunctionObject *m, CYTHON_UNUSED void *closure)
{
    PyObject *self;
    self = m->func_closure;
    if (self == NULL)
        self = Py_None;
    Py_INCREF(self);
    return self;
}
static PyObject *
__Pyx_CyFunction_get_dict(__pyx_CyFunctionObject *op)
{
    if (unlikely(op->func_dict == NULL)) {
        op->func_dict = PyDict_New();
        if (unlikely(op->func_dict == NULL))
            return NULL;
    }
    Py_INCREF(op->func_dict);
    return op->func_dict;
}
static int
__Pyx_CyFunction_set_dict(__pyx_CyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;
    if (unlikely(value == NULL)) {
        PyErr_SetString(PyExc_TypeError,
               "function's dictionary may not be deleted");
        return -1;
    }
    if (unlikely(!PyDict_Check(value))) {
        PyErr_SetString(PyExc_TypeError,
               "setting function's dictionary to a non-dict");
        return -1;
    }
    tmp = op->func_dict;
    Py_INCREF(value);
    op->func_dict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_globals(__pyx_CyFunctionObject *op)
{
    Py_INCREF(op->func_globals);
    return op->func_globals;
}
static PyObject *
__Pyx_CyFunction_get_closure(CYTHON_UNUSED __pyx_CyFunctionObject *op)
{
    Py_INCREF(Py_None);
    return Py_None;
}
static PyObject *
__Pyx_CyFunction_get_code(__pyx_CyFunctionObject *op)
{
    PyObject* result = (op->func_code) ? op->func_code : Py_None;
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_init_defaults(__pyx_CyFunctionObject *op) {
    PyObject *res = op->defaults_getter((PyObject *) op);
    if (unlikely(!res))
        return -1;
    op->defaults_tuple = PyTuple_GET_ITEM(res, 0);
    Py_INCREF(op->defaults_tuple);
    op->defaults_kwdict = PyTuple_GET_ITEM(res, 1);
    Py_INCREF(op->defaults_kwdict);
    Py_DECREF(res);
    return 0;
}
static int
__Pyx_CyFunction_set_defaults(__pyx_CyFunctionObject *op, PyObject* value) {
    PyObject* tmp;
    if (!value) {
        value = Py_None;
    } else if (value != Py_None && !PyTuple_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__defaults__ must be set to a tuple object");
        return -1;
    }
    Py_INCREF(value);
    tmp = op->defaults_tuple;
    op->defaults_tuple = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_defaults(__pyx_CyFunctionObject *op) {
    PyObject* result = op->defaults_tuple;
    if (unlikely(!result)) {
        if (op->defaults_getter) {
            if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
            result = op->defaults_tuple;
        } else {
            result = Py_None;
        }
    }
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_set_kwdefaults(__pyx_CyFunctionObject *op, PyObject* value) {
    PyObject* tmp;
    if (!value) {
        value = Py_None;
    } else if (value != Py_None && !PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__kwdefaults__ must be set to a dict object");
        return -1;
    }
    Py_INCREF(value);
    tmp = op->defaults_kwdict;
    op->defaults_kwdict = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_kwdefaults(__pyx_CyFunctionObject *op) {
    PyObject* result = op->defaults_kwdict;
    if (unlikely(!result)) {
        if (op->defaults_getter) {
            if (__Pyx_CyFunction_init_defaults(op) < 0) return NULL;
            result = op->defaults_kwdict;
        } else {
            result = Py_None;
        }
    }
    Py_INCREF(result);
    return result;
}
static int
__Pyx_CyFunction_set_annotations(__pyx_CyFunctionObject *op, PyObject* value) {
    PyObject* tmp;
    if (!value || value == Py_None) {
        value = NULL;
    } else if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "__annotations__ must be set to a dict object");
        return -1;
    }
    Py_XINCREF(value);
    tmp = op->func_annotations;
    op->func_annotations = value;
    Py_XDECREF(tmp);
    return 0;
}
static PyObject *
__Pyx_CyFunction_get_annotations(__pyx_CyFunctionObject *op) {
    PyObject* result = op->func_annotations;
    if (unlikely(!result)) {
        result = PyDict_New();
        if (unlikely(!result)) return NULL;
        op->func_annotations = result;
    }
    Py_INCREF(result);
    return result;
}
static PyGetSetDef __pyx_CyFunction_getsets[] = {
    {(char *) "func_doc", (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "__doc__",  (getter)__Pyx_CyFunction_get_doc, (setter)__Pyx_CyFunction_set_doc, 0, 0},
    {(char *) "func_name", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__name__", (getter)__Pyx_CyFunction_get_name, (setter)__Pyx_CyFunction_set_name, 0, 0},
    {(char *) "__qualname__", (getter)__Pyx_CyFunction_get_qualname, (setter)__Pyx_CyFunction_set_qualname, 0, 0},
    {(char *) "__self__", (getter)__Pyx_CyFunction_get_self, 0, 0, 0},
    {(char *) "func_dict", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "__dict__", (getter)__Pyx_CyFunction_get_dict, (setter)__Pyx_CyFunction_set_dict, 0, 0},
    {(char *) "func_globals", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "__globals__", (getter)__Pyx_CyFunction_get_globals, 0, 0, 0},
    {(char *) "func_closure", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "__closure__", (getter)__Pyx_CyFunction_get_closure, 0, 0, 0},
    {(char *) "func_code", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "__code__", (getter)__Pyx_CyFunction_get_code, 0, 0, 0},
    {(char *) "func_defaults", (getter)__Pyx_CyFunction_get_defaults, (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *) "__defaults__", (getter)__Pyx_CyFunction_get_defaults, (setter)__Pyx_CyFunction_set_defaults, 0, 0},
    {(char *) "__kwdefaults__", (getter)__Pyx_CyFunction_get_kwdefaults, (setter)__Pyx_CyFunction_set_kwdefaults, 0, 0},
    {(char *) "__annotations__", (getter)__Pyx_CyFunction_get_annotations, (setter)__Pyx_CyFunction_set_annotations, 0, 0},
    {0, 0, 0, 0, 0}
};
static PyMemberDef __pyx_CyFunction_members[] = {
    {(char *) "__module__", T_OBJECT, offsetof(__pyx_CyFunctionObject, func.m_module), PY_WRITE_RESTRICTED, 0},
    {0, 0, 0,  0, 0}
};
static PyObject *
__Pyx_CyFunction_reduce(__pyx_CyFunctionObject *m, CYTHON_UNUSED PyObject *args)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromString(m->func.m_ml->ml_name);
#else
    return PyString_FromString(m->func.m_ml->ml_name);
#endif
}
static PyMethodDef __pyx_CyFunction_methods[] = {
    {"__reduce__", (PyCFunction)__Pyx_CyFunction_reduce, METH_VARARGS, 0},
    {0, 0, 0, 0}
};
#if PY_VERSION_HEX < 0x030500A0
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func_weakreflist)
#else
#define __Pyx_CyFunction_weakreflist(cyfunc) ((cyfunc)->func.m_weakreflist)
#endif
static PyObject *__Pyx_CyFunction_New(PyTypeObject *type, PyMethodDef *ml, int flags, PyObject* qualname,
                                      PyObject *closure, PyObject *module, PyObject* globals, PyObject* code) {
    __pyx_CyFunctionObject *op = PyObject_GC_New(__pyx_CyFunctionObject, type);
    if (op == NULL)
        return NULL;
    op->flags = flags;
    __Pyx_CyFunction_weakreflist(op) = NULL;
    op->func.m_ml = ml;
    op->func.m_self = (PyObject *) op;
    Py_XINCREF(closure);
    op->func_closure = closure;
    Py_XINCREF(module);
    op->func.m_module = module;
    op->func_dict = NULL;
    op->func_name = NULL;
    Py_INCREF(qualname);
    op->func_qualname = qualname;
    op->func_doc = NULL;
    op->func_classobj = NULL;
    op->func_globals = globals;
    Py_INCREF(op->func_globals);
    Py_XINCREF(code);
    op->func_code = code;
    op->defaults_pyobjects = 0;
    op->defaults = NULL;
    op->defaults_tuple = NULL;
    op->defaults_kwdict = NULL;
    op->defaults_getter = NULL;
    op->func_annotations = NULL;
    PyObject_GC_Track(op);
    return (PyObject *) op;
}
static int
__Pyx_CyFunction_clear(__pyx_CyFunctionObject *m)
{
    Py_CLEAR(m->func_closure);
    Py_CLEAR(m->func.m_module);
    Py_CLEAR(m->func_dict);
    Py_CLEAR(m->func_name);
    Py_CLEAR(m->func_qualname);
    Py_CLEAR(m->func_doc);
    Py_CLEAR(m->func_globals);
    Py_CLEAR(m->func_code);
    Py_CLEAR(m->func_classobj);
    Py_CLEAR(m->defaults_tuple);
    Py_CLEAR(m->defaults_kwdict);
    Py_CLEAR(m->func_annotations);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_XDECREF(pydefaults[i]);
        PyMem_Free(m->defaults);
        m->defaults = NULL;
    }
    return 0;
}
static void __Pyx_CyFunction_dealloc(__pyx_CyFunctionObject *m)
{
    PyObject_GC_UnTrack(m);
    if (__Pyx_CyFunction_weakreflist(m) != NULL)
        PyObject_ClearWeakRefs((PyObject *) m);
    __Pyx_CyFunction_clear(m);
    PyObject_GC_Del(m);
}
static int __Pyx_CyFunction_traverse(__pyx_CyFunctionObject *m, visitproc visit, void *arg)
{
    Py_VISIT(m->func_closure);
    Py_VISIT(m->func.m_module);
    Py_VISIT(m->func_dict);
    Py_VISIT(m->func_name);
    Py_VISIT(m->func_qualname);
    Py_VISIT(m->func_doc);
    Py_VISIT(m->func_globals);
    Py_VISIT(m->func_code);
    Py_VISIT(m->func_classobj);
    Py_VISIT(m->defaults_tuple);
    Py_VISIT(m->defaults_kwdict);
    if (m->defaults) {
        PyObject **pydefaults = __Pyx_CyFunction_Defaults(PyObject *, m);
        int i;
        for (i = 0; i < m->defaults_pyobjects; i++)
            Py_VISIT(pydefaults[i]);
    }
    return 0;
}
static PyObject *__Pyx_CyFunction_descr_get(PyObject *func, PyObject *obj, PyObject *type)
{
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    if (m->flags & __Pyx_CYFUNCTION_STATICMETHOD) {
        Py_INCREF(func);
        return func;
    }
    if (m->flags & __Pyx_CYFUNCTION_CLASSMETHOD) {
        if (type == NULL)
            type = (PyObject *)(Py_TYPE(obj));
        return __Pyx_PyMethod_New(func, type, (PyObject *)(Py_TYPE(type)));
    }
    if (obj == Py_None)
        obj = NULL;
    return __Pyx_PyMethod_New(func, obj, type);
}
static PyObject*
__Pyx_CyFunction_repr(__pyx_CyFunctionObject *op)
{
#if PY_MAJOR_VERSION >= 3
    return PyUnicode_FromFormat("<cyfunction %U at %p>",
                                op->func_qualname, (void *)op);
#else
    return PyString_FromFormat("<cyfunction %s at %p>",
                               PyString_AsString(op->func_qualname), (void *)op);
#endif
}
#if CYTHON_COMPILING_IN_PYPY
static PyObject * __Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyCFunctionObject* f = (PyCFunctionObject*)func;
    PyCFunction meth = PyCFunction_GET_FUNCTION(func);
    PyObject *self = PyCFunction_GET_SELF(func);
    Py_ssize_t size;
    switch (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST)) {
    case METH_VARARGS:
        if (likely(kw == NULL) || PyDict_Size(kw) == 0)
            return (*meth)(self, arg);
        break;
    case METH_VARARGS | METH_KEYWORDS:
        return (*(PyCFunctionWithKeywords)meth)(self, arg, kw);
    case METH_NOARGS:
        if (likely(kw == NULL) || PyDict_Size(kw) == 0) {
            size = PyTuple_GET_SIZE(arg);
            if (size == 0)
                return (*meth)(self, NULL);
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes no arguments (%" CYTHON_FORMAT_SSIZE_T "d given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    case METH_O:
        if (likely(kw == NULL) || PyDict_Size(kw) == 0) {
            size = PyTuple_GET_SIZE(arg);
            if (size == 1)
                return (*meth)(self, PyTuple_GET_ITEM(arg, 0));
            PyErr_Format(PyExc_TypeError,
                "%.200s() takes exactly one argument (%" CYTHON_FORMAT_SSIZE_T "d given)",
                f->m_ml->ml_name, size);
            return NULL;
        }
        break;
    default:
        PyErr_SetString(PyExc_SystemError, "Bad call flags in "
                        "__Pyx_CyFunction_Call. METH_OLDARGS is no "
                        "longer supported!");
        return NULL;
    }
    PyErr_Format(PyExc_TypeError, "%.200s() takes no keyword arguments",
                 f->m_ml->ml_name);
    return NULL;
}
#else
static PyObject * __Pyx_CyFunction_Call(PyObject *func, PyObject *arg, PyObject *kw) {
	return PyCFunction_Call(func, arg, kw);
}
#endif
static PyTypeObject __pyx_CyFunctionType_type = {
    PyVarObject_HEAD_INIT(0, 0)
    "cython_function_or_method",
    sizeof(__pyx_CyFunctionObject),
    0,
    (destructor) __Pyx_CyFunction_dealloc,
    0,
    0,
    0,
#if PY_MAJOR_VERSION < 3
    0,
#else
    0,
#endif
    (reprfunc) __Pyx_CyFunction_repr,
    0,
    0,
    0,
    0,
    __Pyx_CyFunction_Call,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
    0,
    (traverseproc) __Pyx_CyFunction_traverse,
    (inquiry) __Pyx_CyFunction_clear,
    0,
#if PY_VERSION_HEX < 0x030500A0
    offsetof(__pyx_CyFunctionObject, func_weakreflist),
#else
    offsetof(PyCFunctionObject, m_weakreflist),
#endif
    0,
    0,
    __pyx_CyFunction_methods,
    __pyx_CyFunction_members,
    __pyx_CyFunction_getsets,
    0,
    0,
    __Pyx_CyFunction_descr_get,
    0,
    offsetof(__pyx_CyFunctionObject, func_dict),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
#if PY_VERSION_HEX >= 0x030400a1
    0,
#endif
};
static int __Pyx_CyFunction_init(void) {
#if !CYTHON_COMPILING_IN_PYPY
    __pyx_CyFunctionType_type.tp_call = PyCFunction_Call;
#endif
    __pyx_CyFunctionType = __Pyx_FetchCommonType(&__pyx_CyFunctionType_type);
    if (__pyx_CyFunctionType == NULL) {
        return -1;
    }
    return 0;
}
static CYTHON_INLINE void *__Pyx_CyFunction_InitDefaults(PyObject *func, size_t size, int pyobjects) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults = PyMem_Malloc(size);
    if (!m->defaults)
        return PyErr_NoMemory();
    memset(m->defaults, 0, size);
    m->defaults_pyobjects = pyobjects;
    return m->defaults;
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsTuple(PyObject *func, PyObject *tuple) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_tuple = tuple;
    Py_INCREF(tuple);
}
static CYTHON_INLINE void __Pyx_CyFunction_SetDefaultsKwDict(PyObject *func, PyObject *dict) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->defaults_kwdict = dict;
    Py_INCREF(dict);
}
static CYTHON_INLINE void __Pyx_CyFunction_SetAnnotationsDict(PyObject *func, PyObject *dict) {
    __pyx_CyFunctionObject *m = (__pyx_CyFunctionObject *) func;
    m->func_annotations = dict;
    Py_INCREF(dict);
}

static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (wraparound & unlikely(i < 0)) i += PyList_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (wraparound & unlikely(i < 0)) i += PyTuple_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely((n >= 0) & (n < PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (PyErr_ExceptionMatches(PyExc_OverflowError))
                        PyErr_Clear();
                    else
                        return NULL;
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = (start + end) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, (size_t)new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        PyThreadState_GET(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        __pyx_d,      /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = py_line;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

#ifdef __FreeBSD__
#include <floatingpoint.h>
#endif
#if PY_MAJOR_VERSION < 3
int main(int argc, char** argv) {
#elif defined(WIN32) || defined(MS_WINDOWS)
int wmain(int argc, wchar_t **argv) {
#else
static int __Pyx_main(int argc, wchar_t **argv) {
#endif
    /* 754 requires that FP exceptions run in "no stop" mode by default,
     * and until C vendors implement C99's ways to control FP exceptions,
     * Python requires non-stop mode.  Alas, some platforms enable FP
     * exceptions by default.  Here we disable them.
     */
#ifdef __FreeBSD__
    fp_except_t m;
    m = fpgetmask();
    fpsetmask(m & ~FP_X_OFL);
#endif
    if (argc && argv)
        Py_SetProgramName(argv[0]);
    Py_Initialize();
    if (argc && argv)
        PySys_SetArgv(argc, argv);
    {
      PyObject* m = NULL;
      __pyx_module_is_main_parser = 1;
      #if PY_MAJOR_VERSION < 3
          initparser();
      #else
          m = PyInit_parser();
      #endif
      if (PyErr_Occurred()) {
          PyErr_Print();
          #if PY_MAJOR_VERSION < 3
          if (Py_FlushLine()) PyErr_Clear();
          #endif
          return 1;
      }
      Py_XDECREF(m);
    }
    Py_Finalize();
    return 0;
}
#if PY_MAJOR_VERSION >= 3 && !defined(WIN32) && !defined(MS_WINDOWS)
#include <locale.h>
static wchar_t*
__Pyx_char2wchar(char* arg)
{
    wchar_t *res;
#ifdef HAVE_BROKEN_MBSTOWCS
    /* Some platforms have a broken implementation of
     * mbstowcs which does not count the characters that
     * would result from conversion.  Use an upper bound.
     */
    size_t argsize = strlen(arg);
#else
    size_t argsize = mbstowcs(NULL, arg, 0);
#endif
    size_t count;
    unsigned char *in;
    wchar_t *out;
#ifdef HAVE_MBRTOWC
    mbstate_t mbs;
#endif
    if (argsize != (size_t)-1) {
        res = (wchar_t *)malloc((argsize+1)*sizeof(wchar_t));
        if (!res)
            goto oom;
        count = mbstowcs(res, arg, argsize+1);
        if (count != (size_t)-1) {
            wchar_t *tmp;
            /* Only use the result if it contains no
               surrogate characters. */
            for (tmp = res; *tmp != 0 &&
                     (*tmp < 0xd800 || *tmp > 0xdfff); tmp++)
                ;
            if (*tmp == 0)
                return res;
        }
        free(res);
    }
#ifdef HAVE_MBRTOWC
    /* Overallocate; as multi-byte characters are in the argument, the
       actual output could use less memory. */
    argsize = strlen(arg) + 1;
    res = (wchar_t *)malloc(argsize*sizeof(wchar_t));
    if (!res) goto oom;
    in = (unsigned char*)arg;
    out = res;
    memset(&mbs, 0, sizeof mbs);
    while (argsize) {
        size_t converted = mbrtowc(out, (char*)in, argsize, &mbs);
        if (converted == 0)
            break;
        if (converted == (size_t)-2) {
            /* Incomplete character. This should never happen,
               since we provide everything that we have -
               unless there is a bug in the C library, or I
               misunderstood how mbrtowc works. */
            fprintf(stderr, "unexpected mbrtowc result -2\\n");
            return NULL;
        }
        if (converted == (size_t)-1) {
            /* Conversion error. Escape as UTF-8b, and start over
               in the initial shift state. */
            *out++ = 0xdc00 + *in++;
            argsize--;
            memset(&mbs, 0, sizeof mbs);
            continue;
        }
        if (*out >= 0xd800 && *out <= 0xdfff) {
            /* Surrogate character.  Escape the original
               byte sequence with surrogateescape. */
            argsize -= converted;
            while (converted--)
                *out++ = 0xdc00 + *in++;
            continue;
        }
        in += converted;
        argsize -= converted;
        out++;
    }
#else
    /* Cannot use C locale for escaping; manually escape as if charset
       is ASCII (i.e. escape all bytes > 128. This will still roundtrip
       correctly in the locale's charset, which must be an ASCII superset. */
    res = (wchar_t *)malloc((strlen(arg)+1)*sizeof(wchar_t));
    if (!res) goto oom;
    in = (unsigned char*)arg;
    out = res;
    while(*in)
        if(*in < 128)
            *out++ = *in++;
        else
            *out++ = 0xdc00 + *in++;
    *out = 0;
#endif
    return res;
oom:
    fprintf(stderr, "out of memory\\n");
    return NULL;
}
int
main(int argc, char **argv)
{
    if (!argc) {
        return __Pyx_main(0, NULL);
    }
    else {
        wchar_t **argv_copy = (wchar_t **)malloc(sizeof(wchar_t*)*argc);
        wchar_t **argv_copy2 = (wchar_t **)malloc(sizeof(wchar_t*)*argc);
        int i, res;
        char *oldloc;
        if (!argv_copy || !argv_copy2) {
            fprintf(stderr, "out of memory\\n");
            return 1;
        }
        oldloc = strdup(setlocale(LC_ALL, NULL));
        setlocale(LC_ALL, "");
        for (i = 0; i < argc; i++) {
            argv_copy2[i] = argv_copy[i] = __Pyx_char2wchar(argv[i]);
            if (!argv_copy[i])
                return 1;
        }
        setlocale(LC_ALL, oldloc);
        free(oldloc);
        res = __Pyx_main(argc, argv_copy);
        for (i = 0; i < argc; i++) {
            free(argv_copy2[i]);
        }
        free(argv_copy);
        free(argv_copy2);
        return res;
    }
}
#endif

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_VERSION_HEX < 0x03030000
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                #if PY_VERSION_HEX < 0x03030000
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                #else
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                #endif
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_VERSION_HEX < 0x03030000
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_VERSION_HEX < 0x03030000
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
    const long neg_one = (long) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
        } else if (sizeof(long) <= sizeof(unsigned long long)) {
            return PyLong_FromUnsignedLongLong((unsigned long long) value);
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(long long)) {
            return PyLong_FromLongLong((long long) value);
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

#if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static PyObject *__Pyx_GetStdout(void) {
    PyObject *f = PySys_GetObject((char *)"stdout");
    if (!f) {
        PyErr_SetString(PyExc_RuntimeError, "lost sys.stdout");
    }
    return f;
}
static int __Pyx_Print(PyObject* f, PyObject *arg_tuple, int newline) {
    int i;
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    for (i=0; i < PyTuple_GET_SIZE(arg_tuple); i++) {
        PyObject* v;
        if (PyFile_SoftSpace(f, 1)) {
            if (PyFile_WriteString(" ", f) < 0)
                goto error;
        }
        v = PyTuple_GET_ITEM(arg_tuple, i);
        if (PyFile_WriteObject(v, f, Py_PRINT_RAW) < 0)
            goto error;
        if (PyString_Check(v)) {
            char *s = PyString_AsString(v);
            Py_ssize_t len = PyString_Size(v);
            if (len > 0) {
                switch (s[len-1]) {
                    case ' ': break;
                    case '\f': case '\r': case '\n': case '\t': case '\v':
                        PyFile_SoftSpace(f, 0);
                        break;
                    default:  break;
                }
            }
        }
    }
    if (newline) {
        if (PyFile_WriteString("\n", f) < 0)
            goto error;
        PyFile_SoftSpace(f, 0);
    }
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
}
#else
static int __Pyx_Print(PyObject* stream, PyObject *arg_tuple, int newline) {
    PyObject* kwargs = 0;
    PyObject* result = 0;
    PyObject* end_string;
    if (unlikely(!__pyx_print)) {
        __pyx_print = PyObject_GetAttr(__pyx_b, __pyx_n_s_print);
        if (!__pyx_print)
            return -1;
    }
    if (stream) {
        kwargs = PyDict_New();
        if (unlikely(!kwargs))
            return -1;
        if (unlikely(PyDict_SetItem(kwargs, __pyx_n_s_file, stream) < 0))
            goto bad;
        if (!newline) {
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                goto bad;
            if (PyDict_SetItem(kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                goto bad;
            }
            Py_DECREF(end_string);
        }
    } else if (!newline) {
        if (unlikely(!__pyx_print_kwargs)) {
            __pyx_print_kwargs = PyDict_New();
            if (unlikely(!__pyx_print_kwargs))
                return -1;
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                return -1;
            if (PyDict_SetItem(__pyx_print_kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                return -1;
            }
            Py_DECREF(end_string);
        }
        kwargs = __pyx_print_kwargs;
    }
    result = PyObject_Call(__pyx_print, arg_tuple, kwargs);
    if (unlikely(kwargs) && (kwargs != __pyx_print_kwargs))
        Py_DECREF(kwargs);
    if (!result)
        return -1;
    Py_DECREF(result);
    return 0;
bad:
    if (kwargs != __pyx_print_kwargs)
        Py_XDECREF(kwargs);
    return -1;
}
#endif

#if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static int __Pyx_PrintOne(PyObject* f, PyObject *o) {
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    if (PyFile_SoftSpace(f, 0)) {
        if (PyFile_WriteString(" ", f) < 0)
            goto error;
    }
    if (PyFile_WriteObject(o, f, Py_PRINT_RAW) < 0)
        goto error;
    if (PyFile_WriteString("\n", f) < 0)
        goto error;
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
    /* the line below is just to avoid C compiler
     * warnings about unused functions */
    return __Pyx_Print(f, NULL, 0);
}
#else
static int __Pyx_PrintOne(PyObject* stream, PyObject *o) {
    int res;
    PyObject* arg_tuple = PyTuple_Pack(1, o);
    if (unlikely(!arg_tuple))
        return -1;
    res = __Pyx_Print(stream, arg_tuple, 1);
    Py_DECREF(arg_tuple);
    return res;
}
#endif

#define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)       \
    {                                                                     \
        func_type value = func_value;                                     \
        if (sizeof(target_type) < sizeof(func_type)) {                    \
            if (unlikely(value != (func_type) (target_type) value)) {     \
                func_type zero = 0;                                       \
                if (is_unsigned && unlikely(value < zero))                \
                    goto raise_neg_overflow;                              \
                else                                                      \
                    goto raise_overflow;                                  \
            }                                                             \
        }                                                                 \
        return (target_type) value;                                       \
    }

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
 #endif
#endif

static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
    const long neg_one = (long) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(long, unsigned long, PyLong_AsUnsignedLong(x))
            } else if (sizeof(long) <= sizeof(unsigned long long)) {
                __PYX_VERIFY_RETURN_INT(long, unsigned long long, PyLong_AsUnsignedLongLong(x))
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +(((PyLongObject*)x)->ob_digit[0]));
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, -(sdigit) ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(long, long, PyLong_AsLong(x))
            } else if (sizeof(long) <= sizeof(long long)) {
                __PYX_VERIFY_RETURN_INT(long, long long, PyLong_AsLongLong(x))
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
    const int neg_one = (int) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(int, unsigned long, PyLong_AsUnsignedLong(x))
            } else if (sizeof(int) <= sizeof(unsigned long long)) {
                __PYX_VERIFY_RETURN_INT(int, unsigned long long, PyLong_AsUnsignedLongLong(x))
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +(((PyLongObject*)x)->ob_digit[0]));
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, -(sdigit) ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(int, long, PyLong_AsLong(x))
            } else if (sizeof(int) <= sizeof(long long)) {
                __PYX_VERIFY_RETURN_INT(int, long long, PyLong_AsLongLong(x))
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else
        if (__Pyx_PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else
        return PyUnicode_AsUTF8AndSize(o, length);
#endif
#endif
    } else
#endif
#if !CYTHON_COMPILING_IN_PYPY
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x) {
  PyNumberMethods *m;
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return Py_INCREF(x), x;
  m = Py_TYPE(x)->tp_as_number;
#if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b)))
      return PyInt_AS_LONG(b);
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
     #if CYTHON_USE_PYLONG_INTERNALS
       switch (Py_SIZE(b)) {
       case -1: return -(sdigit)((PyLongObject*)b)->ob_digit[0];
       case  0: return 0;
       case  1: return ((PyLongObject*)b)->ob_digit[0];
       }
     #endif
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif /* Py_PYTHON_H */
