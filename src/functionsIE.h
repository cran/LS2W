#ifndef ___FUNCTIONSIE_H___
#define ___FUNCTIONSIE_H___



struct complex  {
    double *realval;
    double *imagval;
    };



/* Error condition	*/
/*#define ERROR		(-1)*/
#define OK		(0)

/* For boundary condition handling */
#define PERIODIC        1
#define SYMMETRIC       2

/* For the type of wavelet decomposition */
#define WAVELET     1   /* The standard decomposition */
#define STATION     2   /* The stationary decomposition */

/* Threshold types */
#define HARD    1
#define SOFT    2

/*
 * ACCESSC handles negative accesses, as well as those that exceed the number
 * of elements
 */

#define ACCESS(image, size, i, j)       *(image + (i)*(size) + (j))
#define ACCESSC(c, firstC, lengthC, ix, bc) *(c+reflect(((ix)-(firstC)),(lengthC),(bc)))
#define ACCESSD(l, i)   *(Data + (*LengthData*(l)) + (i))
#define POINTD(l,i) (Data + (*LengthData*(l)) + (i))
#define POINTC(l,i) (Carray +(*LengthData*(l)) + (i))

/*
 * The next three are exclusively for the stationary wavelet packet algorithm
 * WPST
 */
#define NPKTS(level, nlev)  (1 << (2*(nlev-level)))
#define PKTLENGTH(level)    (1 << level)

#define ACCWPST(a, level, avixstart, pkix, i) *((a) + *(avixstart+(level))+(pkix)*PKTLENGTH(level)+i)

/* Optimiser parameters */

#define R   0.61803399  /* The golden ratio for bisection searches */
#define Cons    (1.0-R)     /* For bisection searches          */

/* These next 3 are for the ipndacw code */
#define ACCESSW(w,j,k)  *(*(w+j)+k)
#define max(a,b)        ((a) > (b) ? (a) : (b))
#define min(a,b)        ((a) > (b) ? (b) : (a))

/*
 * The next 5 are for the swt2d code
 */
 

#define ACCESS3D(ar, d1, d12, ix1, ix2, ix3)    *(ar + (ix3)*(d12)+ (ix2)*(d1)+(ix1))

#define TYPES   0
#define TYPEH   1
#define TYPEV   2
#define TYPED   3



#define Nmax 8

typedef struct {
int Length;
double H[2 * Nmax];
double G[2 * Nmax];
double HLeft[Nmax][3 * Nmax - 1];
double GLeft[Nmax][3 * Nmax - 1];
double HRight[Nmax][3 * Nmax - 1];
double GRight[Nmax][3 * Nmax - 1];
double PreLeft[Nmax][Nmax];
double PreInvLeft[Nmax][Nmax];
double PreRight[Nmax][Nmax];
double PreInvRight[Nmax][Nmax];
} Filter;



/* The following was in Fryzlewicz's ``WavInt.h'' */

#define NORMAL 0
#define INVERSE 1

#define NO_PRECOND 0
#define PRECOND 1







/* sigmastruct describes a covariance matrix of size n. diag is an n-vector
   of pointers to double vectors that correspond to the diagonals of the
   matrix. If diag[i]==NULL, then the i-th diagonal is empty. This
   representation is useful for covariance matrices with a band structure. */

struct sigmastruct 
          {
          int n;
          double **diag;
          };


