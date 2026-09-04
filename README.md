# Mini DBMS Storage Engine

A small C++ project for learning how a database storage engine stores
records in fixed-size pages and persists those pages to a binary file.

## What I Implemented

### Record

A `Record` represents one row:

``` cpp
struct Record {
    uint32_t id;   // 4 bytes
    char name[20]; // 20 bytes
};
```

The record is fixed-size, so its expected size is 24 bytes.

``` text
Record 0 -> offset 0
Record 1 -> offset 24
Record 2 -> offset 48
Record 3 -> offset 72
```

### Page

A `Page` provides a 4 KB raw storage area:

``` cpp
class Page {
private:
    char data[4096];
    size_t freeOffset = 0;
};
```

Records are stored sequentially inside `data`.

``` text
Page
+------------+------------+------------+----------------+
| Record 0   | Record 1   | Record 2   | Free Space     |
| 24 bytes   | 24 bytes   | 24 bytes   |                |
+------------+------------+------------+----------------+
                                         ^
                                      freeOffset
```

A 4096-byte data area can contain 170 complete 24-byte records.

### Insert Record

`insertRecord()` checks whether enough space remains and then copies the
record bytes into the page:

``` cpp
memcpy(data + freeOffset, &record, sizeof(Record));
freeOffset += sizeof(Record);
```

This stores the record directly in the page's raw byte array.

### Get Record

`getRecord(index)` calculates the record's byte offset:

``` cpp
size_t offset = index * sizeof(Record);
```

It then interprets that memory location as a `Record*`:

``` cpp
reinterpret_cast<Record*>(data + offset);
```

No record is copied by the cast itself; the same memory address is
interpreted as a `Record`.

### Get All Records

`getAllRecords()` calculates how many records are currently stored:

``` cpp
size_t recordCount = freeOffset / sizeof(Record);
```

It then retrieves each record and copies it into an array:

``` cpp
std::array<Record, 170> records{};

for (size_t i = 0; i < recordCount; ++i) {
    records[i] = *getRecord(i);
}
```

The `{}` initializes unused array elements instead of leaving them
uninitialized.

## Binary File Storage

Pages are persisted to a binary database file.

A page is written using:

``` cpp
file.seekp(pageId * sizeof(Page));

file.write(
    reinterpret_cast<const char*>(&page),
    sizeof(Page)
);
```

A page is read using:

``` cpp
file.seekg(pageId * sizeof(Page));

file.read(
    reinterpret_cast<char*>(&page),
    sizeof(Page)
);
```

The database file is conceptually organized as:

``` text
database.db

+------------------+
| Page 0           |
+------------------+
| Page 1           |
+------------------+
| Page 2           |
+------------------+
| ...              |
+------------------+
```

`seekp()` selects where a page is written, while `seekg()` selects where
a page is read.

## Data Flow

Writing:

``` text
Record
   |
   v
Page::insertRecord()
   |
   v
Page::data
   |
   v
Binary file
```

Reading:

``` text
Binary file
   |
   v
Page
   |
   v
Page::getRecord()
   |
   v
Record
```

## Project Structure

The code is being separated into classes/files:

``` text
DBMS/
├── Record.h
├── Record.cpp
├── Page.h
├── Page.cpp
├── Database.h
├── Database.cpp
└── main.cpp
```

Responsibilities:

-   **Record**: represents one database record.
-   **Page**: manages records inside a page.
-   **Database/Disk layer**: manages reading and writing pages to disk.
-   **main.cpp**: tests the storage engine.

## Concepts Practiced

This project is mainly for learning:

-   Fixed-size records
-   Fixed-size pages
-   Record offsets
-   Free-space tracking
-   Raw byte storage
-   `memcpy`
-   `reinterpret_cast`
-   Pointer arithmetic
-   Binary file I/O
-   `seekg()` and `seekp()`
-   `read()` and `write()`
-   Basic serialization
-   Separation of storage responsibilities

## Current Limitations

This is an educational implementation and intentionally keeps the
storage model simple.

### Page size

`data` is 4096 bytes, but `Page` also contains `freeOffset`, so:

``` cpp
sizeof(Page) > 4096
```

A later version should define an explicit 4096-byte on-disk page layout.

### Fixed-length records

The name is limited to 20 bytes:

``` cpp
char name[20];
```

Variable-length records are not implemented yet.

### Missing operations

The current version does not yet implement:

-   Delete
-   Update
-   Searching by ID
-   Page management
-   Buffer pool
-   Slotted pages

## Next Steps

Possible next improvements:

1.  Implement a `DiskManager`.
2.  Make the on-disk page exactly 4096 bytes.
3.  Add page IDs.
4.  Implement record update and deletion.
5.  Implement a page directory.
6.  Implement slotted pages.
7.  Support variable-length records.
8.  Add a buffer pool.
9.  Build a simple table layer.
10. Add a basic query layer.

The goal is to gradually build a small educational DBMS storage engine
from scratch and understand how database systems manage records, pages,
memory, and disk storage.
