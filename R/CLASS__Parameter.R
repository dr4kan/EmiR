###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021-2024 Davide Pagano & Lorenzo Sostero                     #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################


setClass (
  "Parameter",

  # Defining slot type
  slots = c(
    name     = "character",
    min_val  = "numeric",
    max_val  = "numeric",
    integer  = "logical"
  ),

  # Initializing slots
  prototype = list(
    name     = as.character(NULL),
    min_val  = as.double(NULL),
    max_val  = as.double(NULL),
    integer  = FALSE
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "Parameter",
          definition = function(object) {
            if (object@integer) {
              cat(object@name, ": [ ", object@min_val, ", ", object@max_val, " ] (integer)", sep = "")
            } else {
              cat(object@name, ": [ ", object@min_val, ", ", object@max_val, " ]", sep = "")
            }
          }
)
