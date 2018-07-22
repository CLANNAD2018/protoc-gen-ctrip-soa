#ifndef _CTRIP_PROTOBUF_SERVICE_DESCRIPTOR_H_
#define _CTRIP_PROTOBUF_SERVICE_DESCRIPTOR_H_

#include <string>
#include <google/protobuf/descriptor.h>

using namespace std;
using namespace google::protobuf;

namespace ctrip {
namespace protobuf {

class LIBPROTOBUF_EXPORT CtripServiceDescriptor {
 public:
  CtripServiceDescriptor(const ServiceDescriptor* service, string service_name, string service_namespace) {
    this->service = service;
    this->service_name = service_name;
    this->service_namespace = service_namespace;
  }

  const string serviceName() const;
  const string serviceNamespace() const;
  const ServiceDescriptor* rawServiceDescriptor() const;

  // The name of the service, not including its containing scope.
  const string& name() const;
  // The fully-qualified name of the service, scope delimited by periods.
  const string& full_name() const;
  // Index of this service within the file's services array.
  int index() const;

  // The .proto file in which this service was defined.  Never NULL.
  const FileDescriptor* file() const;

  // Get options for this service type.  These are specified in the .proto file
  // by placing lines like "option foo = 1234;" in the service definition.
  // Allowed options are defined by ServiceOptions in
  // google/protobuf/descriptor.proto, and any available extensions of that
  // message.
  const ServiceOptions& options() const;

  // The number of methods this service defines.
  int method_count() const;
  // Gets a MethodDescriptor by index, where 0 <= index < method_count().
  // These are returned in the order they were defined in the .proto file.
  const MethodDescriptor* method(int index) const;

  // Look up a MethodDescriptor by name.
  const MethodDescriptor* FindMethodByName(const string& name) const;
  // See Descriptor::CopyTo().
  void CopyTo(ServiceDescriptorProto* proto) const;

  // See Descriptor::DebugString().
  string DebugString() const;

  // See Descriptor::DebugStringWithOptions().
  string DebugStringWithOptions(const DebugStringOptions& options) const;

  // Source Location ---------------------------------------------------

  // Updates |*out_location| to the source location of the complete
  // extent of this service declaration.  Returns false and leaves
  // |*out_location| unchanged iff location information was not available.
  bool GetSourceLocation(SourceLocation* out_location) const;

 private:
  const ServiceDescriptor* service;
  string service_name;
  string service_namespace;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(CtripServiceDescriptor);
};

} // namespace protobuf
} // namespace ctrip


#endif