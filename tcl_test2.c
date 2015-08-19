#include <stdio.h>
#include <tcl8.6/tcl.h>
#include <tcl8.6/tclDecls.h>
#include <tcl8.6/tclPlatDecls.h>

int func(ClientData clientData,
             Tcl_Interp *interp,
             Tcl_Value *args,
             Tcl_Value *resultPtr) {

	printf("helloworld\n");
}

int main() {

	struct  Tcl_Interp * interp = Tcl_CreateInterp();
	int a = 10;
	Tcl_CreateMathFunc(interp, "hello", 0, NULL, func, &a);
	hello();
}
