#include <ctrip/protobuf/compiler/ctrip_code_generator.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::compiler;

namespace ctrip {
namespace protobuf {
namespace compiler {

static string PackageToDir(const string& package_name) {
  string package_dir = package_name;
  for (size_t i = 0; i < package_dir.size(); ++i) {
    if (package_dir[i] == '.') {
      package_dir[i] = '/';
    }
  }
  if (!package_dir.empty()) package_dir += "/";
  return package_dir;
}

CtripCodeGenerator::CtripCodeGenerator() {}
CtripCodeGenerator::~CtripCodeGenerator() {}

bool CtripCodeGenerator::Generate(const FileDescriptor* file, const string& parameter, GeneratorContext* context, string* error) const {
    
    vector<pair<string, string>> options;
    ParseGeneratorParameter(parameter, &options);

    this->GenerateFile(file, parameter, context, error);

    string package_name = this->ServicePackage(file);
    string package_filename = PackageToDir(package_name);
    for (int i = 0; i < file->service_count(); ++i) {
      const ServiceDescriptor* service = file->service(i);
      
      const ServiceOptions& serviceOptions = service->options();
      const string service_name = serviceOptions.GetExtension(soa::service::name);
      const string service_namespace = serviceOptions.GetExtension(soa::service::namespace_);

      CtripServiceDescriptor ctripService(service, service_name, service_namespace);
      string filename = package_filename + this->ServiceClassName(&ctripService) + this->FileExtension();
      unique_ptr<ZeroCopyOutputStream> output(context->Open(filename));
      this->GenerateService(&ctripService, output.get());
    }
    
    return true;
}

} // namespace ctrip
} // namespace protobuf
} // namespace compiler