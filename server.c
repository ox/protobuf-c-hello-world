#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ping.pb-c.h"
#include <google/protobuf-c/protobuf-c-rpc.h>

static int starts_with (const char *str, const char *prefix) {
  return memcmp (str, prefix, strlen (prefix)) == 0;
}

// this will handle all rpc calls using the reply_to_ping service
void ping__reply_to_ping(PingService_Service * service,
 const Ping * input,
 Ping_Closure closure,
 void * closure_data) {
  printf("input->message: %s\n", input->message);

  // init the message
  Ping ping_response = PING__INIT;
  ping_response.message = strdup("hi");

  // respond with the ping_response buffer
  closure(&ping_response, closure_data);
}

static PingService_Service ping_service = PING_SERVICE__INIT(ping__);

int main(int argc, char **argv) {
  ProtobufC_RPC_Server * server;
  const char *name = NULL;
  unsigned i;

  for (i = 1; i < (unsigned) argc; i++) {
    if (starts_with(argv[i], "--port=")) {
      name = strchr (argv[i], '=') + 1;
    }
  }

  if (name == NULL) {
    fprintf(stderr, "missing --tcp=HOST:PORT");
    return 1;
  }

  server = protobuf_c_rpc_server_new (PROTOBUF_C_RPC_ADDRESS_TCP, name, (ProtobufCService *) &ping_service, NULL);

  for (;;)
    protobuf_c_dispatch_run (protobuf_c_dispatch_default ());

  protobuf_c_rpc_server_destroy(server, 1);
  return 0;
}
