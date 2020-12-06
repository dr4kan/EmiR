setClass (
  "MinimizationResult",

  # Defining slot type
  slots = c(
    algorithm       = "character",
    best_cost       = "numeric",
    best_parameters = "vector",
    cost_history    = "vector"
  ),

  # Initializing slots
  prototype = list(
    algorithm       = as.character(NULL),
    best_cost       = as.numeric(NULL),
    best_parameters = as.vector(NULL),
    cost_history    = as.vector(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "MinimizationResult",
          definition = function(object) {
            cat("  EmiR minimizer: ", object@algorithm, "\n", sep = "")
            cat("       best cost: ", object@best_cost, "\n", sep = "")
            cat(" best parameters: ")
            cat(object@best_parameters, "\n")
          }
)

# plot method
setMethod(f = "plot",
          signature = "MinimizationResult",
          definition = function(x) {
            plot(x@cost_history, type = "l", xlab = "Iteration", ylab = "Cost", main = "PS minimization")
          }
)
