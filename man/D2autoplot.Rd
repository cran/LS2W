\name{D2autoplot}
\alias{D2autoplot}
\title{Plots a two-dimensional autocorrelation wavelet.}
\description{
Plots a 2-D autocorrelation wavelet for a given wavelet ata specific scale and decomposition direction. 
}
\usage{
D2autoplot(J, filter.number = 1, family = "DaubExPhase", direction = 3,main = "2-D Autocorrelation Wavelet", OPLENGTH = 10000, scaling = "other", box="TRUE")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{J}{A negative integer representing the order of the autocorrelation wavelet to be displayed.}
  \item{filter.number}{The index of the wavelet to be used.}
  \item{family}{The wavelet family employed.}
  \item{direction}{This variable dictates which of the three possible wavelets at a given level is being displayed. Recall from the work of Daubechies, that one way of constructing 2-D wavelets results in three wavelets. One corresponds to the vertical components of an image, another refers to the horizontal components whilst the final wavelet deals with the diagonal. Thus, keeping this construction in mind, it is easy to see that there are three autocorrelation wavelets when we are in two dimensions. This argument simply allows the user to specify which decomposition direction is to be displayed. Direction 1 corresponds to the Vertical direction, Direction 2 to the Horizontal direction whilst specifying direction=3 means that we wish the Diagonal ACW to be displayed.}
  \item{main}{Allows the user to specify a common title for each of the various spectral plots generated}
  \item{OPLENGTH}{This integer variable defines some workspace of length OPLENGTH which is used by the code. If the workspace is not long enough, then the routine will stop and tell you what OPLENGTH should be set to.}
  \item{scaling}{Allows the user to scale the x and y-axes (of minimal use!). There are currently two options. The first is Haar, which scales the x and y axes so that their entries are those of the actual Haar 2-D ACW. The second is other - which basically allows S-plus to do its ow}
  \item{box}{Allows the user to specify whether the resulting plotted is boxed.}
}

\value{
 None.
}

\section{Side Effects}{Produces an image corresponding to the 2-D discrete autocorrelation wavelet of a given wavelet at a specific scale and decomposition direction.}
 

\references{ 
Eckley IA, Nason GP, Treloar RL (2010). Locally stationary elds with application to the
modelling and analysis of image texture. Journal of the Royal Statistical Society (Series
C), 59, (to appear).
}
\author{Idris Eckley}
\examples{
#
# To produce the Haar 2-D discrete autocorrelation wavelet at level -6 in the     diagonal horizontal direction type
#
 D2ACW(J=-6, filter.number=1, family="DaubExPhase")
#
#Now let's look at the actual autocorrelation wavelet at that level
#

 D2autoplot(J=-6, filter.number=1, family="DaubExPhase", scaling="Haar")
}

% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{models}
