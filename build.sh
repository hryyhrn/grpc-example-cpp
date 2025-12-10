#!bin/bash

# Sets your gRPC src, build dir

if [[ -z "${MY_SRC_DIR}" ]]; then
    echo "gRPC src dir not set! Setting gRPC src dir."

    # !!! Add the path to your gRPC src here !!!
    export MY_SRC_DIR=<path_to_cloned_grpc_src>

    echo "Set gRPC src dir to: "
    echo ${MY_SRC_DIR}
else
    echo "Using gRPC src from dir: "
    echo ${MY_SRC_DIR}
fi

if [[ -z "${MY_INSTALL_DIR}" ]]; then
    echo "gRPC build dir not set! Setting gRPC build dir."

    # !!! Add the path to your gRPC build dir here !!!
    export MY_INSTALL_DIR=<path_to_built_grpc>

    export PATH="$MY_INSTALL_DIR/bin:$PATH"
    echo "Set gRPC build dir to: "
    echo ${MY_INSTALL_DIR}
else
    echo "Using gRPC build from dir: "
    echo ${MY_INSTALL_DIR}
fi

# Generate interface using protoc

mkdir -p interface
pushd ./idl
# Generate grpc interface headers and definitions
protoc --grpc_out=../interface --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` example_grpc.proto
# Generate protobuf headers and definitions
protoc --cpp_out=../interface example_grpc.proto
popd

# Build the client server grpc sample application

cmake -B build -DGRPC_SRC_DIR=${MY_SRC_DIR}\
               -DGRPC_BUILD_DIR=${MY_INSTALL_DIR}

cmake --build build