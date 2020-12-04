library(EmiR)

eggholder <- function(x) {
  value = -(x[2]+47)*sin(sqrt(abs(x[1]/2+x[2]+47)))+x[1]*sin(sqrt(abs(x[1]-(x[2]+47))));
  return(value)
}

x1 <- parameter("x1", -512, 512)
x2 <- parameter("x2", -512, 512)
l <- list(x1, x2)
ps <- minimize_PS(eggholder, l)

