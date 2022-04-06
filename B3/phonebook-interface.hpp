#ifndef PHONEBOOKINTERFACE_HPP
#define PHONEBOOKINTERFACE_HPP

#include <unordered_map>

#include "phonebook.hpp"

namespace details {
  enum Error {
    EMPTY,
    INVALID_STEP,
    INVALID_COMMAND,
    INVALID_BOOKMARK
  };
}

class PhonebookInterface {
public:
  struct steps_t {
    enum Steps {
      FIRST,
      LAST
    };
    enum Flag {
      KEYWORD,
      NUMERIC,
      INVALID
    };
    union {
      Steps steps;
      long n;
    };
    Flag flag;
  };

  enum Position {
    BEFORE,
    AFTER
  };

  PhonebookInterface();
  void add(const Phonebook::note_t& note, std::ostream&);
  void store(const std::string& oldName, const std::string& newName, std::ostream&);
  void insert(const Position& position, const std::string& name, const Phonebook::note_t& note, std::ostream&);
  void deleteNote(const std::string& name, std::ostream&);
  void show(const std::string& name, std::ostream&) const;
  void move(const steps_t& steps, const std::string& name, std::ostream& out);
private:
  Phonebook phonebook_;
  std::unordered_map<std::string, Phonebook::iterator> bookmarks_;

  bool empty() const noexcept;
  void refresh();
};

void printErrorMessage(const details::Error& error, std::ostream& out);

#endif
