#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ControlBlock {
private:
  int m_coutner;
  char* m_data;
public:
  static int destruction_count;
  ControlBlock(char* data) : m_data(data), m_coutner(1) {}
  ControlBlock(const ControlBlock& other) = delete;
  ControlBlock& operator=(const ControlBlock& other) = delete;

  void increment() {m_coutner++;}
  void decrement() {
    assert(m_coutner > 0);
    m_coutner--;
  }

  int count() {return m_coutner;}

  char* get() {return m_data;}
  const char* get() const {return m_data;}

  ~ControlBlock() {
    assert(m_coutner == 0);
    destruction_count++;
    delete[] m_data;
  }

};
int ControlBlock::destruction_count = 0;

class my_string {
private:
  void* m_ptr;
  std::size_t m_len;
  std::size_t m_cap;
public:
  my_string(const char* s) {
    std::size_t len = std::strlen(s);
    if (len < 23) {
      char* ptr = reinterpret_cast<char*>(&m_ptr);
      memcpy(ptr, s, len);
      ptr[len] = '\0';
      uint8_t& l_byte = last_writable_byte();
      l_byte = static_cast<uint8_t>(len) | (1 << 7);
    } else {
      m_len = len;
      m_cap = len + 1;
      char* data = new char[m_cap];
      memcpy(data, s, len);
      data[len] = '\0';
      if (is_cow()) {
        m_ptr = new ControlBlock(data);
      } else {
        m_ptr = data;
      }
    }
  }

  my_string(const my_string& other) : m_ptr(nullptr), m_len(other.m_len), m_cap(other.m_cap) { 
    if (other.is_sso()) {
      m_ptr = other.m_ptr;
    } else if (is_cow()) {
      m_ptr = other.m_ptr;
      ControlBlock* cb = static_cast<ControlBlock*>(m_ptr);
      cb->increment();
    } else {
      char* data = new char[other.capacity()];
      memcpy(data, static_cast<char*>(other.m_ptr), other.length());
      data[other.length()] = '\0';
      m_ptr = data;
    }
  }
  my_string& operator=(const my_string& other) {
    my_string tmp(other);
    swap(tmp);
    return *this;
  }

  my_string(my_string&& other) : m_len(other.m_len), m_cap(other.m_cap), m_ptr(other.m_ptr) {
    // Do not change counter for move ctor 
    other.m_ptr = nullptr;
  }

  my_string& operator=(my_string&& other) {
    // Let other's destructor deal with cleaning up m_ptr.
    // Swap all data members so that other will know what type of resource (char*/ControlBlock) m_ptr is
    //
    // If normal string, it will deallocate char*
    // If cow string, it will decrement control block and deallocate string and control
    //    if count is 0
    swap(other);
    return *this;
  }

  ~my_string() {
    if (is_normal()) {
      assert(!is_sso());
      delete[] static_cast<char*>(m_ptr);
    }
    else if (is_cow()) {
      // m_ptr = nullptr when the object has been previously moved and we do not need to clean
      // up control block
      if (m_ptr == nullptr) return;
      // Decrement reference count
      ControlBlock* cb = static_cast<ControlBlock*>(m_ptr);
      cb->decrement();
      // Should delete control block if it is the last reference
      if (cb->count() == 0) delete cb;
    }
  }

  void swap(my_string& other) {
    std::swap(m_ptr, other.m_ptr);
    std::swap(m_len, other.m_len);
    std::swap(m_cap, other.m_cap);
  }

  char* c_str() {
    if (is_sso()) {
      return reinterpret_cast<char*>(this);
    } else if (is_cow()) {
      cow_cpy();
      return (static_cast<ControlBlock*>(m_ptr))->get();
    } else {
      return static_cast<char*>(m_ptr);
    }
  }
  const char* c_str() const {
    if (is_sso()) {
      return reinterpret_cast<const char*>(this);
    } else if (is_cow()) {
      return (static_cast<const ControlBlock*>(m_ptr))->get();
    } else {
      return static_cast<const char*>(m_ptr);
    }
  }

  void cow_cpy() {
    assert(is_cow());
    ControlBlock* old_cb = static_cast<ControlBlock*>(m_ptr);

    // Do not copy if the current string is the last reference
    if (old_cb->count() == 1) return;

    // Copy string
    char* data = new char[capacity()];
    memcpy(data, old_cb->get() , length());
    data[length()] = '\0';

    // Create new control block
    ControlBlock* new_cb = new ControlBlock(data);
    m_ptr = new_cb;

    // Clean up old control block
    old_cb->decrement();
}

