\name{LS2W-package}
\alias{LS2W-package}
\alias{LS2W}
\docType{package}
\title{
Estimates the locally stationary wavelet spectrum for locally stationary 2-D wavelets processes
}
\description{
The LS2W package which provides an implementation of the modelling approach proposed by 
Eckley, Nason, and Treloar (2010) for locally stationary spatial
covariance structure of (regular) lattice processes, such as images. 

The approach, which is an extension of NvSK's time series modelling paradigm, is in part 
motivated by a frequently erent scales. Moreover, several researchers have highlighted that 
the human and mammalian visual systems process images in a multiscale manner, preserving both 
local and global information (see for example, Daugman (1990) or Field (1999)). 
The LS2W package which we introduce implements the estimation scheme described by Eckley
et al. (2010) for such processes. Note that LS2W should be used in conjunction with the
WaveThresh package developed by Nason (1998).
}
\details{
\tabular{ll}{
Package: \tab LS2W\cr
Type: \tab Package\cr
Version: \tab 1.0\cr
Date: \tab 2010-06-01\cr
License: \tab GPL version 2 or newer\cr
}

Note that this package should be used in conjunction with the WaveThresh package. It is
advised that WaveThresh should be loaded first, followed by LS2W. This is because LS2W
currently overwrites a couple of WaveThresh functions to, e.g.,  provide consistent naming structures
for some of the objects created during estimation of  2-D LSW processes.

The central function within the LS2W package is cddews. This executes the LS2W estimation
algorithm as summarised in Algorithm 1, drawing on other functions to calculate the
autocorrelation (ac) wavelets and their inner product matrix. The output of this function is
stored in an object of class "cddews". Print and summary methods are provided for this class
of objects.

Below we provide brief descriptions of the main functions contained within the package. Please
see individual help files for additional information.

\code{PhiJ:} Computes discrete autocorrelation father wavelets. These are automatically stored
within the R session, using a naming convention governed by Phi1Dname. 

\code{PsiiJ:} Computes discrete autocorrelation mother wavelets. These are automatically
stored within the R session, using a naming convention governed by Psi1Dname.

\code{D2ACW:} Computes two-dimensional autocorrelation wavelets. These are autmoatically
stored within the R session, using a naming convention governed by Psi2Dname.

\code{D2autoplot:} Can be used to generate images of two-dimensional discrete autocorrelation
wavelets.

\code{D2Amat:} Computes the inner product matrix of two-dimensional discrete autocorrelation
wavelets. These objects are automatically stored within a session following a naming
convention governed by A2name. 

\code{cddews:} Computes the local wavelet spectrum estimate as described in Eckley et al.
(2010), returning an object of class cddews. 

\code{specplot:} Plots the local wavelet periodogram associated with a cddews object. 

\code{Haar2MA.diag:} Generates a two-dimentional Haar MA object (diagonal direction) of
specied size and order. The functions Haar2MA.vert, Haar2MA.horiz can be used to
construct equivalent realisations for process in the vertical and horizontal direction respectively
whilst HaarMontage generates a realisation of a concatenated two-dimensional
Haar MA process (for an example, see Fig 3 of Eckley and Nason 2009). 
}

\author{
Idris Eckley and Guy Nason.
Maintainer: Who to complain to <i.eckley@lancs.ac.uk> 
}

\references{
Eckley, I. A. and Nason, G. P. (2009) LS2W: The locally stationary 2-D wavelet process
approach in R, In submission

Eckley, I.A., Nason, G.P. and Treloar, R.L. (2010) Locally stationary wavelet fields with application to the modelling and analysis of image texture. 
J. R. Statist. Soc. Series C, 59, (to appear).
}
\keyword{models}
\examples{
    #
    # See comprehensive examples in the help pages for the major functions
    # outlined above.
    #
}
