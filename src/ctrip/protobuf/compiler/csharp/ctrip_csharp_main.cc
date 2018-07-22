#include <google/protobuf/compiler/plugin.h>
#include <ctrip/protobuf/compiler/ctrip_code_generator.h>
#include <ctrip/protobuf/compiler/csharp/ctrip_csharp_code_generator.h>

using namespace ctrip::protobuf::compiler::csharp;


int main(int argc, char** argv) {
  CtripCSharpCodeGenerator generator;
  return compiler::PluginMain(argc, argv, &generator);
}
