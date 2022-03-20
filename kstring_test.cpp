#include "kstring.hpp"
#include <gtest/gtest.h>

template <typename T> class kallocator : public std::allocator<T> {
public:
  typedef size_t size_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  static size_t allocate_size;
  static size_t deallocate_size;

  template <typename _Tp1> struct rebind {
    typedef kallocator<_Tp1> other;
  };

  pointer allocate(size_type n, const void *hint = 0) {
    allocate_size += n*sizeof(T);
    return std::allocator<T>::allocate(n);
  }

  void deallocate(pointer p, size_type n) {
    deallocate_size += n*sizeof(T);
    return std::allocator<T>::deallocate(p, n);
  }

  static void reset_stats() {
    allocate_size = 0;
    deallocate_size = 0;
  }

  kallocator() throw() : std::allocator<T>() {
  }
  kallocator(const kallocator &a) throw() : std::allocator<T>(a) {}
  template <class U>
  kallocator(const kallocator<U> &a) throw() : std::allocator<T>(a) {}
  ~kallocator() throw() {}
};

template<typename T> size_t kallocator<T>::allocate_size = 0;
template<typename T> size_t kallocator<T>::deallocate_size = 0;


// Demonstrate some basic assertions.
TEST(Kstring, Constructors) {

  using kallocator = kallocator<char>;
  ASSERT_EQ(sizeof(k::kstring<kallocator>), 24);

  {
    kallocator::reset_stats();
    k::kstring<kallocator> ss("0123456789012345678901");
    ASSERT_STREQ(ss.c_str(), "0123456789012345678901");
    ASSERT_EQ(ss.length(), 22);
    ASSERT_EQ(ss.capacity(), 23);
  }

  ASSERT_EQ(kallocator::allocate_size, 0);
  ASSERT_EQ(kallocator::deallocate_size, 0);

  {
    kallocator::reset_stats();
    k::kstring<kallocator> ms("012345678901234567890123456789");
    ASSERT_STREQ(ms.c_str(), "012345678901234567890123456789");
    ASSERT_EQ(ms.length(), 30);
    ASSERT_EQ(ms.capacity(), 32);
  }
  ASSERT_EQ(kallocator::allocate_size, 32);
  ASSERT_EQ(kallocator::deallocate_size, 32);

  {
    kallocator::reset_stats();
    std::string long_str(300, 'c');
    k::kstring<kallocator> ls(long_str.c_str());
    ASSERT_STREQ(ls.c_str(), long_str.c_str());
    ASSERT_EQ(ls.length(), 300);
    ASSERT_EQ(ls.capacity(), 512);
  }
  ASSERT_EQ(kallocator::allocate_size, 512);
  ASSERT_EQ(kallocator::deallocate_size, 512);
}
