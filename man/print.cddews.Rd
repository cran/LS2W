\name{print.cddews}
\alias{print.cddews}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{Print out information about a cddews object in readable form.}
\description{
This function prints out information about an cddews object in a nice human-readable form.

Note that this function is automatically called by R whenever the name of an ccdews object is typed or whenever such an object is returned to the top level of the R interpreter. 
}
\usage{
\method{print}{cddews}(x, ...)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{An object of class ccdews that you wish to print out.}
 \item{...}{This argument actually does nothing in this function! }
}
\details{
See description.
}

\section{Side Effects}{Prints out information about ccdews objects in nice readable format.}

\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}
\seealso{ \code{\link{cddews}}, \code{\link{summary.cddews}}}
\examples{
#
# Generate a cddews object for a HaarMontage realisation 
#
monty <- HaarMontage("diagonal")
tmp <- cddews(monty, filter.number=1, family="DaubExPhase", switch="direction",correct=FALSE)
#
# Now get R to use print.cddews
#
tmp
}
\keyword{models}
