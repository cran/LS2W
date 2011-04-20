`HaarMontage` <-
function(direction = "diagonal")
{
#
# HaarMontage program ... creates a realisation of a 
# non-stationary LS2W process. One can specify which
# directions contributions should be made in.
#
if(direction == "diagonal") {
   x1 <- Haar2MA.diag(n = 128., order = 1.)
   x2 <- Haar2MA.diag(n = 128., order = 2.)
   x3 <- Haar2MA.diag(n = 128., order = 3.)
   x4 <- Haar2MA.diag(n = 128., order = 4.)
   temp1 <- cbind(x1, x2)
   temp2 <- cbind(x3, x4)
   Monty <- rbind(temp1, temp2)
   return(Monty)
}
if(direction == "vertical") {
   x1 <- Haar2MA.vert(n = 128., order = 1.)
   x2 <- Haar2MA.vert(n = 128., order = 2.)
   x3 <- Haar2MA.vert(n = 128., order = 3.)
   x4 <- Haar2MA.vert(n = 128., order = 4.)
   temp1 <- cbind(x1, x2)
   temp2 <- cbind(x3, x4)
   Monty <- rbind(temp1, temp2)
   return(Monty)
}
if(direction == "horizontal") {
   x1 <- Haar2MA.horiz(n = 128., order = 1.)
   x2 <- Haar2MA.horiz(n = 128., order = 2.)
   x3 <- Haar2MA.horiz(n = 128., order = 3.)
   x4 <- Haar2MA.horiz(n = 128., order = 4.)
   temp1 <- cbind(x1, x2)
   temp2 <- cbind(x3, x4)
   Monty <- rbind(temp1, temp2)
   return(Monty)
}
else stop("\nDirection can only take the values horizontal, vertical or diagonal!\n")
}

