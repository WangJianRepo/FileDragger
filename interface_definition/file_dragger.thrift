/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * The first thing to know about are types. The available types in Thrift are:
 *
 *  bool        Boolean, one byte
 *  i8 (byte)   Signed 8-bit integer
 *  i16         Signed 16-bit integer
 *  i32         Signed 32-bit integer
 *  i64         Signed 64-bit integer
 *  double      64-bit floating point value
 *  string      String
 *  binary      Blob (byte array)
 *  map<t1,t2>  Map from one type to another
 *  list<t1>    Ordered list of one type
 *  set<t1>     Set of unique elements of one type
 *
 * Did you also notice that Thrift supports C style comments?
 */


/**
 * Thrift files can namespace, package, or prefix their output in various
 * target languages.
 */
namespace cpp file_dragger

/**
 * �ļ���Ϣ
 *
 */
struct FileInfo {
  1: string rpath,
  2: bool isDir
}
 
/**
 * ���ͣ���ѯ������Ӧ
 *
 */
 
struct RequestQuery {
	
}
struct ResponseQuery {
  1: bool has_new_file_dir,
  2: list<FileInfo> file_dir_info
}

/**
 * ���ͣ�����������Ӧ
 * ��������������
 */
struct RequestDownload {
  1: i32 chunk,  // chunk num
  2: i32 num_chunk,  // num of chunks
  3: list<string> file_rpaths
}
struct ResponseDownload {
  1: i32 chunk,  // chunk num
  2: map<string,binary> files  // file_rpath->file_content
}

/**
 * ���ͣ�����������Ӧ
 *
 */
struct RequestFinish {
  1: list<string> file_dir_rpaths  // paths of file to be handled(deleted)
}
struct ResponseFinish {
  1: i32 num_handled  // num of files handled(deleted) successfully
}


/**
 * ����
 * 
 */
service FileDragger {
  // ����
  ResponseQuery Query(),
  // ����
  ResponseDownload Download(1:RequestDownload rd),
  // ����
  ResponseFinish Finish(1:RequestFinish rf)
}
