# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/canonical_matrix/build/_deps/eigen-src"
  "D:/canonical_matrix/build/_deps/eigen-build"
  "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix"
  "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix/tmp"
  "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix/src/eigen-populate-stamp"
  "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix/src"
  "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix/src/eigen-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix/src/eigen-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/canonical_matrix/build/_deps/eigen-subbuild/eigen-populate-prefix/src/eigen-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
