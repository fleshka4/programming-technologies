#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <iosfwd>

#include "phonebook-interface.hpp"

class PhonebookInterface;

using Command = std::function<void(PhonebookInterface&, std::ostream&)>;

std::istream& operator>>(std::istream&, Phonebook::note_t&);
std::istream& operator>>(std::istream&, PhonebookInterface::Position&);
std::istream& operator>>(std::istream&, PhonebookInterface::steps_t&);

namespace details {
  Command parseAdd(std::istream& in);
  Command parseDeleteRecord(std::istream& in);
  Command parseInsert(std::istream& in);
  Command parseMove(std::istream& in);
  Command parseShow(std::istream& in);
  Command parseStore(std::istream& in);

  bool containsGarbage(std::istream& in);
}

Command parseCommand(const std::string& in);

namespace details {
  const std::unordered_map<std::string, std::function<Command(std::istream&)>> COMMANDS = {
    {"add", parseAdd},
    {"store", parseStore},
    {"insert", parseInsert},
    {"delete", parseDeleteRecord},
    {"show", parseShow},
    {"move", parseMove}};
}

#endif
