\name{threshold.imwd}
\alias{threshold.imwd}
\title{Threshold two-dimensional wavelet decomposition object}
\description{
This funcion provides various ways to threshold a \code{imwd} class 
object. It contains a minor variation of the equivalent WaveThresh 
function, which is necessary for the LS2W package.
}
\usage{
\method{threshold}{imwd}(x, levels = 3:(x$nlevels - 1), type = "hard", policy = "universal", 
by.level = FALSE, value = 0, dev = var, verbose = FALSE, 
return.threshold = FALSE, compression = TRUE, Q = 0.05, ...)
}
\arguments{
  \item{x}{The two-dimensional wavelet decomposition object that 
you wish to threshold. }
  \item{levels}{a vector of integers which determines which scale 
levels are thresholded in the decomposition. Each integer in the 
vector must refer to a valid level in the \code{imwd} object 
supplied. This is usually any integer from 0 to 
\code{nlevels(wd)-1} inclusive. Only the levels in this vector 
contribute to the computation of the threshold and it application.}
  \item{type}{Determines whether the type of thresholding is 
\code{"hard"} or \code{"soft"}.}
  \item{policy}{selects the technique by which the threshold value 
is selected. Each policy corresponds to a method in the literature. 
At present the different policies are: \code{"universal"}, 
\code{"manual"}, \code{"fdr"}, \code{"probability"}.}
  \item{by.level}{If \code{FALSE} then a global threshold is 
computed on  and applied to all scale levels defined in levels. If 
\code{TRUE} a threshold is computed and applied separately to each 
scale level.}
  \item{value}{This argument conveys the user supplied threshold. 
If the \code{policy="manual"} then value is the actual threshold 
value; if 
\code{policy="probability"} then value conveys the the user supplied 
quantile level. }
  \item{dev}{This argument supplies the function to be used to 
compute the spread of the absolute values coefficients. The 
function supplied must return a value of spread on the variance 
scale (i.e. not standard deviation) such as the \code{var()} 
function. A popular, useful and robust alternative is the \code{madmad} 
function.}
  \item{verbose}{If \code{TRUE} then the function prints out 
informative messages as it progresses.}
  \item{return.threshold}{If this option is \code{TRUE} then the 
actual value of the threshold is returned. If this option is \code{FALSE}
 then a thresholded version of the input is returned.}
  \item{compression}{If this option is \code{TRUE} then this 
function returns a comressed two-dimensional wavelet transform object of 
class imwdc. This can be useful as the resulting object will be 
smaller than if it was not compressed. The compression makes use of 
the fact that many coefficients in a thresholded object will be 
exactly zero. If this option is \code{FALSE} then a larger imwd 
object will be returned.}
  \item{Q}{Parameter for the false discovery rate \code{"fdr"} policy.}
\item{...}{There are no other arguments for this function!}
}
\value{
An object of class \code{imwdc} if the compression option above is 
\code{TRUE}, 
otherwise a \code{imwd} object is returned. In either case the 
returned 
object contains the thresholded coefficients. Note that if the 
\code{return.threshold} option is set to TRUE then the threshold 
values 
will be returned rather than the thresholded object. 
}
\references{Please refer to the equivalent wavethresh help page.

Guy Nason (2010). wavethresh: Wavelets statistics and transforms. R package
  version 4.5. URL http://CRAN.R-project.org/package=wavethresh
}
\author{Idris Eckley and Guy Nason}
\seealso{\code{\link{imwd}}}

\keyword{models}
\keyword{smooth}
