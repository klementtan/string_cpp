#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <span>
#include <string>
namespace k {

class ref_count {};

/**
 * Memory layout for the different type of strings
 *
 * byte     00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22
 * 23 small:   [value0 value22] [l] medium:  [     pointer         ] [ len ] [
 * cap          ] large:   [     cb_pointer      ] [          len        ] [ cap
 * ]
 *
 */

template <class Alloc> class basic_kstring {

public:
  typedef Alloc allocator_type;
  typedef std::allocator_traits<allocator_type> __alloc_traits;
  typedef typename __alloc_traits::size_type size_type;
  /* typedef typename __alloc_traits::difference_type difference_type; */
  /* typedef typename __alloc_traits::reference reference; */
  /* typedef typename __alloc_traits::const_reference const_reference; */
  typedef typename __alloc_traits::pointer pointer;
  typedef typename __alloc_traits::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  static const size_type npos = -1;

  /* basic_kstring() noexcept( */
  /*     std::is_nothrow_default_constructible<allocator_type>::value); */
  /* explicit basic_kstring(const allocator_type &a); */
  /* basic_kstring(const basic_kstring &str); */
  /* basic_kstring(basic_kstring &&str) noexcept( */
  /*     std::is_nothrow_move_constructible<allocator_type>::value); */
  /* basic_kstring(const basic_kstring &str, size_type pos, */
  /*               const allocator_type &a = allocator_type()); */
  /* basic_kstring(const basic_kstring &str, size_type pos, size_type n, */
  /*               const Alloc &a = Alloc()); */
  /* template <class T> */
  /* basic_kstring(const T &t, size_type pos, size_type n, */
  /*               const Alloc &a = Alloc()); */
  /* template <class T> */
  /* explicit basic_kstring(const T &t, const Alloc &a = Alloc()); */
  basic_kstring(const char *s, const allocator_type &a = allocator_type());
  /* basic_kstring(const char *s, size_type n, */
  /*               const allocator_type &a = allocator_type()); */
  /* basic_kstring(size_type n, char c, */
  /*               const allocator_type &a = allocator_type()); */
  /* template <class InputIterator> */
  /* basic_kstring(InputIterator begin, InputIterator end, */
  /*               const allocator_type &a = allocator_type()); */
  /* basic_kstring(std::initializer_list<char>, const Alloc & = Alloc()); */
  /* basic_kstring(const basic_kstring &, const Alloc &); */
  /* basic_kstring(basic_kstring &&, const Alloc &); */

  ~basic_kstring();

  basic_kstring &operator=(const basic_kstring &str);
  template <class T> basic_kstring &operator=(const T &t); // C++17
  basic_kstring &operator=(basic_kstring &&str) noexcept(
      allocator_type::propagate_on_container_move_assignment::value ||
      allocator_type::is_always_equal::value); // C++17
  basic_kstring &operator=(const char *s);
  basic_kstring &operator=(char c);
  basic_kstring &operator=(std::initializer_list<char>);

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;
  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;

  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  const_reverse_iterator crbegin() const noexcept;
  const_reverse_iterator crend() const noexcept;

  size_type size() const noexcept;
  size_type length() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;

  void resize(size_type n, char c);
  void resize(size_type n);

  void reserve(size_type res_arg = 0);
  void shrink_to_fit();
  void clear() noexcept;
  bool empty() const noexcept;

  /* const_reference operator[](size_type pos) const; */
  /* reference operator[](size_type pos); */

  /* const_reference at(size_type n) const; */
  /* reference at(size_type n); */

  basic_kstring &operator+=(const basic_kstring &str);
  template <class T> basic_kstring &operator+=(const T &t); // C++17
  basic_kstring &operator+=(const char *s);
  basic_kstring &operator+=(char c);
  basic_kstring &operator+=(std::initializer_list<char>);

  basic_kstring &append(const basic_kstring &str);
  template <class T> basic_kstring &append(const T &t); // C++17
  basic_kstring &append(const basic_kstring &str, size_type pos,
                        size_type n = npos); // C++14
  template <class T>
  basic_kstring &append(const T &t, size_type pos, size_type n = npos); // C++17
  basic_kstring &append(const char *s, size_type n);
  basic_kstring &append(const char *s);
  basic_kstring &append(size_type n, char c);
  template <class InputIterator>
  basic_kstring &append(InputIterator first, InputIterator last);
  basic_kstring &append(std::initializer_list<char>);

  void push_back(char c);
  void pop_back();
  /* reference front(); */
  /* const_reference front() const; */
  /* reference back(); */
  /* const_reference back() const; */

  basic_kstring &assign(const basic_kstring &str);
  template <class T> basic_kstring &assign(const T &t); // C++17
  basic_kstring &assign(basic_kstring &&str);
  basic_kstring &assign(const basic_kstring &str, size_type pos,
                        size_type n = npos); // C++14
  template <class T>
  basic_kstring &assign(const T &t, size_type pos, size_type n = npos); // C++17
  basic_kstring &assign(const char *s, size_type n);
  basic_kstring &assign(const char *s);
  basic_kstring &assign(size_type n, char c);
  template <class InputIterator>
  basic_kstring &assign(InputIterator first, InputIterator last);
  basic_kstring &assign(std::initializer_list<char>);

  basic_kstring &insert(size_type pos1, const basic_kstring &str);
  template <class T> basic_kstring &insert(size_type pos1, const T &t);
  basic_kstring &insert(size_type pos1, const basic_kstring &str,
                        size_type pos2, size_type n);
  template <class T>
  basic_kstring &insert(size_type pos1, const T &t, size_type pos2,
                        size_type n); // C++17
  basic_kstring &insert(size_type pos, const char *s,
                        size_type n = npos); // C++14
  basic_kstring &insert(size_type pos, const char *s);
  basic_kstring &insert(size_type pos, size_type n, char c);
  iterator insert(const_iterator p, char c);
  iterator insert(const_iterator p, size_type n, char c);
  template <class InputIterator>
  iterator insert(const_iterator p, InputIterator first, InputIterator last);
  iterator insert(const_iterator p, std::initializer_list<char>);

  basic_kstring &erase(size_type pos = 0, size_type n = npos);
  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);

