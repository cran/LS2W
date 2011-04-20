\name{Phi1Dname}
\alias{Phi1Dname}
\title{Return a PhiJ list object style name.}
\description{
This function returns a character string according to a particular format for naming PhiJ objects.
}
\usage{
Phi1Dname(J, filter.number, family)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{J}{A negative integer representing the order of the PhiJ object.}
  \item{filter.number}{The index number of the wavelet used to build the PhiJ object.}
  \item{family}{The wavelet family used to build the PhiJ object.}
}
\details{
Some of the objects computed by PhiJ take a long time to compute. Hence it is a good idea to store them and reuse them. This function generates a name according to a particular naming scheme that permits a search algorithm to easily find the matrices.

Each object has three defining characteristics: its order, filter.number and family. Each of these three characteristics are concatenated together to form a name.

This function performs exactly the same role as rmname except for objects produced by PhiJ. 
}

\value{
A character string containing the name of an object according to a particular naming scheme.
}
\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}

\examples{
#
# What's the name of the order 4 Haar PhiJ object?
#
 Phi1Dname(-4, filter.number=1, family="DaubExPhase")
#[1] "D1Phi.4.1.DaubExPhase"
#
# What's the name of the order 12 Daubechies least-asymmetric wavelet PhiJ
# with 7 vanishing moments?
#
 Phi1Dname(-12, filter.number=7, family="DaubLeAsymm")             
#[1] "D1Phi.12.7.DaubLeAsymm"
}

% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
