The program is meant to zip multiple files in parallel. To be executed at the same time.
The program intiates multiple threads for each file to execute it. 
Each thread takes a file and zips it. 
After finalize all threads, the main function will concatenate all outputs of all threads and put it in the out file. 
At the end, the file will contain vector of struct of number and character which are the zipping of the string. 
