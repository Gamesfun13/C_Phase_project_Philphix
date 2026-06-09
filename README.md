# C_Phase_project_Philphix


philphix is a very simple and silly replacement tool that accepts a single command line argument, the name of a replacement set to use. This replacement set consists of pairs of “words” (separated by an arbitrary number of tabs and spaces), each pair on its own line. The first word only consists of alphanumeric characters, but the second word can include any non-whitespace printable character. The first word is the target word the input word is being matched against; the second word is what is to replace the input word if at all due to priority.

For each word (sequence of letters and numbers unbroken by any other character) in the input, philphix processes it to see if it should be replaced. Here is the order of match priority:

1.The exact word is in the replacement set
2.The word with all but the first character converted to lower case is in the replacement set
3.The word converted completely to lower case is in the replacement set

If there is no match the word is printed to standard output unchanged; if there is a match, the highest priority replacement for the word is printed.


Read More:https://61c-teach.github.io/sp21/projects/proj1/