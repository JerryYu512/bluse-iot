#!/bin/bash
cd src/config/param/proto
./protoc_cpp.sh
cd -
cd tools
rm -rf ../src/config/param/param_def
python3 gen_protobuf_cpp.py --path=../src/config/param/param_doc/doc.json --out=../src/config/param/param_def
cd -