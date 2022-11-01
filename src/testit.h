#ifndef ___TESTIT_H___
#define ___TESTIT_H___


void ImageDecomposeStepIE(double *C, int Csize, int firstCin, double *H, int LengthH, int LengthCout, int firstCout, int lastCout, int LengthDout, int firstDout, int lastDout, double *cc_out, double *cd_out, double *dc_out, double *dd_out, int bc, int type, int *error, int stepfactor);
void StoIDSIE(double *C, int *Csize, int *firstCin, double *H, int *LengthH, int *LengthCout, int *firstCout, int *lastCout, int *LengthDout, int *firstDout, int *lastDout, double *ImCC, double *ImCD, double *ImDC, double *ImDD, int *bc, int *type, int *error, int *stepfactor);


#endif 
