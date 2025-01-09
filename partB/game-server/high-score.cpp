#include <zmq.hpp>
#include <iostream>

#include <ncurses.h>
#include <cursesw.h> // For ncurses++ features

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

    // Initialize ncurses
    initscr();          // Start curses mode
    noecho();           // Don't echo user input
    cbreak();           // Disable line buffering
    
    // Create a window object using ncurses++
    WINDOW* win = newwin(20, 30, 0, 0); // Height, width, start y, start x
    box(win, 0, 0);     // Draw a box around the window


    while (true) {
        try {
            // Receive the message
            zmq::message_t message_raw;
            subscriber.recv(message_raw, zmq::recv_flags::none);

            // Decode the Protobuf message
            HighScore protobuf_message;
            if (protobuf_message.ParseFromArray(message_raw.data(), message_raw.size())) {
                mvwprintw(win, 0, 10, "HIGH SCORES");
                if (protobuf_message.has_game()) {
                    break;
                }
                // Check if the `num` field is set
                if (protobuf_message.has_pa()) {
                    int pA = protobuf_message.pa();
                    mvwprintw(win, 2, 4, "Player A: %d           ", pA);
                    //std::cout << "Player A score: " << pA << std::endl;
                } else {
                    mvwprintw(win, 2, 4, "Player A not playing");
                    //std::cout << "Player A is not playing" << std::endl;
                }
                if (protobuf_message.has_pb()) {
                    int pB = protobuf_message.pb();
                    mvwprintw(win, 4, 4, "Player B: %d           ", pB);
                    //std::cout << "Player B score: " << pB << std::endl;
                } else {
                    mvwprintw(win, 4, 4, "Player B not playing");
                    //std::cout << "Player B is not playing" << std::endl;
                }
                if (protobuf_message.has_pc()) {
                    int pC = protobuf_message.pc();
                    mvwprintw(win, 6, 4,  "Player C: %d           ", pC);
                    //std::cout << "Player C score: " << pC << std::endl;
                } else {
                    mvwprintw(win, 6, 4, "Player C not playing");
                    //std::cout << "Player C is not playing" << std::endl;
                }
                if (protobuf_message.has_pd()) {
                    int pD = protobuf_message.pd();
                    mvwprintw(win, 8, 4, "Player D: %d           ", pD);
                    //std::cout << "Player D score: " << pD << std::endl;
                } else {
                    mvwprintw(win, 8, 4, "Player D not playing");
                    //std::cout << "Player D is not playing" << std::endl;
                }
                if (protobuf_message.has_pe()) {
                    int pE = protobuf_message.pe();
                    mvwprintw(win, 10, 4, "Player E: %d           ", pE);
                    //std::cout << "Player E score: " << pE << std::endl;
                } else {
                    mvwprintw(win, 10, 4, "Player E not playing");
                    //std::cout << "Player E is not playing" << std::endl;
                }
                if (protobuf_message.has_pf()) {
                    int pF = protobuf_message.pf();
                    mvwprintw(win, 12, 4, "Player F: %d           ", pF);
                    //std::cout << "Player F score: " << pF << std::endl;
                } else {
                    mvwprintw(win, 12, 4, "Player F not playing");
                    //std::cout << "Player F is not playing" << std::endl;
                }
                if (protobuf_message.has_pg()) {
                    int pG = protobuf_message.pg();
                    mvwprintw(win, 14, 4, "Player G: %d           ", pG);
                    //std::cout << "Player G score: " << pG << std::endl;
                } else {
                    mvwprintw(win, 14, 4, "Player G not playing");
                    //std::cout << "Player G is not playing" << std::endl;
                }
                if (protobuf_message.has_ph()) {
                    int pH = protobuf_message.ph();
                    mvwprintw(win, 16, 4, "Player H: %d           ", pH);
                    //std::cout << "Player H score: " << pH << std::endl;
                } else {
                    mvwprintw(win, 16, 4, "Player H not playing");
                    //std::cout << "Player H is not playing" << std::endl;
                }

                wrefresh(win);

            } else {
                std::cerr << "Failed to parse Protobuf message" << std::endl;
            }
        } catch (const zmq::error_t& e) {
            std::cerr << "ZMQ error: " << e.what() << std::endl;
            break;
        }
    }

    endwin(); // End curses mode
    // Clean up and close the socket
    subscriber.close();
    context.close();

    return 0;
}
