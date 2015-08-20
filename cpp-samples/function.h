#ifdef __cplusplus
# define EXTERNC extern "C"
#else /* !__cplusplus */
# define EXTERNC 
#endif /* !__cplusplus */

EXTERNC void test();
