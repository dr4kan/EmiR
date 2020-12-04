setClass (
  "MinimizationResult",

  # Defining slot type
  representation (
    best_cost       = "numeric",
    best_parameters = "vector",
    cost_history    = "vector"
  ),

  # Initializing slots
  prototype = list(
    best_cost       = as.numeric(NULL),
    best_parameters = as.vector(NULL),
    cost_history    = as.vector(NULL)
  ),
)

# overriding the print function
# setMethod(f = "show",
#           signature = "Parameter",
#           definition = function(object) {
#             cat(object@name, ": [ ", object@min_val, ", ", object@max_val, " ]", sep = "")
#           }
# )

# plot method
setMethod(f = "plot",
          signature = "MinimizationResult",
          definition = function(x) {
            plot(ps@cost_history, type = "l", xlab = "Iteration", ylab = "Cost", main = "PS minimization")
          }
)