  size_t length() const {
    if (is_sso()) {

      uint8_t len_mask = -1;
      len_mask ^= (1 << 7);
      std::size_t len = static_cast<std::size_t>(len_mask & last_byte());
      return len;
    } else {
      return m_len;
    }
  }
  size_t capacity() const {
    if (is_sso()) {
      return length();
    } else {
      return m_cap;
    }
  }

  uint8_t& last_writable_byte() {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(this);
    return ptr[23];
  }
  uint8_t last_byte() const {
    const uint8_t* ptr = reinterpret_cast<const uint8_t*>(this);
    return ptr[23];
  }

int cb_count() const {
  return static_cast<ControlBlock*>(m_ptr)->count();
}

  bool is_sso() const {
    return last_byte() & (1 << 7);
  }

  bool is_cow() const {
    return length() > 55;
  }

  bool is_normal() const {
    return !(is_sso() || is_cow());
  }

};

/********** Main()  function **********/
int main()
{
  printf("Initializing Strings\n");
  my_string short_str("0123456789012345678901");
  my_string long_str("012345678901234567890123456789");

  // assert sso
  printf("Testing sso\n");
  assert(short_str.is_sso());
  assert(short_str.c_str()[22] == '\0');
  assert(short_str.length() == 22);
  assert(std::string(short_str.c_str()) == "0123456789012345678901");

  // assert long string
  printf("Testing long\n");
  assert(long_str.is_sso() == false);
  assert(long_str.length() == 30);
  assert(std::string(long_str.c_str()) == "012345678901234567890123456789");

  // assert sso copy ctor
  printf("sso copy ctor\n");
  my_string short_cpyctor(short_str);
  assert(short_cpyctor.is_sso());
  assert(short_cpyctor.c_str()[22] == '\0');
  assert(short_cpyctor.length() == 22);
  assert(std::string(short_cpyctor.c_str()) == "0123456789012345678901");
  
  // assert long string copy ctor
  printf("long copy ctor\n");
  my_string long_cpyctor(long_str);
  assert(long_cpyctor.is_sso() == false);
  assert(long_cpyctor.length() == 30);
  assert(std::string(long_cpyctor.c_str()) == "012345678901234567890123456789");

  // assert sso copy assign 
  printf("sso copy assign\n");
  my_string short_cpyassign("");
  short_cpyassign = short_str;
  assert(short_cpyassign.is_sso());
  assert(short_cpyassign.c_str()[22] == '\0');
  assert(short_cpyassign.length() == 22);
  assert(std::string(short_cpyassign.c_str()) == "0123456789012345678901");
  
  // assert long string copy assign 
  printf("sso long assign\n");
  my_string long_cpyassign("");
  long_cpyassign = long_str;
  assert(long_cpyassign.is_sso() == false);
  assert(long_cpyassign.length() == 30);
  assert(std::string(long_cpyassign.c_str()) == "012345678901234567890123456789");

  // cow
  {
    printf("cow\n");
    // #ControlBlock = 1
    my_string main_cow_string("012456789012456789012456789012456789012456789012456789012456789012456789");
    const char* main_c_str = static_cast<const my_string>(main_cow_string).c_str();
    assert(main_cow_string.is_cow());
    assert(std::string(main_c_str) == "012456789012456789012456789012456789012456789012456789012456789012456789");
    assert(main_cow_string.cb_count() == 1);

    my_string cpy_cow_string(main_cow_string);
    assert(main_cow_string.cb_count() == 2);
    
    // Should point to same string on heap when `const char*` is get
    assert(main_c_str == static_cast<const my_string>(cpy_cow_string).c_str());

    // #ControlBlock = 2
    char* writable_cpy = cpy_cow_string.c_str();
    assert(main_cow_string.cb_count() == 1);
    assert(cpy_cow_string.cb_count() == 1);

    // Getting a writable c string should not change the string
    assert(std::string(writable_cpy) == std::string(static_cast<const my_string>(main_cow_string).c_str()));

    // Getting a writable c string should copy the underlying string on heap
    assert(writable_cpy != main_c_str);

    my_string move_ctor(std::move(cpy_cow_string));
    assert(move_ctor.cb_count() == 1);
    assert(static_cast<const my_string>(move_ctor).c_str() == writable_cpy);

    my_string move_assign("");
    move_assign = std::move(main_cow_string);
    assert(move_assign.cb_count() == 1);
    assert(static_cast<const my_string>(move_assign).c_str() == main_c_str);
  }
  // Check that all control block are destroyed
  assert(ControlBlock::destruction_count == 2);

	return 0;
}
/********  Main() Ends Here *************/
