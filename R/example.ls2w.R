`example.ls2w`<-function(n=25, size=64)
{
load("images.rda")
A.stats<- sample.stats(x=A, n, size)
B.stats<- sample.stats(x=B, n, size)
C.stats<- sample.stats(x=C, n, size)
all.stats<-rbind(A.stats, B.stats, C.stats)
imlabels<-c(rep("a",n), rep("b",n),rep("c",n))
all.stats.lda<-lda(all.stats, imlabels)
all.stats.ld<-predict(all.stats.lda, dimen=2)$x
plot(all.stats.ld, type="n", xlab="First Linear Discriminant", ylab="Second Linear Discriminant")
text(all.stats.ld, imlabels)
return(all.stats.lda)
}
