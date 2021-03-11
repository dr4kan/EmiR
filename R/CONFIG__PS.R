setClass (
  "PSConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    cognitive            = "numeric",
    social               = "numeric",
    inertia              = "numeric",
    velocity_max         = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    cognitive            = as.double(NULL),
    social               = as.double(NULL),
    inertia              = as.double(NULL),
    velocity_max         = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "PSConfig",
          definition = function(object) {
            cat("         PS minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations_same_cost:", object@iterations_same_cost, "\n")
            cat("     population size:", object@population_size, "\n")
            cat("           cognitive:", object@cognitive, "\n")
            cat("              social:", object@social, "\n")
            cat("             inertia:", object@inertia, "\n")
            cat("        velocity_max:", object@velocity_max, "\n")
          }
)
