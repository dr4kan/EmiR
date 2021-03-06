% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/FUNC__Bohachevsky.R
\name{bohachevsky_func}
\alias{bohachevsky_func}
\title{Bohachevsky Function}
\usage{
bohachevsky_func(x)
}
\arguments{
\item{x}{numeric or complex vector.}
}
\value{
The value of the function.
}
\description{
\loadmathjax
Implementation of 2-dimensional Bohachevsky function.
}
\details{
On an 2-dimensional domain it is defined by

\mjdeqn{f(\vec{x}) = x_{1}^2 + 2x_{2}^2 -0.3\cos(3\pi x_{1})-0.4\cos(4\pi x_{2})+0.7}{f(x) = x_{1}^2 + 2x_{2}^2 -0.3cos(3\pi x_{1})-0.4cos(4\pi x_{2})+0.7}
and is usually evaluated on
\mjeqn{x_{i} \in [ -100, 100 ]}{x_{i} in [ -100, 100 ]}, for all
\mjeqn{i=1,2}{i=1,2}. The function has one global minimum at
\mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{\vec{x} = [ 0, 0 ]}{x = [ 0, 0 ]}.
}
\references{
\insertRef{bohachevsky1986generalized}{EmiR}
}
