setClass (
  "MinimizationResult",

  # Defining slot type
  slots = c(
    algorithm       = "character",
    best_cost       = "numeric",
    best_parameters = "vector",
    parameter_names = "vector",
    cost_history    = "vector"
  ),

  # Initializing slots
  prototype = list(
    algorithm       = as.character(NULL),
    best_cost       = as.numeric(NULL),
    best_parameters = as.vector(NULL),
    parameter_names = as.vector(NULL),
    cost_history    = as.vector(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "MinimizationResult",
          definition = function(object) {
            cat("\n")
            cat("         EmiR Minimization Results \n")
            cat("  --------------------------------------- \n")
            cat("           minimizer | ", object@algorithm, "\n", sep = "")
            cat("       minimum value | ", object@best_cost, "\n", sep = "")
            cat("     best parameters | ")
            for (i in 1:length(object@best_parameters)) {
              if (i == 1) {
                cat(object@parameter_names[i], " = ", object@best_parameters[i], "\n", sep = "")
              } else {
                cat("                     | ", object@parameter_names[i], " = ", object@best_parameters[i], "\n", sep = "")
              }
            }
            cat("  --------------------------------------- \n")
          }
)
