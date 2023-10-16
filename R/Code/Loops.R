typeI.tester <- function(mu0,sigma,n,alpha,ITERATIONS=10000){
  pvals <- rep(NA,ITERATIONS)
  for(i in 1:ITERATIONS){
    temporary.sample <- rnorm(n=n,mean=mu0,sd=sigma)
    temporary.mean <- mean(temporary.sample)
    temporary.sd <- sd(temporary.sample)
    pvals[i] <- 1-pt((temporary.mean-mu0)/(temporary.sd/sqrt(n)),df=n-1)
  }
  return(mean(pvals<alpha))
}