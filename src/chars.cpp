#include <cstring>
#include <string>
#include <cmath>
#include <bits/stdc++.h>
#include <vector>

/*
 * These are, admittedly, some of the ugliest functions I've ever needed
 * to write. However, they are necessary. No functions existed for the
 * specific conversions required  for Excel coordinate parsing. Unfortunately,
 * this specific "caps only to int and back" doesn't translate well into
 * ASCII, and there isn't an obvious pattern. Giant switch statements it is!
 */

static char back_to_char(int n)
{
    switch (n) {
        case 1:
            return 'A';
            break;
        case 2:
            return 'B';
            break;
        case 3:
            return 'C';
            break;
        case 4:
            return 'D';
            break;
        case 5:
            return 'E';
            break;
        case 6:
            return 'F';
            break;
        case 7:
            return 'G';
            break;
        case 8:
            return 'H';
            break;
        case 9:
            return 'I';
            break;
        case 10:
            return 'J';
            break;
        case 11:
            return 'K';
            break;
        case 12:
            return 'L';
            break;
        case 13:
            return 'M';
            break;
        case 14:
            return 'N';
            break;
        case 15:
            return 'O';
            break;
        case 16:
            return 'P';
            break;
        case 17:
            return 'Q';
            break;
        case 18:
            return 'R';
            break;
        case 19:
            return 'S';
            break;
        case 20:
            return 'T';
            break;
        case 21:
            return 'U';
            break;
        case 22:
            return 'V';
            break;
        case 23:
            return 'W';
            break;
        case 24:
            return 'X';
            break;
        case 25:
            return 'Y';
            break;
        case 26:
            return 'Z';
            break;
        default:
            return '*';
            break;
    }
}

static int char_to_value(char n)
{
    switch (n) {
        case 'A':
            return 1;
            break;
        case 'B':
            return 2;
            break;
        case 'C':
            return 3;
            break;
        case 'D':
            return 4;
            break;
        case 'E':
            return 5;
            break;
        case 'F':
            return 6;
            break;
        case 'G':
            return 7;
            break;
        case 'H':
            return 8;
            break;
        case 'I':
            return 9;
            break;
        case 'J':
            return 10;
            break;
        case 'K':
            return 11;
            break;
        case 'L':
            return 12;
            break;
        case 'M':
            return 13;
            break;
        case 'N':
            return 14;
            break;
        case 'O':
            return 15;
            break;
        case 'P':
            return 16;
            break;
        case 'Q':
            return 17;
            break;
        case 'R':
            return 18;
            break;
        case 'S':
            return 19;
            break;
        case 'T':
            return 20;
            break;
        case 'U':
            return 21;
            break;
        case 'V':
            return 22;
            break;
        case 'W':
            return 23;
            break;
        case 'X':
            return 24;
            break;
        case 'Y':
            return 25;
            break;
        case 'Z':
            return 26;
            break;
        default:
            return 8888;
    }
}

static int row_to_int(char *col)
{
    std::string column = col;
    std::reverse(column.begin(), column.end());
    int x = 0;
    int len = column.length();
    int res = 0;

    for (x = 0; x < len; x++) {
        res += (char_to_value(column[x]) * ((x == 0) ? 1 : (std::pow(26, x))));
    }

    return res;
}

static char *int_to_row (int column)
{
    std::string ret = "";
    if (column <= 26) {
        ret += back_to_char(column);
    } else if (column <= 676) {
        ret += back_to_char(std::floor(column / 26));
        ret += back_to_char(column % 26);
    } else {
        /* three is the max for excel spreadsheets */
        ret += back_to_char(std::floor(column / 676));
        ret += back_to_char (std::floor((column - std::floor(column / 676) * 676) / 26));
        ret += back_to_char(column % 26);
    }
    return const_cast<char *>(ret.c_str());
}

extern "C" char **sequence (char *start, char *end)
{
    std::vector<char *> x;
    for(int y = row_to_int(start); y <= row_to_int(end); y++) {
        x.push_back(int_to_row(y));
    }
    return &x[0];
}
