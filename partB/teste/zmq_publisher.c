#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "simple_message.pb-c.h"

int main() {
    // Initialize ZeroMQ context and publisher socket
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);

    // Bind the publisher to a specific endpoint
    const char *endpoint = "tcp://*:5553";
    if (zmq_bind(publisher, endpoint) != 0) {
        perror("Failed to bind publisher");
        zmq_ctx_destroy(context);
        return 1;
    }

    printf("Publisher bound to %s\n", endpoint);

    // Send messages in a loop
    for (int i = 1; i <= 10; i++) {
        // Create and populate the Protobuf message
        SimpleMessage msg = SIMPLE_MESSAGE__INIT;

        // Randomly decide whether to include the `num` field
        if (i % 2 == 0) {
            msg.has_num = 1;  // Mark the field as present
            msg.num = i;
            printf("Sending message with num = %d\n", msg.num);
        } else {
            msg.has_num = 0;  // Field is not set
            printf("Sending message without num\n");
        }

        // Serialize the Protobuf message
        size_t msg_size = simple_message__get_packed_size(&msg);
        void *buffer = malloc(msg_size);
        if (!buffer) {
            perror("Failed to allocate memory for message");
            break;
        }
        simple_message__pack(&msg, buffer);

        // Send the serialized message via ZeroMQ
        zmq_msg_t zmq_message;
        zmq_msg_init_size(&zmq_message, msg_size);
        memcpy(zmq_msg_data(&zmq_message), buffer, msg_size);
        zmq_msg_send(&zmq_message, publisher, 0);
        zmq_msg_close(&zmq_message);

        free(buffer);  // Free the allocated buffer

        sleep(1);  // Wait for 1 second between messages
    }

    // Clean up and close the socket and context
    zmq_close(publisher);
    zmq_ctx_destroy(context);

    return 0;
}
