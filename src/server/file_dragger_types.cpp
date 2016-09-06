/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "file_dragger_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace file_dragger {


FileInfo::~FileInfo() throw() {
}


void FileInfo::__set_rpath(const std::string& val) {
  this->rpath = val;
}

void FileInfo::__set_isDir(const bool val) {
  this->isDir = val;
}

uint32_t FileInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->rpath);
          this->__isset.rpath = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->isDir);
          this->__isset.isDir = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t FileInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("FileInfo");

  xfer += oprot->writeFieldBegin("rpath", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->rpath);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("isDir", ::apache::thrift::protocol::T_BOOL, 2);
  xfer += oprot->writeBool(this->isDir);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(FileInfo &a, FileInfo &b) {
  using ::std::swap;
  swap(a.rpath, b.rpath);
  swap(a.isDir, b.isDir);
  swap(a.__isset, b.__isset);
}

FileInfo::FileInfo(const FileInfo& other0) {
  rpath = other0.rpath;
  isDir = other0.isDir;
  __isset = other0.__isset;
}
FileInfo& FileInfo::operator=(const FileInfo& other1) {
  rpath = other1.rpath;
  isDir = other1.isDir;
  __isset = other1.__isset;
  return *this;
}
void FileInfo::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "FileInfo(";
  out << "rpath=" << to_string(rpath);
  out << ", " << "isDir=" << to_string(isDir);
  out << ")";
}


RequestQuery::~RequestQuery() throw() {
}


uint32_t RequestQuery::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    xfer += iprot->skip(ftype);
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RequestQuery::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RequestQuery");

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(RequestQuery &a, RequestQuery &b) {
  using ::std::swap;
  (void) a;
  (void) b;
}

RequestQuery::RequestQuery(const RequestQuery& other2) {
  (void) other2;
}
RequestQuery& RequestQuery::operator=(const RequestQuery& other3) {
  (void) other3;
  return *this;
}
void RequestQuery::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "RequestQuery(";
  out << ")";
}


ResponseQuery::~ResponseQuery() throw() {
}


void ResponseQuery::__set_has_new_file_dir(const bool val) {
  this->has_new_file_dir = val;
}

void ResponseQuery::__set_file_dir_info(const std::vector<FileInfo> & val) {
  this->file_dir_info = val;
}

uint32_t ResponseQuery::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->has_new_file_dir);
          this->__isset.has_new_file_dir = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->file_dir_info.clear();
            uint32_t _size4;
            ::apache::thrift::protocol::TType _etype7;
            xfer += iprot->readListBegin(_etype7, _size4);
            this->file_dir_info.resize(_size4);
            uint32_t _i8;
            for (_i8 = 0; _i8 < _size4; ++_i8)
            {
              xfer += this->file_dir_info[_i8].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.file_dir_info = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ResponseQuery::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ResponseQuery");

  xfer += oprot->writeFieldBegin("has_new_file_dir", ::apache::thrift::protocol::T_BOOL, 1);
  xfer += oprot->writeBool(this->has_new_file_dir);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("file_dir_info", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->file_dir_info.size()));
    std::vector<FileInfo> ::const_iterator _iter9;
    for (_iter9 = this->file_dir_info.begin(); _iter9 != this->file_dir_info.end(); ++_iter9)
    {
      xfer += (*_iter9).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ResponseQuery &a, ResponseQuery &b) {
  using ::std::swap;
  swap(a.has_new_file_dir, b.has_new_file_dir);
  swap(a.file_dir_info, b.file_dir_info);
  swap(a.__isset, b.__isset);
}

ResponseQuery::ResponseQuery(const ResponseQuery& other10) {
  has_new_file_dir = other10.has_new_file_dir;
  file_dir_info = other10.file_dir_info;
  __isset = other10.__isset;
}
ResponseQuery& ResponseQuery::operator=(const ResponseQuery& other11) {
  has_new_file_dir = other11.has_new_file_dir;
  file_dir_info = other11.file_dir_info;
  __isset = other11.__isset;
  return *this;
}
void ResponseQuery::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ResponseQuery(";
  out << "has_new_file_dir=" << to_string(has_new_file_dir);
  out << ", " << "file_dir_info=" << to_string(file_dir_info);
  out << ")";
}


RequestDownload::~RequestDownload() throw() {
}


void RequestDownload::__set_chunk(const int32_t val) {
  this->chunk = val;
}

void RequestDownload::__set_num_chunk(const int32_t val) {
  this->num_chunk = val;
}

void RequestDownload::__set_file_rpaths(const std::vector<std::string> & val) {
  this->file_rpaths = val;
}

