#include <R.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "functionsIE.h"
#include "phij.h"

/*
#include <curses.h>
*/



/* Make \Psi_j(\tau) components	*/

void 
mkcoefIE (
    int *J,	/* Dimension of the problem				*/
    int BigJ,	/* The maximum depth that we have to go to		*/
    double *H,	/* Wavelet filter coefficients				*/
    int *LengthH,	/* Number of wavelet filter coefficients		*/
    double ***coefvec, /* Coefficients of \Psi_j(\tau)			*/
    int *lvec,	/* Vector of length *J that will contain length of
		 * each component of coefvec */
    double *tol,	/* Elements smaller than this will be deleted		*/
    int *error	/* Error code						*/
)
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
int LengthC, LengthD, levels=0;
int type,bc;
int n_to_rotate;
int start_level;



ndata = (int)0x01 << BigJ;

/*
 * Create ixvec
 */

if ((ixvec = (int *)calloc((1+BigJ),sizeof(int)))==NULL){
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

for(i=0; i<=BigJ; ++i){
	--*(ixvec+i);
}

/*
 * Basically a dummy wavelet transform to set up first/last stuff
 */

if ((TheData = (double *)calloc(ndata,sizeof(double)))==NULL)	{
	*error = 141l;
	return;
}

for(i=0; i<ndata; ++i)
	*(TheData+i) = 0.0;

/*
 * Do the wavelet transform
 */

/* MAN 6/12/10.  The call to simpleWT doesn't know what memory it's using
and so during the next for loop, *D is being used when we don't know what 
it contains.  I am going to allocate memory specifically for the input into
simpleWT.
*/

firstC=calloc(BigJ+1,sizeof(int));
lastC=calloc(BigJ+1,sizeof(int));
offsetC=calloc(BigJ+1,sizeof(int));
firstD=calloc(BigJ,sizeof(int));
lastD=calloc(BigJ,sizeof(int));
offsetD=calloc(BigJ,sizeof(int));
C=calloc(2*ndata-1,sizeof(double));
D=calloc(ndata-1,sizeof(double));

simpleWT(TheData, &ndata, H, LengthH,
	C, &LengthC, D, &LengthD, &levels,
	firstC, lastC, offsetC,
	firstD, lastD, offsetD,
	&type, &bc, error);

if (*error != 0)
	return;

if ((lcoefvec = (double **)calloc(*J,sizeof(double*)))==NULL){
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
	if ((tmpcfvec = (double *)calloc(large_ones,sizeof(double)))== NULL){
		*error = 143l;
		return;
	}

	large_ones = 0;

	for(j=0; j<ndata; ++j)
		if (fabs(*(TheData+j)) > *tol)
			*(tmpcfvec+large_ones++) = *(TheData+j);


	/* Install this vector into the array */

	*(lcoefvec+i-1) = tmpcfvec;
	/* MAN: to record now big tmpcfvec is */
	/*
	int tmp;
	tmp=large_ones;
	mycpyd(tmpcfvec,&tmp,*(coefvec+i-1));
	*/
	*(lvec+i-1) = (int)large_ones;

}

/* Install the lcoefvec into the coefvec */

*coefvec = lcoefvec;

free((void *)ixvec);
free((void *)TheData);

/* MAN 6/12/10.  Free the memory allocated above for simpleWT. 
 and the other vectors from the loop
*/

/* 1: tmpcfvec still exists from last iteration of loop. */
/*
free(tmpcfvec);
*/
/* 2:  now the pesky ** vector.*/
/*
for(i=0; i<*J; ++i)
        free((void *)*(lcoefvec+i));

free((void *)lcoefvec);
*/
free((void *)C);
free((void *)D);
free((void *)firstC); 
free((void *)lastC);
free((void *)offsetC);
free((void *)firstD); 
free((void *)lastD);
free((void *)offsetD);

}


