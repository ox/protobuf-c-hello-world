# Protobuf-c Hello World

This is the smallest useful demonstration of [protobuf-c](https://code.google.com/p/protobuf-c/)'s RPC capabilities. I made this project because the _only_ [example use of RPC](https://code.google.com/p/protobuf-c/wiki/RPC_Example) was incredibly convoluted and managed to hide the core logic that was needed to actually _use_ the RPC capabilities. Hopefully this little example will manage to show off some of the incredible RPC capabilities that protobuf-c offers.

# Prereqs

You should go and get [protobuf-c](https://code.google.com/p/protobuf-c/) some how. For OS X users with [homebrew](http://mxcl.github.io/homebrew/), just run:

    $ brew install protobuf-c

Alternatively, you can download the latest source code from the [downloads page](https://code.google.com/p/protobuf-c/downloads/list) and compile it by hand.

# Building and Running

To build both the server and the client, run `make` in the root folder. It should build the `ping.proto` file as well as `client.c` and `server.c`.

To run the server:

    $ make test_server

To run the client:

    $ make test_client

The server is a long-running process and will stay up until you kill it.

# License

fuck it.