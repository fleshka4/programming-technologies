#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <list>
#include <string>

class Phonebook {
public:
  struct note_t {
    std::string number;
    std::string name;
  };

  using iterator = std::list<note_t>::iterator;
  using const_iterator = std::list<note_t>::const_iterator;

  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  iterator begin() noexcept;
  iterator end() noexcept;

  void push_back(const note_t& note);
  iterator insertBefore(iterator iterator, const note_t& note);
  iterator insertAfter(iterator iterator, const note_t& note);
  iterator erase(iterator iterator);
  bool empty() const noexcept;
private:
  std::list<note_t> phoneBook_;
};


#endif
