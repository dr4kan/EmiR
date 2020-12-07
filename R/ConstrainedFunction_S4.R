setClass (
  "ConstrainedFunction",

  # Defining slot type
  slots = c(
    func       = "function",
    constraint = "list"
  ),

  # Initializing slots
  prototype = list(
    func       = as.function(alist(NULL)),
    constraint = as.list(NULL)
  )
)
