setClass (
  "MinimizationResult",

  # Defining slot type
  slots = c(
    algorithm       = "character",
    iterations      = "numeric",
    obj_function    = "function",
    best_cost       = "numeric",
    best_parameters = "vector",
    parameter_names = "vector",
    parameter_range = "vector",
    particles       = "list",
    cost_history    = "vector"
  ),

  # Initializing slots
  prototype = list(
    algorithm       = as.character(NULL),
    iterations      = as.numeric(NULL),
    obj_function    = NULL,
    best_cost       = as.numeric(NULL),
    best_parameters = as.vector(NULL),
    parameter_names = as.vector(NULL),
    parameter_range = as.vector(NULL),
    particles       = as.list(NULL),
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
            cat("          iterations | ", object@iterations, "\n", sep = "")
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
