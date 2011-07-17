\name{D1Amat}
\alias{D1Amat}
\title{Inner product matrix of ac wavelets(1-D)}
\description{
This function calculates the inner product matrix of discrete autocorrelation wavelets (1D).
}
\usage{
D1Amat(J, filter.number = 10, family = "DaubLeAsymm", tol = 1e-100, verbose = FALSE)
}
\arguments{
 \item{J}{The level to which the decomposition must extend. This number should
be a positive integer. }
  \item{filter.number}{The index of the wavelet used to compute the correction m
atrix A.}
  \item{family}{The wavelet family used to compute A.}
  \item{tol}{In the brute force computation for Daubechies compactly supported wavelets many inner product computations are performed. This 
tolerance discounts any results which are smaller than tol which effectively defines how long the inner product/autocorrelation products 
are. }
  \item{verbose}{Logical variable, if set to \code{TRUE} informative statements are printed to screen during execution of the function.}
}
\value{
A matrix of order (-J)x(-J) containing the inner product matrix of the discrete non-decimated autocorrelation matrices. 
}
\references{
Nason, G.P., von Sachs, R. and Kroisandt, G. (2000) Wavelet processes and adaptive estimation of the evolutionary wavelet 
spectrum. J. R. Statist. Soc. Series B, 62, 271-292. 

Eckley, I.A. and Nason, G.P. (2011). LS2W: Implementing the Locally Stationary 2D Wavelet Process Approach in R, Journal of Statistical Software, 43(3), 1-23.
URL http://www.jstatsoft.org/v43/i03/.
}

\author{Idris Eckley}
\note{ 
An equivalent function \code{ipndacw} already exists in WaveThresh. This function is added to help create a consistent naming convention 
across both the one- and two-dimensional inner product matrix of ac wavelets.
}
\seealso{\code{\link{D2Amat}}}
%\examples{
%##---- Should be DIRECTLY executable !! ----
%##-- ==>  Define data, use random,
%##--	or do  help(data=index)  for the standard data sets.
%
%}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
