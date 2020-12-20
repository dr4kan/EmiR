setClass (
  "Constraint",

  # Defining slot type
  slots = c(
    func       = "function",
    inequality = "character"
  ),

  # Initializing slots
  prototype = list(
    func       = as.function(alist(NULL)),
    inequality = as.character(NULL)
  )
)

