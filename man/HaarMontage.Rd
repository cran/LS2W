\name{HaarMontage}
\alias{HaarMontage}
\title{Generate a 2-D Haar MA process.}
\description{
This function generates a particular set of four 2-D Haar MA processes. These are subsequently collated to form a montage.
}
\usage{
HaarMontage(direction = "diagonal")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{direction}{Three directions can be specified: \code{horizontal}, \code{vertical} and \code{diagonal}. The direction chosen dictates the 
decomposition direction in which the wavelet spectral structure exists.
}
}

\details{
This function generates a realisation of a particular kind of non-stationary lattice model, an example of which is displayed in figure 3 of Eckley, 
Nason and Treloar (2009). 
The returned lattice is the result of combining four HaarMA processes. One process is of order 1, whilst another is of order 2. The two remaining processes are of order 3 and 4 respectively. Each individual lattice has dimension 128*128. The standard deviation of the innovations is 1.
}

\value{
A vector containing 512*512 observations from four collated 2-D Haar MA processes.
}
\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}
\seealso{\code{\link{Haar2MA.diag}}}
\examples{
# Generate a realisation of the non-stationary combined Haar MA
# process with structure in the vertical direction. 
MyHaar2 <- HaarMontage(direction="vertical") 
# Plot it.
#
 image(MyHaar2)
}
\keyword{models}
