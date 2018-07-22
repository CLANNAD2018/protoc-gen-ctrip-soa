#ifndef CTRIP_PROTOBUF_COMPILER_GENERATOR_H__
#define CTRIP_PROTOBUF_COMPILER_GENERATOR_H__

#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/compiler/code_generator.h>

#include <ctrip/protobuf/soa.service.pb.h>
#include <ctrip/protobuf/ctrip_service_descriptor.h>
#include <ctrip/protobuf/compiler/ctrip_constants.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;

namespace ctrip {
namespace protobuf {
namespace compiler {


// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
template <typename DescriptorType>
static string GetCommentsForDescriptor(const DescriptorType* descriptor);

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
static std::vector<string> GetDocLines(const string& comments);

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
template <typename DescriptorType>
static std::vector<string> GetDocLinesForDescriptor(const DescriptorType* descriptor);

class LIBPROTOC_EXPORT CtripCodeGenerator : public CodeGenerator {

public:
  CtripCodeGenerator();
  ~CtripCodeGenerator();

  // implements CodeGenerator ----------------------------------------
  bool Generate(const FileDescriptor* file, const string& parameter, GeneratorContext* context, string* error) const;

  // Returns the version of this code generator
  virtual string version() const = 0;

  // Returns the package/namespace name of the gRPC services defined in the given file.
  virtual string ServicePackage(const FileDescriptor* file) const = 0;

  // Returns the name of the outer class that wraps in all the generated code for the given service.
  virtual string ServiceClassName(const CtripServiceDescriptor* service) const = 0;

  // Returns the name of the source code file extension: .java .cs
  virtual string FileExtension() const = 0;

  // Hanlding files
  virtual bool GenerateFile(const FileDescriptor* file, const string& parameter, GeneratorContext* context, string* error) const = 0;

  // Writes the generated service interface into the given ZeroCopyOutputStream
  virtual void GenerateService(const CtripServiceDescriptor* service, ZeroCopyOutputStream* out) const = 0;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(CtripCodeGenerator);
};

} // namespace ctrip
} // namespace protobuf
} // namespace compiler

#endif  // CTRIP_PROTOBUF_COMPILER_GENERATOR_H__