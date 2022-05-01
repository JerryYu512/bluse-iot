#!/bin/bash

rm -rf ../param_pb
mkdir -p ../param_pb
protoc -I. *.proto --cpp_out=../param_pb
