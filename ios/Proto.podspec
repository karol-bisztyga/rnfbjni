Pod::Spec.new do |s|
  s.name     = "Proto"
  s.version  = "0.0.1"
  s.license  = "Apache License, Version 2.0"
  s.authors  = { 'gRPC contributors' => 'grpc-io@googlegroups.com' }
  s.homepage = "https://grpc.io/"
  s.summary = "Proto example"
  s.source = { :git => 'https://github.com/grpc/grpc.git' }

  s.ios.deployment_target = "9.0"
  s.osx.deployment_target = "10.10"

  # Base directory where the .proto files are.
  src = "../cpp/net/protos"

  # Run protoc with the Objective-C and gRPC plugins to generate protocol messages and gRPC clients.
  s.dependency "!ProtoCompiler-gRPCCppPlugin"

  # Pods directory corresponding to this app's Podfile, relative to the location of this podspec.
  pods_root = 'Pods'

  # Path where Cocoapods downloads protoc and the gRPC plugin.
  protoc_dir = "#{pods_root}/!ProtoCompiler"
  protoc = "#{protoc_dir}/protoc"
  plugin = "#{pods_root}/!ProtoCompiler-gRPCCppPlugin/grpc_cpp_plugin"

  # Directory where the generated files will be placed.
  dir = "#{pods_root}/#{s.name}"

  s.prepare_command = <<-CMD
    mkdir -p #{dir}
    #{protoc} \
        --plugin=protoc-gen-grpc=#{plugin} \
        --cpp_out=#{dir} \
        --grpc_out=#{dir} \
        -I #{src} \
        -I #{protoc_dir} \
        #{src}/helloworld.proto
  CMD

end