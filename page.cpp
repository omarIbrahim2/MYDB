#include "Page.h"
#include "Record.h"
#include <cstring>
#include <array>

void Page::insertRecord(const Record& record)
{
    if (freeOffset + sizeof(Record) > sizeof(data)) {
        return;
    }

    memcpy(
        data + freeOffset,
        &record,
        sizeof(Record)
    );

    freeOffset += sizeof(Record);
}

Record* Page::getRecord(size_t index)
{
    size_t offset = index * sizeof(Record);

    if (offset + sizeof(Record) > freeOffset) {
        return nullptr;
    }

    return reinterpret_cast<Record*>(data + offset);
}

std::array<Record, 170> Page::getAllRecords()
{
    std::array<Record, 170> records{};

    size_t recordCount = freeOffset / sizeof(Record);

    for (size_t i = 0; i < recordCount; ++i) {
        records[i] = *getRecord(i);
    }

    return records;
}