#pragma once

#include <cstdint>

class Record {
public:
    Record();
    Record(uint32_t id, const char* name);

    uint32_t getId() const;
    const char* getName() const;

private:
    uint32_t id;
    char name[20];
};