\name{LS2Wsim.cddews}
\alias{LS2Wsim.cddews}

\title{
Simulate an LS2W process with underlying Daubechies wavelet.
}
\description{
Simulates a realisation of an LS2W process of a given spectral structure for Daubechies wavelets.
}
\usage{
\method{LS2Wsim}{cddews}(spectrum,innov=rnorm,...)
}

\arguments{
  \item{spectrum}{
True spectrum of class \code{cddews} which may be the output of \code{cddews}. 
}
  \item{innov}{
The distribution of the innovations of the LS2W process.  Defaults to the (unit) normal distribution.
}
  \item{...}{
Any other arguments passed into the \code{innov} function.
}
}
\details{
This function uses the provided spectral structure to simulate an LS2W process. The provided spectral structure should take positive values, any negative values will be set to zero by the function.

The process of simulation for Daubechies wavelets follows by firstly extracting the coefficients from the provided spectrum and squaring. They are then multiplied by random increments (from \code{rnorm()}) and an appropriate multiple of 4 (depending on the scale) which allows for the effect of basis averaging. After converting to the appropriate form (a \code{wst2D} object) the basis average is taken to give a realisation of an LS2W process. 
}
\value{
A simulated image matrix that will exhibit the spectral characteristics defined by \code{spectrum}.
}
%\references{
%Eckley, I.A., Nason, G.P., and Treloar, R.L. (2010) Locally stationary wavelet fields with application to the modelling and analysis of image texture \emph{Journal of the Royal Statistical Society Applied Statistics}, \bold{59}, 595-616.
%}
\author{
Sarah L Taylor
}


\seealso{
\code{\link{HaarMontage}}
}
\examples{

#Generate an empty spectrum
#
Spectrum<-cddews(matrix(0,64,64),smooth=FALSE)
#
#Add power at the first scale, in the vertical direction
#
Spectrum$S[1,,]<-matrix(1,64,64)
#                                                          
# Simulate an LS2W process with this structure
#           
testimage<- LS2Wsim(Spectrum)
#
  }
  
\keyword{datagen}

