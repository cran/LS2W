\name{Haar2MA.vert}
\alias{Haar2MA.vert}
\title{Generate 2-D Haar MA process (vertical direction).}
\description{
These functions generate an arbitrary number of observations from a Haar MA process of any order with a particular variance. We will focus here on 
\code{Haar2MA.vert} --- the routine which generates processes having spectral structure solely in the vertical decomposition direction.
}
\usage{
Haar2MA.vert(n, sd = 1, order = 5)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{n}{The dimension of the realisation that you want to create. Note that \code{n} does NOT have to be a power of two, though it is square 
(nxn).}
  \item{sd}{The standard deviation of the innovations.}
  \item{order}{The order of the MA process.}
}
\details{
A two-dimensional Haar MA process is a special kind of moving-average (MA) field. A \emph{vertical} Haar MA process of order $k$ is a MA field of 
order 
$2^k-1$, the coefficients of the process being given by the filter coefficients of the two-dimensional, discrete Haar wavelet at various scales within 
the vertical direction. For example: the vertical Haar MA field of order 1 is an MA process of order 1. 
It is possible to define such processes for other wavelets as well.

}
\value{
A matrix containing a realisation of the specified dimension, order and standard deviation.
}
\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).}
\author{Idris Eckley}
\seealso{\code{\link{Haar2MA.diag}}, \code{\link{HaarMontage}}}
\examples{
#
# Generate a realisation of a diagonal component 2-D MA field
# of order 4.
#
image1 <- Haar2MA.vert(n=128, sd=3, order=4)
#
#
#
}
\keyword{models}
