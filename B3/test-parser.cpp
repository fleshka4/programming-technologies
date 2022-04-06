#include <iostream>
#include <boost/test/unit_test.hpp>
#include "parser.hpp"

BOOST_AUTO_TEST_SUITE(test_parser)

struct fixture {
  PhonebookInterface phonebookInterface;
  const Phonebook::note_t note = {"872251296363", "xXBhuYANUGzVcm"};
  const Phonebook::note_t note2 = {"888292862786", "vWJUFtPbEI wyNdNHeaNZ"};
  const Phonebook::note_t note3 = {"316283157688", "rnW zQHfcd\"WSrVJEStpZZGgH\"hYg"};
  std::ostringstream out;
  std::ostringstream out2;
  std::ostringstream out3;

  Command command;
};

BOOST_FIXTURE_TEST_CASE(correct_add, fixture)
{
  command = parseCommand("add 464948817669 \"zWEGSBaFCdyr,FDJMFPfg AU\"");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "");
  phonebookInterface.show("current", out);
  BOOST_CHECK_EQUAL(out.str(), "464948817669 zWEGSBaFCdyr,FDJMFPfg AU\n");
}

BOOST_FIXTURE_TEST_CASE(correct_delete_and_show, fixture)
{
  phonebookInterface.add(note, out);

  command = parseCommand("show current");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "872251296363 xXBhuYANUGzVcm\n");

  phonebookInterface.add(note2, out2);

  command = parseCommand("delete current");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  command = parseCommand("show current");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "888292862786 vWJUFtPbEI wyNdNHeaNZ\n");
}

BOOST_FIXTURE_TEST_CASE(correct_insert, fixture)
{
  phonebookInterface.add(note, out);
  command = parseCommand("insert after current 179116565809 \"PNgTOdaBGNazdrSUsr\"");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "");

  PhonebookInterface::steps_t steps{};
  steps.n = 1;
  steps.flag = PhonebookInterface::steps_t::NUMERIC;

  phonebookInterface.move(steps, "current", out);
  BOOST_CHECK_EQUAL(out.str(), "");
  phonebookInterface.show("current", out);
  BOOST_CHECK_EQUAL(out.str(), "179116565809 PNgTOdaBGNazdrSUsr\n");

  command = parseCommand("insert before current 358496195357 \"wacXQbkgnLRzbIvsI\"");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  steps.n = -1;
  phonebookInterface.move(steps, "current", out2);
  BOOST_CHECK_EQUAL(out2.str(), "");
  phonebookInterface.show("current", out2);
  BOOST_CHECK_EQUAL(out2.str(), "358496195357 wacXQbkgnLRzbIvsI\n");
}

BOOST_FIXTURE_TEST_CASE(correct_move_with_keywords, fixture)
{
  phonebookInterface.add(note, out);
  phonebookInterface.add(note2, out);
  phonebookInterface.add(note3, out);

  command = parseCommand("move current last");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("current", out);
  std::string expected = note3.number + ' ' + note3.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);

  command = parseCommand("move current first");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  phonebookInterface.show("current", out2);
  expected = note.number + ' ' + note.name + '\n';
  BOOST_CHECK_EQUAL(out2.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(correct_move_with_numeric_steps, fixture)
{
  const Phonebook::note_t note4 = {"973237822526", "hIID qKxAHob\"L,pTQY,clzGlVmNP"};
  const Phonebook::note_t note5 = {"760376686664", "xGXxsEgbDaM g"};
  const Phonebook::note_t note6 = {"212677136711", "KifspBIwpPaMwvWpPv"};

  phonebookInterface.add(note4, out);
  phonebookInterface.add(note5, out);
  phonebookInterface.add(note6, out);

  command = parseCommand("move current 5");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("current", out);
  std::string expected = note6.number + ' ' + note6.name + '\n';
  BOOST_CHECK_EQUAL(out.str(), expected);

  command = parseCommand("move current -2");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "");

  phonebookInterface.show("current", out2);
  expected = note4.number + ' ' + note4.name + '\n';
  BOOST_CHECK_EQUAL(out2.str(), expected);
}

BOOST_FIXTURE_TEST_CASE(correct_store, fixture)
{
  phonebookInterface.add(note, out);
  command = parseCommand("store current markname");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "");

  phonebookInterface.show("markname", out);
  BOOST_CHECK_EQUAL(out.str(), note.number + ' ' + note.name + '\n');
}

BOOST_FIXTURE_TEST_CASE(invalid_number, fixture)
{
  command = parseCommand("add 942djk53 \"nbSjGkaQfpSKtX\"");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_name, fixture)
{
  command = parseCommand("add 942djk53\"nbSjGkaQfpSKtX\"");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");

  command = parseCommand("add 942djk53 ");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_add_without_arguments, fixture)
{
  command = parseCommand("add");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_delete, fixture)
{
  command = parseCommand("delete current");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<EMPTY>\n");

  command = parseCommand("delete");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_show, fixture)
{
  command = parseCommand("show current");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<EMPTY>\n");

  command = parseCommand("show");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_arguments_insert, fixture)
{
  command = parseCommand("insert before 942553\"nbSjGkaQfpSKtX\"");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");

  command = parseCommand("insert after 942djk53 \"nbSjGkaQfpSKtX\"");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID COMMAND>\n");

  command = parseCommand("insert after");
  command(phonebookInterface, out3);
  BOOST_CHECK_EQUAL(out3.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_move, fixture)
{
  command = parseCommand("move");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");

  command = parseCommand("move current fdsfs");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID STEP>\n");

  command = parseCommand("move current first");
  command(phonebookInterface, out3);
  BOOST_CHECK_EQUAL(out3.str(), "<EMPTY>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_store, fixture)
{
  command = parseCommand("store");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");

  command = parseCommand("store current");
  command(phonebookInterface, out2);
  BOOST_CHECK_EQUAL(out2.str(), "<INVALID COMMAND>\n");
}

BOOST_FIXTURE_TEST_CASE(invalid_command, fixture)
{
  phonebookInterface.add(note, out);
  command = parseCommand("remove current");
  command(phonebookInterface, out);
  BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");
}

BOOST_AUTO_TEST_SUITE_END()
