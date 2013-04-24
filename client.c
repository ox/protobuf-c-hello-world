#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include <google/protobuf-c/protobuf-c-rpc.h>
#include "ping.pb-c.h"

static int starts_with (const char *str, const char *prefix) {
  return memcmp (str, prefix, strlen (prefix)) == 0;
}

static void handle_ping_response (const Ping *result,
 void *closure_data) {
  printf("ping reply: %s\n", result->message);
  *(protobuf_c_boolean *) closure_data = 1;
}

int main (int argc, char ** argv) {
  ProtobufCService *service;
  ProtobufC_RPC_Client * client;
  const char * name = NULL;
  unsigned i;

  // the ping message we will be sending
  Ping ping = PING__INIT;

  for (i = 1; i < (unsigned) argc; i++) {
    if (starts_with (argv[i], "--tcp=")) {
      name = strchr (argv[i], '=') + 1;
    }
  }

  if (name == NULL) {
    fprintf(stderr, "missing --tcp=HOST:PORT");
    return 1;
  }

  // service creates an rpc client, and client is a special cast
  service = protobuf_c_rpc_client_new (PROTOBUF_C_RPC_ADDRESS_TCP, name, &ping_service__descriptor, NULL);
  client = (ProtobufC_RPC_Client *) service;

  fprintf (stderr, "Connecting... ");
  while (!protobuf_c_rpc_client_is_connected (client))
    protobuf_c_dispatch_run (protobuf_c_dispatch_default ());
  fprintf (stderr, "done.\n");

  // create the message
  ping.message = strdup("HELLO WORLD");

  // send it on it's way
  protobuf_c_boolean is_done = 0;
  printf("sending ping... ");
  // handle_ping_response will be called with the resulting PingResponse
  ping_service__reply_to_ping(service, &ping, handle_ping_response, &is_done);

  while (!is_done)
    protobuf_c_dispatch_run (protobuf_c_dispatch_default ());
}
