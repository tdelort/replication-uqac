cmake_minimum_required(VERSION 3.19)

include(FetchContent)

FetchContent_Declare(
  USerialisation
  GIT_REPOSITORY https://github.com/tdelort/serialisation-uqac.git
  GIT_TAG v1.0
)

FetchContent_MakeAvailable(USerialisation)