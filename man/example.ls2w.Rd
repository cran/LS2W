\name{example.ls2w}
\alias{example.ls2w}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{Example of how the LS2W package can be used in texture analysis}
\description{
This function provides an example of how LS2W can be used to 
discriminate between three different textures. The approach provided 
simply consists of (i) sampling a number of subimages from the specified 
data sets; (ii) estimating the local wavelet spectrum  properties for 
each sub-image; (iii) summarising this information in a feature vector; 
(iv) using all feature vectors to identify whether it is possible to 
discriminate between the different image types. Linear Discriminant 
Analysis is the approach which we adopt in this example.
}
\usage{
example.ls2w(n=25, size=64)
}
\arguments{
\item{n}{The number of sub-images to be sampled from each texture type.}
\item{size}{The number of rows-columns required for each sub-image.}
}
\value{
An object of class \code{lda}.
}
\references{Eckley, I.A., Nason, G.P. and Treloar, R.L. (2010) Locally stationary wavelet fields with 
application to the modelling and analysis of image texture. J. R. Statist. Soc. Series C, 59, (to 
appear). }
\author{Idris Eckley}
%\seealso{\code{\link{sample.stats}}}
%\examples{
%##---- Should be DIRECTLY executable !! ----
%##-- ==>  Define data, use random,
%##--	or do  help(data=index)  for the standard data sets.
%}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
