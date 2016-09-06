/*
* File Dragger Server
* wait for client request and then send all files in current dir
* all file paths are formatted: ./a/b/c.ext(relative paths)
*
* author	WangJian (wangjian4500@gmail.com)
* version	v1.0
* date		20160825
*/


#include "FileDragger.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

#include <glog/logging.h>
#include <boost/filesystem.hpp>

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using boost::shared_ptr;

using namespace  ::file_dragger;

class FileDraggerHandler : virtual public FileDraggerIf {
 public:
  FileDraggerHandler() {
    // Your initialization goes here
  }

  void Query(ResponseQuery& _return) {
    // Your implementation goes here
    LOG(INFO) << "Query";

    boost::filesystem::path p("./");
    typedef boost::filesystem::recursive_directory_iterator rd_iterator;
    rd_iterator end;
    for (rd_iterator pos(p); pos != end; ++pos) {
      FileInfo file_dir_info;
      file_dir_info.rpath = pos->path().string();
      file_dir_info.isDir = boost::filesystem::is_directory(pos->path());
      _return.file_dir_info.push_back(file_dir_info);
    }

    if (_return.file_dir_info.size() > 0) {
      _return.has_new_file_dir = true;
    }
    else {
      _return.has_new_file_dir = false;
    }
  }

  void Download(ResponseDownload& _return, const RequestDownload& rd) {
    // Your implementation goes here
    LOG(INFO) << "Download: " << rd.chunk << "/" << rd.num_chunk;

    const std::vector<std::string>& file_rpaths = rd.file_rpaths;
    
    _return.chunk = rd.chunk;

    //read all files 
    
    for (auto rpath : file_rpaths) {
      LOG(INFO) << "File:\t" << rpath;
      boost::filesystem::path p(rpath);
      std::fstream fstrm;
      while (true) {
        try {
          fstrm.open(rpath, std::ios::in | std::ios::out | std::ios::binary);
          if (fstrm.good()) break;
          //std::cout << "File has been opened, waiting... : " << rpath << std::endl;
          LOG(INFO) << "File has been opened, waiting to be closed... : " << rpath;
          boost::this_thread::sleep(boost::posix_time::milliseconds(2 * 1000)); // sleep 2 sec

        }
        catch (std::exception& e) {
          LOG(ERROR) << e.what() << std::endl;
        }
        fstrm.close();
      }
      std::ostringstream osstrm;
      osstrm << fstrm.rdbuf();


      _return.files.insert(std::pair<std::string, std::string>(rpath, osstrm.str()));
      fstrm.close();
    }
    
  }

  void Finish(ResponseFinish& _return, const RequestFinish& rf) {
    // Your implementation goes here

    _return.num_handled = 0;

    //std::set<boost::filesystem::path> removed_paths;

    // remove all files and then remove empty dirs
    for (auto item : rf.file_dir_rpaths) {
      boost::filesystem::path p(item);
      if (boost::filesystem::is_regular_file(p)) {
        try {
          boost::filesystem::remove(p);
          _return.num_handled++;
          LOG(INFO) << "File deleted:\t" << item;
        }
        catch (std::exception& e){
          LOG(ERROR) << "ERROR:File deleted:\t" << item << "\n" << e.what();
        }
        p = p.parent_path();
      }
      // if dir is not . and not deleted and empty, remove dir recursively
      while (p.string() != "." && boost::filesystem::exists(p) && boost::filesystem::is_empty(p)) {
        //if (removed_paths.find(p) == removed_paths.end()) { // not deleted
          try {
            boost::filesystem::remove(p);
            _return.num_handled++;
            LOG(INFO) << "Dir deleted:\t" << p.string();
          }
          catch (std::exception& e){
            LOG(ERROR) << "ERROR:File deleted:\t" << item << "\n" << e.what();
          }
          //removed_paths.insert(p);
        //}
        p = p.parent_path();
      }
    }


    //std::set<boost::filesystem::path> root_dirs;
    //// get all root dir of files, remove duplicated paths
    //for (auto file_path : rf.file_rpaths) {
    //  boost::filesystem::path p(file_path);
    //  boost::filesystem::path::iterator itr = p.begin();  // path ./a/b/c
    //  itr++;  // point to a
    //  root_dirs.insert(*itr);
    //}

    //for (auto item : root_dirs) {
    //  // remove the root folder
    //  LOG(INFO) << "File(dir) deleted:\t" << item.string();
    //  boost::filesystem::remove_all(item); // remove the root dir
    //  _return.num_handled++;
    //}
    LOG(INFO) << "Finish" << std::endl;
  }

};

/*
FileDraggerIfFactory is code generated.
FileDraggerCloneFactory is useful for getting access to the server side of the
transport.  It is also useful for making per-connection state.  Without this
CloneFactory, all connections will end up sharing the same handler instance.
*/
class FileDraggerCloneFactory : virtual public FileDraggerIfFactory {
public:
  virtual ~FileDraggerCloneFactory() {}
  virtual FileDraggerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo)
  {
    boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
    std::cout << "Incoming connection\n";
    std::cout << "\tSocketInfo: " << sock->getSocketInfo() << "\n";
    std::cout << "\tPeerHost: " << sock->getPeerHost() << "\n";
    std::cout << "\tPeerAddress: " << sock->getPeerAddress() << "\n";
    std::cout << "\tPeerPort: " << sock->getPeerPort() << "\n";
    return new FileDraggerHandler;
  }
  virtual void releaseHandler(FileDraggerIf* handler) {
    delete handler;
  }
};

int main(int argc, char* argv[]) {
  // log
  FLAGS_stderrthreshold = ::google::GLOG_INFO;  // also print to stderr
  ::google::InitGoogleLogging("FileDraggerServer");

  if (argc != 2) {
    LOG(INFO) << "Usage: command port" << std::endl;
    return -1;
  }
  LOG(INFO) << "port: " << argv[1];

  int port = 0;
  sscanf(argv[1], "%d", &port);

  shared_ptr<FileDraggerHandler> handler(new FileDraggerHandler());
  shared_ptr<TProcessor> processor(new FileDraggerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

  //TThreadedServer server(
  //  boost::make_shared<FileDraggerProcessor>(boost::make_shared<FileDraggerHandler>()),
  //  boost::make_shared<TServerSocket>(port), //port
  //  boost::make_shared<TBufferedTransportFactory>(),
  //  boost::make_shared<TBinaryProtocolFactory>());
  
  LOG(INFO) << "serving...";
  server.serve();

  // shutdown logging
  ::google::ShutdownGoogleLogging();
  return 0;
}

