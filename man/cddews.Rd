\name{cddews}
\alias{cddews}
\title{Compute the local wavelet spectrum estimate}
\description{This function computes the local wavelet spectrum (LWS) estimate of an image (or non-decimated wavelet transform of a time series). The estimate is computed by taking the non-decimated wavelet transform of the image, squaring the detail coefficients, smoothing using wavelet shrinkage and then correcting the redundancy caused by use of the non-decimated wavelet transform.
}
\usage{
cddews(data, filter.number = 1, family = "DaubExPhase", switch = "direction", correct = TRUE, verbose = FALSE, smooth = TRUE, sm.filter.number = 4, 
sm.family = "DaubExPhase", levels = 3:6, type = "hard", policy = "LSuniversal", by.level = FALSE, value = 0, dev = var)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{data}{The image you want to analyse.}
  \item{filter.number}{This selects the index of the wavelet used in the analysis of the time series (i.e.\ the wavelet basis functions used to model the time series). For Daubechies compactly supported wavelets the filter number is the number of vanishing moments.}
  \item{family}{This selects the wavelet family to use in the analysis of the time series (i.e.\ which wavelet family to use to model the time 
series). Only use the Daubechies compactly supported wavelets \code{DaubExPhase} and \code{DaubLeAsymm}.}
  \item{switch}{ This allows one to order the corrected spectrum by scale or decomposition direction. Two options are available 
 \code{switch = "direction"}: structures the matrix by scale within each decomposition direction.  Thus, the ordering goes as 
follows $(-1, V), (-2, V), (-3, V)\ ...$. 
 \code{switch = "level"} structures the matrix by direction within  each scale. Thus the ordering is as follows $(-1,V), (-1, H), (-1, D), 
(-2, V), (-2, H), (-2, D), ...$.  For further details, see Eckley Nason and Treloar (2010). }
  \item{correct}{Eckley, Nason and Treloar (2009) have  demonstrated that, as a consequence of the inherent redundancy of the non-decimated wavelet 
transform, the raw wavelet spectrum  is biased. However, an asymptotically unbiased estimator may be obtained by applying the inverse of the inner 
product matrix of discrete autocorrelation wavelets. This argument permits the user to decide whether or not to correct for this inherent bias.}  
  \item{verbose}{Allows certain informative messages to be printed on screen.}
  \item{smooth}{This binary argument allows the user to specify whether or not the resulting local wavelet periodogram 
should  be smoothed to obtain. It is advised that this option be set to \code{TRUE} in order that consistent estimates be obtained.}
  \item{sm.filter.number}{Selects the index number of the wavelet that smooths each scale of the wavelet periodogram.}
  \item{sm.family}{Selects the wavelet family that smooths each scale of the wavelet periodogram.}
  \item{levels}{This specifies the levels which are smoothed when performing the wavelet shrinkage.}
  \item{type}{The type of shrinkage: either \code{"hard"} or \code{"soft"}.}
  \item{policy}{This dictates the threshold selection method used for smoothing. For LWS estimation \code{LSuniversal} is recommended for thi 
Chi-squared nature of the periodogram coefficients.}
  \item{by.level}{If \code{TRUE} then the wavelet shrinkage is performed by computing and applying a separate threshold to each level in the 
transform of each scale. Note that each scale in the LWS is smoothed separately and independently. Each smooth consists of taking the (second-stage) 
non-decimated wavelet transform and applying a threshold to each level of a wavelet transformed scale.

If \code{FALSE} then the same threshold is applied to the discrete wavelet transform of a scale. Different thresholds may be computed for different 
scales but the threshold will be the same for each level arising from the non-decimated transform of a scale.
}
  \item{value}{This argument supplies the threshold value used when a manual policy is adopted.}
  \item{dev}{The method for estimating the variance of the empirical wavelet coefficients for smoothing purposes.}
}
\details{
This function computes an estimate of the directionally dependent wavelet spectrum of an image according to the work of  Eckley, Nason and Treloar 
(2010). The  function works as follows: 
  
1. The non-decimated wavelet transform of the series is computed.

2. The squared modulus of the non-decimated wavelet transform is computed (this is the raw 
wavelet periodogram, which is returned).

3. The squared modulus is smoothed using wavelet shrinkage.

4. The smoothed coefficients are corrected using the inverse of the inner product matrix of 
the autocorrelation wavelets. 
To display the LWS use the \code{specplot} function on the \code{S} component (see the examples below).}
\value{
  A list with the following components: 
\item{S:}{The directionally dependent wavelet spectral estimate of the input data. This is a \emph{large} array, the first
dimension refers  to a specific scale-direction pair (see Eckley et al. (2009) for further details). The next dimension refers to the rows of the 
spectral image, whilst the third element refers to the columns of the image. }
\item{datadim}{The dimension of the original image.}
\item{filter.number:}{This gives the index of the wavelet used in the analysis of the image (i.e. the wavelet basis functions used in the 
modelling). For Daubechies compactly supported wavelets the filter number is the number of vanishing moments.}
\item{family:}{This contains the wavelet family used in the analysis of the image (i.e. the wavelet family used in the modelling).}
\item{structure:}{Explains the structure of the inner product matrix and S. It can only take two values, \code{direction} and 
\code{scale}.}
\item{nlevels:}{The number of levels in the decomposition.}
\item{correct:}{\code{TRUE} or \code{FALSE}, depending on whether the user corrected for the bias.}
\item{smooth:}{\code{TRUE} or \code{FALSE}, depending on whether the LWP has been smoothed.}
\item{date:}{The date when the analysis was perfromed.}
}
\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}
\seealso{\code{\link{D2Amat}}, \code{\link{specplot}}}
\examples{
# Apply the cddews estimate function to a HaarMontage realisation
#
monty <- HaarMontage("diagonal")
monty.cddews <- cddews(monty, filter.number=1, family="DaubExPhase")
monty.cddews
}
\keyword{models}
