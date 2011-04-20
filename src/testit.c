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


/*
 * ImageDecomposeStep	-	Take an image and do a one level decomp
 *
 * Error Codes
 *
 *	0	-	Ok.
 *
 *	1	-	Memory error for (afterC) temporary image
 *
 *	2	-	Memory error for (afterD) temporary image
 *
 *	3	-	Memory error for (ccopy) temporary row store
 *
 *	4	-	Memory error for (ccopy_out) temporary row store
 *
 *	5	-	Memory error for (dcopy_out) temporary row store
 *
 *	6-9	-	Memory errors for (afterCC,afterCD,afterDC,afterDD)
 *			store for the answers
 */



void ImageDecomposeStepIE(C, Csize, firstCin, H, LengthH,
	LengthCout, firstCout, lastCout,
	LengthDout, firstDout, lastDout,
	cc_out, cd_out, dc_out, dd_out, bc, type,
	error, stepfactor)
double *C;	/* Input data image					*/
int Csize;	/* Size of image (side length)				*/
int firstCin;	/* Index number of first element in input "C" image	*/
double *H;	/* Filter coefficients					*/
int LengthH;	/* Length of filter					*/
/* Details about output image */
int LengthCout;/* Length of C part of output image			*/
int firstCout;	/* Index number of first element in output "C" image	*/
int lastCout;	/* Index number of last element				*/
int LengthDout;/* Length of D part of output image			*/
int firstDout;	/* Index number of first element in output "D" image	*/
int lastDout;	/* Index number of last element				*/
double *cc_out;/* Smoothed output image				*/
double *cd_out;/* Horizontal detail					*/
double *dc_out;/* Vertical detail					*/
double *dd_out;/* Diagonal detail					*/
int bc;	/* Method of boundary correction			*/
int type;	/* Type of transform, wavelet or stationary		*/
int *error;	/* Error code						*/
int stepfactor;
{
register int j,row,col;
double *ccopy;	/* Used to copy input data to convolution routines	*/
double *ccopy_out;/* Used to copy output data to afterC after conv.	*/
double *dcopy_out;/* Used to copy output data to afterD after conv.	*/
double *afterC;	/* Temporary store for image data after C convolution	*/
double *afterD;	/* Temporary store for image data after D convolution	*/
double *afterCC,*afterCD,*afterDC,*afterDD;	/* Results		*/
int step_factor;	/* This should always be 1 for the WAVELET trans*/

void convolveC();
void convolveD();

void mycpyd();

*error = 0l;

step_factor = (int) stepfactor;

/* Get memory for afterC */

if ((afterC = (double *)malloc((unsigned)(Csize*LengthCout*sizeof(double))))==NULL){
    *error = 1;
    return;
    }

/* Get memory for afterD */

if ((afterD = (double *)malloc((unsigned)(Csize*LengthDout*sizeof(double))))==NULL){
        *error = 2;
        return;
        }

/* Get memory for row of image to pass to convolution routines */

if ((ccopy = (double *)malloc((unsigned)(Csize*sizeof(double)))) == NULL) {
    *error = 3;
    return;
    }

/* Get memory for output row after C convolution */

if ((ccopy_out = (double *)malloc((unsigned)(LengthCout*sizeof(double))))==NULL) {
    *error = 4;
    return;
    }

/* Get memory for output row after D convolution */

if ((dcopy_out = (double *)malloc((unsigned)(LengthDout*sizeof(double))))==NULL) {
        *error = 5;
        return;
        }


/* Do convolutions on rows of C */

for(row=0; row < (int)Csize; ++row)	{

	/* Copy row of C into ccopy */

	for(j=0; j<Csize; ++j)
		*(ccopy+j) = ACCESS(C, Csize, row, j);

	/* Now convolve this row with C filter */

	convolveC(ccopy, (int)Csize, (int)firstCin,H, (int)LengthH, ccopy_out,
		(int)firstCout, (int)lastCout,
		(int)type, step_factor, (int)bc); 

	/* Now convolve this row with D filter */

	convolveD(ccopy, (int)Csize, (int)firstCin, H, (int)LengthH, dcopy_out,
		(int)firstDout, (int)lastDout,
		(int)type, step_factor, (int)bc);

	/* Copy answer back to arrays */

	for(j=0; j<(int)LengthCout; ++j)
		ACCESS(afterC, (int)LengthCout, row, j) = *(ccopy_out + j);

	for(j=0; j<(int)LengthDout; ++j)
		ACCESS(afterD, (int)LengthDout, row, j) = *(dcopy_out + j);

	}


/* Now we have to apply both the C and D filters to afterC and afterD.
 * We get four answers. First we get the necessary memory
 */

if ((afterCC = (double *)malloc((unsigned)(LengthCout*LengthCout*sizeof(double))
        ))==NULL)   {
    *error = 6;
    return;
    }

if ((afterCD = (double *)malloc((unsigned)(LengthDout*LengthCout*sizeof(double))
        ))==NULL)   {
    *error = 7;
    return;
    }

if ((afterDC = (double *)malloc((unsigned)(LengthCout*LengthDout*sizeof(double))
        ))==NULL)   {
    *error = 8;
    return;
    }

if ((afterDD = (double *)malloc((unsigned)(LengthDout*LengthDout*sizeof(double))
        ))==NULL)   {
    *error = 9;
    return;
    }

/* Link this memory to the returning pointers */
/*
*cc_out = afterCC;
*cd_out = afterCD;
*dc_out = afterDC;
*dd_out = afterDD;
*/

/* Apply the filters, first to afterC to get afterCC and afterCD */

for(col=0; col < (int)LengthCout; ++col)	{

	/* Copy column to ccopy */

	for(j=0; j<(int)Csize; ++j)
		*(ccopy + j) = ACCESS(afterC, (int)LengthCout, j, col);

	/* Apply C filter */

	convolveC(ccopy, (int)Csize, (int)firstCin, H, (int)LengthH, ccopy_out,
		(int)firstCout, (int)lastCout,
		(int)type, step_factor, (int)bc);

	/* Apply D filter */

	convolveD(ccopy, (int)Csize, (int)firstCin, H, (int)LengthH, dcopy_out,
		(int)firstDout, (int)lastDout,
		(int)type, step_factor, (int)bc);

	/* Copy answer back */

	for(j=0; j<(int)LengthCout; ++j)
		ACCESS(afterCC, (int)LengthCout, j, col) = *(ccopy_out+j);

	for(j=0; j<(int)LengthDout; ++j)
		ACCESS(afterCD, (int)LengthCout, j, col) = *(dcopy_out+j);
	}

/* Apply the filters, now to afterD to get afterDC and afterDD */

for(col=0; col < (int)LengthDout; ++col)	{

	/* Copy column to ccopy */

	for(j=0; j<(int)Csize; ++j)
		*(ccopy + j) = ACCESS(afterD, (int)LengthDout, j, col);

	/* Apply C filter */

	convolveC(ccopy, (int)Csize, (int)firstCin, H, (int)LengthH, ccopy_out,
		(int)firstCout, (int)lastCout,
		(int)type, step_factor, (int)bc);

	/* Apply D filter */

	convolveD(ccopy, (int)Csize, (int)firstCin, H, (int)LengthH, dcopy_out,
		(int)firstDout, (int)lastDout,
		(int)type, step_factor, (int)bc);

	/* Copy answer back */

	for(j=0; j<(int)LengthCout; ++j)
		ACCESS(afterDC, (int)LengthDout, j, col) = *(ccopy_out+j);

	for(j=0; j<(int)LengthDout; ++j)
		ACCESS(afterDD, (int)LengthDout, j, col) = *(dcopy_out+j);
	}

/* That should be it ! */

free((char *) afterD);
free((char *) afterC);
free((char *)dcopy_out);
free((char *)ccopy_out);
free((char *)ccopy);

/* MAN  extra frees */

int tmp;

tmp=LengthCout*LengthCout;
mycpyd(afterCC,&tmp,cc_out);

tmp=LengthDout*LengthCout;
mycpyd(afterCD,&tmp,cd_out);
mycpyd(afterDC,&tmp,dc_out);

tmp=LengthDout*LengthDout;
mycpyd(afterDD,&tmp,dd_out);

free(afterCC);
free(afterDD);
free(afterDC);
free(afterCD);

return;
}


