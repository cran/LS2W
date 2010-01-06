#include <R.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/*
#include <curses.h>
*/


/* Error condition	*/
/*#define ERROR		(-1)*/
#define OK		(0)

/* For boundary condition handling */
#define PERIODIC        1
#define SYMMETRIC       2

/* For the type of wavelet decomposition */
#define	WAVELET		1	/* The standard decomposition */
#define	STATION		2	/* The stationary decomposition */

/* Threshold types */
#define HARD    1
#define SOFT    2

/*
 * ACCESSC handles negative accesses, as well as those that exceed the number
 * of elements
 */

#define ACCESS(image, size, i, j)       *(image + (i)*(size) + (j))
#define	ACCESSC(c, firstC, lengthC, ix, bc) *(c+reflect(((ix)-(firstC)),(lengthC),(bc)))
#define ACCESSD(l, i)   *(Data + (*LengthData*(l)) + (i))
#define POINTD(l,i) (Data + (*LengthData*(l)) + (i))
#define POINTC(l,i) (Carray +(*LengthData*(l)) + (i))

/*
 * The next three are exclusively for the stationary wavelet packet algorithm
 * WPST
 */
#define	NPKTS(level, nlev)	(1l << (2l*(nlev-level)))
#define PKTLENGTH(level)	(1l << level)

#define ACCWPST(a, level, avixstart, pkix, i) *((a) + *(avixstart+(level))+(pkix)*PKTLENGTH(level)+i)

/* Optimiser parameters */

#define	R	0.61803399	/* The golden ratio for bisection searches */
#define Cons	(1.0-R)		/* For bisection searches		   */

/* These next 3 are for the ipndacw code */
#define ACCESSW(w,j,k)  *(*(w+j)+k)
#define max(a,b)        ((a) > (b) ? (a) : (b))
#define min(a,b)        ((a) > (b) ? (b) : (a))

/*
 * The next 5 are for the swt2d code
 */
 

#define ACCESS3D(ar, d1, d12, ix1, ix2, ix3)    *(ar + (ix3)*(d12)+ (ix2)*(d1)+(ix1))

#define TYPES	0
#define TYPEH	1
#define TYPEV	2
#define TYPED	3

/*
 * End of the swt2d  macro code
 */


/* Make \Psi_j(\tau) components	*/

void mkcoefIE(J, BigJ, H, LengthH, coefvec, lvec, tol, error)
int *J;	/* Dimension of the problem				*/
int BigJ;	/* The maximum depth that we have to go to		*/
double *H;	/* Wavelet filter coefficients				*/
int *LengthH;	/* Number of wavelet filter coefficients		*/
double ***coefvec; /* Coefficients of \Psi_j(\tau)			*/
int *lvec;	/* Vector of length *J that will contain length of
		 * each component of coefvec */
