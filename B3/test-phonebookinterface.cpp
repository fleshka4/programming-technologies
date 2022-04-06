#include <iostream>
#include <boost/test/unit_test.hpp>
#include "phonebook-interface.hpp"

BOOST_AUTO_TEST_SUITE(test_phonebookinterface)

struct fixture {
  PhonebookInterface phonebookInterface;
  const Phonebook::note_t note = {"872251296363", "xXBhuYANUGzVcm"};
  const Phonebook::note_t note2 = {"888292862786", "vWJUFtPbEI wyNdNHeaNZ"};
  const Phonebook::note_t note3 = {"316283157688", "rnW zQHfcd\"WSrVJEStpZZGgH\"hYg"};
  const Phonebook::note_t note4 = {"973237822526", "hIID qKxAHob\"L,pTQY,clzGlVmNP"};
  const Phonebook::note_t note5 = {"760376686664", "xGXxsEgbDaM g"};
  const Phonebook::note_t note6 = {"212677136711", "KifspBIwpPaMwvWpPv"};
  std::ostringstream out;
  std::ostringstream out2;

  fixture()
  {
    phonebookInterface.add(note, out);
    phonebookInterface.add(note2, out);
    phonebookInterface.add(note3, out);
  }
};

BOOST_FIXTURE_TEST_CASE(correct_add_empty, fixture)
{
  PhonebookInterface empty;
  empty.add(note, out);

  empty.show("current", out);
  const std::string expected = note.number + ' ' + note.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(correct_store, fixture)
{
  const std::string newName = "wCiwqVEBj4kwoBpAt5837";
  phonebookInterface.store("current", newName, out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show(newName, out);
  const std::string expected = note.number + ' ' + note.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(correct_insert, fixture)
{
  phonebookInterface.insert(PhonebookInterface::BEFORE, "current", note4, out);
  BOOST_CHECK_EQUAL(out.str(), "");

  PhonebookInterface::steps_t steps{};
  steps.n = -1;
  steps.flag = PhonebookInterface::steps_t::NUMERIC;
  phonebookInterface.move(steps, "current", out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("current", out);
  const std::string expected = note4.number + ' ' + note4.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);

  phonebookInterface.insert(PhonebookInterface::AFTER, "current", note5, out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  steps.n = 1;
  phonebookInterface.move(steps, "current", out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  phonebookInterface.show("current", out2);
  const std::string expected2 = note5.number + ' ' + note5.name + '\n';
  BOOST_CHECK_EQUAL(out2.str(), expected2);
}

BOOST_FIXTURE_TEST_CASE(correct_move_with_keywords, fixture)
{
  PhonebookInterface::steps_t steps{};
  steps.steps = PhonebookInterface::steps_t::LAST;
  phonebookInterface.move(steps, "current", out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("current", out);
  std::string expected = note3.number + ' ' + note3.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);

  steps.steps = PhonebookInterface::steps_t::FIRST;
  phonebookInterface.move(steps, "current", out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  phonebookInterface.show("current", out2);
  expected = note.number + ' ' + note.name + '\n';
  BOOST_CHECK_EQUAL(out2.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(correct_move_with_numeric_steps, fixture)
{
  phonebookInterface.add(note4, out);
  phonebookInterface.add(note5, out);
  phonebookInterface.add(note6, out);
  PhonebookInterface::steps_t steps{};
  steps.n = 5;
  steps.flag = PhonebookInterface::steps_t::NUMERIC;
  phonebookInterface.move(steps, "current", out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("current", out);
  std::string expected = note6.number + ' ' + note6.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);

  steps.n = -2;
  phonebookInterface.move(steps, "current", out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  phonebookInterface.show("current", out2);
  expected = note4.number + ' ' + note4.name + '\n';
  BOOST_CHECK_EQUAL(out2.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(correct_delete, fixture)
{
  phonebookInterface.deleteNote("current", out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("current", out);
  std::string expected = note2.number + ' ' + note2.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(invalid_store, fixture)
{
  phonebookInterface.store("wCiwqVEBj4kwoBpAt5837", "new", out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID BOOKMARK>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_insert, fixture)
{
  phonebookInterface.insert(PhonebookInterface::BEFORE, "wCiwqVEBj4kwoBpAt5837", note5, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID BOOKMARK>\n");

  phonebookInterface.insert(PhonebookInterface::AFTER, "wCiwqVEBj4kwoBpAt5837", note4, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID BOOKMARK>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_show, fixture)
{
  phonebookInterface.show("wCiwqVEBj4kwoBpAt5837", out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID BOOKMARK>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_move, fixture)
{
  PhonebookInterface::steps_t steps{};
  steps.steps = PhonebookInterface::steps_t::LAST;
  phonebookInterface.move(steps, "wCiwqVEBj4kwoBpAt5837", out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID BOOKMARK>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_delete, fixture)
{
  phonebookInterface.deleteNote("wCiwqVEBj4kwoBpAt5837", out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID BOOKMARK>\n");
}

BOOST_AUTO_TEST_SUITE_END()
