\name{D2ACW}
\alias{D2ACW}
\title{ Compute 2-D discrete autocorrelation wavelets.}
\description{
This function computes two-dimensional discrete autocorrelation wavelets.  The inner products of these wavelets are required for correction of the (biased) raw wavelet periodograms.
}
\usage{
D2ACW(J, filter.number = 1, family = "DaubExPhase", switch = "direction", 
tol = 1e-100, OPLENGTH = 2000, verbose = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{J}{ Discrete autocorrelation wavelets will be computed for scales 1 to J within each decomposition direction (horizontal, vertical and diagonal). This number should be a positive integer.}
  \item{filter.number}{The index of the wavelet used to compute the discrete autocorrelation wavelets.}
  \item{family}{ The wavelet family used to compute the discrete autocorrelation wavelets.}
  \item{switch}{Allows the user to define how they wish their inner product matrix to be formed. There are two available options:\\
 \code{switch = "direction"} - structures the matrix by scale within each decomposition direction. Thus, the ordering goes as follows $(1, V), 
(2, V), \ldots$.\\
 \code{switch = "level"} - structures the matrix by direction within each scale. Thus the ordering is as follows $(-1,V), (-1, H), (-1, D), (-2, 
V), (-2, H),\ldots$.
 }
  \item{tol}{ In the brute force computation for Daubechies compactly supported wavelets many inner product computations are performed. This tolerance 
discounts any results which are smaller than  \code{tol} which effectively defines how long the inner product/autocorrelation products are.
 }
  \item{OPLENGTH}{ This integer variable defines some workspace of length OPLENGTH. The code uses this workspace. If the workspace is not long enough then the routine will stop and tell you what OPLENGTH should be set to.}
  \item{verbose}{If \code{TRUE} various informative statements are printed to screen.}
}
\details{
 This function computes the 2-D discrete autocorrelation wavelets. It does not have any direct use for space-scale analysis.  The construction method 
is a brute force approach -- a more elegant solution would be based on the recursive schemes as described in Eckley and Nason (2005). The routine 
returns only the values of the discrete autocorrelation wavelets, not their spatial positions. Each discrete autocorrelation wavelet is compactly supported. This support is determined from the discrete wavelets upon which these autocorrelations are based.
}

\value{
A list containing $3J$ components, numbered from 1 to $3J$.
If switch="direction", the first $J$ components contain the vertical autocorrelation wavelet coefficients, the second set of $J$ components contains the horizontal autocorrelation wavelet coefficients (scales $1,\ldots, J$) and the last $J$ components constitute the diagonal autocorrelation wavelet coefficients.
However, if switch="level", then the first 3 components contain the finest scale autocorrelation wavelet coefficients in the vertical, horizontal and diagonal decomposition directions respectively. The second set of 3 contains the vertical, horizontal and diagonal coefficients at scale 2 etc. \\
\\
Note that these 2-D autocorrelation wavelets are stored as matrices. The central element of the matrix refers to lag 0.
 }

\references{ 
Eckley, I.A., Nason, G.P. and Treloar, R.L. (2010) Locally stationary wavelet fields with application to the modelling and analysis of image texture. Journal of the Royal Statistical Society (Series C), 59, 595 - 616. 

Eckley, I.A. and Nason, G.P. (2011). LS2W: Implementing the Locally Stationary 2D Wavelet Process Approach in R, Journal of Statistical Software, 43(3), 1-23.
URL http://www.jstatsoft.org/v43/i03/.
}
\author{Idris Eckley}

\seealso{\code{\link{D2autoplot}}}
\examples{
#
# Let us create the discrete autocorrelation wavelets for the Haar wavelet.
# We shall create up to scale 2.
#
D2ACW(J=-2, filter.number=1, family="DaubExPhase", switch="direction")
#[[1]]:
#      [,1] [,2]  [,3]
#[1,] -0.25 -0.5 -0.25
#[2,]  0.50  1.0  0.50
#[3,] -0.25 -0.5 -0.25
#
#[[2]]:
#        [,1]   [,2]    [,3]  [,4]    [,5]   [,6]    [,7]
#[1,] -0.0625 -0.125 -0.1875 -0.25 -0.1875 -0.125 -0.0625
#[2,] -0.1250 -0.250 -0.3750 -0.50 -0.3750 -0.250 -0.1250
#[3,]  0.0625  0.125  0.1875  0.25  0.1875  0.125  0.0625
#[4,]  0.2500  0.500  0.7500  1.00  0.7500  0.500  0.2500
#[5,]  0.0625  0.125  0.1875  0.25  0.1875  0.125  0.0625
#[6,] -0.1250 -0.250 -0.3750 -0.50 -0.3750 -0.250 -0.1250
#[7,] -0.0625 -0.125 -0.1875 -0.25 -0.1875 -0.125 -0.0625
#
#... and the remaining terms follow suit. 
}
\keyword{models}
