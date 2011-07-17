\name{imwd}
\alias{imwd}
\title{Two-dimensional wavelet transform (decomposition). }
\description{
This function replaces WaveThresh's imwd which currently contains a minor bug (for the case 
\code{type="station"}_.The function can perform two types of two-dimensional discrete wavelet transform 
(DWT). The standard transform (\code{type="wavelet"}) computes the 2D DWT according to Mallat's pyramidal 
algorithm (Mallat, 1989). 
The spatially ordered non-decimated 2D DWT (NDWT) (\code{type="station"}) contains all possible spatially 
shifted versions of the DWT. The order of computation of the DWT is O(n), and it is O(n log n) for the 
NDWT if n is the number of pixels. 
}
\usage{
imwd(image, filter.number = 10, family = "DaubLeAsymm", type = "wavelet", bc = "periodic", RetFather = TRUE, verbose = FALSE)
}
\arguments{
  \item{image}{A square matrix containing the image data you wish to decompose. The sidelength of this 
matrix must be a power of 2. }
  \item{filter.number}{This selects the smoothness of wavelet that you want to use in the decomposition. 
By default this is 10, the Daubechies least-asymmetric orthonormal compactly supported wavelet with 10 
vanishing moments.}
  \item{family}{Specifies the family of wavelets that you want to use. The options are "DaubExPhase" and 
"DaubLeAsymm".}
  \item{type}{Specifies the type of wavelet transform. This can be "wavelet" (default) in which case the 
standard 2D DWT is performed (as in previous releases of WaveThresh). If type is "station" then the 2D 
spatially-ordered non-decimated DWT is performed. At present, only periodic boundary conditions can be 
used with the 2D spatially ordered non-decimated wavelet transform.}
  \item{bc}{specifies the boundary handling. If bc=="periodic" the default, then the function you 
decompose is assumed to be periodic on it's interval of definition, if bc=="symmetric" then the function 
beyond its boundaries is assumed to be a symmetric reflection of the function in the boundary. The 
symmetric option was the implicit default in releases prior to 2.2. Note that only periodic boundary 
conditions are valid for the 2D spatially-ordered non-decimated wavelet transform.}
  \item{RetFather}{If TRUE then this argument causes the scaling function coefficients at each 
resolution level to be returned as well as the wavelet coefficients. If FALSE then no scaling function 
coefficients are returned. The opportunity of returning father wavelet coefficients has been added since 
previous versions of WaveThresh.}
  \item{verbose}{Controls the printing of "informative" messages whilst the computations progress. Such 
messages are generally annoying so it is turned off by default.}
}
\value{
An object of class imwd object containing the two-dimensional wavelet transform (possibly 
spatially-ordered non-decimated). 
}
\references{Mallat, S.G. (1989b). 
A theory for multiresolution signal decomposition: the wavelet representation. IEEE Trans. Pattn Anal. 
Mach. Intell., 11, 674-693.

Eckley, I.A. and Nason, G.P. (2011). LS2W: Implementing the Locally Stationary 2D Wavelet Process Approach in R, Journal of Statistical Software, 43(3), 1-23.
URL http://www.jstatsoft.org/v43/i03/.

}
\author{Idris Eckley  and Guy Nason}
\seealso{\code{\link{cddews}}}
\examples{
#
#First let's create an image
#
tmp <- HaarMontage("diagonal")
#
# Now let's do the 2D discrete wavelet transform on the image.
#
lwd <- imwd(tmp)
#
# Let's look at the coefficients
#
plot(lwd)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
