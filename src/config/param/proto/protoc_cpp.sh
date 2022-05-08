#!/bin/bash

rm -rf ../param_pb
# rm -rf ../param_doc
mkdir -p ../param_pb
mkdir -p ../param_doc
mkdir -p ../param_doc/enums
protoc -I. -Ienums *.proto enums/*.proto --cpp_out=../param_pb
protoc -I. -Ienums *.proto enums/*.proto --doc_out=../param_doc --doc_opt=json,doc.json
protoc -I. -Ienums *.proto enums/*.proto --doc_out=../param_doc --doc_opt=markdown,doc.md
protoc -I. -Ienums *.proto enums/*.proto --doc_out=../param_doc --doc_opt=html,doc.html
