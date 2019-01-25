#ifndef INC_4_PROCESSOR_FILE_BUFFER_HPP
#define INC_4_PROCESSOR_FILE_BUFFER_HPP

#include <iostream>
#include <sys/stat.h>
#include <memory>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include <cstring>

class FileBuffer{
 public:
  char* buffer_;
  size_t countRows_ = 0;
  size_t length_ = 0;
  std::vector<char*> pointers_;

 public:
  FileBuffer() {}
  FileBuffer(const char* filename) {
    struct stat sb;
    if (stat(filename, &sb) == -1) {
      printf("ERROR: file stat failed\n");
      assert(1);
      return;
    }
    int file = open(filename, O_RDWR);
    buffer_ = static_cast<char*>(mmap(nullptr, sb.st_size + 1, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0));
    if (buffer_ == MAP_FAILED) {
      delete buffer_;
      printf("ERROR: file map failed\n");
      assert(1);
      return;
    }

    length_ = sb.st_size + 1;
    for (int i = 0; i < length_; ++i) {
      if (buffer_[i] == '\n')
        buffer_[i] = '\0';
      if (buffer_[i] == '\0')
        ++countRows_;
    }

    pointers_.assign(countRows_, nullptr);
    pointers_[0] = buffer_;
    for (int i = 0, count = 0; i < length_ - 1; ++i) {
      if (buffer_[i] == '\0')
        pointers_[++count] = buffer_ + i + 1;
    }
  }

  ~FileBuffer() {
    for (int i = 0; i < length_; ++i) {
      if (buffer_[i] == '\0')
        buffer_[i] = '\n';
    }
  }
};



#endif //INC_4_PROCESSOR_FILE_BUFFER_HPP
