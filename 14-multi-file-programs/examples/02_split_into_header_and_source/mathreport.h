// Header file: DECLARATIONS only. This is the "menu" of what
// mathreport.c offers -- no function bodies, just prototypes, plus the
// one constant every file that uses this module might need.
//
// Include guard: without this, including mathreport.h twice in the same
// .c file (directly once, and again indirectly through another header)
// would paste these declarations in twice and the compiler would choke
// on the duplicate. See examples/03_include_guards_demo/ for that
// failure happening on purpose.
#ifndef MATHREPORT_H
#define MATHREPORT_H

#define SEPARATOR_WIDTH 20

int square(int n);
int cube(int n);
void printSeparator(void);
void printReport(int n);

#endif
