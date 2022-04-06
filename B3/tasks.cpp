#include "tasks.hpp"

#include <iostream>

#include "factorial-container.hpp"
#include "phonebook-interface.hpp"
#include "parser.hpp"

void doFirstTask()
{
  PhonebookInterface phonebookInterface;
  std::string cmd;
  while (std::getline(std::cin, cmd)) {
    Command command = parseCommand(cmd);
    command(phonebookInterface, std::cout);
  }
}

void doSecondTask()
{
  const FactorialContainer factorialContainer(10);
  std::copy(factorialContainer.begin(), factorialContainer.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';

  std::copy(factorialContainer.rbegin(), factorialContainer.rend(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