void 
PhiJ_impl (
    int *J,	/* The dimension of the problem				*/
    double *H,	/* The wavelet filter coefficients			*/
    int *LengthH,	/* The number of wavelet filter coefficients		*/
    double *tol,	/* Elements smaller than this will be deleted		*/
    double *wout,	/* Answers for \Psi_j(\tau)				*/
    int *lwout,	/* Length of previous array				*/
    int *rlvec,	/* Vector of length J contains lengths of \psi_j	*/
    int *error	/* Error code. Nonzero is an error			*/
)
{
register int i;
int BigJ;	/* The level we must go to to be able to compute
		 * coefficients without error
		 */
double **coefvec;	/* These are the \psi_j (\tau)			*/
int *lvec;		/* Vector of length *J contains the length	
			 * of each vector in coefvec
			 */



/* whichlevel */

wlpart(J, &BigJ, H, LengthH, error);

if (*error != 0)
	return;

/* mkcoef */

if ((lvec = (int *)calloc(*J,sizeof(int)))==NULL)	{
	*error = 130;
	return;
}

for(i=0; i<*J; ++i)
	*(lvec+i) = 0;

/* MAN 6/12/10.  coefvec needs to be alloc'd some memory. 

Let's try and give it something sensible.
*/
/*
coefvec=calloc(*J,sizeof(double*));
int tmp;
for(i=0; i<*J; ++i){
	tmp= (int) pow(2,i+1) -1;
	tmp=2*tmp*(*LengthH-1)+1;
	*(coefvec+i) = calloc(tmp,sizeof(double));  
}
*/

mkcoefIE(J, BigJ, H, LengthH, &coefvec, lvec, tol, error); 

if (*error != 0)
	return;


PsiJonlyIE(J, coefvec, lvec, wout, lwout, error);

if (*error != 0)
	return;

for(i=0; i<*J; ++i)
	*(rlvec + i) = *(lvec+i);

free((void *)lvec);

/* MAN 6/12/10 Remove free? */

for(i=0; i<*J; ++i)
	free((void *)*(coefvec+i));

free((void *)coefvec);

}

void 
PsiJonlyIE (
    int *J,		/* The desired maximum level (positive)		*/
    double **coefvec,	/* The \psi_{jk} stacked into one vector	*/
    int *lvec,		/* A vector of lengths of each \psi_j vector in
			   coefvec. The jth element is the length of the
			   jth \psi_j in coefvec
			 */
    double *wout,		/* Output contains the \Psi_j(\tau)		*/
    int *lwout,		/* Length of this vector. If it is not int
			 * enough an error code is returned		*/
    int *error		/* Error code					*/
)
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


if ((w = (double **)calloc(*J,sizeof(double*)))==NULL)	{
	*error = 161;
	return;
}

/* Now populate each of the *w */

for(j=0; j<*J; ++j)	{
	if ((*(w+j) = (double *)calloc(*(lvec+j)*2-1,sizeof(double)))==NULL)	{
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

void 
IEwaverecons (
    double *C,              /* Input data, and the subsequent smoothed data */
    double *D,              /* The wavelet coefficients                     */
    double *H,              /* The smoothing filter H                       */
    int *LengthH,          /* Length of smoothing filter                   */
    int *levels,           /* The number of levels in this decomposition   */
    int *firstC,           /* The first possible C coef at a given level   */
    int *lastC,            /* The last possible C coef at a given level    */
    int *offsetC,          /* Offset from C[0] for certain level's coeffs  */
    int *firstD,           /* The first possible D coef at a given level   */
    int *lastD,            /* The last possible D coef at a given level    */
    int *offsetD,          /* Offset from D[0] for certain level's coeffs  */
    int *start_level,	/* Start level to start synthesis (==at_level)	*/
    int *type,		/* The type of wavelet decomposition		*/
    int *bc,		/* Which boundary handling are we doing		*/
    int *error            /* Error code                                   */
)
{
register int next_level, at_level;
register int verbose;	/* Printing messages, passed in error		*/



if (*error == 1l)
	verbose = 1;
else
	verbose = 0;

switch(*bc)	{

	case PERIODIC:	/* Periodic boundary conditions */
		if (verbose) Rprintf("Periodic boundary method\n");
		break;

	case SYMMETRIC: /* Symmetric boundary conditions */
		if (verbose) Rprintf("Symmetric boundary method\n");
		break;

	default:	/* The bc must be one of the above */
		Rprintf("Unknown boundary correction method\n");
		*error = 1;
		return;
	}

switch(*type)	{

	case WAVELET:	/* Standard wavelets */
		if (verbose) Rprintf("Standard wavelet decomposition\n");
		break;

	case STATION:	/* Stationary wavelets */
		if (verbose) Rprintf("Stationary wavelet decomposition\n");
		break;

	default:	/* The type must be of one the above */
		if (verbose) Rprintf("Unknown decomposition type\n");
		*error = 2;
		return;
	}

if (verbose) Rprintf("Building level: ");

*error = 0l;

for(next_level = *start_level+1; next_level <= *levels; ++next_level)	{

	
	if (verbose)
		Rprintf("%d ", next_level);

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
	Rprintf("\n");

return;
}
