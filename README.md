# word-locator

#Usage

    0. remove any existing executable files with
        > make clean

    1. compile with the given make file.
        > make

    2. run program with executable file name wl
        > wl
        (sometimes >./wl)  Depends on which system you're running on

    3. exit program with
        >end

#Program Commands
    The word locator has 4 valid commands

    1. >load <filename>
       this command loads a specified file. The file may be specified by either
       absolute or relative path name.  When this command is run, words are
       parsed from the file into a binary search tree.

    2. >locate <word> <n>
       this command ouputs the number of the word, counting from the beginning
       of the file, of the nth occurrance of the word. Word numbering starts
       from 1, so the first word in the load file has a word number of 1.  The
       locate command is case insensitive.

       The syntax of the locate command is “locate <word> <n>”. The “<word>”
       parameter will have whitespace before and after it, and “<n>” should be
       an integer greater than 0.

       The following commands are not legal: “locate sing3”, “locate sing 3q”.
       The first command does not specify a parameter “<n>”, and in the second
       command the parameter “<n>” is not an integer. Please note that the
       command “locate sing23 4” is a legal command for locating the fourth
       occurrence of the word “sing23”.

    3. >new
       this command resets the word list (tree) to its original (empty) state

    4. >end
       this command terminates the program




