#include <zmq.hpp>
#include <iostream>
#include "simple_message.pb.h"

int main() {
    // Initialize ZeroMQ context and subscriber socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, zmq::socket_type::sub);

    // Connect the subscriber socket to the publisher
    const std::string endpoint = "tcp://localhost:5553";
    subscriber.connect(endpoint);
    std::cout << "Subscriber connected to " << endpoint << std::endl;

    // Subscribe to all messages
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    while (true) {
        try {
            // Receive the message
            zmq::message_t message_raw;
            subscriber.recv(message_raw, zmq::recv_flags::none);

            // Decode the Protobuf message
            SimpleMessage protobuf_message;
            if (protobuf_message.ParseFromArray(message_raw.data(), message_raw.size())) {
                // Check if the `num` field is set
                if (protobuf_message.has_num()) {
                    int num = protobuf_message.num();
                    std::cout << "Received Protobuf message, num: " << num << std::endl;
                } else {
                    std::cout << "Received Protobuf message without 'num' field" << std::endl;
                }
            } else {
                std::cerr << "Failed to parse Protobuf message" << std::endl;
            }
        } catch (const zmq::error_t& e) {
            std::cerr << "ZMQ error: " << e.what() << std::endl;
            break;
        }
    }

    // Clean up and close the socket
    subscriber.close();
    context.close();

    return 0;
}
