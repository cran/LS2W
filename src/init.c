

#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .C calls */
extern void PhiJ_impl(void *, void *, void *, void *, void *, void *, void *, void *);
extern void PsiJ_impl(void *, void *, void *, void *, void *, void *, void *, void *);
extern void rainmatPARENT(void *, void *, void *, void *, void *, void *);
extern void rainmatPARTIAL(void *, void *, void *, void *, void *, void *, void *);
extern void SAvBasis(void *, void *, void *, void *, void *, void *, void *, void *);
extern void StoIDS(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void StoIDSIE(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void StoIRS(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);

static const R_CMethodDef CEntries[] = {
    {"PhiJ_impl",      (DL_FUNC) &PhiJ_impl,       8},
    {"PsiJ_impl",      (DL_FUNC) &PsiJ_impl,       8},
    {"rainmatPARENT",  (DL_FUNC) &rainmatPARENT,   6},
    {"rainmatPARTIAL", (DL_FUNC) &rainmatPARTIAL,  7},
    {"SAvBasis",       (DL_FUNC) &SAvBasis,        8},
    {"StoIDS",         (DL_FUNC) &StoIDS,         18},
    {"StoIDSIE",       (DL_FUNC) &StoIDSIE,       19},
    {"StoIRS",         (DL_FUNC) &StoIRS,         16},
    {NULL, NULL, 0}
};

void R_init_LS2W(DllInfo *dll)
{
    R_registerRoutines(dll, CEntries, NULL, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

