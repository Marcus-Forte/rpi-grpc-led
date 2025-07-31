
#include "blinky_service.hh"
#include "gpiodLed.hh"
#include "simLed.hh"

#include <boost/program_options.hpp>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <print>

namespace po = boost::program_options;

int main(int argc, char **argv) {

  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "Show help message")(
      "sim", po::bool_switch()->default_value(false),
      "Use simulated LED")("chip", po::value<std::string>()->required(),
                           "GPIO chip name (e.g., gpiochip0)");

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  } catch (const po::error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << desc << std::endl;
    return 1;
  }

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  const auto chip_name = vm["chip"].as<std::string>();
  const auto use_sim = vm["sim"].as<bool>();

  std::shared_ptr<ILED> led;

  if (use_sim) {
    led = std::make_shared<SimLed>(chip_name);
  } else {
    led = std::make_shared<GpiodLed>(chip_name);
  }

  BlinkyServiceImpl service(led);

  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::println("gRPC server listening..");
  server->Wait();

  return 0;
}
