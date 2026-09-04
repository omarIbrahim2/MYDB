#pragma once

#include "Page.h"
#include <cstddef>
#include <fstream>

class Storage {
private:
    std::fstream file;

public:
    explicit Storage(const char* filename);

    void writePage(const Page& page, std::size_t pageId);
    Page readPage(std::size_t pageId);
};
