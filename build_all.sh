bazel build --strip=never lib:protoc
bazel build --strip=never src:protoc-gen-ctrip-soa-java
bazel build --strip=never src:protoc-gen-ctrip-soa-csharp

bazel_bin=$(readlink -f bazel-bin)
mkdir $bazel_bin/sample
mkdir $bazel_bin/sample/google/protobuf -p
mkdir $bazel_bin/generated
cp sample/google/protobuf/descriptor.proto $bazel_bin/sample/google/protobuf/
cp sample/soa.service.proto $bazel_bin/sample
cp sample/HelloService.proto $bazel_bin/sample
#cp tools/protoc.exe $bazel_bin/
cp $bazel_bin/lib/protoc.exe $bazel_bin/
cp $bazel_bin/src/protoc-gen-ctrip-soa-java.exe $bazel_bin/
cp $bazel_bin/src/protoc-gen-ctrip-soa-csharp.exe $bazel_bin/

echo "build completed."