  basic_kstring &replace(size_type pos1, size_type n1,
                         const basic_kstring &str);
  template <class T>
  basic_kstring &replace(size_type pos1, size_type n1, const T &t); // C++17
  basic_kstring &replace(size_type pos1, size_type n1, const basic_kstring &str,
                         size_type pos2, size_type n2 = npos); // C++14
  template <class T>
  basic_kstring &replace(size_type pos1, size_type n1, const T &t,
                         size_type pos2, size_type n); // C++17
  basic_kstring &replace(size_type pos, size_type n1, const char *s,
                         size_type n2);
  basic_kstring &replace(size_type pos, size_type n1, const char *s);
  basic_kstring &replace(size_type pos, size_type n1, size_type n2, char c);
  basic_kstring &replace(const_iterator i1, const_iterator i2,
                         const basic_kstring &str);
  template <class T>
  basic_kstring &replace(const_iterator i1, const_iterator i2,
                         const T &t); // C++17
  basic_kstring &replace(const_iterator i1, const_iterator i2, const char *s,
                         size_type n);
  basic_kstring &replace(const_iterator i1, const_iterator i2, const char *s);
  basic_kstring &replace(const_iterator i1, const_iterator i2, size_type n,
                         char c);
  template <class InputIterator>
  basic_kstring &replace(const_iterator i1, const_iterator i2, InputIterator j1,
                         InputIterator j2);
  basic_kstring &replace(const_iterator i1, const_iterator i2,
                         std::initializer_list<char>);

  size_type copy(char *s, size_type n, size_type pos = 0) const;
  basic_kstring substr(size_type pos = 0, size_type n = npos) const;

  void swap(basic_kstring &str) noexcept(
      std::allocator_traits<
          allocator_type>::propagate_on_container_swap::value ||
      std::allocator_traits<allocator_type>::is_always_equal::value); // C++17

  const char *c_str() const noexcept;
  const char *data() const noexcept;
  char *data() noexcept; // C++17

  allocator_type get_allocator() const noexcept;

  size_type find(const basic_kstring &str, size_type pos = 0) const noexcept;
  template <class T>
  size_type find(const T &t, size_type pos = 0) const; // C++17
  size_type find(const char *s, size_type pos, size_type n) const noexcept;
  size_type find(const char *s, size_type pos = 0) const noexcept;
  size_type find(char c, size_type pos = 0) const noexcept;

