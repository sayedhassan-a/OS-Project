## Wgrep
 This tool looks through a file, line by line, trying to find a user-specified search term in the line. <br> 
 If a line has the word within it, the line is printed out, otherwise it is not.
 ### Cases 
     -The search is case sensitive 
     -No file name has not been entered the code prints "wgrep: searchterm [file ...]" and exit with 1.
     -The file cannot be opened the code prints"wgrep: cannot open file" and exit with 1.
     -If there were no matches on the file the code will not print any thing and return with 0.
     -If the string space the code will print the entire file 
### colmplesity :- 
      The complexity of this program is O(n+m) where n is the length of the input string and the m is the length of the file 
