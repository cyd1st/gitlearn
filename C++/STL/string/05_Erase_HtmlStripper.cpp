//: C03:HTMLStripper.cpp {RunByHand}
//{L} ReplaceAll
// Filter to remove html tags and markers.
#include <cassert>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include "../../b2_Think-in-C++/lib/require.h"
#include "03_ReplaceAll.h"
using namespace std;

string &stripHTMLTags(string &s)
{
    bool inTag = false; // 标记当前是否处于 <> 之内，找到 < 就处于括号内了
    bool done = false;

    while (!done) {
        if (inTag) {
            // The previous line started an HTML tag
            // but didn't finish. Must search for '>'.
            size_t rightPos = s.find('>');
            if (rightPos != string::npos) {
                inTag = false;
                s.erase(0, rightPos + 1);
            } else {
                done = true;
                s.erase();
            }
        } else {
            // Look for start of tag:
            size_t leftPos = s.find('<');
            if (leftPos != string::npos) {
                // See if tag close is in this line:
                size_t rightPos = s.find('>');
                if (rightPos == string::npos) {
                    inTag = done = true;
                    s.erase(leftPos);
                } else
                    s.erase(leftPos, rightPos - leftPos + 1);
            } else
                done = true;
        }
    }

    // Remove all special HTML characters
    // 不处理用字符表示的符号
    replaceAll(s, "&lt;", "<");
    replaceAll(s, "&gt;", ">");
    replaceAll(s, "&amp;", "&");
    replaceAll(s, "&nbsp;", " ");
    // Etc...
    return s;
}

int main(int argc, char *argv[])
{
    requireArgs(argc, 2);
    ifstream in(argv[1]);
    assure(in, argv[1]);
    string s;
    while (getline(in, s))
        if (!stripHTMLTags(s).empty())
            cout << s << endl;
} ///:~