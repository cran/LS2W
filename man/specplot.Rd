\name{specplot}
\alias{specplot}
\title{Plot the LWP associated with a cddews object}
\description{
This function displays the LWP associated with a cddews object, allowing the user to dictate display type.
}
\usage{
specplot(cddews, scaling = "by.level", arrangement = c(3, 3), page = TRUE, dataname = "Image", verbose = 
FALSE, display = "persp", reset = TRUE, wtitle="TRUE")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{cddews}{An object of class \code{cddews} must be supplied to the function.}
  \item{scaling}{Two scaling options are available. The default setting is to scale \code{"by.level"} 
-- an option which is useful if you wish to compare coefficients within a resolution level. The 
alternative setting is \code{global}, whereby one scale factor is chosen for all plots. This factor 
depends on the largest coefficient which is to be included in the suite of plots.
}
  \item{arrangement}{Allows the user to specify the number of spectral plots which are to appear on any given page.}
  \item{page}{An argument which allows the user to request that they be prompted when a new page of plots 
appears. Two options are available: \code{TRUE} or \code{FALSE}.}
  \item{dataname}{A name for the image whose LWP is being displayed. This will appear as part of the title associated with each plot.}
  \item{verbose}{If set to \code{TRUE} certain informative statements are printed to screen during execution.}
  \item{display}{Two display methods are available. Using the option \code{display="persp"} 
displays a 3-dimensional plot of the LWP, using the routine \code{persp}. The option 
\code{display="image"} displays the LWP as a collection of images.}
  \item{reset}{If set to \code{TRUE}, this restores the plot settings to their default configuration 
(i.e. \code{par(mfrow=c(1,1))}). If \code{FALSE}, then the current settings will remain in operation.}
\item{wtitle}{A logical variable which dictates whether a common title is displayed on all spectral plots.}
}
\value{
  No value is returned.
}
\references{ 
Eckley, I.A., Nason, G.P. and Treloar, R.L. (2010) Locally stationary wavelet fields with application to the modelling and analysis of image texture. Journal of the Royal Statistical Society (Series C), 59, 595 - 616. 

Eckley, I.A. and Nason, G.P. (2011). LS2W: Implementing the Locally Stationary 2D Wavelet Process Approach in R, Journal of Statistical Software, 43(3), 1-23.
URL http://www.jstatsoft.org/v43/i03/.

}
\author{Idris Eckley}
\seealso{\code{\link{cddews}}}
\examples{
#
# First let us create a textured image and create a cddews object.
#
monty <- HaarMontage(direction="diagonal")
monty.cddews <- cddews(monty, filter.number=1, family="DaubExPhase")
#
# Finally let's view this using a perspective plot.
#
specplot(monty.cddews, display = "persp")
}
\keyword{models}
