#ifndef __WRAPPER_HPP__
#define __WRAPPER_HPP__

#ifdef __cplusplus
extern "C"
{
#endif

#include "c_functions.h"

/* 1. we put the functions in namespace.h to dxyan namespace
 * Note: we can not stop namespace_test.c use func1 directly.
 */
namespace dxyan
{
using ::fun1;
using ::fun2;
using ::fun3;
using ::fun4;
};

/**
 * It can not stop user use func1 directly, that is t say:
 * they are still in global namespace
 */
#undef func1
#undef func2
#undef func3
#undef func4

#ifdef __cplusplus
}
#endif

#endif	/* __WRAPPER_HPP__ */
