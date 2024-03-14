
## A Bit if History: Donald Knuth and the Art of Computer Programming
![[Donald-Ervin-Knuth.jpg]]

[Donald Knuth](https://en.wikipedia.org/wiki/Donald_Knuth) is a renowned computer scientist whose most famous work is a series of books called [The Art of Computer Programming](https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming). In 1962, he wrote a 7-book outline for it, and as of 2024 has not quite finished book 4.

In these books he gives detailed mathematical analyses of many important algorithms. In Volume 1 (published in 1967), finding the max value among a list of numbers was one of problems that Knuth studied. Let's look at it here. While the algorithm is simple, determining its performance has unexpected depth.
## Finding the Max
Finding the maximum value among a list of numbers is a common and practical problem. It can be stated precisely:

> **The Max of a List**: Given values $v_0, v_1, \ldots, v_{n-1}$ with $n > 0$, find $i$ such that $v_i \geq v_j$ for all $j$ in $0, 1, \ldots , n-1$. In other words, find the largest value among $v_0, v_1, \ldots, v_{n-1}$.

Notice that this definition allows for the possibility that the max occurs 2 or more times. Also, we assume *nothing* about the order of the elements: $v_0, v_1, \ldots, v_{n-1}$ could be in *any* order at all.
## Basic Solution
The basic algorithm for solving this problem checks each element of the list to see if it's bigger than the values that have been checked earlier:

- Step 1: $k \leftarrow 0$ (the $\leftarrow$ means assignment, i.e. `k = 0` in C++)
- Step 2: if $v_1 \geq v_k$ then $k \leftarrow 1$
- Step 3: if $v_2 \geq v_k$ then $k \leftarrow 2$
- Step 4: if $v_3 \geq v_k$ then $k \leftarrow 3$
- ...
- Step i +1: if $v_i \geq v_k$ then $k \leftarrow i$
- ...
- Step n: if $v_{n-1} \geq v_k$ then $k \leftarrow n-1$
- Step n + 1: return $k$

Since $n$'s exact value is unknown, we use a loop (or [[recursion]]) to execute all the if-statements. Here is a [[pseudocode]] implementation:

```
max_so_far = v[0] 
for i = 1 to n - 1 do
   if v[i] > max_so_far then
       max_so_far = v[i]
   end
end
```

There is a pre-condition that `v` have at least one element. If `v` is empty, then there is no max to find, and we assume the algorithm throws an exception.
## Basic Solution Performance
The performance of a max-finding algorithm is usually measured by counting how many *comparisons* it does. All computers, no matter how fast or slow, will do the same number of comparisons when they run this algorithm.

By inspecting the algorithm's [[pseudocode]], we can see that it does exactly $n-1$ comparisons in *every* case, no matter where the max value happens to be located.

So we say the number of comparisons it does is proportional to $n$, i.e. it's *linear*. Or, in [[O-notation]], we can say this algorithm is $O(n)$.

## Can Fewer Comparisons be Done?
Is there a max-finding algorithm that can do fewer than $n-1$ comparisons?

In general, *no*, there's no such algorithm. After setting the initial max value to be $v_0$, we must check each of the remaining $n-1$ values to find if any are bigger. If we skip even one of those values, then that value might have been the max. So at least $n-1$ comparisons are needed.

The max can be found more quickly in some special cases. For example, if we happen to know that $v_0, \ldots, v_{n-1}$ are in ascending sorted order, then $v_{n-1}$ is the max element. But, in our statement of the max problem above, we explicitly said we are *not* assuming anything about the order of the elements, and so, in general, we can't assume the values are sorted.
## A C++ Implementation
Implementing the max algorithm is fairly straightforward. Notice that pre-condition requires that `v` has at least one element:

```cpp
// Pre-condition:
//    v.size() > 0
// Post-condition:
//    Returns an index value mi such that 0 <= mi < v.size()
//    and v[mi] >= v[i] for 0 <= i < v.size().
int index_of_max(const vector<int>& v) 
{
    int mi = 0;
	// note i starts at 1
    for(int i = 1; i < v.size(); i++) 
    {
        if (v[i] > v[mi]) 
        {
            mi = i;
        }
    }
    return mi;
}

int max_for(const vector<int>& v) 
{
    return v[index_of_max(v)];
}
```

## A Recursive Max
We can implement the max algorithm recursively using these rules:

- **Base case**: if `v` has 1 element, return that element.
- **Recursive case**: otherwise, return the max of the first element and the max of the rest of `v`.

In C++, we can implement it like this:

```cpp
int index_of_max_rec(const vector<int>& v, int begin) 
{
    if (begin >= v.size()) cmpt::error("empty vector");

    if (begin == v.size() - 1) 
    {  
        // only 1 element, so return it
        return begin;
    } 
    else 
    {
        int mi = index_of_max_rec(v, begin + 1);
        if (v[mi] > v[begin]) 
        {
            return mi;
        } 
        else 
        {
            return begin;
        }
    }
}

int index_of_max_rec(const vector<int>& v) 
{
    return index_of_max_rec(v, 0);
}

int max_rec(const vector<int> &v) 
{
    return v[index_of_max_rec(v)];
}
```

## A while-loop Implementation
Here's a version that uses a while-loop:

```cpp
int index_of_max_while(const vector<int>& v) 
{
    int mi = 0;
    int i = 1;
    while (i < v.size()) 
    {
        if (v[i] > v[mi]) 
        {
            mi = i;
        }
        i++;
    }
    return mi;
}

int max_while(const vector<int>& v) 
{
    return v[index_of_max_while(v)];
}
```

## Statement Counts
When `index_of_while(v)` below is called, how many times is each individual statement called? Assuming `v` contains `n` elements, we get these counts:

```cpp
int index_of_while(const vector<int>& v) 
{
    int mi = 0;              // 1
    int i = 1;               // 1
    while (i < v.size()) {   // n
        if (v[i] > v[mi]) {  // n - 1
            mi = i;          // ???
        }
        i++;                 // n - 1
    }
    return mi;               // 1
}
```

Most of the counts are easy to figure out. But the one with the ??? is not so obvious!
## Counting mi = i
How many times is `mi = i` called? Two extreme cases are easy:

- 0 times, when `v[0]` is the max
- n - 1 times, when `v` is in [[descending sorted order]]

What about on *average*? That's tricky! So lets run some experiments and count how many times `mi = i` is called. Here's some code that generates random vectors of length `n`:

```cpp
vector<int> rand_vec(int n) 
{
    vector<int> result(n);
    for(int i = 0; i < n; i++) 
    {
        // rand() returns a random int
        // from 0 to RAND_MAX
        result[i] = rand();
    }
    return result;
}
```

`rand()` is from `<cmath>`, and it generates [[pseudo-random number|pseudo-random numbers]]. To make it unpredictable, we can set an initial seed based on the current time:

```cpp
// srand sets the seed for rand()
// time comes from <ctime>
srand(time(NULL));
```

> If you *don't* set a seed, or use the same seed value every time, then the sequence of random numbers will be the *same* each time you run the program. Having the same random numbers each time can be helpful for debugging.

Now this version of max counts the number of times the line `mi = i` runs:

```cpp
int index_of_max_count(const vector<int>& v) 
{
    int mi = 0;
    int i = 1;
    int mi_assign_i_count = 0;
    while (i < v.size()) 
    {
        if (v[i] > v[mi]) 
        {
            mi = i;
            mi_assign_i_count++;
        }
        i++;
    }
    cout << "mi_assign_i_count = " 
         << mi_assign_i_count << "\n";
    return mi;
}
```

Now we can write some code for an experiment:

```cpp
void test() 
{
    const int n = 10;
    cout << "n = " << n << "\n";
    for(int i = 0; i < n; i++) 
    {
        vector<int> v = rand_vec(n);
        index_of_max_count(v);
    }
}
```

Here are some results:

- n = 100: 4, 6, 3, 7, 5, 2  (mean = 4.5)
- n = 1000: 7, 4, 8, 5, 3, 10 (mean = 6.17)
- n = 10000: 8, 7, 5, 12, 12, 10 (mean = 9.0)
- n = 100000: 8, 9, 9, 13, 14, 9 (mean = 10.33)
- n = 1000000: 9, 11, 19, 14, 8, 12 (mean = 12.17)

These results are based on random data, so if you were to repeat these trials you won't get exactly the same values. But the means should be similar.

What's surprising about these numbers is how *small* they are, even with very large vectors. They suggest that for large amounts of randomly-ordered data `mi = i` is executed very few times. This is not obvious from the algorithm!

## Visualization

Here's a array of 400 random numbers with a single max value. The red dots show when `mi` changes.

Click the mouse the to re-generate the array.

<iframe src="https://editor.p5js.org/tjdonaldson/full/KniVoMk-2F" width=410 height=450></iframe>
## Practice Questions
1. Give a definition for the *min* of a list, in the same style as the definition for the max of a list.
2. Suppose you have a list of $n$ elements in some unknown order. About how many comparisons would you expect to do to calculate *both* the min and max item? What is the answer when written in [[O-notation]]?
3. Implement a more general version of the max function that returns the max element in the range `v[begin]` to `v[end-1]` (note that `v[end]` is *not* included!):
   ```cpp
   int max(const vector<int>& v, int begin, int end)
   ```
4. In your own words, explain the *seed* for the `rand()` random number generator. How is it set? What happens if you set it to the same value every time? How can you make different random numbers each run of a program?
5. Suppose vector `v` has 5000 `int`s in some unknown order. What is the:
	1. minimum number of times that `mi = i` could be called? Under what conditions would that happen?
	2. maximum number of times that `mi = i` could be called? Under what conditions would that happen?
	3. average number of times that `mi = i` could be called?