  size_type rfind(const basic_kstring &str,
                  size_type pos = npos) const noexcept;
  template <class T>
  size_type rfind(const T &t, size_type pos = npos) const; // C++17
  size_type rfind(const char *s, size_type pos, size_type n) const noexcept;
  size_type rfind(const char *s, size_type pos = npos) const noexcept;
  size_type rfind(char c, size_type pos = npos) const noexcept;

  size_type find_first_of(const basic_kstring &str,
                          size_type pos = 0) const noexcept;
  template <class T>
  size_type find_first_of(const T &t, size_type pos = 0) const; // C++17
  size_type find_first_of(const char *s, size_type pos,
                          size_type n) const noexcept;
  size_type find_first_of(const char *s, size_type pos = 0) const noexcept;
  size_type find_first_of(char c, size_type pos = 0) const noexcept;

  size_type find_last_of(const basic_kstring &str,
                         size_type pos = npos) const noexcept;
  template <class T>
  size_type find_last_of(const T &t,
                         size_type pos = npos) const noexcept; // C++17
  size_type find_last_of(const char *s, size_type pos,
                         size_type n) const noexcept;
  size_type find_last_of(const char *s, size_type pos = npos) const noexcept;
  size_type find_last_of(char c, size_type pos = npos) const noexcept;

  size_type find_first_not_of(const basic_kstring &str,
                              size_type pos = 0) const noexcept;
  template <class T>
  size_type find_first_not_of(const T &t, size_type pos = 0) const; // C++17
  size_type find_first_not_of(const char *s, size_type pos,
                              size_type n) const noexcept;
  size_type find_first_not_of(const char *s, size_type pos = 0) const noexcept;
  size_type find_first_not_of(char c, size_type pos = 0) const noexcept;

  size_type find_last_not_of(const basic_kstring &str,
                             size_type pos = npos) const noexcept;
  template <class T>
  size_type find_last_not_of(const T &t, size_type pos = npos) const; // C++17
  size_type find_last_not_of(const char *s, size_type pos,
                             size_type n) const noexcept;
  size_type find_last_not_of(const char *s,
                             size_type pos = npos) const noexcept;
  size_type find_last_not_of(char c, size_type pos = npos) const noexcept;

  int compare(const basic_kstring &str) const noexcept;
  template <class T> int compare(const T &t) const noexcept; // C++17
  int compare(size_type pos1, size_type n1, const basic_kstring &str) const;
  template <class T>
  int compare(size_type pos1, size_type n1, const T &t) const; // C++17
  int compare(size_type pos1, size_type n1, const basic_kstring &str,
              size_type pos2, size_type n2 = npos) const; // C++14
  template <class T>
  int compare(size_type pos1, size_type n1, const T &t, size_type pos2,
              size_type n2 = npos) const; // C++17
  int compare(const char *s) const noexcept;
  int compare(size_type pos1, size_type n1, const char *s) const;
  int compare(size_type pos1, size_type n1, const char *s, size_type n2) const;

  bool starts_with(std::basic_string_view<char> sv) const noexcept; // C++2a
  bool starts_with(char c) const noexcept;                          // C++2a
  bool starts_with(const char *s) const;                            // C++2a
  bool ends_with(std::basic_string_view<char> sv) const noexcept;   // C++2a
  bool ends_with(char c) const noexcept;                            // C++2a
  bool ends_with(const char *s) const;                              // C++2a

  bool __invariants() const;

private:
  static constexpr size_type __kstring_max_size =
      sizeof(size_type) * 2 + sizeof(pointer);
  static constexpr size_type __max_short_size = 23;
  static constexpr size_type __max_mid_size = 255;

  enum class Category { kShort = 0, kMid, kLong };

  class ControlBlock {
    pointer m_ptr;
    std::atomic<size_type> m_count;
    size_type m_cap;

  public:
    ControlBlock(pointer p, size_type len);

    ControlBlock(const ControlBlock &) = delete;
    ControlBlock &operator=(const ControlBlock &) = delete;
    ControlBlock(ControlBlock &&) = delete;
    ControlBlock &operator=(ControlBlock &&p) = delete;
    ~ControlBlock();

    void acquire();
    void release();
    pointer get();
  };

  struct Short {
    char m_data[(__kstring_max_size - sizeof(uint8_t)) / sizeof(char)];
    uint8_t m_len;
  };
  struct ShortTag {};
  static constexpr ShortTag short_tag{};

