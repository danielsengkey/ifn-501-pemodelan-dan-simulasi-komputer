library(simmer)
interArrival <- c(
	rep(1, 5), rep(6, 20),
	rep(2, 7), rep(7, 10),
	rep(3, 8), rep(8, 8),
	rep(4, 10), rep(9, 7),
	rep(5, 20), rep(10, 5)
)

interArrivalM <- rep(interArrival, 1e4)
interArrival.sample <- sample(
	1:10,
	1e7,
	replace = T,
	prob = c(
		.05,
		.07,
		.08,
		.10,
		.20,
		.20,
		.10,
		.08,
		.07,
		.05
	)
)
interService.sample <- sample(
	1:5,
	1e7,
	replace = T,
	prob = c(
		.1,
		.25,
		.30,
		.25,
		.1
	)
)

customer <-
	trajectory("Customer's path") %>%
	log_("Arrival") %>%
#	timeout(function() interService.sample[runif(1,1,5)]) %>%
	timeout(1) %>%
	log_("Thanks for the service!")

atm <-
	simmer("atm") %>%
#	add_generator("Customer", customer, at(function() interArrival.sample[runif(1,1,10)]))
	add_generator("Customer", customer, at(5))

atm %>% run(until = 1000)
atm %>% get_mon_arrivals()
