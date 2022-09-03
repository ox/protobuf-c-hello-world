/*
 * Copyright (c) 2013, Artem Titoulenko
 * Copyright (c) 2022, Ekawahyu Susilo
 * 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include <protobuf-c-rpc/protobuf-c-rpc.h>
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
    protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
  fprintf (stderr, "done.\n");

  // create the message
  ping.message = strdup("HELLO WORLD");

  // send it on it's way
  protobuf_c_boolean is_done = 0;
  printf("sending ping... ");
  // handle_ping_response will be called with the resulting PingResponse
  ping_service__reply_to_ping(service, &ping, handle_ping_response, &is_done);

  while (!is_done)
    protobuf_c_rpc_dispatch_run (protobuf_c_rpc_dispatch_default ());
}
