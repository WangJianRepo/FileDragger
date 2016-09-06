

#include "FileDragger.h"

#include <stdio.h>
#include <math.h>

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <glog/logging.h>
#include <boost/timer.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp> 

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace  ::file_dragger;

void CreateFolders(std::vector<FileInfo>& file_info);
void SaveFiles(map<string, string>& path_file_map);

int main(int argc, char* argv[]) {


  // logging
  FLAGS_stderrthreshold = ::google::GLOG_INFO;  // also print to stderr
  ::google::InitGoogleLogging("FileDraggerClient");

  // Check command line
  if (argc != 6) {
    LOG(INFO) << "Usage: command ip port time_interval_hour time_wait_to_download_minute chunk_size";
    return -1;
  } 
  LOG(INFO) << "ip: " << argv[1] << " port: " << argv[2] << " time_interval_hour: " << argv[3] << " time_wait_to_download_minute: " << argv[4] << " chunk_size: " << argv[5];

  string ip = argv[1];
  int port = 0;
  sscanf(argv[2], "%d", &port);

  boost::shared_ptr<TTransport> socket(new TSocket(ip, port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));


  FileDraggerClient client(protocol);
  

  // get time interval
  double hour_interval = 0;
  sscanf(argv[3], "%lf", &hour_interval);
  double minute_wait = 0;
  sscanf(argv[4], "%lf", &minute_wait);

  while (true) {
    LOG(INFO) << "Start!!!";
    try {
      // Timer
      boost::timer time;
      double diff = 0;
      while (true) {
        try {

          // 1. Query
          transport->open();
          LOG(INFO) << "Connected.";
          LOG(INFO) << "Query...";
          ResponseQuery rpq;
          client.Query(rpq);
          if (!rpq.has_new_file_dir) { // if there is no file
            LOG(INFO) << "No new file.";

            // wait for next cycle
            diff = hour_interval - (time.elapsed() / 3600);
            if (diff > 0){  // if time is not reached
              transport->close();
              LOG(INFO) << "Disconnected.";
              LOG(INFO) << "Query again after " << diff << " hours...";
              boost::this_thread::sleep(boost::posix_time::milliseconds(diff * 3600 * 1000));
            }
            time.restart();

            continue;
          }
          LOG(INFO) << rpq.file_dir_info.size() << " new files found.";


          // 2. Download file using chunk = 50
          // create folders according to file rpaths in response
          CreateFolders(rpq.file_dir_info);
          // waiting for file to be stable, 1 minute
          transport->close();
          LOG(INFO) << "Disconnected.";
          LOG(INFO) << "Waiting " << minute_wait << " min to download...";
          boost::this_thread::sleep(boost::posix_time::milliseconds(minute_wait * 60 * 1000));
          transport->open();
          LOG(INFO) << "Connected.";
          // find all file paths
          const vector<FileInfo>& file_dir_info = rpq.file_dir_info;
          vector<string> file_rpaths;
          for (auto item : file_dir_info) {
            if (!(item.isDir)) {
              file_rpaths.push_back(item.rpath);

            }
          }
          int chunk_size = 0;
          sscanf(argv[5], "%d", &chunk_size);
          int chunks = ceil(file_rpaths.size() / (float)chunk_size);

          RequestDownload rqd;
          ResponseDownload rpd;

          vector<string>::iterator start;
          vector<string>::iterator end;
          for (int chunk = 0; chunk < chunks; ++chunk) {
            LOG(INFO) << "Downloading files: " << chunk << "/" << chunks << " chunks...";
            // file to be dowloaded
            rqd.file_rpaths.clear();
            rqd.chunk = chunk + 1;
            rqd.num_chunk = chunks;

            start = file_rpaths.begin() + chunk*chunk_size;
            if (chunk == chunks - 1) {
              end = file_rpaths.end();
            }
            else {
              end = file_rpaths.begin() + (chunk + 1)*chunk_size;
            }
            rqd.file_rpaths.assign(start, end);

            // Download
            rpd.files.clear();
            client.Download(rpd, rqd);
            // Save
            SaveFiles(rpd.files);
          }



          // 3. Finish
          // remove all files after 5 minutes, empty dir will be deleted if no new file added during this time.
          transport->close();
          LOG(INFO) << "Disconnected.";
          LOG(INFO) << "Delete files and dir if empty after 5 minutes!!!";
          boost::this_thread::sleep(boost::posix_time::milliseconds(5 * 60 * 1000));
          transport->open();
          LOG(INFO) << "Connected.";

          LOG(INFO) << "Deleting...";
          vector<string> rpaths;
          for (auto item : file_dir_info) {
            rpaths.push_back(item.rpath);
          }
          RequestFinish rqf;
          rqf.file_dir_rpaths = rpaths;
          ResponseFinish rpf;
          client.Finish(rpf, rqf);
          LOG(INFO) << "Finish." << std::endl;

          transport->close();
          LOG(INFO) << "Disconnected.";

          // wait for next cycle
          diff = hour_interval - (time.elapsed() / 3600);
          if (diff > 0){  // if time is not reached
            LOG(INFO) << "Query again after " << diff << " hours...";
            boost::this_thread::sleep(boost::posix_time::milliseconds(diff * 3600 * 1000));
          }
          time.restart();

        } // end of thrift exception
        catch (TException& tx) {
          LOG(INFO) << "ERROR: " << tx.what() << endl;
        }

      }
    } // end of all exception
    catch (std::exception& e) {
      LOG(INFO) << "ERROR: " << e.what() << endl;
    }
  }



  // shutdown logging
  ::google::ShutdownGoogleLogging();
  return 0;
}

void CreateFolders(std::vector<FileInfo>& file_info) {

  for (auto file : file_info) {
    // if dir not exist, and create recursively
    if (file.isDir && !(boost::filesystem::exists(file.rpath))) {
      boost::filesystem::create_directories(file.rpath);
    }
  }


  //set<boost::filesystem::path> parent_paths;
  //// get all parent paths of files, remove duplicated paths
  //for (auto file_path : file_paths) {
  //  boost::filesystem::path p(file_path);
  //  parent_paths.insert(p.parent_path());
  //}
  //// create all folders according paths in parent_paths
  //vector<boost::filesystem::path> folder_names;
  //for (auto folder_path : parent_paths) {
  //  boost::filesystem::create_directories(folder_path);
  //}

}

void SaveFiles(map<string, string>& path_file_map) {
  for (auto item : path_file_map) {
    ofstream ofstrm(item.first, ios::binary | ios::trunc);
    ofstrm << item.second;
    ofstrm.close();
  }
}