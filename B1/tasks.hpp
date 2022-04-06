#ifndef TASKS_HPP
#define TASKS_HPP

#include <functional>

void doFirstTask(const std::function<bool(int, int)>& compare);
void doSecondTask(const char* filename);
void doThirdTask();
void doFourthTask(const std::function<bool(double, double)>& compare, int size);

void fillRandom(double* array, int size);

#endif
