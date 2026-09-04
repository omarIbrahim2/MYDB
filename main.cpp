#include "Storage.h"
#include "Record.h"
#include <iostream>

int main()
{
    Storage db("database.db");

    Page page;

    Record r1(1, "Omar");
    Record r2(2, "Ahmed");

    page.insertRecord(r1);
    page.insertRecord(r2);

    db.writePage(page, 0);

    Page loadedPage = db.readPage(0);

    auto records = loadedPage.getAllRecords();

    for (const auto& record : records) {

        if (record.getId() != 0) {
            std::cout
                << record.getId()
                << " "
                << record.getName()
                << '\n';
        }
    }
}