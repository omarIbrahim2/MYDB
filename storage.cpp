#include "Storage.h"

Storage::Storage(const char* filename)
{
    file.open(
        filename,
        std::ios::in |
        std::ios::out |
        std::ios::binary
    );
}

void Storage::writePage(const Page& page, std::size_t pageId)
{
    file.seekp(pageId * sizeof(Page));

    file.write(
        reinterpret_cast<const char*>(&page),
        sizeof(Page)
    );

    file.flush();
}

Page Storage::readPage(std::size_t pageId)
{
    Page page;

    file.seekg(pageId * sizeof(Page));

    file.read(
        reinterpret_cast<char*>(&page),
        sizeof(Page)
    );

    return page;
}