uint32_t RequestDownload::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->chunk);
          this->__isset.chunk = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->num_chunk);
          this->__isset.num_chunk = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->file_rpaths.clear();
            uint32_t _size12;
            ::apache::thrift::protocol::TType _etype15;
            xfer += iprot->readListBegin(_etype15, _size12);
            this->file_rpaths.resize(_size12);
            uint32_t _i16;
            for (_i16 = 0; _i16 < _size12; ++_i16)
            {
              xfer += iprot->readString(this->file_rpaths[_i16]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.file_rpaths = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RequestDownload::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RequestDownload");

  xfer += oprot->writeFieldBegin("chunk", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->chunk);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("num_chunk", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->num_chunk);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("file_rpaths", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->file_rpaths.size()));
    std::vector<std::string> ::const_iterator _iter17;
    for (_iter17 = this->file_rpaths.begin(); _iter17 != this->file_rpaths.end(); ++_iter17)
    {
      xfer += oprot->writeString((*_iter17));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(RequestDownload &a, RequestDownload &b) {
  using ::std::swap;
  swap(a.chunk, b.chunk);
  swap(a.num_chunk, b.num_chunk);
  swap(a.file_rpaths, b.file_rpaths);
  swap(a.__isset, b.__isset);
}

RequestDownload::RequestDownload(const RequestDownload& other18) {
  chunk = other18.chunk;
  num_chunk = other18.num_chunk;
  file_rpaths = other18.file_rpaths;
  __isset = other18.__isset;
}
RequestDownload& RequestDownload::operator=(const RequestDownload& other19) {
  chunk = other19.chunk;
  num_chunk = other19.num_chunk;
  file_rpaths = other19.file_rpaths;
  __isset = other19.__isset;
  return *this;
}
void RequestDownload::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "RequestDownload(";
  out << "chunk=" << to_string(chunk);
  out << ", " << "num_chunk=" << to_string(num_chunk);
  out << ", " << "file_rpaths=" << to_string(file_rpaths);
  out << ")";
}


ResponseDownload::~ResponseDownload() throw() {
}


void ResponseDownload::__set_chunk(const int32_t val) {
  this->chunk = val;
}

void ResponseDownload::__set_files(const std::map<std::string, std::string> & val) {
  this->files = val;
}

uint32_t ResponseDownload::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->chunk);
          this->__isset.chunk = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->files.clear();
            uint32_t _size20;
            ::apache::thrift::protocol::TType _ktype21;
            ::apache::thrift::protocol::TType _vtype22;
            xfer += iprot->readMapBegin(_ktype21, _vtype22, _size20);
            uint32_t _i24;
            for (_i24 = 0; _i24 < _size20; ++_i24)
            {
              std::string _key25;
              xfer += iprot->readString(_key25);
              std::string& _val26 = this->files[_key25];
              xfer += iprot->readBinary(_val26);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.files = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ResponseDownload::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ResponseDownload");

  xfer += oprot->writeFieldBegin("chunk", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->chunk);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("files", ::apache::thrift::protocol::T_MAP, 2);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->files.size()));
    std::map<std::string, std::string> ::const_iterator _iter27;
    for (_iter27 = this->files.begin(); _iter27 != this->files.end(); ++_iter27)
    {
      xfer += oprot->writeString(_iter27->first);
      xfer += oprot->writeBinary(_iter27->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ResponseDownload &a, ResponseDownload &b) {
  using ::std::swap;
  swap(a.chunk, b.chunk);
  swap(a.files, b.files);
  swap(a.__isset, b.__isset);
}

ResponseDownload::ResponseDownload(const ResponseDownload& other28) {
  chunk = other28.chunk;
  files = other28.files;
  __isset = other28.__isset;
}
ResponseDownload& ResponseDownload::operator=(const ResponseDownload& other29) {
  chunk = other29.chunk;
  files = other29.files;
  __isset = other29.__isset;
  return *this;
}
void ResponseDownload::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ResponseDownload(";
  out << "chunk=" << to_string(chunk);
  out << ", " << "files=" << to_string(files);
  out << ")";
}


RequestFinish::~RequestFinish() throw() {
}


void RequestFinish::__set_file_dir_rpaths(const std::vector<std::string> & val) {
  this->file_dir_rpaths = val;
}

uint32_t RequestFinish::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->file_dir_rpaths.clear();
            uint32_t _size30;
            ::apache::thrift::protocol::TType _etype33;
            xfer += iprot->readListBegin(_etype33, _size30);
            this->file_dir_rpaths.resize(_size30);
            uint32_t _i34;
            for (_i34 = 0; _i34 < _size30; ++_i34)
            {
              xfer += iprot->readString(this->file_dir_rpaths[_i34]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.file_dir_rpaths = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RequestFinish::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RequestFinish");

  xfer += oprot->writeFieldBegin("file_dir_rpaths", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->file_dir_rpaths.size()));
    std::vector<std::string> ::const_iterator _iter35;
    for (_iter35 = this->file_dir_rpaths.begin(); _iter35 != this->file_dir_rpaths.end(); ++_iter35)
    {
      xfer += oprot->writeString((*_iter35));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(RequestFinish &a, RequestFinish &b) {
  using ::std::swap;
  swap(a.file_dir_rpaths, b.file_dir_rpaths);
  swap(a.__isset, b.__isset);
}

RequestFinish::RequestFinish(const RequestFinish& other36) {
  file_dir_rpaths = other36.file_dir_rpaths;
  __isset = other36.__isset;
}
RequestFinish& RequestFinish::operator=(const RequestFinish& other37) {
  file_dir_rpaths = other37.file_dir_rpaths;
  __isset = other37.__isset;
  return *this;
}
void RequestFinish::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "RequestFinish(";
  out << "file_dir_rpaths=" << to_string(file_dir_rpaths);
  out << ")";
}


ResponseFinish::~ResponseFinish() throw() {
}


void ResponseFinish::__set_num_handled(const int32_t val) {
  this->num_handled = val;
}

uint32_t ResponseFinish::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->num_handled);
          this->__isset.num_handled = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ResponseFinish::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ResponseFinish");

  xfer += oprot->writeFieldBegin("num_handled", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->num_handled);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ResponseFinish &a, ResponseFinish &b) {
  using ::std::swap;
  swap(a.num_handled, b.num_handled);
  swap(a.__isset, b.__isset);
}

ResponseFinish::ResponseFinish(const ResponseFinish& other38) {
  num_handled = other38.num_handled;
  __isset = other38.__isset;
}
ResponseFinish& ResponseFinish::operator=(const ResponseFinish& other39) {
  num_handled = other39.num_handled;
  __isset = other39.__isset;
  return *this;
}
void ResponseFinish::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ResponseFinish(";
  out << "num_handled=" << to_string(num_handled);
  out << ")";
}

} // namespace