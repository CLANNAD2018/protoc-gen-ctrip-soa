#include <google/protobuf/compiler/plugin.h>
#include <ctrip/protobuf/compiler/ctrip_code_generator.h>
#include <ctrip/protobuf/compiler/java/ctrip_java_code_generator.h>

using namespace ctrip::protobuf::compiler::java;

int main(int argc, char** argv) {
  CtripJavaCodeGenerator generator;
  return compiler::PluginMain(argc, argv, &generator);
}