  struct Mid {
    pointer m_ptr;
    size_type m_len;
    size_type m_cap;
  };
  struct MidTag {};
  static constexpr MidTag mid_tag{};

  struct Long {
    // TODO: use allocator traits instead
    ControlBlock* m_cbptr;
    size_type m_len;
    size_type m_cap;
  };
  struct LongTag {};
  static constexpr LongTag long_tag{};

  static_assert(sizeof(Short) <= __kstring_max_size,
                "Short struct is larger than max size");
  static_assert(sizeof(Mid) <= __kstring_max_size,
                "Mid struct is larger than max size");
  static_assert(sizeof(Long) <= __kstring_max_size,
                "Long struct is larger than max size");

  union Members {
    Short m_short;
    Mid m_mid;
    Long m_long;
  };
  Members m_members;

  Category category() const;
  static Category get_category(size_type cap);

  bool msb() const;

  uint8_t &msbyte();
  uint8_t cmsbyte() const;
  void set_capacity(size_type cap);
  static size_type gen_capacity(size_type len);
  void set_length(size_type len, Category cat);
  void print_mem() const;

  void construct_basic_kstring(const char *s, size_type len,
                               const allocator_type &a, ShortTag);
  void construct_basic_kstring(const char *s, size_type len, size_type cap,
                               const allocator_type &a, MidTag);
  void construct_basic_kstring(const char *s, size_type len, size_type cap,
                               const allocator_type &a, LongTag);
};

template <class Alloc> basic_kstring<Alloc>::~basic_kstring() {
  auto cat = category();
  if (cat == Category::kMid) {
    allocator_type().deallocate(m_members.m_mid.m_ptr, m_members.m_mid.m_cap);
  } else if (cat == Category::kLong) {
    m_members.m_long.m_cbptr->release();
  }

}

template <class Alloc>
basic_kstring<Alloc>::basic_kstring(const char *s, const allocator_type &a) {
  const auto len = std::strlen(s);
  const auto cap = gen_capacity(len + 1);
  const auto cat = get_category(cap);
  switch (cat) {
  case Category::kShort:
    construct_basic_kstring(s, len, a, short_tag);
    break;
  case Category::kMid:
    construct_basic_kstring(s, len, cap, a, mid_tag);
    break;
  case Category::kLong:
    construct_basic_kstring(s, len, cap, a, long_tag);
    break;
  }
}

template <class Alloc>
void basic_kstring<Alloc>::construct_basic_kstring(const char *s, size_type len,
                                                   const allocator_type &a,
                                                   ShortTag) {
  assert(len < __max_short_size);
  for (size_type i = 0; i < len; i++) {
    new (m_members.m_short.m_data + i) char{s[i]};
  }
  new (m_members.m_short.m_data + len) char{'\0'};
  set_length(len, Category::kShort);
}

template <class Alloc>
void basic_kstring<Alloc>::construct_basic_kstring(const char *s, size_type len,
                                                   size_type cap,
                                                   const allocator_type &a,
                                                   MidTag) {
  assert(len < cap);
  m_members.m_mid.m_ptr = allocator_type().allocate(cap);

  // use placement new to construct each character at the allocated memory
  for (size_type i = 0; i < len; i++) {
    new (m_members.m_mid.m_ptr + i) char{s[i]};
  }
  new (m_members.m_mid.m_ptr + len) char{'\0'};

  set_length(len, Category::kMid);
  set_capacity(cap);
}

template <class Alloc>
void basic_kstring<Alloc>::construct_basic_kstring(const char *s, size_type len,
                                                   size_type cap,
                                                   const allocator_type &a,
                                                   LongTag) {
  assert(len < cap);
  auto ptr = allocator_type().allocate(cap);
  for (size_type i = 0; i < len; i++) {
    new (ptr + i) char{s[i]};
  }
  new (ptr + len) char{'\0'};
  set_length(len, Category::kLong);
  set_capacity(cap);
  m_members.m_long.m_cbptr = new ControlBlock(ptr, cap);
}

template <class Alloc> uint8_t &basic_kstring<Alloc>::msbyte() {
  return *reinterpret_cast<uint8_t *>(this + 23);
}

template <class Alloc> void basic_kstring<Alloc>::print_mem() const {
  uint8_t mem[24];
  memcpy(mem, this, 24);
  std::cerr << "Mem: ";
  for (int i = 0; i < 24; i++)
    std::cerr << std::hex << uint32_t{mem[i]} << " ";
  std::cerr << std::endl;
}

