cmake_minimum_required(VERSION 3.28.3)
project(example_grpc)

if(DEFINED GRPC_SRC_DIR AND DEFINED GRPC_BUILD_DIR)
    # Setting up gRPC modules and variables
    include("${GRPC_SRC_DIR}/examples/cpp/cmake/common.cmake")

    # Find absl package
    find_package(absl CONFIG REQUIRED)

    # Inc dirs
        # gRPC
    include_directories("${GRPC_BUILD_DIR}/include")
        # Local
    include_directories("${CMAKE_SOURCE_DIR}/inc/service")
    include_directories("${CMAKE_SOURCE_DIR}/inc/stub")
    include_directories("${CMAKE_SOURCE_DIR}/interface")
    # Link dirs
    link_directories("${GRPC_BUILD_DIR}/lib")

    # Interface source files
    set(INTERFACE_SRC
        ${CMAKE_SOURCE_DIR}/interface/example_grpc.grpc.pb.cc
        ${CMAKE_SOURCE_DIR}/interface/example_grpc.pb.cc
    )

    # Server source files
    set(SERVER_SRC
        ${CMAKE_SOURCE_DIR}/src/server.cpp
        ${CMAKE_SOURCE_DIR}/src/service/service_impl.cpp
    )

    # Client source files
    set(CLIENT_SRC
        ${CMAKE_SOURCE_DIR}/src/client.cpp
        ${CMAKE_SOURCE_DIR}/src/stub/client_stub.cpp
    )

    # Build interface lib
    add_library(eg_grpc_proto ${INTERFACE_SRC})
    target_link_libraries(eg_grpc_proto
        absl::absl_log
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
    )
    
    # Build Server executable
    add_executable(example_grpc_server ${SERVER_SRC})
    target_link_libraries(example_grpc_server
        eg_grpc_proto
        absl::flags_parse
        absl::absl_log
        absl::log_initialize
        absl::log_globals
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
    )

    # Build Client executable
    add_executable(example_grpc_client ${CLIENT_SRC})
    target_link_libraries(example_grpc_client
        eg_grpc_proto
        absl::flags_parse
        absl::absl_log
        absl::log_initialize
        absl::log_globals
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
    )

else()

    message(
        FATAL_ERROR    
        "Use -DGRPC_SRC_DIR to specify path to GRPC src.\nUse -DGRPC_BUILD_DIR to specify path to GRPC build."
    )

endif()