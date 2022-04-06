#include "parser.hpp"

#include <functional>
#include <iostream>
#include <sstream>

std::istream& operator>>(std::istream& in, Phonebook::note_t& note)
{
  std::string number;
  in >> number;
  for (char& i : number) {
    if (!isdigit(i)) {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  std::string name;
  char temp;
  in >> temp;

  if (temp != '\"') {
    in.setstate(std::ios::failbit);
    return in;
  }

  bool isShielded = false;
  while ((in) && (in.peek() != '\r') && (in.peek() != '\n')) {
    temp = in.get();
    if (temp == '\\') {
      if (isShielded) {
        name.pop_back();
      }
      isShielded = !isShielded;
    }
    if (temp == '\"') {
      if (isShielded) {
        name.pop_back();
        isShielded = false;
        if ((in) && (in.peek() != '\r') && (in.peek() != '\n')) {
          name.push_back(temp);
        }
        continue;
      }
      break;
    }

    name.push_back(temp);
  }

  if ((temp != '\"') || (name.empty())) {
    in.setstate(std::ios::failbit);
    return in;
  }

  note = {number, name};
  return in;
}

std::istream& operator>>(std::istream& in, PhonebookInterface::Position& position)
{
  std::string pos;
  in >> pos;

  if (pos == "before") {
    position = PhonebookInterface::BEFORE;
  } else if (pos == "after") {
    position = PhonebookInterface::AFTER;
  } else {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& operator>>(std::istream& in, PhonebookInterface::steps_t& steps)
{
  std::string string;
  in >> string;

  if (string.empty()) {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (string == "first") {
    steps.steps = PhonebookInterface::steps_t::FIRST;
    steps.flag = PhonebookInterface::steps_t::KEYWORD;
  } else if (string == "last") {
    steps.steps = PhonebookInterface::steps_t::LAST;
    steps.flag = PhonebookInterface::steps_t::KEYWORD;
  } else {
    std::istringstream temp(string);
    temp >> steps.n;
    if (temp.fail()) {
      in.setstate(std::ios::failbit);
      steps.flag = PhonebookInterface::steps_t::INVALID;
      return in;
    }
    steps.flag = PhonebookInterface::steps_t::NUMERIC;
  }

  return in;
}

Command details::parseAdd(std::istream& in)
{
  Phonebook::note_t note;
  in >> note;

  if (!in || containsGarbage(in)) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  return std::bind(&PhonebookInterface::add, std::placeholders::_1, note, std::placeholders::_2);
}

Command details::parseStore(std::istream& in)
{
  std::string oldName, newName;
  in >> oldName >> newName;

  if (!in || containsGarbage(in)) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  return std::bind(&PhonebookInterface::store, std::placeholders::_1, oldName, newName, std::placeholders::_2);
}

Command details::parseInsert(std::istream& in)
{
  PhonebookInterface::Position position;
  in >> position;

  if (!in) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  std::string name;
  in >> name;

  if (!in) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  Phonebook::note_t note;
  in >> note;

  if (!in || containsGarbage(in)) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  return std::bind(&PhonebookInterface::insert, std::placeholders::_1, position, name, note, std::placeholders::_2);
}

Command details::parseDeleteRecord(std::istream& in)
{
  std::string name;
  in >> name;

  if (!in || containsGarbage(in)) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  return std::bind(&PhonebookInterface::deleteNote, std::placeholders::_1, name, std::placeholders::_2);
}

Command details::parseShow(std::istream& in)
{
  std::string name;
  in >> name;

  if (!in || containsGarbage(in)) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  return std::bind(&PhonebookInterface::show, std::placeholders::_1, name, std::placeholders::_2);
}

Command details::parseMove(std::istream& in)
{
  std::string name;
  in >> name;

  if (!in) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  PhonebookInterface::steps_t steps{};
  in >> steps;

  if (!in) {
    return std::bind(&printErrorMessage, details::INVALID_STEP, std::placeholders::_2);
  }

  if (containsGarbage(in)) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  return std::bind(&PhonebookInterface::move, std::placeholders::_1, steps, name, std::placeholders::_2);
}

bool details::containsGarbage(std::istream& in)
{
  std::string garbage;
  while (isblank(in.peek())) {
    in.get();
  }
  std::getline(in, garbage);
  return !(garbage == "\r") && !garbage.empty();
}

Command parseCommand(const std::string& in)
{
  std::istringstream stream(in);
  std::string cmd;
  stream >> cmd;

  if (details::COMMANDS.find(cmd) == details::COMMANDS.end()) {
    return std::bind(&printErrorMessage, details::INVALID_COMMAND, std::placeholders::_2);
  }

  const auto function = details::COMMANDS.at(cmd);
  return function(stream);
}