template <class Alloc> uint8_t basic_kstring<Alloc>::cmsbyte() const {
  return reinterpret_cast<const uint8_t *>(this)[23];
}

template <class Alloc>
typename basic_kstring<Alloc>::size_type
basic_kstring<Alloc>::gen_capacity(size_type len) {
  if (len <= __max_short_size)
    return len;
  size_type ret{1};
  while (ret < len)
    ret = ret << 1;
  return ret;
}

template <class Alloc> bool basic_kstring<Alloc>::msb() const {
  return (cmsbyte() & (static_cast<uint8_t>(1 << 7)));
}

template <class Alloc>
typename basic_kstring<Alloc>::size_type
basic_kstring<Alloc>::length() const noexcept {
  switch (category()) {
  case Category::kShort:
    return m_members.m_short.m_len ^ (1 << 7);
  case Category::kMid:
    return m_members.m_mid.m_len;
  case Category::kLong:
    return m_members.m_long.m_len;
  }
}

template <class Alloc>
void basic_kstring<Alloc>::set_length(basic_kstring<Alloc>::size_type length,
                                      Category cat) {
  if (cat == Category::kShort) {
    m_members.m_short.m_len = static_cast<uint8_t>(
        static_cast<uint8_t>(length) | static_cast<uint8_t>(1 << 7));
  } else if (cat == Category::kMid) {
    m_members.m_mid.m_len = length;
  } else {
    m_members.m_long.m_len = length;
  }
}

template <class Alloc>
void basic_kstring<Alloc>::set_capacity(
    basic_kstring<Alloc>::size_type capacity) {

  const auto cat = get_category(capacity);
  if (cat == Category::kShort) {
    assert(capacity == __max_short_size);
  } else if (cat == Category::kMid) {
    m_members.m_mid.m_cap = capacity;
  } else {
    m_members.m_long.m_cap = capacity;
  }
}

template <class Alloc>
typename basic_kstring<Alloc>::size_type
basic_kstring<Alloc>::capacity() const noexcept {
  if (msb()) {
    return __max_short_size;
  } else {
    auto cap_byte_ptr = reinterpret_cast<const std::byte *>(this) + 16;
    std::shared_ptr<char> s;
    return *reinterpret_cast<const size_type *>(cap_byte_ptr);
  }
}

template <class Alloc>
typename basic_kstring<Alloc>::Category basic_kstring<Alloc>::category() const {
  if (msb()) {
    return Category::kShort;
  } else {
    const auto cap = capacity();
    if (cap > __max_mid_size) {
      return Category::kLong;
    } else {
      return Category::kMid;
    }
  }
}

template <class Alloc>
typename basic_kstring<Alloc>::Category
basic_kstring<Alloc>::get_category(size_type cap) {
  if (cap <= __max_short_size) {
    return Category::kShort;
  } else if (cap <= __max_mid_size) {
    return Category::kMid;
  } else {
    return Category::kLong;
  }
}

template <typename Alloc = std::allocator<char>>
using kstring = basic_kstring<Alloc>;
} // namespace k

namespace std {
template <class Alloc>
void swap(typename k::basic_kstring<Alloc>::ControlBlock &a,
          typename k::basic_kstring<Alloc>::ControlBlock &b) {
  std::swap(a.m_ptr, b.m_ptr);
  std::swap(a.m_count, b.m_count);
}
} // namespace std

template <class Alloc>
k::basic_kstring<Alloc>::ControlBlock::ControlBlock(pointer p, size_type len)
    : m_ptr{p}, m_count{0}, m_cap{len} {
  acquire();
}

template <class Alloc> k::basic_kstring<Alloc>::ControlBlock::~ControlBlock() {
  assert(m_count == 0);
  assert(m_ptr);
  allocator_type().deallocate(m_ptr, m_cap);
}

template <class Alloc> void k::basic_kstring<Alloc>::ControlBlock::acquire() {
  m_count++;
}

template <class Alloc>
typename k::basic_kstring<Alloc>::pointer
k::basic_kstring<Alloc>::ControlBlock::get() {
  return m_ptr;
}

template <class Alloc> void k::basic_kstring<Alloc>::ControlBlock::release() {
  m_count--;
  if (m_count == 0) {
    delete this;
  }
}