double *tol;	/* Elements smaller than this will be deleted		*/
int *error;	/* Error code						*/
{
register int i,j;
register int large_ones;
int ndata;
int *ixvec;		/* Index vector for inserting 1s into blank WT  */
double **lcoefvec;	/* Local version of coefvec			*/
double *tmpcfvec;	/* Temporary vector				*/

/* Things needed for the simpleWT */
double *TheData;
double *C, *D;
int *firstC, *lastC, *offsetC, *firstD, *lastD, *offsetD;
int LengthC, LengthD, levels;
int type,bc;
int n_to_rotate;
int start_level;

void simpleWT();
int idlastzero();
void rotateleft();
void IEwaverecons();

ndata = (int)0x01 << BigJ;

/*
 * Create ixvec
 */

if ((ixvec = (int *)Calloc((1+BigJ),int))==NULL){
	*error = 140l;
	return;
	}

/* IAE changed from i< J to i <= J 
* changed the contents of the first loop also (see notes for further
* details
*/

for(i=0; i<=BigJ; ++i)
	*(ixvec+i) =(0x01 << (BigJ - i)); 

for(i=1; i<=BigJ; ++i)
	*(ixvec+i) = *(ixvec+i-1) + *(ixvec+i);

for(i=0; i<=BigJ; ++i)
	--*(ixvec+i);

/*
 * Basically a dummy wavelet transform to set up first/last stuff
 */
if ((TheData = (double *)Calloc(ndata,double))==NULL)	{
	*error = 141l;
	return;
	}

for(i=0; i<ndata; ++i)
	*(TheData+i) = 0.0;

/*
 * Do the wavelet transform
 */

simpleWT(TheData, &ndata, H, LengthH,
	&C, &LengthC, &D, &LengthD, &levels,
	&firstC, &lastC, &offsetC,
	&firstD, &lastD, &offsetD,
	&type, &bc, error);

if (*error != 0)
	return;

if ((lcoefvec = (double **)Calloc(*J,double*))==NULL){
	*error = 142l;
	return;
	}

for(i=1; i <=*J; ++i)	{
	for(j=0; j<LengthC; ++j)
		*(C+j) = 0.0;

	*(C+ *(ixvec+i)) = 1;

start_level=BigJ-i;

 IEwaverecons(C, D, H, LengthH, &levels,
		firstC, lastC, offsetC, firstD, lastD, offsetD,
		&start_level, &type, &bc, error);

	if (*error != 0)
		return;

	/* Now copy reconstruction into TheData  (vec in S) */

	for(j=0; j<ndata; ++j)
		*(TheData+j) = *(C+j);

	n_to_rotate = (int)idlastzero(TheData, &ndata);

	if (n_to_rotate < 0)
		n_to_rotate = 0;

	rotateleft(TheData, &ndata, &n_to_rotate, error);

	if (*error != 0)
		return;

	large_ones = 0;

	for(j=0; j<ndata; ++j)
		if (fabs(*(TheData+j)) > *tol)
			++large_ones;

	/* Now get memory for the large ones */

	if ((tmpcfvec = (double *)Calloc(large_ones,double))==
		NULL)	{
		*error = 143l;
		return;
		}

	large_ones = 0;

	for(j=0; j<ndata; ++j)
		if (fabs(*(TheData+j)) > *tol)
			*(tmpcfvec+large_ones++) = *(TheData+j);


	/* Install this vector into the array */

	*(lcoefvec+i-1) = tmpcfvec;
	*(lvec+i-1) = (int)large_ones;
	}

/* Install the lcoefvec into the coefvec */

*coefvec = lcoefvec;

free((void *)ixvec);
free((void *)TheData);
}


void PhiJ(J, H, LengthH, tol, wout, lwout, rlvec, error)
int *J;	/* The dimension of the problem				*/
double *H;	/* The wavelet filter coefficients			*/
int *LengthH;	/* The number of wavelet filter coefficients		*/
double *tol;	/* Elements smaller than this will be deleted		*/
double *wout;	/* Answers for \Psi_j(\tau)				*/
int *lwout;	/* Length of previous array				*/
int *rlvec;	/* Vector of length J contains lengths of \psi_j	*/
/*double *psivec; */
int *error;	/* Error code. Nonzero is an error			*/
{
register int i;
int BigJ;	/* The level we must go to to be able to compute
		 * coefficients without error
		 */
double **coefvec;	/* These are the \psi_j (\tau)			*/
int *lvec;		/* Vector of length *J contains the length	
			 * of each vector in coefvec
			 */

void wlpart();	/* Substitute for whichlevel function			*/
void mkcoefIE();
void PsiJonlyIE();

/* whichlevel */

printf("J is %d\n", *J);

wlpart(J, &BigJ, H, LengthH, error);

if (*error != 0)
	return;

/* mkcoef */

if ((lvec = (int *)Calloc(*J,int))==NULL)	{
	*error = 130l;
	return;
	}

for(i=0; i<*J; ++i)
	*(lvec+i) = 0l;

mkcoefIE(J, BigJ, H, LengthH, &coefvec, lvec, tol, error); 

if (*error != 0)
	return;


PsiJonlyIE(J, coefvec, lvec, wout, lwout, error);

if (*error != 0)
	return;

for(i=0; i<*J; ++i)
	*(rlvec + i) = *(lvec+i);

/*
 *for(i=0; i<*J; ++i) 
 **(psivec + i) = **(coefvec+i);
 */

free((void *)lvec);

for(i=0; i<*J; ++i)
	free((void *)*(coefvec+i));

free((void *)coefvec);
}

void PsiJonlyIE(J, coefvec, lvec, wout, lwout, error)
int *J;		/* The desired maximum level (positive)		*/
double **coefvec;	/* The \psi_{jk} stacked into one vector	*/
int *lvec;		/* A vector of lengths of each \psi_j vector in
			   coefvec. The jth element is the length of the
			   jth \psi_j in coefvec
			 */
double *wout;		/* Output contains the \Psi_j(\tau)		*/
int *lwout;		/* Length of this vector. If it is not int
			 * enough an error code is returned		*/
