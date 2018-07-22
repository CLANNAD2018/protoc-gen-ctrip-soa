#include <string>
#include <google/protobuf/descriptor.h>
#include <ctrip/protobuf/ctrip_service_descriptor.h>


namespace ctrip {
namespace protobuf {
    
const string CtripServiceDescriptor::serviceName() const {
  return this->service_name;
}

const string CtripServiceDescriptor::serviceNamespace() const {
  return this->service_namespace;
}

const ServiceDescriptor* CtripServiceDescriptor::rawServiceDescriptor() const {
  return this->service;
}

// The name of the service, not including its containing scope.
const string& CtripServiceDescriptor::name() const {
  return this->service->name();
}

// The fully-qualified name of the service, scope delimited by periods.
const string& CtripServiceDescriptor::full_name() const {
  return this->service->full_name();
}

// Index of this service within the file's services array.
int CtripServiceDescriptor::index() const {
  return this->service->index();
}

// The .proto file in which this service was defined.  Never NULL.
const FileDescriptor* CtripServiceDescriptor::file() const {
  return this->service->file();
}

// Get options for this service type.  These are specified in the .proto file
// by placing lines like "option foo = 1234;" in the service definition.
// Allowed options are defined by ServiceOptions in
// google/protobuf/descriptor.proto, and any available extensions of that
// message.
const ServiceOptions& CtripServiceDescriptor::options() const {
  return this->service->options();
}

// The number of methods this service defines.
int CtripServiceDescriptor::method_count() const {
  return this->service->method_count(); 
}
// Gets a MethodDescriptor by index, where 0 <= index < method_count().
// These are returned in the order they were defined in the .proto file.
const MethodDescriptor* CtripServiceDescriptor::method(int index) const {
  return this->service->method(index);
}

// Look up a MethodDescriptor by name.
const MethodDescriptor* CtripServiceDescriptor::FindMethodByName(const string& name) const {
  return this->service->FindMethodByName(name);
}
// See Descriptor::CopyTo().
void CtripServiceDescriptor::CopyTo(ServiceDescriptorProto* proto) const {
  return this->service->CopyTo(proto);
}

// See Descriptor::DebugString().
string CtripServiceDescriptor::DebugString() const {
  return this->service->DebugString();
}

// See Descriptor::DebugStringWithOptions().
string CtripServiceDescriptor::DebugStringWithOptions(const DebugStringOptions& options) const {
  return this->service->DebugStringWithOptions(options);
}


// Source Location ---------------------------------------------------

// Updates |*out_location| to the source location of the complete
// extent of this service declaration.  Returns false and leaves
// |*out_location| unchanged iff location information was not available.
bool CtripServiceDescriptor::GetSourceLocation(SourceLocation* out_location) const {
  return this->service->GetSourceLocation(out_location);
}


} // namespace protobuf
} // namespace ctrip
