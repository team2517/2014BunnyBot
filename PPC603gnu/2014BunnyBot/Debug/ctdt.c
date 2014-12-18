/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */


void _GLOBAL__I__Z8DeadBandf();

extern void (*_ctors[])();
void (*_ctors[])() =
    {
    _GLOBAL__I__Z8DeadBandf,
    0
    };

void _GLOBAL__D__Z8DeadBandf();

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    _GLOBAL__D__Z8DeadBandf,
    0
    };
