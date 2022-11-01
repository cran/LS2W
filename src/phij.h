#ifndef ___PHIJ_H___
#define ___PHIJ_H___


void mkcoefIE(int *J, int BigJ, double *H, int *LengthH, double ***coefvec, int *lvec, double *tol, int *error);
void PhiJ_impl(int *J, double *H, int *LengthH, double *tol, double *wout, int *lwout, int *rlvec, int *error);
void PsiJonlyIE(int *J, double **coefvec, int *lvec, double *wout, int *lwout, int *error);
void IEwaverecons(double *C, double *D, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *start_level, int *type, int *bc, int *error);



#endif
