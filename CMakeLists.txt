# CMakeList.txt: projekt CMake dla elementu VampireCpp, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.20)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("VampireCpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (VampireCpp "VampireCpp.cpp" "VampireCpp.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VampireCpp PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.20
)

FetchContent_MakeAvailable(SDL3)

target_link_libraries(VampireCpp PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(
        TARGET VampireCpp POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        $<TARGET_FILE:SDL3::SDL3-shared>
        $<TARGET_FILE_DIR:VampireCpp>
        VERBATIM
    )
endif()