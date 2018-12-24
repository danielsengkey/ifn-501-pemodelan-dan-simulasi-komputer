normal30.hc <- normal30rep$scalars$value
nsb30.hc <- noSendBack30rep$scalars$value

normal100.hc <- normal100rep$scalars$value
nsb100.hc <- noSendBack100rep$scalars$value

normal1000.hc <- normal1000rep$scalars$value
nsb1000.hc <- noSendBack1000rep$scalars$value

normal10000.hc <- normal10000rep$scalars$value
nsb10000.hc <- noSendBack10000rep$scalars$value

col30 <- rgb(
	0,
	0,
	1,
	alpha = 0.2
)

col100 <- rgb(
	0,
	1,
	0,
	alpha = 0.2
)

col1000 <- rgb(
	1,
	0,
	0,
	alpha = 0.2
)

col10000 <- rgb(
	0.5,
	0.5,
	1,
	alpha = 0.2
)

getXMax <- function(x, y){
	ret <- max(c(x, y))
	
	return(ret*1.1)
}

getYMax <- function(x, y){
	ret <- max(
			c(
				hist(x, plot = F)$density,
				hist(y, plot = F)$density
			)
		)
	
	return(ret*1.1)
}

######## Per Rep -----------------
normal.col <- col30
nsb.col <- col1000
xlim <- c(0, getXMax(normal30.hc, nsb30.hc))
ylim <- c(0, getYMax(normal30.hc, nsb30.hc))
hist(
	x = normal30.hc,
	main = "Hop Counts comparison for 30 Repetitions",
	col = normal.col,
	xlim = xlim,
	ylim = ylim,
	xlab = "Hop Counts",
	freq = F,
	cex = 0.8
)
hist(
	x = nsb30.hc,
	col = nsb.col,
	freq = F,
	add = T
)
lines(
	density(normal30.hc),
	col = "blue"
)
lines(
	density(nsb30.hc),
	col = "red"
)
legend(
	x = "topright",
	legend = c("Normal", "No Send Back"),
	fill = c(normal.col, nsb.col),
	inset = 0.05
)

############# Plotting Function --------------
plotDensity <- function(x, y, mainTitle){
	xlim <- c(0, getXMax(x, y))
	ylim <- c(0, getYMax(x, y))
	breaksX <- seq(0, max(x)*1.1, by = 5)
	breaksY <- seq(0, max(y)*1.1, by = 5)
	
	hist(
		x = x,
		main = mainTitle,
		col = normal.col,
		xlim = xlim,
		ylim = ylim,
		xlab = "Hop Counts",
		breaks = breaksX,
		freq = F,
		cex.main = 0.8
	)
	hist(
		x = y,
		col = nsb.col,
		breaks = breaksY,
		freq = F,
		add = T
	)
	lines(
		density(normal30.hc),
		col = "blue"
	)
	lines(
		density(nsb30.hc),
		col = "red"
	)
	legend(
		x = "topright",
		legend = c("Normal", "No Send Back"),
		fill = c(normal.col, nsb.col),
		inset = 0.05
	)
}