void StoIDSIE(C, Csize, firstCin, H, LengthH,
	LengthCout, firstCout, lastCout,
	LengthDout, firstDout, lastDout,
	ImCC, ImCD, ImDC, ImDD, bc, type,
	error, stepfactor)
	
double *C;
int *Csize;
int *firstCin;
double *H;
int *LengthH;
int *LengthCout;
int *firstCout;
int *lastCout;
int *LengthDout;
int *firstDout;
int *lastDout;
double *ImCC,*ImCD,*ImDC,*ImDD;
int *bc;
int *type;
int *error;
int *stepfactor;
{
register int i,j;
double *cc_out, *cd_out, *dc_out, *dd_out;
int step_factor;

void ImageDecomposeStepIE();

step_factor = *stepfactor;

/* MAN  I think the out vectors should be alloc'd - see frees at 
the end 
*/

cc_out=calloc(*LengthCout**LengthCout,sizeof(double));
dd_out=calloc(*LengthDout**LengthDout,sizeof(double));
cd_out=calloc(*LengthCout**LengthDout,sizeof(double));
dc_out=calloc(*LengthCout**LengthDout,sizeof(double));


ImageDecomposeStepIE(C, *Csize, *firstCin, H, *LengthH,
	*LengthCout, *firstCout, *lastCout,
	*LengthDout, *firstDout, *lastDout,
	cc_out, cd_out, dc_out, dd_out, *bc, *type,
	error, *stepfactor);

/* Copy images */

for(i=0; i<(int)*LengthDout; ++i)	{
	for(j=0; j<(int)*LengthDout; ++j)
		ACCESS(ImDD, (int)*LengthDout, i, j) = ACCESS(dd_out,
			*LengthDout, i, j);

	for(j=0; j<(int)*LengthCout; ++j)
		ACCESS(ImDC, (int)*LengthDout, j,i) = ACCESS(dc_out,
			*LengthDout, j,i);
	}

for(i=0; i<(int)*LengthCout; ++i)	{
	for(j=0; j<(int)*LengthDout; ++j)
		ACCESS(ImCD, (int)*LengthCout, j,i) = ACCESS(cd_out,
			*LengthCout, j,i);

	for(j=0; j<(int)*LengthCout; ++j)
		ACCESS(ImCC, (int)*LengthCout,j,i) = ACCESS(cc_out,
			*LengthCout, j,i);
	}

/* MAN  unnec. frees now make sense */

free((void *)cc_out);
free((void *)cd_out);
free((void *)dc_out);
free((void *)dd_out);

}
