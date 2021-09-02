#!/bin/bash

rm helloworld.* || echo "no files present, skipping"

protoc -I=protos --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` protos/helloworld.proto