#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include "CSVTable.hpp"
#include "TablePrinter.hpp"

class MockCSVTable : public CSVTable
{
    public:
    MockCSVTable(){
    }

    MOCK_METHOD(std::string, getCellValue, (int, int));
    MOCK_METHOD(std::vector<std::string>&, getRow, (int));
    MOCK_METHOD(int, getRowsCount, ());
    MOCK_METHOD(int, getColumnCount, ());

};

class TablePrinterToTest:public TablePrinter
{
    FRIEND_TEST(TablePrinterTestSuite, FillMaxLengthTest);
    FRIEND_TEST(TablePrinterTestSuite, realUTF8CharLengthTest);
    FRIEND_TEST(TablePrinterTestSuite, realUTF8CharLengthTestSpecialChars);
    FRIEND_TEST(TablePrinterTestSuite, SplitRowInLinesTest);
    FRIEND_TEST(TablePrinterTestSuite, SplitRowInLinesTestShorterText);
    FRIEND_TEST(TablePrinterTestSuite, SplitRowInLinesTestThreeLinesEmpty);
    public:
    std::vector<unsigned int>& getMaxLength(){
        return m_maxLength;
    }
};

TEST(TablePrinterTestSuite, FillMaxLengthTest)
{
    

    std::vector<std::vector<std::string>> table;
    table = {{"Name","Street","City","Age"},
            {"Pedro de Alcântara João Carlos Leopoldo Salvador Bibiano Francisco Xavier de Paula Leocádio Miguel Gabriel Rafael Gonzaga de Bragança e Bourbon","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"}};

    MockCSVTable csvTable; 

    EXPECT_CALL(csvTable, getCellValue(0,0)).WillRepeatedly(testing::Return(table[0][0]));
    EXPECT_CALL(csvTable, getCellValue(0,1)).WillRepeatedly(testing::Return(table[0][1]));
    EXPECT_CALL(csvTable, getCellValue(0,2)).WillRepeatedly(testing::Return(table[0][2]));
    EXPECT_CALL(csvTable, getCellValue(0,3)).WillRepeatedly(testing::Return(table[0][3]));
    EXPECT_CALL(csvTable, getCellValue(1,0)).WillRepeatedly(testing::Return(table[1][0]));
    EXPECT_CALL(csvTable, getCellValue(1,1)).WillRepeatedly(testing::Return(table[1][1]));
    EXPECT_CALL(csvTable, getCellValue(1,2)).WillRepeatedly(testing::Return(table[1][2]));
    EXPECT_CALL(csvTable, getCellValue(1,3)).WillRepeatedly(testing::Return(table[1][3]));
    EXPECT_CALL(csvTable, getRowsCount()).WillRepeatedly(testing::Return(2));
    EXPECT_CALL(csvTable, getColumnCount()).WillRepeatedly(testing::Return(4));
    
    TablePrinterToTest tablePrinter;
    tablePrinter.fillMaxLength(csvTable);
    std::vector<unsigned int>& maxVect = tablePrinter.getMaxLength();
    EXPECT_EQ(maxVect[0], 43);
    EXPECT_EQ(maxVect[1], 14);
    EXPECT_EQ(maxVect[2], 15);
    EXPECT_EQ(maxVect[3], 3);
}

TEST(TablePrinterTestSuite, realUTF8CharLengthTest)
{
    TablePrinterToTest tablePrinter;
    EXPECT_EQ(tablePrinter.realUTF8CharLength("54321 Nirgendwo"), 15);
}

TEST(TablePrinterTestSuite, realUTF8CharLengthTestSpecialChars)
{
    TablePrinterToTest tablePrinter;
    EXPECT_EQ(tablePrinter.realUTF8CharLength("Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11"), 47);
}


TEST(TablePrinterTestSuite, SplitRowInLinesTest)
{
    TablePrinterToTest tablePrinter;

    std::vector<std::string> row = {"Pedro de Alcântara João Carlos Leopoldo Salvador Bibiano Francisco Xavier de Paula Leocádio Miguel Gabriel Rafael Gonzaga de Bragança e Bourbon","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"};
    std::pair<std::vector<std::vector<std::string>>,int> rowSplitInLines;

    tablePrinter.m_maxLength.resize(4);
    tablePrinter.m_maxLength[0]= 43;
    tablePrinter.m_maxLength[1]= 14;
    tablePrinter.m_maxLength[2]= 15;
    tablePrinter.m_maxLength[3]= 3;

    rowSplitInLines = tablePrinter.splitRowInLines(row);

    EXPECT_EQ(rowSplitInLines.second, 4);
    EXPECT_EQ(rowSplitInLines.first[0][0], "Pedro de Alcântara João Carlos Leopoldo Sal");
    EXPECT_EQ(rowSplitInLines.first[0][1], "vador Bibiano Francisco Xavier de Paula Leo");
    EXPECT_EQ(rowSplitInLines.first[0][2], "cádio Miguel Gabriel Rafael Gonzaga de Brag");
    EXPECT_EQ(rowSplitInLines.first[0][3], "ança e Bourbon");
    
}

TEST(TablePrinterTestSuite, SplitRowInLinesTestShorterText)
{
    TablePrinterToTest tablePrinter;

    std::vector<std::string> row = {"Pedro de Alcântara João Carlos Leopoldo Salvador Bibiano Francisco Xavier de Paula Leocádio Miguel Gabriel Rafael Gonzaga de Bragança e Bourbon","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"};
    std::pair<std::vector<std::vector<std::string>>,int> rowSplitInLines;

    tablePrinter.m_maxLength.resize(4);
    tablePrinter.m_maxLength[0]= 43;
    tablePrinter.m_maxLength[1]= 14;
    tablePrinter.m_maxLength[2]= 15;
    tablePrinter.m_maxLength[3]= 3;

    rowSplitInLines = tablePrinter.splitRowInLines(row);

    EXPECT_EQ(rowSplitInLines.second, 4);
    EXPECT_EQ(rowSplitInLines.first[1][0], "Bischöflich-Ge");
    EXPECT_EQ(rowSplitInLines.first[1][1], "istlicher-Rat-");
    EXPECT_EQ(rowSplitInLines.first[1][2], "Zinnbauer-Stra");
    EXPECT_EQ(rowSplitInLines.first[1][3], "ße 11");

    
}

TEST(TablePrinterTestSuite, SplitRowInLinesTestThreeLinesEmpty)
{
    TablePrinterToTest tablePrinter;

    std::vector<std::string> row = {"Pedro de Alcântara João Carlos Leopoldo Salvador Bibiano Francisco Xavier de Paula Leocádio Miguel Gabriel Rafael Gonzaga de Bragança e Bourbon","Bischöflich-Geistlicher-Rat-Zinnbauer-Straße 11","54321 Nirgendwo","22"};
    std::pair<std::vector<std::vector<std::string>>,int> rowSplitInLines;

    tablePrinter.m_maxLength.resize(4);
    tablePrinter.m_maxLength[0]= 43;
    tablePrinter.m_maxLength[1]= 14;
    tablePrinter.m_maxLength[2]= 15;
    tablePrinter.m_maxLength[3]= 3;

    rowSplitInLines = tablePrinter.splitRowInLines(row);

    EXPECT_EQ(rowSplitInLines.second, 4);
    EXPECT_EQ(rowSplitInLines.first[3][0], "22");
    EXPECT_EQ(rowSplitInLines.first[3].size(), 1);
}
