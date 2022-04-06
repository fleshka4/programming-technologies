#include "phonebook.hpp"

void Phonebook::push_back(const Phonebook::note_t& note)
{
  phoneBook_.push_back(note);
}

Phonebook::iterator Phonebook::insertBefore(iterator iterator, const Phonebook::note_t& note)
{
  return std::next(phoneBook_.insert(iterator, note));
}

Phonebook::iterator Phonebook::insertAfter(iterator iterator, const Phonebook::note_t& note)
{
  return std::prev(phoneBook_.insert(std::next(iterator), note));
}

Phonebook::iterator Phonebook::erase(iterator iterator)
{
  return phoneBook_.erase(iterator);
}

bool Phonebook::empty() const noexcept
{
  return phoneBook_.empty();
}

Phonebook::const_iterator Phonebook::begin() const noexcept
{
  return phoneBook_.begin();
}

Phonebook::const_iterator Phonebook::end() const noexcept
{
  return phoneBook_.end();
}

Phonebook::iterator Phonebook::begin() noexcept
{
  return phoneBook_.begin();
}

Phonebook::iterator Phonebook::end() noexcept
{
  return phoneBook_.end();
}
