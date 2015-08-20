#ifndef USE_C_FUNCTION
#define USE_C_FUNCTION

/* include the extern in namespace */
namespace dxyan {
extern "C"
{
    #include "function.h"
}

//   using ::test;
}

#endif /* USE_C_FUNCTION */
