\name{D2Amat}
\alias{D2Amat}
\title{Creates the A matrix required for analysing LS2W processes.}
\description{
This function creates the matrix used to correct the raw periodogram of a LS2W process.
}
\usage{
D2Amat(J, filter.number = 10, family = "DaubLeAsymm", OPLENGTH = 10000, switch = "direction", verbose = FALSE)
}
\arguments{
  \item{J}{The level to which the decomposition must extend. This number should be a positive integer. }
  \item{filter.number}{The index of the wavelet used to compute the correction matrix A.}
  \item{family}{The wavelet family used to compute A.}
  \item{OPLENGTH}{This integer variable defines some workspace of length OPLENGTH which is used by the code. If the workspace is not long enough, then the routine will stop and tell you what OPLENGTH should be set to.}
  \item{switch}{Dictates the structure of the matrix [by direction or by scale].}
  \item{verbose}{Allows certain informative messages to be printed on screen.}
}
\value{
A matrix of order (3J)*(3J) containing the elements A_(j,l) defined in Eckley, Nason and Treloar 
(2010). Each element is the sum over all lags of the product of the matrix coefficients of a 2-D DACW 
matrix at level $j_1$ in direction $ l_1$ with that of another (not necessarily different) matrix of DACW 
coefficients at level $j_2$ in direction $l_2$. The structure of this matrix is as follows: the rows and 
columns of the matrix are labeled $1,\ldots, 3J$ in accordance with the notation of Eckley, Nason and 
Treloar (2010). When \code{switch="direction"} the matrix has the following structure:
\item{}{Levels $1,\ldots, J$ correspond to the different levels of the decomposition in the vertical direction. $1=$fine and $J =$coarse scale.}
\item{}{Levels $J+1, \ldots, 2J$ correspond to the different levels in the horizontal direction.}
\item{}{Levels $2J+1,\ldots, 3J$ correspond to the different directions in the diagonal direction.}

When \code{switch="level"}, the row and column elements cycle as follows:\\
level 1 vertical, level 1 horizontal, level 1 diagonal, level 2 vertical, etc.
}

\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}
\examples{
#
# Let's compute the A matrix for the Haar wavelet in 2-D.
#
D2Amat(J=-2, filter.number=1, family="DaubExPhase", switch="direction")
#       1      2      3      4      5      6
#1 2.2500 1.3125 0.2500 0.3125 0.7500 0.9375
#2 1.3125 4.8125 0.3125 0.5625 0.1875 1.3125
#3 0.2500 0.3125 2.2500 1.3125 0.7500 0.9375
#4 0.3125 0.5625 1.3125 4.8125 0.1875 1.3125
#5 0.7500 0.1875 0.7500 0.1875 2.2500 0.5625
#6 0.9375 1.3125 0.9375 1.3125 0.5625 3.0625
#
# And now for the same matrix structured by level
#
D2Amat(J=-2, filter.number=1, family="DaubExPhase", switch="level")
#       1      2      3      4      5      6
#1 2.2500 0.2500 0.7500 1.3125 0.3125 0.9375
#2 0.2500 2.2500 0.7500 0.3125 1.3125 0.9375
#3 0.7500 0.7500 2.2500 0.1875 0.1875 0.5625
#4 1.3125 0.3125 0.1875 4.8125 0.5625 1.3125
#5 0.3125 1.3125 0.1875 0.5625 4.8125 1.3125
#6 0.9375 0.9375 0.5625 1.3125 1.3125 3.0625
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
