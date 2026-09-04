#pragma once

#include "Record.h"
#include <array>
#include <cstddef>

class Page {
private:
    char data[4096];
    size_t freeOffset = 0;

public:
    void insertRecord(const Record& record);

    Record* getRecord(size_t index);

    std::array<Record, 170> getAllRecords();
};