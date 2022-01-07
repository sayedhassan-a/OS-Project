## wzip
This tool compresses a file using RLE(run-length encoding).
When you encounter n characters c the tool turns it into the number of repeatitions n and the charachter c.
### For example when you encounter 
    aaaabbb
    cc
#### The tool turns it into
    4a3b1
    2c
### complexity 
        since we will traverse all over the file the complexity will be O(N)
        N -->> length of the file