/* functionsIE.c */
void CWaveletCV(double *noisy, int *nnoisy, double *UniversalThresh, double *C, double *D, int *LengthD, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *ntt, int *ll, int *bc, double *tol, double *xvthresh, int *interptype, int *error);
void Call_Crsswav(double *noisy, int *nnoisy, double *value, double *C, double *D, int *LengthD, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *ntt, int *ll, int *bc, double *ssq, int *interptype, int *error);
void Crsswav(double *noisy, int *nnoisy, double *value, double *C, double *D, int *LengthD, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *ntt, int *ll, int *bc, double *ssq, int *error);
void Crsswav2(double *noisy, int *nnoisy, double *value, double *C, double *D, int *LengthD, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *ntt, int *ll, int *bc, double *ssq, int *error);
void Cthreshold(double *D, int *LengthD, int *firstD, int *lastD, int *offsetD, int *Dlevels, int *ntt, double *value, int *levels, int *qlevels, int *bc, int *error);
double SoftThreshold(double cough, double threshold);
void EstWitRem(double *ynoise, int *Lynoise, int *removed, double *thresh, double *H, int *LengthH, int *ntt, int *ll, double *answer, int *error);
int LargerPowerOfTwo(int n);
void FullWaveletCV(double *noisy, int *nnoisy, double *UniversalThresh, double *H, int *LengthH, int *ntt, int *ll, double *tol, double *xvthresh, int *error);
void GetRSS(double *ynoise, int *Lynoise, double *thresh, double *H, int *LengthH, int *ntt, int *ll, double *rss, int *smallestRSSindex, int *verbose, int *error);
void ImageDecomposeStep(double *C, int Csize, int firstCin, double *H, int LengthH, int LengthCout, int firstCout, int lastCout, int LengthDout, int firstDout, int lastDout, double *cc_out, double *cd_out, double *dc_out, double *dd_out, int bc, int type, int *error);
void StoIDS(double *C, int *Csize, int *firstCin, double *H, int *LengthH, int *LengthCout, int *firstCout, int *lastCout, int *LengthDout, int *firstDout, int *lastDout, double *ImCC, double *ImCD, double *ImDC, double *ImDD, int *bc, int *type, int *error);
void StoIRS(double *ImCC, double *ImCD, double *ImDC, double *ImDD, int *LengthCin, int *firstCin, int *LengthDin, int *firstDin, double *H, int *LengthH, int *LengthCout, int *firstCout, int *lastCout, double *ImOut, int *bc, int *error);
void ImageReconstructStep(double *ImCC, double *ImCD, double *ImDC, double *ImDD, int LengthCin, int firstCin, int LengthDin, int firstDin, double *H, int LengthH, int LengthCout, int firstCout, int lastCout, double *ImOut, int *bc, int *error);
double *av_basis(double *wst, double *wstC, int nlevels, int level, int ix1, int ix2, double *H, int LengthH, int *error);
double *getpacket(double *wst, int nlevels, int level, int index, int *error);
void av_basisWRAP(double *wst, double *wstC, int *LengthData, int *level, double *H, int *LengthH, double *answer, int *error);
void conbar(double *c_in, int LengthCin, int firstCin, double *d_in, int LengthDin, int firstDin, double *H, int LengthH, double *c_out, int LengthCout, int firstCout, int lastCout, int type, int bc);
void conbarL(double *c_in, int *LengthCin, int *firstCin, double *d_in, int *LengthDin, int *firstDin, double *H, int *LengthH, double *c_out, int *LengthCout, int *firstCout, int *lastCout, int *type, int *bc);
void convolveC(double *c_in, int LengthCin, int firstCin, double *H, int LengthH, double *c_out, int firstCout, int lastCout, int type, int step_factor, int bc);
void convolveD(double *c_in, int LengthCin, int firstCin, double *H, int LengthH, double *d_out, int firstDout, int lastDout, int type, int step_factor, int bc);
int reflect(int n, int lengthC, int bc);
void rotater(double *book, int length);
void rotateback(double *book, int length);
void simpleWT(double *TheData, int *ndata, double *H, int *LengthH, double *C, int *LengthC, double *D, int *LengthD, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *type, int *bc, int *error);
void wavedecomp(double *C, double *D, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *type, int *bc, int *error);
void accessDwp(double *Data, int *LengthData, int *nlevels, int *level, double *answer, int *error);
void wavepackde(double *Data, int *LengthData, int *levels, double *H, int *LengthH);
void wvpkr(double *Data, int startin, int lengthin, int outstart1, int outstart2, int level, double *H, int LengthH, int *LengthData);
void wavepackrecon(double *rdata, int *ldata, int *nrsteps, int *rvector, double *H, int *LengthH, int *error);
void wavepackst(double *Carray, double *Data, int *LengthData, int *levels, double *H, int *LengthH, int *error);
void wvpkstr(double *Carray, double *Data, int startin, int lengthin, int outstart1, int outstart2, int level, double *H, int LengthH, int *LengthData, double *book, int *error);
void waverecons(double *C, double *D, double *H, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *type, int *bc, int *error);
void comadd(double a, double b, double c, double d, double *e, double *f);
void comsub(double a, double b, double c, double d, double *e, double *f);
void commul(double a, double b, double c, double d, double *e, double *f);
void comdiv(double a, double b, double c, double d, double *e, double *f);
void comcbr(double *c_inR, double *c_inI, int LengthCin, int firstCin, int lastCin, double *d_inR, double *d_inI, int LengthDin, int firstDin, int lastDin, double *HR, double *HI, double *GR, double *GI, int LengthH, double *c_outR, double *c_outI, int LengthCout, int firstCout, int lastCout, int type, int bc);
void comconC(double *c_inR, double *c_inI, int LengthCin, int firstCin, double *HR, double *HI, int LengthH, double *c_outR, double *c_outI, int LengthCout, int firstCout, int lastCout, int type, int step_factor, int bc);
void comconD(double *c_inR, double *c_inI, int LengthCin, int firstCin, double *GR, double *GI, int LengthH, double *d_outR, double *d_outI, int LengthDout, int firstDout, int lastDout, int type, int step_factor, int bc);
void comwd(double *CR, double *CI, int *LengthC, double *DR, double *DI, int *LengthD, double *HR, double *HI, double *GR, double *GI, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *type, int *bc, int *error);
void comwr(double *CR, double *CI, int *LengthC, double *DR, double *DI, int *LengthD, double *HR, double *HI, double *GR, double *GI, int *LengthH, int *levels, int *firstC, int *lastC, int *offsetC, int *firstD, int *lastD, int *offsetD, int *type, int *bc, int *error);
void CWavDE(double *x, int *n, double *minx, double *maxx, int *Jmax, double *threshold, double *xout, double *fout, int *nout, double *PrimRes, double *SFx, double *SFy, int *lengthSF, double *WVx, double *WVy, int *lengthWV, int *kmin, int *kmax, int *kminW, int *kmaxW, double *xminW, double *xmaxW, double *phiLH, double *phiRH, double *psiLH, double *psiRH, int *verbose, int *error);
void SCevalF(double *Fx, double *Fy, int *lengthF, double *widthF, double *x, int *nx, double *answer);
double evalF(double *Fx, double *Fy, int *lengthF, double widthF, double x);
void CScalFn(double *v, double *ans, int *res, double *H, int *lengthH);
void tpwd(double *image, int *nrow, int *ncol, int *levr, int *levc, int *firstCr, int *lastCr, int *offsetCr, int *firstDr, int *lastDr, int *offsetDr, int *firstCc, int *lastCc, int *offsetCc, int *firstDc, int *lastDc, int *offsetDc, int *type, int *bc, double *H, int *LengthH, int *error);
void tpwr(double *image, int *nrow, int *ncol, int *levr, int *levc, int *firstCr, int *lastCr, int *offsetCr, int *firstDr, int *lastDr, int *offsetDr, int *firstCc, int *lastCc, int *offsetCc, int *firstDc, int *lastDc, int *offsetDc, int *type, int *bc, double *H, int *LengthH, int *error);
void ShannonEntropy(double *v, int *lengthv, double *zilchtol, double *answer, int *error);
void Cmnv(double *wst, double *wstC, int *LengthData, int *nlevels, int *upperctrl, double *upperl, int *firstl, int *verbose, int *error);
void wpCmnv(double *wp, int *LengthData, int *nlevels, int *upperctrl, double *upperl, int *firstl, int *verbose, int *error);
void wpst(double *ansvec, int *lansvec, int *nlev, int *finish_level, int *avixstart, double *H, int *LengthH, int *error);
void wpsub(double *c_in, int lc_in, double *c_out, double *d_out, double *c_outR, double *d_outR, double *H, int *LengthH);
void accessDwpst(double *coefvec, int *lansvec, int *nlev, int *avixstart, int *primaryindex, int *nwppkt, int *pklength, int *level, double *weave, int *lweave, int *error);
void c2to4(int *l, int *a);
int ddcomp(const void *a, const void *b);
void makegrid(double *x, double *y, int *n, double *gridx, double *gridy, int *gridn, double *G, int *Gindex);
int createSigma(struct sigmastruct *Sigma, int n);
void freeSigma(struct sigmastruct *Sigma);
void cleanupSigma(struct sigmastruct *Sigma);
int putSigma(struct sigmastruct *Sigma, int i, int j, double s);
int allocateSigma(struct sigmastruct *Sigma, int *d);
void computec(int *n, double *c, int *gridn, double *Gmatrix, int *Gindex, double *H, int *LengthH, int *bc, int *error);
void rainmat(int *J, int *donej, double **coefvec, int *lvec, double *fmat, int *error);
void wlpart(int *J, int *BigJ, double *H, int *LengthH, int *error);
int idlastzero(double *v, int *nv);
void rotateleft(double *v, int *nv, int *n, int *error);
void rainmatPARENT(int *J, double *H, int *LengthH, double *fmat, double *tol, int *error);
void mkcoef(int *J, int BigJ, double *H, int *LengthH, double ***coefvec, int *lvec, double *tol, int *error);
void rainmatOLD(int *J, double *coefvec, int *ixvec, int *lvec, double *fmat, int *error);
void rainmatPARTIAL(int *J, int *donej, double *H, int *LengthH, double *fmat, double *tol, int *error);
void PsiJ_impl(int *J, double *H, int *LengthH, double *tol, double *wout, int *lwout, int *rlvec, int *error);
void PsiJonly(int *J, double **coefvec, int *lvec, double *wout, int *lwout, int *error);
void haarmat(int *J, int *donej, double *fmat, int *error);
void SWT2Dall(double *m, int *nm, double *am, int *J, double *H, int *LengthH, int *error);
void SmallStore(double *am, int D1, int D12, int J, int sl, int x, int y, int ix, int jy, double *hhout, double *hgout, double *ghout, double *ggout, int nm);
void initSWT2D(double *m, int *nm, double *am, int *J, double *H, int *LengthH, int *error);
void SWT2Drec(double *am, int D1, int D12, int x, int y, int TWOsl, int sl, int J, double *H, int *LengthH, int *error);
void SWT2D(double *m, int *nm, double *hhout, double *hgout, double *ghout, double *ggout, double *H, int *LengthH, int *error);
void SWT2DROWblock(double *m, int *nm, double *hout, double *gout, double *H, int LengthH, int *error);
void SWT2DCOLblock(double *m, int *nm, double *hout, double *gout, double *H, int LengthH, int *error);
void ixtoco(int *level, int *maxlevel, int *index, int *x, int *y);
void SWTRecon(double *am, int D1, int D12, int levj, double *out, int x, int y, double *H, int *LengthH, int *error);
void SAvBasis(double *am, int *D1, int *D12, double *TheSmooth, int *levj, double *H, int *LengthH, int *error);
void SWTGetSmooth(double *am, int D1, int D12, double *TheSmooth, int levj, int x, int y, int sl, double *H, int *LengthH, int *error);
void tpose(double *m, int l);
void getpacketwst2D(double *am, int *D1, int *D12, int *maxlevel, int *level, int *index, int *type, double *out, int *sl);
void putpacketwst2D(double *am, int *D1, int *D12, int *maxlevel, int *level, int *index, int *type, double *in, int *sl);
void Precondition(int Scale, int Direction, Filter F, double *Vect);
void TransStep(int Scale, Filter F, double *Vect);
void InvTransStep(int Scale, Filter F, double *Vect);
void Trans(int MinScale, int Direction, int FilterNumber, double *Vect, int Size, int Precond, int *FilterHistory);
void dec(double *data, int *size, int *filternumber, int *minscale, int *precond, int *filterhistory);
void rec(double *data, int *size, int *filterhistory, int *currentscale, int *precond);
Filter GetFilt(int N);
double Sum(double *vect, int length);
double *CreateArray3D(int nr, int nc, int ns, int *error);
void DestroyArray3D(double *array, int *error);
void wd3Dstep(double *Carray, int *truesize, int *size, double *H, int *LengthH, int *error);
void wd3D(double *Carray, int *size, double *H, int *LengthH, int *error);
void wr3D(double *Carray, int *truesize, double *H, int *LengthH, int *error);
void wr3Dstep(double *Carray, int *truesize, int *sizeout, double *H, int *LengthH, int *error);
void getARRel(double *Carray, int *size, int *level, double *GHH, double *HGH, double *GGH, double *HHG, double *GHG, double *HGG, double *GGG);
void putarr(double *Carray, int *truesize, int *level, int *Iarrayix, double *Iarray);
void multiwd(double *C, int *lengthc, double *D, int *lengthd, int *nlevels, int *nphi, int *npsi, int *ndecim, double *H, double *G, int *NH, int *lowerc, int *upperc, int *offsetc, int *lowerd, int *upperd, int *offsetd, int *nbc);
void multiwr(double *C, int *lengthc, double *D, int *lengthd, int *nlevels, int *nphi, int *npsi, int *ndecim, double *H, double *G, int *NH, int *lowerc, int *upperc, int *offsetc, int *lowerd, int *upperd, int *offsetd, int *nbc, int *startlevel);
int trd_reflect(int a, int b);
int trd_module(int a, int b);
int IsPowerOfTwo(int n);
void TRDerror(char *s);
void comwst(double *CaR, double *CaI, double *DataR, double *DataI, int *LengthData, int *levels, double *HR, double *HI, double *GR, double *GI, int *LengthH, int *error);
void comwvpkstr(double *CaR, double *CaI, double *DataR, double *DataI, int startin, int lengthin, int outstart1, int outstart2, int level, double *HR, double *HI, double *GR, double *GI, int LengthH, int *LengthData, double *bookR, double *bookI, int *error);
void comrotater(double *bookR, double *bookI, int length);
void comAB_WRAP(double *wstR, double *wstI, double *wstCR, double *wstCI, int *LengthData, int *level, double *HR, double *HI, double *GR, double *GI, int *LengthH, double *answerR, double *answerI, int *error);
void destroycomplex(struct complex *a);
struct complex *comAB(double *wstR, double *wstI, double *wstCR, double *wstCI, int nlevels, int level, int ix1, int ix2, double *HR, double *HI, double *GR, double *GI, int LengthH, int *error);


#endif
