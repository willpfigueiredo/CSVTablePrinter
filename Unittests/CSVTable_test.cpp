#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "CSVTable.hpp"

class CSVTableToTest : public CSVTable
{
    public:

    std::vector<std::vector<std::string>>& getTable(){
        return m_table;
    }
};

TEST(CSVTableTestSuite, FileParseTest)
{
    CSVTableToTest csvTable;
    csvTable.parseFile("data.csv");
    std::vector<std::vector<std::string>> &table = csvTable.getTable();

    EXPECT_EQ("Name", table[0][0]);
    EXPECT_EQ("Street", table[0][1]);
    EXPECT_EQ("City", table[0][2]);
    EXPECT_EQ("Age", table[0][3]);
    EXPECT_EQ("Paul Meier", table[4][0]);
    EXPECT_EQ("Münchener Weg 1", table[4][1]);
    EXPECT_EQ("87654 München", table[4][2]);
    EXPECT_EQ("65", table[4][3]);
}

TEST(CSVTableTestSuite, GetCellValueTest)
{
    CSVTableToTest csvTable;
    std::vector<std::vector<std::string>> &table = csvTable.getTable();

    table = {{"Name","Street","City","Age"},
            {"Peter Pan","Am Hang 5","12345 Einsam","42"},
            {"Maria Schmitz","Kölner Straße 45","50123 Köln",""},
            {"Max Mustermann","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"}};

    EXPECT_EQ(table[0][0], csvTable.getCellValue(0,0));
    EXPECT_EQ(table[1][2], csvTable.getCellValue(1,2));
    EXPECT_EQ(table[3][3], csvTable.getCellValue(3,3));
    EXPECT_EQ(table[2][3], csvTable.getCellValue(2,3));
}

TEST(CSVTableTestSuite, GetColumnsCountTest)
{
    CSVTableToTest csvTable;
    std::vector<std::vector<std::string>> &table = csvTable.getTable();

    table = {{"Name","Street","City","Age"},
            {"Peter Pan","Am Hang 5","12345 Einsam","42"},
            {"Maria Schmitz","Kölner Straße 45","50123 Köln",""},
            {"Max Mustermann","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"}};

    EXPECT_EQ(4, csvTable.getColumnCount());

}

TEST(CSVTableTestSuite, GetRowsCountTest)
{
    CSVTableToTest csvTable;
    std::vector<std::vector<std::string>> &table = csvTable.getTable();

    table = {{"Name","Street","City","Age"},
            {"Peter Pan","Am Hang 5","12345 Einsam","42"},
            {"Maria Schmitz","Kölner Straße 45","50123 Köln",""},
            {"Max Mustermann","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"}};

    EXPECT_EQ(4, csvTable.getRowsCount());

}