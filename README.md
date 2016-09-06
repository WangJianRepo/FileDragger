# FileDragger
Monitoring files and dirs in a dir from server and dragging them to client.

Download files and dirs in a designated dir in server automatically and periodically. After downloading files, all downloaded files will be deleted, and empty dirs will be also deleted after those files are deleted.

# Usage
Run command in a dir, and all files and dirs will be downloaded to this dir.

Client: 

    command ip port time_interval_hour time_wait_to_download_minute chunk_size
    ip: server ip
    port: server port
    time_interval_hour: how many hours to wait to require downloading
    time_wait_to_download_minute: how many minutes to wait to download files after request
    chunk_size: how many files to be downloaded at a time
    
Run command in a dir, and all files and dirs in this dir will be dragged by client.

Server: 

    command port
    port: server port
    
Tips: This executable file should not be in the same dir with files to be dragged, otherwise it would be uploaded and removed with other files.
