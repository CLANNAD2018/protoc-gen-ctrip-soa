################################################################################
# Protobuf Runtime Library
################################################################################

MSVC_COPTS = [
    "/DHAVE_PTHREAD",
    "/wd4018", # -Wno-sign-compare
    "/wd4065", # switch statement contains 'default' but no 'case' labels
    "/wd4146", # unary minus operator applied to unsigned type, result still unsigned
    "/wd4244", # 'conversion' conversion from 'type1' to 'type2', possible loss of data
    "/wd4251", # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
    "/wd4267", # 'var' : conversion from 'size_t' to 'type', possible loss of data
    "/wd4305", # 'identifier' : truncation from 'type1' to 'type2'
    "/wd4307", # 'operator' : integral constant overflow
    "/wd4309", # 'conversion' : truncation of constant value
    "/wd4334", # 'operator' : result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
    "/wd4355", # 'this' : used in base member initializer list
    "/wd4506", # no definition for inline function 'function'
    "/wd4514", # -Wno-unused-function
    "/wd4800", # 'type' : forcing value to bool 'true' or 'false' (performance warning)
    "/wd4996", # The compiler encountered a deprecated declaration.
    "/JMC", "/W3", "/Zc:inline", "/Zi", "/Od", "/diagnostics:classic"
]

COPTS = select({
    ":msvc" : MSVC_COPTS,
    "//conditions:default": [
        "-DHAVE_PTHREAD",
        "-Wall",
        #"-Woverloaded-virtual",
        #"-Wno-sign-compare",
        #"-Wno-unused-function",
        # Prevents ISO C++ const string assignment warnings for pyext sources.
        #"-Wno-writable-strings",
        #"-Wno-write-strings"
    ],
})

# MSVC builds do not need to link in a separate pthread library.
LINK_OPTS = select({
    ":msvc": [
        # Suppress linker warnings about files with no symbols defined.
        "-ignore:4221",
    ],
    "//conditions:default": ["-lpthread", "-lm"],
})

config_setting(
    name = "msvc",
    values = { "compiler": "msvc-cl" },
)

cc_library(
    name = "spdlog",
    srcs = [],
    hdrs = glob(["spdlog/**/*.h"]),
    includes = ["lib/spdlog/"],
    linkopts = LINK_OPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "protoc",
    srcs = ["google/protobuf/compiler/main.cc"],
    linkopts = LINK_OPTS,
    visibility = ["//visibility:public"],
    deps = [":protoc_lib"],
)