int *error;		/* Error code					*/
{

/* First we compute the w. One for each j			*/

double **w;
register int j,k,m;
double sum;
int totall;
int lj,cnt;

/* Check output vector is int enough to store answer */

totall = 0;
for(j=0; j < *J; ++j)
	totall += *(lvec+j)*2l - 1l; 

if (totall > *lwout)	{
	*error = 160l;
	*lwout = totall;
	return;
	}


if ((w = (double **)Calloc(*J,double*))==NULL)	{
	*error = 161;
	return;
	}

/* Now populate each of the *w */

for(j=0; j<*J; ++j)	{
	if ((*(w+j) = (double *)Calloc(*(lvec+j)*2-1,double))==NULL)	{
		*error = 162;
		*J = (int)j;
		return;
		}
	}

/* Now compute each of the wjk */

for(j=0; j< *J; ++j)	{
	lj = *(lvec+j);
	for(k = 1-lj; k <= lj-1; ++k)	{
		sum = 0.0;
		for(m = max(0, k); m <= min(lj-1, lj-1+k); ++m)	{
			sum += *((*(coefvec+j))+m) *
				*((*(coefvec+j))+m-k);
			}
		ACCESSW(w, j, k-1+lj) = sum;
		}
	}

/* Store the w */

cnt = 0;

for(j=0; j < *J; ++j)	{
	lj = *(lvec+j);
	for(k = 1-lj; k <= lj-1; ++k)	{
		*(wout+cnt) = ACCESSW(w, j, k-1+lj);
		++cnt;
		}
	}


/* Now free the w */
for(j=0; j<*J; ++j)	{
	free((void *)*(w+j));
	}
free((void *)w);
}




/*
 * waverecons:	Do 1D wavelet reconstruction
 */

void IEwaverecons(C, D, H, LengthH, levels,
	firstC, lastC, offsetC, firstD, lastD, offsetD, start_level,
	type, bc, error)
double *C;              /* Input data, and the subsequent smoothed data */
double *D;              /* The wavelet coefficients                     */
double *H;              /* The smoothing filter H                       */
int *LengthH;          /* Length of smoothing filter                   */
int *levels;           /* The number of levels in this decomposition   */
int *firstC;           /* The first possible C coef at a given level   */
int *lastC;            /* The last possible C coef at a given level    */
int *offsetC;          /* Offset from C[0] for certain level's coeffs  */
int *firstD;           /* The first possible D coef at a given level   */
int *lastD;            /* The last possible D coef at a given level    */
int *offsetD;          /* Offset from D[0] for certain level's coeffs  */
int *start_level;	/* Start level to start synthesis (==at_level)	*/
int *type;		/* The type of wavelet decomposition		*/
int *bc;		/* Which boundary handling are we doing		*/
int *error;            /* Error code                                   */
{
register int next_level, at_level;
register int verbose;	/* Printing messages, passed in error		*/

void conbar();

if (*error == 1l)
	verbose = 1;
else
	verbose = 0;

switch(*bc)	{

	case PERIODIC:	/* Periodic boundary conditions */
		if (verbose) printf("Periodic boundary method\n");
		break;

	case SYMMETRIC: /* Symmetric boundary conditions */
		if (verbose) printf("Symmetric boundary method\n");
		break;

	default:	/* The bc must be one of the above */
		printf("Unknown boundary correction method\n");
		*error = 1;
		return;
	}

switch(*type)	{

	case WAVELET:	/* Standard wavelets */
		if (verbose) printf("Standard wavelet decomposition\n");
		break;

	case STATION:	/* Stationary wavelets */
		if (verbose) printf("Stationary wavelet decomposition\n");
		break;

	default:	/* The type must be of one the above */
		if (verbose) printf("Unknown decomposition type\n");
		*error = 2;
		return;
	}

if (verbose) printf("Building level: ");

*error = 0l;

for(next_level = *start_level+1; next_level <= *levels; ++next_level)	{

	
	if (verbose)
		printf("%d ", next_level);

	at_level = next_level - 1; 

	conbar( (C+*(offsetC+at_level)),
		(int)(*(lastC+at_level) - *(firstC+at_level) + 1),
		(int)(*(firstC+at_level)),
		(D+*(offsetD+at_level)),
		(int)(*(lastD+at_level) - *(firstD+at_level) + 1),
		(int)(*(firstD+at_level)),
		H,
		(int)*LengthH,
		(C+*(offsetC+next_level)),
		(int)(*(lastC+next_level) - *(firstC+next_level)+1),
                (int)(*(firstC+next_level)),
                (int)(*(lastC+next_level)),
		(int)(*type),
		(int)(*bc) );
	}
if (verbose)
	printf("\n");

return;
}
