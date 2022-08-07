#include "book.h"
#include<stdio.h>
#include<malloc.h>


Book* creatEmptyBook()
{
    Book* book = calloc(1, sizeof(Book));
    if (!book)
    {
        printf("createEmptyBook failed");
        return NULL;
    }
    return book;
}

Book* book_fromString(const char* str)
{
    Book* book = creatEmptyBook();
    int ret =sscanf(str, "%d %d %s %s %s %d %d %d %d %d", &book->recordNumber, &book->bookNumber, book->bookName, book->bookAuthor, book->bookPublishHouse,
        &book->bookCnt, &book->borrowCnt, &book->p1, &book->p2, &book->p3);
    if (ret<=0)
    {
        printf("book_fromString failed");
        free(book);
        return NULL;
    }
    return book;
}

void book_save(Book* book, FILE* fp)
{
    char buf[BUFSIZ] = { 0 };
    sprintf(buf, "%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",
        book->recordNumber,book->bookNumber,book->bookName,book->bookAuthor,book->bookPublishHouse,book->bookCnt,book->borrowCnt,
        book->p1, book->p2, book->p3);
    fputs(buf, fp);
}

void book_print(Book* book)
{
    printf("%-8d %-5d %-10s %-10s %-10s %-6d %d\n", book->recordNumber, book->bookNumber, book->bookName, book->bookAuthor, book->bookPublishHouse,
       book->borrowCnt, book->borrowCnt);



}
