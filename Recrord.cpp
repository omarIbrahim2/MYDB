#include "Record.h"
#include <cstring>

Record::Record()
    : id(0), name{}
{
}

Record::Record(uint32_t id, const char* name)
    : id(id)
{
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
}

uint32_t Record::getId() const {
    return id;
}

const char* Record::getName() const {
    return name;
}