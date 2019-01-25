#include <iostream>
#include "ProtectedStack.h"

int main() {
  ProtectedStack<int> st;
  st.Push(1);
  //st.ERROR = ERROR_TYPE::BROKEN_CANARY;
//  st.ERROR = ERROR_TYPE::BROKEN_CHECKSUM;
  st.Push(2);st.Push(2);st.Push(2);st.Push(2);st.Push(2);st.Push(2);
  *((unsigned*)&st + 8) = 0xAAAA1111;
  std::cout << st.IsOk() << std::endl;
  st.Dump();
  return 0;
}