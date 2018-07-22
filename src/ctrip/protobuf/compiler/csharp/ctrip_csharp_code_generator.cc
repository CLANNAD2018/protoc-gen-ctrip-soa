#include <ctrip/protobuf/compiler/csharp/ctrip_csharp_code_generator.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;
using namespace google::protobuf::compiler::csharp;

namespace ctrip {
namespace protobuf {
namespace compiler {
namespace csharp {

CtripCSharpCodeGenerator::CtripCSharpCodeGenerator() {}
CtripCSharpCodeGenerator::~CtripCSharpCodeGenerator() {}

std::string UnderscoresToCamelCase(const std::string& input,
                                   bool cap_next_letter,
                                   bool preserve_period) {
  string result;
  // Note:  I distrust ctype.h due to locales.
  for (int i = 0; i < input.size(); i++) {
    if ('a' <= input[i] && input[i] <= 'z') {
      if (cap_next_letter) {
        result += input[i] + ('A' - 'a');
      } else {
        result += input[i];
      }
      cap_next_letter = false;
    } else if ('A' <= input[i] && input[i] <= 'Z') {
      if (i == 0 && !cap_next_letter) {
        // Force first letter to lower-case unless explicitly told to
        // capitalize it.
        result += input[i] + ('a' - 'A');
      } else {
        // Capital letters after the first are left as-is.
        result += input[i];
      }
      cap_next_letter = false;
    } else if ('0' <= input[i] && input[i] <= '9') {
      result += input[i];
      cap_next_letter = true;
    } else {
      cap_next_letter = true;
      if (input[i] == '.' && preserve_period) {
        result += '.';
      }
    }
  }
  // Add a trailing "_" if the name should be altered.
  if (input.size() > 0 && input[input.size() - 1] == '#') {
    result += '_';
  }
  return result;
}

std::string GetFileNamespace(const FileDescriptor* descriptor) {
  if (descriptor->options().has_csharp_namespace()) {
    return descriptor->options().csharp_namespace();
  }
  return UnderscoresToCamelCase(descriptor->package(), true, true);
}

// Returns the package/namespace name of the gRPC services defined in the given file.
string CtripCSharpCodeGenerator::ServicePackage(const FileDescriptor* file) const {
  string result = GetFileNamespace(file);
  size_t last_dot_pos = result.find_last_of('.');
  if (last_dot_pos != string::npos) {
    result.resize(last_dot_pos);
  } else {
    result = "";
  }
  return result;
}

// Returns the name of the outer class that wraps in all the generated code for the given service.
string CtripCSharpCodeGenerator::ServiceClassName(const CtripServiceDescriptor* service) const {
    return service->name();
}

// Returns the name of the source code file extension: .java .cs
inline string CtripCSharpCodeGenerator::FileExtension() const { 
  return ".cs"; 
}

void BeginPrintNamespace(Printer* printer, string code_namespace) {
  printer->Print("namespace $code_namespace$\n{\n", "code_namespace", code_namespace);
}

void EndPrintNamespace(Printer* printer) {
  printer->Print("}");
}

void PrintImport(Printer* printer) {
  printer->Print("using CServiceStack.ServiceHost;\n");
  printer->Print("using CServiceStack.Common.Types;\n");
  printer->Print("\n");
}

void PrintService(const CtripServiceDescriptor* ctripService, Printer* printer) {
  printer->Print(
    "[CServiceInterface(\"$service_name$\", \"$service_namespace$\", \"1.0.0\"]\n",
    "service_name", ctripService->serviceName(),
    "service_namespace",ctripService->serviceNamespace());
  printer->Print("public interface $service_interface_name$ \n{", "service_interface_name", ctripService->name());
  printer->Print("\n    CheckHealthResponseType CheckHealth(CheckHealthRequestType request);\n");
  for(int i = 0; i < ctripService->method_count(); i++) {
    const MethodDescriptor* method = ctripService->method(i);
    string method_name = method->name();
    string input_type = method->input_type()->full_name();
    string output_type = method->output_type()->full_name();
    printer->Print("\n    $output_type$ $method_name$($input_type$);\n","output_type", output_type, "method_name", method_name, "input_type", input_type);
  }
  printer->Print("}");
}

// Hanlding files
bool CtripCSharpCodeGenerator::GenerateFile(const FileDescriptor* file, const string& parameter, GeneratorContext* context, string* error) const {
  Generator csharpGenerator;
  return csharpGenerator.Generate(file, parameter, context, error);
}

// Writes the generated service interface into the given ZeroCopyOutputStream
void CtripCSharpCodeGenerator::GenerateService(const CtripServiceDescriptor* ctripService, ZeroCopyOutputStream* out) const {
    Printer printer(out, '$');
    
    string package_name = this->ServicePackage(ctripService->file());
    BeginPrintNamespace(&printer, package_name);
    PrintImport(&printer);
    PrintService(ctripService, &printer);
    EndPrintNamespace(&printer);
}

} // namespace csharp
} // namespace ctrip
} // namespace protobuf
} // namespace compiler