Simple command line Wordle solver. Use only when terminally frustrated!

    Usage:
      wordle green_pattern yellow_pattern yellow_letters black_letters
    green_pattern  = 5 letter known pattern, lower case letters and ?s
    yellow_pattern = As above, but word cannot match any of this
    yellow_letters = letters known to be included, '-' to omit
    black_letters  = letters known to be excluded, '-' to omit
    For example:
      wordle b?nk? ?s??? s o
    Prints 'banks', 'bunks
    Run it more than once if you need more than one yellow_pattern

Bill Forster, billforsternz@gmail.com

