#include <boost/test/unit_test.hpp>
#include "phonebook.hpp"

BOOST_AUTO_TEST_SUITE(test_phonebook)
struct fixture {
  Phonebook phonebook;
  const Phonebook::note_t note = {"872251296363", "xXBhuYANUGzVcm"};
  const Phonebook::note_t note2 = {"888292862786", "vWJUFtPbEI wyNdNHeaNZ"};
  const Phonebook::note_t note3 = {"316283157688", "rnW zQHfcd\"WSrVJEStpZZGgH\"hYg"};
  const Phonebook::note_t note4 = {"973237822526", "hIID qKxAHob\"L,pTQY,clzGlVmNP"};
  const Phonebook::note_t note5 = {"760376686664", "xGXxsEgbDaM g"};
  const Phonebook::note_t note6 = {"212677136711", "KifspBIwpPaMwvWpPv"};

  fixture()
  {
    phonebook.push_back(note);
    phonebook.push_back(note2);
    phonebook.push_back(note3);
  }
};

BOOST_FIXTURE_TEST_CASE(correct_begin_end, fixture)
{
  BOOST_CHECK_EQUAL(phonebook.begin()->name, note.name);
  BOOST_CHECK_EQUAL(phonebook.begin()->number, note.number);
  BOOST_CHECK_EQUAL(std::prev(phonebook.end())->number, note3.number);
  BOOST_CHECK_EQUAL(std::prev(phonebook.end())->name, note3.name);
}

BOOST_FIXTURE_TEST_CASE(correct_insert, fixture)
{
  phonebook.push_back(note4);
  const auto iter = std::prev(phonebook.end());

  BOOST_CHECK_EQUAL(iter->name, note4.name);
  BOOST_CHECK_EQUAL(iter->number, note4.number);

  phonebook.insertBefore(iter, note5);
  BOOST_CHECK_EQUAL(std::prev(iter)->name, note5.name);
  BOOST_CHECK_EQUAL(std::prev(iter)->number, note5.number);

  phonebook.insertAfter(iter, note6);
  BOOST_CHECK_EQUAL(std::prev(phonebook.end())->name, note6.name);
  BOOST_CHECK_EQUAL(std::prev(phonebook.end())->number, note6.number);
}

BOOST_FIXTURE_TEST_CASE(correct_erase, fixture)
{
  const auto iter = phonebook.erase(phonebook.begin());
  BOOST_CHECK_EQUAL(iter->name, phonebook.begin()->name);
  BOOST_CHECK_EQUAL(iter->number, phonebook.begin()->number);
  BOOST_CHECK_EQUAL(note2.name, phonebook.begin()->name);
  BOOST_CHECK_EQUAL(note2.number, phonebook.begin()->number);
}

BOOST_FIXTURE_TEST_CASE(correct_empty, fixture)
{
  BOOST_CHECK_EQUAL(phonebook.empty(), false);

  Phonebook empty;
  BOOST_CHECK_EQUAL(empty.empty(), true);

  empty.push_back(note4);
  BOOST_CHECK_EQUAL(empty.empty(), false);
  BOOST_CHECK_EQUAL(empty.begin()->name, note4.name);
  BOOST_CHECK_EQUAL(empty.begin()->number, note4.number);
}

BOOST_AUTO_TEST_SUITE_END()
