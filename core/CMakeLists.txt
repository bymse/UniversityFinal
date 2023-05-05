cmake_minimum_required(VERSION 3.25)
project(UniversityFinal)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_EXE_LINKER_FLAGS "-pthread -sMODULARIZE -sEXPORTED_RUNTIME_METHODS=ccall -sPROXY_TO_PTHREAD -sEXPORT_NAME=myModule -sASSERTIONS -sALLOW_MEMORY_GROWTH")

add_executable(UniversityFinal main.cpp tasks/tasks.h commands/commands.h storage/storage.h client_funcs/client_funcs.h storage/storage.cpp tasks/tasks.cpp host_communication/host_communication.h host_communication/host_communication.cpp nodes/nodes.h commands/commands.cpp ../exmaple_task/main.cpp logs/logs.h logs/logs.cpp commands/data_parsers.h results/results.h utils/utils.h utils/utils.cpp nodes/nodes.cpp results/results.cpp commands/data_parsers.cpp)

set_target_properties(UniversityFinal PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../runner/static/build
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../runner/static/build
        )
