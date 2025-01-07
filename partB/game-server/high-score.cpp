#include <zmq.hpp>
#include <iostream>
#include "high_score.pb.h" 

int main() {
    // Prepare the ZMQ context and subscriber socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, zmq::socket_type::sub);

    // Connect the subscriber socket to the desired endpoint
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
            HighScore protobuf_message;
            if (protobuf_message.ParseFromArray(message_raw.data(), message_raw.size())) {
                // Check if the `num` field is set
                if (protobuf_message.has_pa()) {
                    int pA = protobuf_message.pa();
                    std::cout << "Player A score: " << pA << std::endl;
                } else {
                    std::cout << "Player A is not playing" << std::endl;
                }
                if (protobuf_message.has_pb()) {
                    int pB = protobuf_message.pb();
                    std::cout << "Player B score: " << pB << std::endl;
                } else {
                    std::cout << "Player B is not playing" << std::endl;
                }
                if (protobuf_message.has_pc()) {
                    int pC = protobuf_message.pc();
                    std::cout << "Player C score: " << pC << std::endl;
                } else {
                    std::cout << "Player C is not playing" << std::endl;
                }
                if (protobuf_message.has_pd()) {
                    int pD = protobuf_message.pa();
                    std::cout << "Player D score: " << pD << std::endl;
                } else {
                    std::cout << "Player D is not playing" << std::endl;
                }
                if (protobuf_message.has_pe()) {
                    int pE = protobuf_message.pe();
                    std::cout << "Player E score: " << pE << std::endl;
                } else {
                    std::cout << "Player E is not playing" << std::endl;
                }
                if (protobuf_message.has_pf()) {
                    int pF = protobuf_message.pa();
                    std::cout << "Player F score: " << pF << std::endl;
                } else {
                    std::cout << "Player F is not playing" << std::endl;
                }
                if (protobuf_message.has_pg()) {
                    int pG = protobuf_message.pg();
                    std::cout << "Player G score: " << pG << std::endl;
                } else {
                    std::cout << "Player G is not playing" << std::endl;
                }
                if (protobuf_message.has_ph()) {
                    int pH = protobuf_message.ph();
                    std::cout << "Player H score: " << pH << std::endl;
                } else {
                    std::cout << "Player H is not playing" << std::endl;
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
