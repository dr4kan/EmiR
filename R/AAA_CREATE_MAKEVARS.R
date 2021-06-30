output <- "src/Makevars"

cpp_files <- Sys.glob("src/*/*.cpp")
cpp_files <- paste(basename(dirname(cpp_files)), basename(cpp_files), sep = "/")

cat(paste0("SOURCES = ", cpp_files[1], " \\"), file=output, sep = "\n")
for (i in 2:(length(cpp_files)-1)) {
  cat(paste0("\t", cpp_files[i], " \\"), file=output, append = TRUE, sep = "\n")
}
cat(paste0("\t", cpp_files[length(cpp_files)]), file=output, append = TRUE, sep = "\n")

cat("", file=output, append = TRUE, sep = "\n")

obj_files <- Sys.glob("src/*.cpp")
obj_files <- basename(obj_files)
obj_files <- tools::file_path_sans_ext(obj_files)
obj_files <- paste(obj_files, "o", sep = ".")

cat(paste0("OBJECTS.src = ", obj_files[1], " \\"), file=output, append = TRUE, sep = "\n")
for (i in 2:(length(obj_files)-1)) {
  cat(paste0("\t", obj_files[i], " \\"), file=output, append = TRUE, sep = "\n")
}
cat(paste0("\t", obj_files[length(obj_files)]), file=output, append = TRUE, sep = "\n")

cat("", file=output, append = TRUE, sep = "\n")

cat("OBJECTS = $(OBJECTS.src) $(SOURCES:.cpp=.o)", file=output, append = TRUE, sep = "\n")



