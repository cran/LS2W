\name{Psi2Dname}
\alias{Psi2Dname}
\title{Return a D2ACW list object style name.}
\description{
This function returns a character string according to a particular format for naming D2ACW objects.
}
\usage{
Psi2Dname(J, filter.number, family, switch)
}
\arguments{
  \item{J}{A negative integer representing the order of the D2ACW object.}
  \item{filter.number}{The index number of the wavelet used to build the D2ACW object.}
  \item{family}{The wavelet family used to build the D2ACW object.}
  \item{switch}{Can take the values \code{direction} or \code{level} - enabling control of whether the returned value is structured by scales within a given direction (-1, D), (-2, D), (-3, D), ... or by direction within scales (-1, H), (-1, V), (-1, D), (-2, H), ... }
}
\details{
Some of the objects computed by D2ACW take a long time to compute. Hence it is a good idea to store them and reuse them. This function generates a name according to a particular naming scheme that permits a search algorithm to easily find the matrices.

Each object has three defining characteristics: its order, filter.number and family. Each of these three characteristics are concatenated together to form a name.

This function performs exactly the same role as rmname except for objects produced by D2ACW. 
}
\value{
A character string containing the name of an object according to a particular naming scheme.
}
\references{
Eckley, I.A. and  Nason, G.P. (2005). Efficient computation of the inner-product matrix of discrete
autocorrelation wavelets. Statistics and Computing, 15, 83-92.
}
\author{Idris Eckley}
\seealso{\code{\link{D2ACW}},\code{\link{Psi1Dname}}}
\examples{
#
# What's the name of the order 4 Haar PsiJ object?
#
 Psi2Dname(-4, filter.number=1, family="DaubExPhase", switch="direction")
#[1] "D1Psi.d.4.1.DaubExPhase"
}
\keyword{models}
