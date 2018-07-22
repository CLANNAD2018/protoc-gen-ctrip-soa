#include <ctrip/protobuf/compiler/java/ctrip_java_code_generator.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;
using namespace google::protobuf::compiler::java;

namespace ctrip {
namespace protobuf {
namespace compiler {
namespace java {

CtripJavaCodeGenerator::CtripJavaCodeGenerator() {}
CtripJavaCodeGenerator::~CtripJavaCodeGenerator() {}


// java keywords from: https://docs.oracle.com/javase/specs/jls/se8/html/jls-3.html#jls-3.9
static std::set<string> java_keywords = {
  "abstract",
  "assert",
  "boolean",
  "break",
  "byte",
  "case",
  "catch",
  "char",
  "class",
  "const",
  "continue",
  "default",
  "do",
  "double",
  "else",
  "enum",
  "extends",
  "final",
  "finally",
  "float",
  "for",
  "goto",
  "if",
  "implements",
  "import",
  "instanceof",
  "int",
  "interface",
  "long",
  "native",
  "new",
  "package",
  "private",
  "protected",
  "public",
  "return",
  "short",
  "static",
  "strictfp",
  "super",
  "switch",
  "synchronized",
  "this",
  "throw",
  "throws",
  "transient",
  "try",
  "void",
  "volatile",
  "while",
  // additional ones added by us
  "true",
  "false",
};


// Adjust a method name prefix identifier to follow the JavaBean spec:
//   - decapitalize the first letter
//   - remove embedded underscores & capitalize the following letter
//  Finally, if the result is a reserved java keyword, append an underscore.
static string MixedLower(const string& word) {
  string w;
  w += tolower(word[0]);
  bool after_underscore = false;
  for (size_t i = 1; i < word.length(); ++i) {
    if (word[i] == '_') {
      after_underscore = true;
    } else {
      w += after_underscore ? toupper(word[i]) : word[i];
      after_underscore = false;
    }
  }
  if (java_keywords.find(w) != java_keywords.end()) {
    return w + "_";
  }
  return w;
}

static string LowerMethodName(const MethodDescriptor* method) {
  return MixedLower(method->name());
}

// Returns the package/namespace name of the gRPC services defined in the given file.
string CtripJavaCodeGenerator::ServicePackage(const FileDescriptor* file) const {
  string result = ClassName(file);
  size_t last_dot_pos = result.find_last_of('.');
  if (last_dot_pos != string::npos) {
    result.resize(last_dot_pos);
  } else {
    result = "";
  }
  return result;
}


// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
template <typename ITR>
static void SplitStringToIteratorUsing(const string& full,
                                       const char* delim,
                                       ITR& result) {
  // Optimize the common case where delim is a single character.
  if (delim[0] != '\0' && delim[1] == '\0') {
    char c = delim[0];
    const char* p = full.data();
    const char* end = p + full.size();
    while (p != end) {
      if (*p == c) {
        ++p;
      } else {
        const char* start = p;
        while (++p != end && *p != c);
        *result++ = string(start, p - start);
      }
    }
    return;
  }

  string::size_type begin_index, end_index;
  begin_index = full.find_first_not_of(delim);
  while (begin_index != string::npos) {
    end_index = full.find_first_of(delim, begin_index);
    if (end_index == string::npos) {
      *result++ = full.substr(begin_index);
      return;
    }
    *result++ = full.substr(begin_index, (end_index - begin_index));
    begin_index = full.find_first_not_of(delim, end_index);
  }
}

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
static void SplitStringUsing(const string& full,
                             const char* delim,
                             std::vector<string>* result) {
  std::back_insert_iterator< std::vector<string> > it(*result);
  SplitStringToIteratorUsing(full, delim, it);
}

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
static std::vector<string> Split(const string& full, const char* delim) {
  std::vector<string> result;
  SplitStringUsing(full, delim, &result);
  return result;
}

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
static string EscapeJavadoc(const string& input) {
  string result;
  result.reserve(input.size() * 2);

  char prev = '*';

  for (string::size_type i = 0; i < input.size(); i++) {
    char c = input[i];
    switch (c) {
      case '*':
        // Avoid "/*".
        if (prev == '/') {
          result.append("&#42;");
        } else {
          result.push_back(c);
        }
        break;
      case '/':
        // Avoid "*/".
        if (prev == '*') {
          result.append("&#47;");
        } else {
          result.push_back(c);
        }
        break;
      case '@':
        // '@' starts javadoc tags including the @deprecated tag, which will
        // cause a compile-time error if inserted before a declaration that
        // does not have a corresponding @Deprecated annotation.
        result.append("&#64;");
        break;
      case '<':
        // Avoid interpretation as HTML.
        result.append("&lt;");
        break;
      case '>':
        // Avoid interpretation as HTML.
        result.append("&gt;");
        break;
      case '&':
        // Avoid interpretation as HTML.
        result.append("&amp;");
        break;
      case '\\':
        // Java interprets Unicode escape sequences anywhere!
        result.append("&#92;");
        break;
      default:
        result.push_back(c);
        break;
    }

    prev = c;
  }

  return result;
}

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
template <typename DescriptorType>
static string GrpcGetCommentsForDescriptor(const DescriptorType* descriptor) {
  SourceLocation location;
  if (descriptor->GetSourceLocation(&location)) {
    return location.leading_comments.empty() ?
      location.trailing_comments : location.leading_comments;
  }
  return string();
}

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
static std::vector<string> GrpcGetDocLines(const string& comments) {
  if (!comments.empty()) {
    // TODO(kenton):  Ideally we should parse the comment text as Markdown and
    //   write it back as HTML, but this requires a Markdown parser.  For now
    //   we just use <pre> to get fixed-width text formatting.

    // If the comment itself contains block comment start or end markers,
    // HTML-escape them so that they don't accidentally close the doc comment.
    string escapedComments = EscapeJavadoc(comments);

    std::vector<string> lines = Split(escapedComments, "\n");
    while (!lines.empty() && lines.back().empty()) {
      lines.pop_back();
    }
    return lines;
  }
  return std::vector<string>();
}

// TODO(nmittler): Remove once protobuf includes javadoc methods in distribution.
template <typename DescriptorType>
static std::vector<string> GrpcGetDocLinesForDescriptor(const DescriptorType* descriptor) {
  return GrpcGetDocLines(GrpcGetCommentsForDescriptor(descriptor));
}

// Returns the name of the outer class that wraps in all the generated code for the given service.
string CtripJavaCodeGenerator::ServiceClassName(const CtripServiceDescriptor* service) const {
    return service->name();
}

// Returns the name of the source code file extension: .java .cs
inline string CtripJavaCodeGenerator::FileExtension() const { 
  return ".java"; 
}

void PrintImport(Printer* printer) {
  printer->Print("import com.ctriposs.baiji.rpc.common.BaijiContract;\n");
  printer->Print("import com.ctriposs.baiji.rpc.common.types.CheckHealthRequestType;\n");
  printer->Print("import com.ctriposs.baiji.rpc.common.types.CheckHealthResponseType;\n");
  printer->Print("\n");
}

void PrintService(const CtripServiceDescriptor* ctripService, Printer* printer) {
  printer->Print(
    "@BaijiContract(serviceName = \"$service_name$\", serviceNamespace = \"$service_namespace$\", codeGeneratorVersion = \"1.0.0\")\n",
    "service_name", ctripService->serviceName(),
    "service_namespace",ctripService->serviceNamespace());
  printer->Print("public interface $service_interface_name$ {\n", "service_interface_name", ctripService->name());
  printer->Print("\n    CheckHealthResponseType checkHealth(CheckHealthRequestType request) throws Exception;\n");
  for(int i = 0; i < ctripService->method_count(); i++) {
    const MethodDescriptor* method = ctripService->method(i);
    string method_name = LowerMethodName(method);
    string input_type = method->input_type()->full_name();
    string output_type = method->output_type()->full_name();
    printer->Print("\n    $output_type$ $method_name$($input_type$) throws Exception;\n","output_type", output_type, "method_name", method_name, "input_type", input_type);
  }
  printer->Print("}");
}


// Hanlding files
bool CtripJavaCodeGenerator::GenerateFile(const FileDescriptor* file, const string& parameter, GeneratorContext* context, string* error) const {
  JavaGenerator javaGenerator;
  return javaGenerator.Generate(file, parameter, context, error);
}

// Writes the generated service interface into the given ZeroCopyOutputStream
void CtripJavaCodeGenerator::GenerateService(const CtripServiceDescriptor* ctripService, ZeroCopyOutputStream* out) const {
    Printer printer(out, '$');
    
    string package_name = this->ServicePackage(ctripService->file());
    if (!package_name.empty()) {
      printer.Print("package $package_name$;\n\n", "package_name", package_name);
    }

    PrintImport(&printer);

    PrintService(ctripService, &printer);
}

} // namespace java
} // namespace ctrip
} // namespace protobuf
} // namespace compiler