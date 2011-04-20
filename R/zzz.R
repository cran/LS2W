## this is the equivalent of .First.lib (for packages with a namespace)
## note that it is general, so the name of the package etc doesn't need
## to be specified (just say whatever you want in the prints though).

.onAttach <-function(lib,pkg)
{
ver <- read.dcf(file.path(lib, pkg, "DESCRIPTION"), "Version")
     ver <- as.character(ver)	
curdate <- read.dcf(file.path(lib, pkg, "DESCRIPTION"), "Date")
    curdate <- as.character(curdate)	

# Welcome message (MAN):

cat("\n")
cat("***********************************************************\n")
cat("LS2W: a package for 2D Locally Stationary Wavelet processes\n\n")
cat("--- Written by Idris Eckley and Guy Nason ---\n")
cat(" Current package version: ",ver," (",curdate,") \n\n",sep="")
cat("\n")
cat("***********************************************************\n")
cat("\n")

}
