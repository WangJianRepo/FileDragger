// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "FileDragger.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::file_dragger;

class FileDraggerHandler : virtual public FileDraggerIf {
 public:
  FileDraggerHandler() {
    // Your initialization goes here
  }

  void Query(ResponseQuery& _return) {
    // Your implementation goes here
    printf("Query\n");
  }

  void Download(ResponseDownload& _return, const RequestDownload& rd) {
    // Your implementation goes here
    printf("Download\n");
  }

  void Finish(ResponseFinish& _return, const RequestFinish& rf) {
    // Your implementation goes here
    printf("Finish\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<FileDraggerHandler> handler(new FileDraggerHandler());
  shared_ptr<TProcessor> processor(new FileDraggerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

