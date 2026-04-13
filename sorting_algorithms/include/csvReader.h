#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "DynamicArray.h"

void clear_directory(const std::string& path);

DynamicArray load_csv(const std::string& filename);

DynamicArray load_data(const DynamicArray& source, int n);