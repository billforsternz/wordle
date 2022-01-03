#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

bool check_word( const std::string &word, const std::string &green_pattern, const std::string &yellow_pattern, const std::string &yellow_letters, const std::set<char> &black_letters )
{
    int idx=0;
    std::set<char> build;
    for( char c: word )
    {
        char p = green_pattern[idx];
        if( p == '?' )
        {
            auto it = black_letters.find(c);
            bool is_banned = (it != black_letters.end());
            if( is_banned )
                return false;   // wildcard letter is banned
        }
        else if( c != p )
        {
            return false;   // word doesn't match acceptable pattern
        }
        idx++;
        build.insert(c);
    }
    for( char c: yellow_letters )
    {
        if( c != '-' )
        {
            auto it = build.find(c);
            bool is_present = (it != build.end());
            if( !is_present )
                return false;   // yellow_letters letter not present
        }
    }
    idx = 0;
    for( char c: word )
    {
        char p = yellow_pattern[idx];
        if( c == p )
            return false;   // word matches unacceptable pattern
        idx++;
    }
    return true;
}

void rtrim( std::string &s )
{
    size_t final_char_offset = s.find_last_not_of(" \n\r\t");
    if( final_char_offset == std::string::npos )
        s.clear();
    else
        s.erase(final_char_offset+1);
}

int main( int argc, char *argv[] )
{
    const char *usage =
    "Simple command line Wordle solver. Use only when terminally frustrated!\n"
    "\n"
    "Usage:\n"
    "  wordle green_pattern yellow_pattern yellow_letters black_letters\n"
    "green_pattern  = 5 letter known pattern, lower case letters and ?s\n"
    "yellow_pattern = As above, but word cannot match any of this\n"
    "yellow_letters = letters known to be included, '-' to omit\n"
    "black_letters  = letters known to be excluded, '-' to omit\n"
    "For example:\n"
    "  wordle b?nk? ?s??? s o\n"
    "Prints 'banks', 'bunks\n"
    "Run it more than once if you need more than one yellow_pattern\n"
    "\n"
    "Bill Forster, billforsternz@gmail.com\n";

    const char *wordlist =  "words_alpha.txt";
    std::ifstream fin( wordlist );
    if( !fin )
    {
        printf( "Cannot read file %s\n", wordlist );
        return -1;
    }
    if( argc != 5 )
    {
        printf( "%s\n", usage );
        return -1;
    }
    std::string green_pattern(argv[1]);
    std::string yellow_pattern(argv[2]);
    std::string yellow_letters(argv[3]);
    std::string black_letters(argv[4]);
    bool err = false;
    if( green_pattern.find_first_not_of("?abcdefghijklmnopqrstuvwxyz") != std::string::npos )
        err = true;
    if( yellow_pattern.find_first_not_of("?abcdefghijklmnopqrstuvwxyz") != std::string::npos )
        err = true;
    if( yellow_letters.find_first_not_of("-abcdefghijklmnopqrstuvwxyz") != std::string::npos )
        err = true;
    if( black_letters.find_first_not_of("-abcdefghijklmnopqrstuvwxyz") != std::string::npos )
        err = true;
    if( green_pattern.length() != 5 || yellow_pattern.length() != 5 )
        err = true;
    if( err )
    {
        printf( "%s", usage );
        return -1;
    }
    std::set<char> banned;
    for( char c: black_letters )
    {
        if( c != '-' )
            banned.insert(c);
    }
    std::vector<std::string> words;
    for(;;)
    {
        std::string line;
        if( !std::getline(fin,line) )
            break;
        rtrim(line);
        if( line.length() == 5 )
            words.push_back(line);
    }
    printf( "Checking %u known five letter words\n", words.size() ); 
    for( std::string word: words )
    {
        if( check_word( word, green_pattern, yellow_pattern, yellow_letters, banned ) )
            printf( "%s\n", word.c_str() );
    }
    return 0;
}
