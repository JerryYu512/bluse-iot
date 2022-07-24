#!/bin/bash
# 1.安装gcc,cmake,make,automake,go
# 2.安装sqlite3,ssl-lib,protobuf,https://github.com/pseudomuto/protoc-gen-doc
go env -w GOPROXY=https://goproxy.cn,direct
go get -u github.com/pseudomuto/protoc-gen-doc/cmd/protoc-gen-doc
cd cmd/protoc-gen-doc
go build
udo cp protoc-gen-doc /usr/local/bin/