setClass (
  "Parameter",

  # Defining slot type
  slots = c(
    name    = "character",
    min_val = "numeric",
    max_val = "numeric"
  ),

  # Initializing slots
  prototype = list(
    name    = as.character(NULL),
    min_val = as.double(NULL),
    max_val = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "Parameter",
          definition = function(object) {
            cat(object@name, ": [ ", object@min_val, ", ", object@max_val, " ]", sep = "")
          }
)
