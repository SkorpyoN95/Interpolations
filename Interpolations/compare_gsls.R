library("ggplot2")
results = read.csv("times2.csv")
avg_results = aggregate( time ~ size:method, data=results, FUN=mean)
avg_results$sd = aggregate( time ~ size:method, data=results, FUN=sd)$time
ggplot(avg_results, aes(x=size,y=time,colour=method)) + geom_line() +
geom_errorbar(aes(ymin=time-sd, ymax=time+sd), width=.1)