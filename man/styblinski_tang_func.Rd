% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/FUNC__Styblinski-Tang.R
\name{styblinski_tang_func}
\alias{styblinski_tang_func}
\title{Styblinski-Tang Function}
\usage{
styblinski_tang_func(x)
}
\arguments{
\item{x}{numeric or complex vector.}
}
\value{
The value of the function.
}
\description{
\loadmathjax
Implementation of n-dimensional Styblinski-Tang function.
}
\details{
On an n-dimensional domain it is defined by

\mjdeqn{f(\vec{x}) = \frac{1}{2} \sum_{i=1}^{n} \left( x_{i}^4 - 16x_{i}^2 + 5x_{i} \right),}{f(x) = 1/2 sum_1^n ( x_i^4 -16\emph{x_i^2 +5}x_i ),}
and is usually evaluated on
\mjeqn{x_{i} \in [ -5, 5 ]}{x_{i} in [-5, 5]}, for all
\mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
\mjeqn{f(\vec{x}) = -39.16599n}{f(x) = -39.16599n} for \mjeqn{x_{i}=-2.903534}{x_i=-2.903534} for all \mjeqn{i=1,...,n}{i=1,...,n}.
}
\references{
\insertRef{Styblinski1990}{EmiR}
}