cc_library(
    name = "protoc_lib",
    srcs = [
        # AUTOGEN(protoc_lib_srcs)
        "google/protobuf/compiler/code_generator.cc",
        "google/protobuf/compiler/command_line_interface.cc",
        "google/protobuf/compiler/cpp/cpp_enum.cc",
        "google/protobuf/compiler/cpp/cpp_enum_field.cc",
        "google/protobuf/compiler/cpp/cpp_extension.cc",
        "google/protobuf/compiler/cpp/cpp_field.cc",
        "google/protobuf/compiler/cpp/cpp_file.cc",
        "google/protobuf/compiler/cpp/cpp_generator.cc",
        "google/protobuf/compiler/cpp/cpp_helpers.cc",
        "google/protobuf/compiler/cpp/cpp_map_field.cc",
        "google/protobuf/compiler/cpp/cpp_message.cc",
        "google/protobuf/compiler/cpp/cpp_message_field.cc",
        "google/protobuf/compiler/cpp/cpp_padding_optimizer.cc",
        "google/protobuf/compiler/cpp/cpp_primitive_field.cc",
        "google/protobuf/compiler/cpp/cpp_service.cc",
        "google/protobuf/compiler/cpp/cpp_string_field.cc",
        "google/protobuf/compiler/csharp/csharp_doc_comment.cc",
        "google/protobuf/compiler/csharp/csharp_enum.cc",
        "google/protobuf/compiler/csharp/csharp_enum_field.cc",
        "google/protobuf/compiler/csharp/csharp_field_base.cc",
        "google/protobuf/compiler/csharp/csharp_generator.cc",
        "google/protobuf/compiler/csharp/csharp_helpers.cc",
        "google/protobuf/compiler/csharp/csharp_map_field.cc",
        "google/protobuf/compiler/csharp/csharp_message.cc",
        "google/protobuf/compiler/csharp/csharp_message_field.cc",
        "google/protobuf/compiler/csharp/csharp_primitive_field.cc",
        "google/protobuf/compiler/csharp/csharp_reflection_class.cc",
        "google/protobuf/compiler/csharp/csharp_repeated_enum_field.cc",
        "google/protobuf/compiler/csharp/csharp_repeated_message_field.cc",
        "google/protobuf/compiler/csharp/csharp_repeated_primitive_field.cc",
        "google/protobuf/compiler/csharp/csharp_source_generator_base.cc",
        "google/protobuf/compiler/csharp/csharp_wrapper_field.cc",
        "google/protobuf/compiler/java/java_context.cc",
        "google/protobuf/compiler/java/java_doc_comment.cc",
        "google/protobuf/compiler/java/java_enum.cc",
        "google/protobuf/compiler/java/java_enum_field.cc",
        "google/protobuf/compiler/java/java_enum_field_lite.cc",
        "google/protobuf/compiler/java/java_enum_lite.cc",
        "google/protobuf/compiler/java/java_extension.cc",
        "google/protobuf/compiler/java/java_extension_lite.cc",
        "google/protobuf/compiler/java/java_field.cc",
        "google/protobuf/compiler/java/java_file.cc",
        "google/protobuf/compiler/java/java_generator.cc",
        "google/protobuf/compiler/java/java_generator_factory.cc",
        "google/protobuf/compiler/java/java_helpers.cc",
        "google/protobuf/compiler/java/java_lazy_message_field.cc",
        "google/protobuf/compiler/java/java_lazy_message_field_lite.cc",
        "google/protobuf/compiler/java/java_map_field.cc",
        "google/protobuf/compiler/java/java_map_field_lite.cc",
        "google/protobuf/compiler/java/java_message.cc",
        "google/protobuf/compiler/java/java_message_builder.cc",
        "google/protobuf/compiler/java/java_message_builder_lite.cc",
        "google/protobuf/compiler/java/java_message_field.cc",
        "google/protobuf/compiler/java/java_message_field_lite.cc",
        "google/protobuf/compiler/java/java_message_lite.cc",
        "google/protobuf/compiler/java/java_name_resolver.cc",
        "google/protobuf/compiler/java/java_primitive_field.cc",
        "google/protobuf/compiler/java/java_primitive_field_lite.cc",
        "google/protobuf/compiler/java/java_service.cc",
        "google/protobuf/compiler/java/java_shared_code_generator.cc",
        "google/protobuf/compiler/java/java_string_field.cc",
        "google/protobuf/compiler/java/java_string_field_lite.cc",
        "google/protobuf/compiler/js/js_generator.cc",
        "google/protobuf/compiler/js/well_known_types_embed.cc",
        "google/protobuf/compiler/objectivec/objectivec_enum.cc",
        "google/protobuf/compiler/objectivec/objectivec_enum_field.cc",
        "google/protobuf/compiler/objectivec/objectivec_extension.cc",
        "google/protobuf/compiler/objectivec/objectivec_field.cc",
        "google/protobuf/compiler/objectivec/objectivec_file.cc",
        "google/protobuf/compiler/objectivec/objectivec_generator.cc",
        "google/protobuf/compiler/objectivec/objectivec_helpers.cc",
        "google/protobuf/compiler/objectivec/objectivec_map_field.cc",
        "google/protobuf/compiler/objectivec/objectivec_message.cc",
        "google/protobuf/compiler/objectivec/objectivec_message_field.cc",
        "google/protobuf/compiler/objectivec/objectivec_oneof.cc",
        "google/protobuf/compiler/objectivec/objectivec_primitive_field.cc",
        "google/protobuf/compiler/php/php_generator.cc",
        "google/protobuf/compiler/plugin.cc",
        "google/protobuf/compiler/plugin.pb.cc",
        "google/protobuf/compiler/python/python_generator.cc",
        "google/protobuf/compiler/ruby/ruby_generator.cc",
        "google/protobuf/compiler/subprocess.cc",
        "google/protobuf/compiler/zip_writer.cc",
    ],
    hdrs = glob(["google/**/*.h"]),
    copts = COPTS,
    includes = [""],
    linkopts = LINK_OPTS + select({
        ":msvc": [
            # Linking to setargv.obj makes the default command line argument
            # parser expand wildcards, so the main method's argv will contain the
            # expanded list instead of the wildcards.
            #
            # Adding dummy "-DEFAULTLIB:kernel32.lib", because:
            # - Microsoft ships this object file next to default libraries
            # - but this file is not a library, just a precompiled object
            # - "-WHOLEARCHIVE" and "-DEFAULTLIB" only accept library,
            #   not precompiled object.
            # - Bazel would assume linkopt that does not start with "-" or "$"
            #   as a label to a target, so we add a harmless "-DEFAULTLIB:kernel32.lib"
            #   before "setargv.obj".
            # See https://msdn.microsoft.com/en-us/library/8bch7bkk.aspx
            "-DEFAULTLIB:kernel32.lib setargv.obj",
        ],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:public"],
    deps = [":protobuf"],
)

cc_library(
    name = "protobuf",
    srcs = [
        # AUTOGEN(protobuf_srcs)
        "google/protobuf/any.cc",
        "google/protobuf/any.pb.cc",
        "google/protobuf/api.pb.cc",
        "google/protobuf/compiler/importer.cc",
        "google/protobuf/compiler/parser.cc",
        "google/protobuf/descriptor.cc",
        "google/protobuf/descriptor.pb.cc",
        "google/protobuf/descriptor_database.cc",
        "google/protobuf/duration.pb.cc",
        "google/protobuf/dynamic_message.cc",
        "google/protobuf/empty.pb.cc",
        "google/protobuf/extension_set_heavy.cc",
        "google/protobuf/field_mask.pb.cc",
        "google/protobuf/generated_message_reflection.cc",
        "google/protobuf/generated_message_table_driven.cc",
        "google/protobuf/io/gzip_stream.cc",
        "google/protobuf/io/printer.cc",
        "google/protobuf/io/strtod.cc",
        "google/protobuf/io/tokenizer.cc",
        "google/protobuf/io/zero_copy_stream_impl.cc",
        "google/protobuf/map_field.cc",
        "google/protobuf/message.cc",
        "google/protobuf/reflection_ops.cc",
        "google/protobuf/service.cc",
        "google/protobuf/source_context.pb.cc",
        "google/protobuf/struct.pb.cc",
        "google/protobuf/stubs/mathlimits.cc",
        "google/protobuf/stubs/substitute.cc",
        "google/protobuf/text_format.cc",
        "google/protobuf/timestamp.pb.cc",
        "google/protobuf/type.pb.cc",
        "google/protobuf/unknown_field_set.cc",
        "google/protobuf/util/delimited_message_util.cc",
        "google/protobuf/util/field_comparator.cc",
        "google/protobuf/util/field_mask_util.cc",
        "google/protobuf/util/internal/datapiece.cc",
        "google/protobuf/util/internal/default_value_objectwriter.cc",
        "google/protobuf/util/internal/error_listener.cc",
        "google/protobuf/util/internal/field_mask_utility.cc",
        "google/protobuf/util/internal/json_escaping.cc",
        "google/protobuf/util/internal/json_objectwriter.cc",
        "google/protobuf/util/internal/json_stream_parser.cc",
        "google/protobuf/util/internal/object_writer.cc",
        "google/protobuf/util/internal/proto_writer.cc",
        "google/protobuf/util/internal/protostream_objectsource.cc",
        "google/protobuf/util/internal/protostream_objectwriter.cc",
        "google/protobuf/util/internal/type_info.cc",
        "google/protobuf/util/internal/utility.cc",
        "google/protobuf/util/json_util.cc",
        "google/protobuf/util/message_differencer.cc",
        "google/protobuf/util/time_util.cc",
        "google/protobuf/util/type_resolver_util.cc",
        "google/protobuf/wire_format.cc",
        "google/protobuf/wrappers.pb.cc",
    ],
    hdrs = glob(["google/**/*.h"]),
    copts = COPTS,
    includes = [""],
    linkopts = LINK_OPTS,
    visibility = ["//visibility:public"],
    deps = [":protobuf_lite"],
)

cc_library(
    name = "protobuf_lite",
    srcs = [
        # AUTOGEN(protobuf_lite_srcs)
        "google/protobuf/arena.cc",
        "google/protobuf/arenastring.cc",
        "google/protobuf/extension_set.cc",
        "google/protobuf/generated_message_table_driven_lite.cc",
        "google/protobuf/generated_message_util.cc",
        "google/protobuf/implicit_weak_message.cc",
        "google/protobuf/io/coded_stream.cc",
        "google/protobuf/io/zero_copy_stream.cc",
        "google/protobuf/io/zero_copy_stream_impl_lite.cc",
        "google/protobuf/message_lite.cc",
        "google/protobuf/repeated_field.cc",
        "google/protobuf/stubs/bytestream.cc",
        "google/protobuf/stubs/common.cc",
        "google/protobuf/stubs/int128.cc",
        "google/protobuf/stubs/io_win32.cc",
        "google/protobuf/stubs/status.cc",
        "google/protobuf/stubs/statusor.cc",
        "google/protobuf/stubs/stringpiece.cc",
        "google/protobuf/stubs/stringprintf.cc",
        "google/protobuf/stubs/structurally_valid.cc",
        "google/protobuf/stubs/strutil.cc",
        "google/protobuf/stubs/time.cc",
        "google/protobuf/wire_format_lite.cc",
    ],
    copts = COPTS,
    hdrs = glob(["google/**/*.h"]),
    includes = [""],
    linkopts = LINK_OPTS,
    visibility = ["//visibility:public"],
)