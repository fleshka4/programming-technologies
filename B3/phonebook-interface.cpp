#include "phonebook-interface.hpp"

#include <algorithm>
#include <ostream>

PhonebookInterface::PhonebookInterface():
  bookmarks_({{"current", phonebook_.begin()}})
{}

void PhonebookInterface::add(const Phonebook::note_t& note, std::ostream&)
{
  if (phonebook_.empty()) {
    phonebook_.push_back(note);
    refresh();
    return;
  }
  phonebook_.push_back(note);
}

void PhonebookInterface::store(const std::string& oldName, const std::string& newName, std::ostream& out)
{
  if (bookmarks_.find(oldName) != bookmarks_.end()) {
    bookmarks_.insert({newName, bookmarks_.at(oldName)});
  } else {
    printErrorMessage(details::INVALID_BOOKMARK, out);
  }
}

void PhonebookInterface::insert(const Position& position, const std::string& name,
    const Phonebook::note_t& note, std::ostream& out)
{
  if (bookmarks_.find(name) == bookmarks_.end()) {
    printErrorMessage(details::INVALID_BOOKMARK, out);
    return;
  }

  const bool isEmpty = phonebook_.empty();
  if (position == BEFORE) {
    bookmarks_[name] = phonebook_.insertBefore(bookmarks_[name], note);
  } else if (position == AFTER) {
    bookmarks_[name] = phonebook_.insertAfter(bookmarks_[name], note);
  }
  if (isEmpty) {
    phonebook_.push_back(note);
    refresh();
  }
}

void PhonebookInterface::deleteNote(const std::string& name, std::ostream& out)
{
  if (bookmarks_.find(name) == bookmarks_.end()) {
    printErrorMessage(details::INVALID_BOOKMARK, out);
    return;
  }
  if (phonebook_.empty()) {
    printErrorMessage(details::EMPTY, out);
    return;
  }

  const auto deleted = bookmarks_[name];
  for (auto& bookmark : bookmarks_) {
    if (deleted == bookmark.second) {
      if ((std::next(bookmark.second) != phonebook_.end()) || (bookmark.second == phonebook_.begin())) {
        ++bookmark.second;
      } else {
        --bookmark.second;
      }
    }
  }

  phonebook_.erase(deleted);
}

void PhonebookInterface::show(const std::string& name, std::ostream& out) const
{
  if (bookmarks_.find(name) == bookmarks_.end()) {
    printErrorMessage(details::INVALID_BOOKMARK, out);
  } else if (empty()) {
    printErrorMessage(details::EMPTY, out);
  } else {
    out << bookmarks_.at(name)->number << ' ' << bookmarks_.at(name)->name << '\n';
  }
}

void PhonebookInterface::move(const steps_t& steps, const std::string& name, std::ostream& out)
{
  if (empty()) {
    printErrorMessage(details::EMPTY, out);
    return;
  }
  if (steps.flag == steps_t::INVALID) {
    printErrorMessage(details::INVALID_STEP, out);
    return;
  }
  const auto bookmark = bookmarks_.find(name);
  if (bookmark == bookmarks_.end()) {
    printErrorMessage(details::INVALID_BOOKMARK, out);
    return;
  }

  if (steps.flag == steps_t::NUMERIC) {
    auto num = steps.n;

    if (steps.n > 0) {
      num = std::min(steps.n, std::distance(bookmark->second, phonebook_.end()) - 1);
    } else {
      num = std::max(steps.n, -std::distance(phonebook_.begin(), bookmark->second));
    }

    std::advance(bookmarks_[name], num);
  } else if (steps.steps == steps_t::FIRST) {
    bookmarks_[name] = phonebook_.begin();
  } else {
    bookmarks_[name] = std::prev(phonebook_.end());
  }
}

bool PhonebookInterface::empty() const noexcept
{
  return phonebook_.empty();
}

void PhonebookInterface::refresh()
{
  for (auto& bookmark : bookmarks_) {
    bookmark.second = phonebook_.begin();
  }
}

void printErrorMessage(const details::Error& error, std::ostream& out)
{
  switch (error) {
    case details::EMPTY:
      out << "<EMPTY>";
      break;
    case details::INVALID_STEP:
      out << "<INVALID STEP>";
      break;
    case details::INVALID_COMMAND:
      out << "<INVALID COMMAND>";
      break;
    case details::INVALID_BOOKMARK:
      out << "<INVALID BOOKMARK>";
      break;
  }
  out << '\n';
}
