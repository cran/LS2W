\name{getdata}
\alias{getdata}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{Extracts detail coefficients from imwd object  }
\description{
This function is called by cddews to extract the detail coefficients from an object of class imwd.
}
\usage{
getdata(imwd, switch, co.type = "sqr", verbose = FALSE)
}
\arguments{
  \item{imwd}{An object of class imwd.}
  \item{switch}{Dictates whether the extracted information is structured by \code{"direction"} or 
\code{"scale"}.}
  \item{co.type}{Dictates the coefficient type which is used. For cddews this must be \code{"sqr"}. }
  \item{verbose}{Allows certain informative statements to be printed to the screen}
}
\value{
An array which can be used by cddews.
}
\references{Eckley, I.A., Nason, G.P. and Treloar, R.L. (2010) Locally stationary wavelet fields with 
application to the modelling and analysis of image texture. J. R. Statist. Soc. Series C, 59, (to 
appear). }
\author{Idris Eckley}
\seealso{\code{\link{cddews}}}
%\examples{
%##---- Should be DIRECTLY executable !! ----
%##-- ==>  Define data, use random,
%##--	or do  help(data=index)  for the standard data sets.
%}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
