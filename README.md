Simple command line Wordle solver. Use only when terminally frustrated!

    Usage;
      wordle green_pattern black_letters yellow_patterns...
        green_pattern   = 5 letter known pattern, lower case letters and ?s
        black_letters   = letters known to be excluded, '-' to omit
        yellow_patterns = 5 letter patterns, lower case letters and ?s
    For example;
      You know o is the middle letter, you know e,l,i,a,n and r aren't
      included. You know s and t are included, but t can't be the second
      letter and s can't be the first, second or last letter. Run this
      command;
      wordle ??o?? elianr st??s ?s???
    Prints 'boost', 'coost', 'ghost', 'moost' and 'toosh'. The large word
    list, courtesy of https://github.com/dwyl/english-words (thank you)
    includes many strange words, use your judgement!

Thanks to [https://github.com/dwyl/english-words](https://github.com/dwyl/english-words) for the unaltered
word list (which is now baked in, no external file needed).

Thanks to Josh at powerlanguage.co.uk for creating Wordle.

I have included a Windows executable in the release directory. If it
doesn't work on your system I blame Microsoft for overcomplicating things,
it used to be easy to share simple executables!
