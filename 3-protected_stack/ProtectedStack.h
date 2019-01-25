#define CANAREIKA static_cast<T>(0xDEADBEEF)

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

#define LOG_OK fprintf(logOut, "#%s - completed\n", __FUNCTION__);
#define LOG_ERROR(mess) fprintf(logOut, "#%s - failed with error: %s\n", __FUNCTION__, mess);

#define FAILURE(fail, type) ERROR = type; LOG_ERROR(fail) return false;

enum class ERROR_TYPE{
  NO_ERROR = -1,
  OVERSIZE,
  BROKEN_CANARY,
  BROKEN_CHECKSUM
};

template <typename T>
class ProtectedStack{
 public:
  ProtectedStack(size_t start_capacity = 8);
  ~ProtectedStack();

  bool IsOk();
  bool IsEmpty() const;

  void Dump() const;
  size_t Size() const;

  bool Push(T item);
  bool Pop(T& item);
  T Pop();
  T Top();

 private:
  size_t CalculateCheckSum() const;
  void Resize();

  T* buffer_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  size_t check_sum_ = 0;
  ERROR_TYPE ERROR = ERROR_TYPE::NO_ERROR;

  FILE* logOut;

  std::hash<T> hash_;
};


template <typename T>
ProtectedStack<T>::ProtectedStack(size_t start_capacity)
        : capacity_(start_capacity),
          size_(0) {
  buffer_ = new T[capacity_ + 2];
  buffer_[0] = CANAREIKA;
  buffer_[capacity_ + 1] = CANAREIKA;
  logOut = fopen("logs.txt",  "w");
  check_sum_ = CalculateCheckSum();
}

template <typename T>
ProtectedStack<T>::~ProtectedStack() {
//  Dump();
  delete [] buffer_;
  LOG_OK
  fclose(logOut);
}

template <typename T>
bool ProtectedStack<T>::IsEmpty() const {
  LOG_OK
  return size_ == 0;
}

template <typename T>
size_t ProtectedStack<T>::Size() const {
  LOG_OK
  return size_;
}

template <typename T>
bool ProtectedStack<T>::IsOk() {
  if (size_ > capacity_) {
    FAILURE("size bigger than capacity", ERROR_TYPE::OVERSIZE)
  }
  if (buffer_[0] != CANAREIKA || buffer_[capacity_ + 1] != CANAREIKA) {
    FAILURE("CANAREIKA was broken", ERROR_TYPE::BROKEN_CANARY)
  }
  if (CalculateCheckSum() != check_sum_) {
    FAILURE("Check sum broken", ERROR_TYPE::BROKEN_CHECKSUM)
  }
  LOG_OK
  return true;
}

template <typename T>
size_t ProtectedStack<T>::CalculateCheckSum() const {
  size_t cur_sum = capacity_ + size_;
  for (size_t i = 1; i <= size_; ++i)
    cur_sum += hash_(buffer_[i]);
  return cur_sum;
}

template <typename T>
bool ProtectedStack<T>::Push(T item) {
  if (!IsOk()) {
    LOG_ERROR("PUSH failed")
    return false;
  }
  if (size_ == capacity_)
    Resize();

  buffer_[++size_] = item;
  check_sum_ = CalculateCheckSum();
  LOG_OK
  return IsOk();
}

template <typename T>
bool ProtectedStack<T>::Pop(T& item) {
  if (!IsOk() || IsEmpty()) {
    LOG_ERROR("POP failed")
    return false;
  }

  item = buffer_[size_--];
  check_sum_ = CalculateCheckSum();
  LOG_OK
  return IsOk();
}

template <typename T>
T ProtectedStack<T>::Pop() {
  if (!IsOk() || IsEmpty()) {
    LOG_ERROR("POP failed")
    return nullptr;
  }

  T item = buffer_[size_--];
  check_sum_ = CalculateCheckSum();
  LOG_OK
  return item;
}

template <typename T>
T ProtectedStack<T>::Top() {
  return buffer_[size_];
}

template <typename T>
void ProtectedStack<T>::Resize() {
  try {
    size_t new_capacity = capacity_ * 2;
    T *dopData = new T[capacity_];
    for (size_t i = 1; i <= size_; ++i)
      dopData[i - 1] = buffer_[i];
    delete[] buffer_;
    buffer_ = new T[new_capacity + 2];
    buffer_[0] = CANAREIKA;
    buffer_[new_capacity + 1] = CANAREIKA;
    for (size_t i = 0; i < size_; ++i)
      buffer_[i + 1] = dopData[i];
    capacity_ = new_capacity;
  } catch (std::exception& e) {
    LOG_ERROR("Resize failed")
  }
}

#define OK GREEN "(OK)" RESET
#define CHECK_ERROR(type, mess) if (ERROR == type) { message = mess; color = RED; } \
                                else { message = OK; color = RESET; }
#define START_DEFINE(not_error, error) const_cast<char*>((ERROR == ERROR_TYPE::NO_ERROR) ? not_error : error)

template <typename T>
void ProtectedStack<T>::Dump() const {
  char* color = START_DEFINE(RESET, RED);
  char* message = START_DEFINE(OK, "(FAILED)");
  printf("%sStack [%X] %s {%s\n", color, this, message, RESET);

  CHECK_ERROR(ERROR_TYPE::BROKEN_CANARY, "canary failed")
  printf("%s\tcanary1 = %X; %s\n\tcanary2 = %X; %s%s\n", color, buffer_[0], message, buffer_[capacity_ + 1], message, RESET);

  CHECK_ERROR(ERROR_TYPE::OVERSIZE, "fail with size")
  printf("%s\tsize = %ld; %s \n\tcapacity = %ld; %s%s\n", color, size_, message, capacity_, message, RESET);

  CHECK_ERROR(ERROR_TYPE::BROKEN_CHECKSUM, "checksum failed")
  printf("%s\tbuffer[%ld] [%ld] %s {\n", color, size_, buffer_, message);
  for (size_t i = 1; i <= size_; ++i)
    printf("%s\t * [%ld]: %ld\n", color, i - 1, buffer_[i]);
  printf("\t}%s\n}", START_DEFINE(RESET, RED));
  LOG_OK
}
