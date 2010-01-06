\name{A2name}
\alias{A2name}
\title{Return a D2Amat list object style name.}
\description{
This function returns a character string according to a particular format for naming D2Amat objects.
}
\usage{A2name(J, filter.number, family, switch = "direction")}
\arguments{
  \item{J}{Discrete autocorrelation wavelets will be computed for scales -1 up to scale J. This number should be a negative integer.}
  \item{filter.number}{The index number of the wavelet used to build the PsiJ/PhiJ object.}
  \item{family}{The wavelet family used to build the PhiJIE object.}
  \item{switch}{Allows the user to define how they wish their inner product matrix to be formed. There are two available options:
\code{switch = "direction"} - structures the matrix by scale within each 
decomposition direction. Thus, the ordering goes as follows (-1, V), (-2, V), ...
\code{switch = "scale"} - structures the matrix by direction within each 
scale.  Thus the ordering is as follows (-1,V), (-1, H), (-1, D), (-2, V),(-2, H), ... }
}
\details{
Some of the matrices computed by D2Amat take a long time to compute. Hence it is a good idea to store and re-use them. This function generates a name according to a particular naming scheme that permits a search algorithm to easily find the matrices.
Each matrix has three defining characteristics: its order, filter.number, family and the method of construction of the matrix (switch="direction" or "level"). Each of these characteristics are concatenated together to form a name.
}

\value{
A character string containing the name of a matrix according to a particular naming scheme.
}

\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}

\seealso{ \code{\link{D2Amat}}}
\examples{
#
# What's the name of the order 4 Haar matrix when structured by scale within decompositon direction?
#
A2name(J=-4, filter.number=1, family="DaubExPhase", switch="direction")
#[1] "D2Amat.d.4.1.DaubExPhase"
#
# What's the name of the order 15 Daubechies least-asymmetric wavelet
# with 7 vanishing moments, when ordered by direction within each scale?
#
A2name(J=-15, filter.number=7, family="DaubLeAsymm")
#[1] "D2Amat.l.15.7.DaubLeAsymm"
}

\keyword{models}

