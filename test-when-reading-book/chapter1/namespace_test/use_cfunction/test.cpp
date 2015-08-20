#include "wrapper.hpp"
#include <cstring>

int
main ()
{
	fun1();
	dxyan::fun1();

	/* like cstring, both cases are legals.
	 * But this is what C++ want, compile C programs withut change
	 */
	std::strcmp("abc", "aaa");
	strcmp("abc", "aaa");
	return 0;

}
