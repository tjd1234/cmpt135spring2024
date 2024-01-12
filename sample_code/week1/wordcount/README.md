## Example: Counting Words in a Text File

### The Problem

The standard Linux utility `wc` counts characters, lines, and words in a file.
For example:

```
> wc austenPride.txt
 13427 124580 704158 austenPride.txt
```

This says that [austenPride.txt](austenPride.txt) has 13427 lines, 124580 words,
and 704158 characters.

Using the file [count_chars_start.cpp](count_chars_start.cpp) as a start, create
your own version of `wc` that does this:

1. **Count the number of characters in a file**. To do this, use `cin.get`.
   `cin.get(c)` sets the `char` `c` to the next character from `cin`. After
   calling `cin.get(c)`. If there are no more characters, i.e. an end of file
   (EOF) character is read in, then `cin.get(c)` returns `false`.
    
   You don't need to use any special file processing in your program. Instead,
   use file re-direction in the terminal like this:
  
   ```bash
   > ./count_chars < austenPride.txt
   #chars: 704158
   #lines: 13427
   #tabs: 0
   #words: 124580
   ```

2. **Count the number of lines in a file**. For simplicity, a line is an
   occurrence of a `'\n'` (newline) character.

3. **Count the number of `'\t'` (tab) characters in a file**.

4. **Count the number of words in a file**. The precise definition of a word is
   tricky, so instead it is easier to count *non*-words, i.e. sequences of
   whitespace characters that appear between words. Count the number of
   sub-strings consisting of one or more whitespace characters, where whitespace
   characters are `' '` (space), `'\n'` (newline), and `'\t'` (tab).


### Sample Solution

[count_chars.cpp](count_chars.cpp) is a pretty good solution to the problem.

Note the following about [count_chars.cpp](count_chars.cpp):

- **It is short and readable**. Programmers don't want to have to read a lot of
  messy code.

- **It's pretty efficient in both time and memory**. It only reads the file
  once, and use a very small amount of memory (it doesn't read the entire file
  into memory).

- **Counting words is tricky**. The insight of counting the whitespace *between*
  words is not completely obvious, and so that's a good reason to explain it in
  comments. This tricks works well enough in practice, but it is not perfect.
  For example, `hoi polloi` is one English word, but it is counted as two
  because of the space. And text like `one...two...three` is counted as *one*
  word because it has no spaces.

- **[count_chars_start.cpp](count_chars_start.cpp) is a good starting point for
  writing other character-by-character utilities**. For instance, starting with
  it you could write a program that adds line numbers to the start of each line,
  or strips-out source code comments, etc.


## Extra

[count_chars.cpp](count_chars.cpp) could be extended in many different ways. See
[this code](opp_version/) for an example of how to make it more general-purpose
and object-oriented.
