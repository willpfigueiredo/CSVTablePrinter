# CSVTablePrinter

This code prints a table from CSV data and output it formatted.

The input to the function is a list of strings. Each string is formatted as a CSV record. Here’s an example for a possible input:

Name;Street;City;Age \
Peter Pan;Am Hang 5;12345 Einsam;42 \
Maria Schmitz;Kölner Straße 45;50123 Köln;43 \
Paul Meier;Münchener Weg 1;87654 München;65

In the input a semicolon separates values within a line. 

The output should is the data formatted as an “ASCII table”. The first record is interpreted as a header line. 
A separator line follows the header line. 
The column width follows the longest value in a column (which includes the header). Here’s an example output for the above input:

```bash
Name         |Street          |City         |Age|
-------------+----------------+-------------+---+
Peter Pan    |Am Hang 5       |12345 Einsam |42 |
Maria Schmitz|Kölner Straße 45|50123 Köln   |43 |
Paul Meier   |Münchener Weg 1 |87654 München|65 |
```
- Standard C++ (STL) is used;
- all output is written to standard output
- the line length of the output never exceeds 80 characters
