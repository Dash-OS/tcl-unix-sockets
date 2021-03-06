#ifndef _TCLSTUFF_H
#define _TCLSTUFF_H

#include "tcl.h"

#define NEW_CMD( tcl_cmd, c_cmd ) \
	Tcl_CreateObjCommand( interp, tcl_cmd, \
			(Tcl_ObjCmdProc *) c_cmd, \
			(ClientData *) NULL, NULL );

#define THROW_ERROR( msg... )		\
	{								\
		Tcl_Obj		*res;			\
		res = Tcl_GetObjResult( interp ); \
		Tcl_AppendStringsToObj( res, msg, NULL ); \
		return TCL_ERROR;			\
	}

// convenience macro to check the number of arguments passed to a function
// implementing a tcl command against the number expected, and to throw
// a tcl error if they don't match.  Note that the value of expected does
// not include the objv[0] object (the function itself)
#define CHECK_ARGS(expected, msg)	\
	if (objc != expected + 1) {		\
		Tcl_Obj		*res;			\
		res = Tcl_GetObjResult( interp ); \
		Tcl_AppendStringsToObj( res, "Wrong # of arguments.  Must be \"", \
				msg, "\"", NULL );	\
		return TCL_ERROR;			\
	}


// A rather frivolous macro that just enhances readability for a common case
#ifdef DEBUG
#warning Using DEBUG version of TEST_OK
#define TEST_OK( cmd )		\
	if (cmd != TCL_OK) { \
		fprintf( stderr, "TEST_OK() returned TCL_ERROR\n" ); \
		return TCL_ERROR; \
	}
#else
#define TEST_OK( cmd )		\
	if (cmd != TCL_OK) return TCL_ERROR;
#endif


#endif
