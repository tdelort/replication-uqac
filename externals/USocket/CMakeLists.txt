cmake_minimum_required(VERSION 3.19)

include(FetchContent)

FetchContent_Declare(
  USocket
  GIT_REPOSITORY https://github.com/tdelort/TP-Socket-Berkeley.git
  GIT_TAG v1.1
)

FetchContent_MakeAvailable(USocket)