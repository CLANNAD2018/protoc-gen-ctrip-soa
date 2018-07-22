# MSVC builds do not need to link in a separate pthread library.
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

LINK_OPTS = select({
    ":msvc": [
        # Suppress linker warnings about files with no symbols defined.
        "-ignore:4221"
    ],
    "//conditions:default": ["-lpthread", "-lm"],
})

config_setting(
    name = "msvc",
    values = { "compiler": "msvc-cl" },
)

cc_binary(
    name = "protoc-gen-ctrip-soa-java",
    srcs = [
        "ctrip/protobuf/soa.service.pb.cc",
        "ctrip/protobuf/ctrip_service_descriptor.cc",
        "ctrip/protobuf/compiler/ctrip_code_generator.cc",
        "ctrip/protobuf/compiler/java/ctrip_java_code_generator.cc",
        "ctrip/protobuf/compiler/java/ctrip_java_main.cc",
    ],
    includes = [""],
    copts = COPTS,
    linkopts = LINK_OPTS,
    visibility = ["//visibility:public"],
    deps = [
        "//lib:protoc_lib",
        "//lib:spdlog"
    ]
)

cc_binary(
    name = "protoc-gen-ctrip-soa-csharp",
    srcs = [
        "ctrip/protobuf/soa.service.pb.cc",
        "ctrip/protobuf/ctrip_service_descriptor.cc",
        "ctrip/protobuf/compiler/ctrip_code_generator.cc",
        "ctrip/protobuf/compiler/csharp/ctrip_csharp_code_generator.cc",
        "ctrip/protobuf/compiler/csharp/ctrip_csharp_main.cc",
    ],
    includes = [""],
    copts = COPTS,
    linkopts = LINK_OPTS,
    visibility = ["//visibility:public"],
    deps = [
        "//lib:protoc_lib",
        "//lib:spdlog"
    ]
)
