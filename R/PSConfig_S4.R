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
    max_velocity         = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    n_particles          = as.integer(NULL),
    cognitive            = as.double(NULL),
    social               = as.double(NULL),
    inertia              = as.double(NULL),
    max_velocity         = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "PSConfig",
          definition = function(object) {
            cat("         PS minimizer options")
            cat("          iterations:", object@iterations)
            cat("iterations_same_cost:", object@iterations_same_cost)
            cat("         n_particles:", object@n_particles)
            cat("           cognitive:", object@cognitive)
            cat("              social:", object@social)
            cat("             inertia:", object@inertia)
            cat("        max_velocity:", object@max_velocity)
          }
)
