setClass (
  "PSConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    n_particles          = "numeric",
    cognitive            = "numeric",
    social               = "numeric",
    inertia              = "numeric",
    max_velocity         = "numeric",
    penalty_parameter    = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    n_particles          = as.integer(NULL),
    cognitive            = as.double(NULL),
    social               = as.double(NULL),
    inertia              = as.double(NULL),
    max_velocity         = as.double(NULL),
    penalty_parameter    = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "PSConfig",
          definition = function(object) {
            cat("         PS minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations_same_cost:", object@iterations_same_cost, "\n")
            cat("         n_particles:", object@n_particles, "\n")
            cat("           cognitive:", object@cognitive, "\n")
            cat("              social:", object@social, "\n")
            cat("             inertia:", object@inertia, "\n")
            cat("        max_velocity:", object@max_velocity, "\n")
            cat("   penalty_parameter:", object@penalty_parameter, "\n")
          }
)
