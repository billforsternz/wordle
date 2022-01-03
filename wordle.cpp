//
// A very simple, no frills Wordle solver - for those times when you think the answer is just
//  not in your vocabulary.
//
// Thanks to Josh at powerlanguage for Wordle!
//
// Bill Forster billforsternz@gmail.com 2021.01.03
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

// Check the word list, one word at a time
bool check_word( const std::string &word, const std::string &green_pattern,
                 const std::vector<std::string> &yellow_patterns, const std::string &yellow_letters,
                 const std::set<char> &black_letters )
{
    int idx=0;
    std::set<char> build;   // build a set of letters from the word
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
        build.insert(c);    // dups are automatically ignored
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
    for( std::string yellow_pattern: yellow_patterns )
    {
        idx = 0;
        for( char c: word )
        {
            char p = yellow_pattern[idx];
            if( c == p )
                return false;   // word matches unacceptable pattern
            idx++;
        }
    }
    return true;
}

// Entry point
int main( int argc, char *argv[] )
{
    const char *usage =
    "Usage;\n"
    "  wordle green_pattern black_letters yellow_patterns...\n"
    "    green_pattern   = 5 letter known pattern, lower case letters and ?s\n"
    "    black_letters   = letters known to be excluded, '-' to omit\n"
    "    yellow_patterns = 5 letter patterns, lower case letters and ?s\n"
    "For example;\n"
    "  You know o is the middle letter, you know e,l,i,a,n and r aren't\n"
    "  included. You know s and t are included, but t can't be the second\n"
    "  letter and s can't be the first, second or last letter. Run this\n"
    "  command;\n"
    "  wordle ??o?? elianr st??s ?s???\n"
    "Prints 'boost', 'coost', 'ghost', 'moost' and 'toosh'. The large word\n"
    "list, courtesy of \"https://github.com/dwyl/english-words\" (thank you)\n"
    "includes many strange words, use your judgement!\n"
    "\n"
    "Thanks to Josh at powerlanguage.co.uk for creating Wordle.\n"
    "\n"
    "Bill Forster, github.com/billforsternz/wordle, billforsternz@gmail.com\n";

    // Check a few preconditions etc.
    if( argc < 3 )
    {
        printf( "Simple command line Wordle solver. Use only when terminally frustrated!\n\n" );
        printf( "%s", usage );
        return -1;
    }
    std::string green_pattern(argv[1]);
    std::string black_letters(argv[2]);
    bool err = false;
    size_t offset;
    if( green_pattern.length() != 5 )
    {
        printf( "Error: Green pattern string '%s' should be 5 characters long\n", green_pattern.c_str() );
        err = true;
    }
    if( (offset=green_pattern.find_first_not_of("?abcdefghijklmnopqrstuvwxyz")) != std::string::npos )
    {
        printf( "Error: Illegal character '%c' in green pattern string '%s'\n", green_pattern[offset], green_pattern.c_str() );
        err = true;
    }
    if( (offset=black_letters.find_first_not_of("-abcdefghijklmnopqrstuvwxyz")) != std::string::npos )
    {
        printf( "Error: Illegal character '%c' in black letters string '%s'\n", black_letters[offset], black_letters.c_str() );
        err = true;
    }

    // Create yellow_patterns and yellow_letters
    std::vector<std::string> yellow_patterns;
    std::string yellow_letters;
    for( int i=3; !err && i<argc; i++ )
    {
        std::string s(argv[i]);
        if( (offset=s.find_first_not_of("?abcdefghijklmnopqrstuvwxyz")) != std::string::npos )
        {
            printf( "Error: Illegal character '%c' in yellow pattern string '%s'\n", s[offset], s.c_str() );
            err = true;
        }
        if( s.length() != 5 )
        {
            printf( "Error: Yellow pattern string '%s' should be 5 characters long\n", s.c_str() );
            err = true;
        }
        yellow_patterns.push_back(s);
        for( char c: s )
        {
            if( c != '?' && yellow_letters.find(c)==std::string::npos )
                yellow_letters.push_back(c);
        }
    }
    if( err )
    {
        printf( "%s", usage );
        return -1;
    }

    // Parameter black_letters is a std::set of banned letters
    std::set<char> banned;
    for( char c: black_letters )
    {
        if( c != '-' )
            banned.insert(c);
    }

    // Loop through the word list, easy peasy
    extern const char *wordlist[];
    extern unsigned int wordlist_length;
    printf( "Checking %u known five letter words\n", wordlist_length );
    for( unsigned int i=0; i<wordlist_length; i++ )
    {
        std::string word(wordlist[i]);
        if( check_word( word, green_pattern, yellow_patterns, yellow_letters, banned ) )
            printf( "%s\n", word.c_str() );
    }
    return 0;
}
