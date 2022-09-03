# Protobuf-c Hello World

This is the smallest useful demonstration of [protobuf-c-rpc](https://github.com/protobuf-c/protobuf-c-rpc)'s RPC capabilities. I made this project because the _only_ [example use of RPC](https://code.google.com/p/protobuf-c/wiki/RPC_Example) was incredibly convoluted and managed to hide the core logic that was needed to actually _use_ the RPC capabilities. This simple hello world example has been updated to work with the latest protobuf-c-rpc, complementary on the existing examples. Hopefully this little example will manage to show off some of the incredible RPC capabilities that protobuf-c and protobuf-c-rpc offer.

## Prerequisites

You should go and get [protobuf-c](https://github.com/protobuf-c/protobuf-c) and [protobuf-c](https://github.com/protobuf-c/protobuf-c) some how. For macOS users with [homebrew](https://brew.sh), just run:

    $ brew install protobuf-c

However, to this date, there is no homebrew port available for protobuf-c-rpc just yet. So, you may need to clone the latest source code from the [GitHub page](https://github.com/protobuf-c/protobuf-c-rpc) and compile it by hand.

# Build Protobuf-c-rpc from Source

    $ git clone https://github.com/protobuf-c/protobuf-c-rpc
    $ ./autgen.sh
    $ ./configure
    $ make && make install

# Build and Run Hello World

To build both the server and the client, run `make` in the root folder. It should build the `ping.proto` file as well as `client.c` and `server.c`.

To run the server:

    $ make test_server

To run the client:

    $ make test_client

The server is a long-running process and will stay up until you kill it.

## Authors

* **Artem Titoulenko** - *Initial work* - [ox](https://github.com/ox)
* **Ekawahyu Susilo** - *Modification to the latest protobuf-c-rpc and proto3* - [ekawahyu](https://github.com/ekawahyu)

## License

This project is licensed under the 2-Clause BSD License - see the [LICENSE](LICENSE) file for details