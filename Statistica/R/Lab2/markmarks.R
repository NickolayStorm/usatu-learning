#xs <- runif(100, 0, 10)
#M <- matrix(xs, 10, 10)

#метод моментов (2/n)*sum(M[1:10])
# метод максимального правдоподобия function(x)((n+1)/n) * max(x)
#quantile - квантиль
# метод порядковых статистик 2*quantile(x, c(0,5))
#экспоненциальное распределение - rexp
# нормальное -- x <- rnorm(n)
#sd -- среднеквадратическое отклонение
#рисование plot(x1, col = "red")
#фикс par(mar=c(1,1,1,1))
#lines: lines(x2, col = 2, lty = 2) 
#M <- cbind(M, rez) #для конечной склейкм)))0000)))
n <- 10
varCount <- 20
foo = rnorm

xs <- foo(n*varCount, 0.5)
M <- matrix(xs, varCount, n)
rez1 <- apply(M, 1, function(x) (2/n)*sum(x))
rez2 <- apply(M, 1, function(x) ((n+1)/n) * max(x))
rez3 <- apply(M, 1, function(x) (2*quantile(x, c(0.5))))

#par(mfrow=c(1, 3))
#plot(rez1, col = "red")
#lines(rez1, col = "red")
#par(new=T)
#plot(rez2, col = "blue")
#lines(rez2, col = "blue")
#par(new=T)
#plot(rez3, col = "yellow")
#lines(rez3, col = "yellow")
#par(new=F)

p11 <- sd(rez1)
p12 <- sd(rez2)
p13 <- sd(rez3)

n <- 40
varCount <- 20
foo = rnorm

xs <- foo(n*varCount, 0.5)
M <- matrix(xs, varCount, n)
rez1 <- apply(M, 1, function(x) (2/n)*sum(x))
rez2 <- apply(M, 1, function(x) ((n+1)/n) * max(x))
rez3 <- apply(M, 1, function(x) (2*quantile(x, c(0.5))))

#par(mfrow=c(1, 3))
#plot(rez1, col = "red")
#lines(rez1, col = "red")
#par(new=T)
#plot(rez2, col = "blue")
#lines(rez2, col = "blue")
#par(new=T)
#plot(rez3, col = "yellow")
#lines(rez3, col = "yellow")
#par(new=F)

p21 <- sd(rez1)
p22 <- sd(rez2)
p23 <- sd(rez3)

n <- 160
varCount <- 20
foo = rnorm

xs <- foo(n*varCount, 0.5)
M <- matrix(xs, varCount, n)
rez1 <- apply(M, 1, function(x) (2/n)*sum(x))
rez2 <- apply(M, 1, function(x) ((n+1)/n) * max(x))
rez3 <- apply(M, 1, function(x) (2*quantile(x, c(0.5))))

#par(mfrow=c(1, 3))
#plot(rez1, col = "red")
#lines(rez1, col = "red")
#par(new=T)
#plot(rez2, col = "blue")
#lines(rez2, col = "blue")
#par(new=T)
#plot(rez3, col = "yellow")
#lines(rez3, col = "yellow")
#par(new=F)

p31 <- sd(rez1)
p32 <- sd(rez2)
p33 <- sd(rez3)

mark10 <- c(p11, p12, p13)
mark40 <- c(p21, p22, p23)
mark160 <- c(p31, p32, p33)

plot(mark10, col = "red")
lines(mark10, col = "red")
par(new=T)
plot(mark40, col = "blue")
lines(mark40, col = "blue")
par(new=T)
plot(mark160, col = "yellow")
lines(mark160, col = "yellow")
par(new=F)