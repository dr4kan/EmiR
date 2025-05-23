% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/METHOD__Minimize.R
\name{minimize}
\alias{minimize}
\title{Minimize an Objective Function}
\usage{
minimize(algorithm_id, obj_func, parameters, config, constraints = NULL, ...)
}
\arguments{
\item{algorithm_id}{id of the algorithm to be used. See \link[EmiR]{list_of_algorithms} for
the list of the available algorithms.}

\item{obj_func}{objective function be minimized/maximized.}

\item{parameters}{list of parameters composing the search space for the objective function.
Parmeters are requested to be objects of class \code{Parameter} (see \link[EmiR]{parameter}).}

\item{config}{an object with the configuration parameters of the chosen algorithm. For each
algorithm there is different function for the tuning of its configuration parameter, as
reported in the following list:
\describe{
\item{\link[EmiR]{config_abc}}{ -- configuration function for the \emph{Artificial Bee Colony Algorithm}.}
\item{\link[EmiR]{config_bat}}{ -- configuration function for the \emph{Bat Algorithm}.}
\item{\link[EmiR]{config_cs} }{ -- configuration function for the \emph{Cuckoo Search Algorithm}.}
\item{\link[EmiR]{config_ga} }{ -- configuration function for the \emph{Genetic Algorithm}.}
\item{\link[EmiR]{config_gsa}}{ -- configuration function for the \emph{Gravitational Search Algorithm}.}
\item{\link[EmiR]{config_gwo}}{ -- configuration function for the \emph{Grey Wolf Optimizer Algorithm}.}
\item{\link[EmiR]{config_hs} }{ -- configuration function for the \emph{Harmony Search Algorithm}.}
\item{\link[EmiR]{config_ihs}}{ -- configuration function for the \emph{Improved Harmony Search Algorithm}.}
\item{\link[EmiR]{config_mfo}}{ -- configuration function for the \emph{Moth-flame Optimization Algorithm}.}
\item{\link[EmiR]{config_ps} }{ -- configuration function for the \emph{Particle Swarm Algorithm}.}
\item{\link[EmiR]{config_sa} }{ -- configuration function for the \emph{Simulated Annealing algorithm}.}
\item{\link[EmiR]{config_woa}}{ -- configuration function for the \emph{Whale Optimization Algorithm}.}
}}

\item{constraints}{list of constraints. Constraints are requested to be objects of
class \code{Constraint} (see \link[EmiR]{constraint}).}

\item{...}{additional options (see \link[EmiR]{MinimizerOpts}).}
}
\value{
\code{minimize} returns an object of class \code{OptimizationResults} (see \link[EmiR]{OptimizationResults}).
}
\description{
Minimize (or maximize) an objective function, possibly subjected to inequality constraints, using
any of the algorithms available in EmiR.
}
\examples{
\dontrun{
 results <- minimize(algorithm_id = "BAT", obj_func = ob, config = conf,
 parameters = list(p1,p2, p3, p4), constraints = list(c1,c2,c3),
    save_pop_history = TRUE, constrained_method = "BARRIER",
    constr_init_pop = TRUE, oob_solutions = "RBC", seed = 1)
}


}
