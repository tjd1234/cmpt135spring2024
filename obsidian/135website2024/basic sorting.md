Sorting is an important and well-studied topic in computer science. A **sorting algorithm** re-arranges the elements of a vector (or an array, or string, or similar linear data structure) into [[sorted order]], i.e. from smallest to biggest. For simplicity, in these notes we'll stick to sorting a `vector<int>`.

For example, these numbers are in [[sorted order]]:

```
2, 3, 8, 8, 10, 101   // sorted
```

These are not:

```
2, 4, 1, 6, 2, 7, 10   // unsorted
```

Finding the *min* and *max* value of a sorted list is easy: the first value is the min, and the last value is the max. 

*Hundreds* of different sorting algorithms have been created. Most of them can be described by this specification (written as a [[contract]]):

```cpp
// Pre-condition:
//     none
// Post-condition:
//    The elements of v are re-arranged into ascending 
//    order, i.e. v[0] <= v[1] <= ... <= v[n-1].
void sort(vector<int>& v)
```

Note that this modifies `v`. It's called an **in-place** sorting algorithm. You can use it to make an function that doesn't modify the vector:

```cpp
// Pre-condition:
//     none
// Post-condition:
//    Returns a sorted copy of v. 
vector<int> sorted_copy(vector<int> v) 
{
    // v was passed by value, so it is a copy
    // of the original vector
    sort(v);
    return v;
}
```
Of course, `sorted_copy` takes more memory since it stores both the original vector and its sorted copy.

### A Bad Specification of Sorting
Consider this *incorrect* specification of sorting:
```cpp
// Pre-condition:
//     none
// Post-condition:
//    The elements of v are in ascending sorted order, i.e.
//    v[0] <= v[1] <= ... <= v[n-1]
void sort_bad(vector<int>& v)
```
This might sound equivalent to the specification above, but this one is wrong. For example, these implementations fit the post-condition of `bad_sort`, but they are not correct sorting algorithms:
```cpp
void sort_bad_a(vector<int>& v) 
{
   for(int i = 0; i < v.size(); i++) 
   {
      v[i] = 3;  // set all values of v to 3
   }
}

void sort_bad_b(vector<int>& v) 
{
   v.clear();  // removes all elements from v
}
```
Clearly these are not what we mean by sorting. But `sort_bad_a` and `sort_bad_b` both satisfy the specification of `sort_bad`. 

The problem with `sort-bad` is that it misses the requirement that the elements must be *re-arranged*, i.e. the elements must be **permuted**. `bad_sort` does not rule out adding, removing, or changing values in the vector.
## Linear Insertion Sort
[[insertion sort|Linear insertions sort]], or just [[insertion sort]], is a relatively simple sorting algorithm. In practice it is often used for sorting small amounts of data. For larger amounts of data, it is too slow and so other, more efficient, algorithms are used.

Suppose we want to arrange these values into ascending order using [[insertion sort]]:
```
5  6  1  2  4
```
Insertion sort divides the list into a *sorted* part and an *unsorted* part. Initially, only the first element is in the sorted part:
```
sorted    unsorted
     5 |  6  1  2  4
```
The `|` is an imaginary line that shows where the sorted/unsorted parts begin and end.

Insertion sort then repeats the following until the unsorted part is empty:
- Take the *first* element of unsorted and insert it into its correct position in sorted (so that the sorted part is always in [[sorted order|ascending sorted order]]).

Lets trace this on our sample data:
```
5  |  6  1  2  4

5  6  |  1  2  4

1  5  6  |  2  4

1  2  5  6  |  4

1  2  4  5  6  | 
```
Note that finding the correct insertion point requires searching through the sorted part. Typically, we use a variation of [[linear search]] to do this, hence the name *linear* insertion sort. It's also possible to do the insertion using [[binary search]], in which case the [[algorithm]] is called [[binary insertion sort]].
## Implementation of Linear Insertion Sort
Here's an implementation of insertion sort:
```cpp
void insertion_sort(vector<int>& v) 
{
   for(int i = 1; i < v.size(); ++i) 
   {

     // key is the value we are going to insert
     // into the sorted part of v
     int key = v[i];      

     // j points to one position before the 
     // (possible) insertion point of the key;
     // thus, key will eventually be inserted at 
     // v[j + 1]
     int j = i - 1;

     //
     // This loop determines where to insert the key 
     // into the sorted part of v. It does this by 
     // searching backwards through the sorted part 
     // for the first value that is less than, or equal 
     // to, key.
     //
     // This loop combines searching with element 
     // moving. Every time an element bigger than the 
     // key is found, it is moved up one position.
     //
     // It's possible that there is no value in the 
     // sorted part that is smaller than key, in which 
     // case key gets inserted at the very start of v. 
     // This is a special case that is handled by j >= 0 
     // in the loop condition.
     //
     while (j >= 0 && v[j] > key) 
     {
        v[j + 1] = v[j];
        --j;
     }
     // After loop ends this is true: 
     // (j < 0 || v[j] <= key)

     v[j + 1] = key;   // j points to the location 
                       // *before* the one where key 
                       // will be inserted
   }
}
```
While insertion sort is conceptually simple, the details can be tricky to get right and so you should test it carefully on a variety of different inputs.
 
The following function is helpful for testing:
```cpp
// returns true if v is in ascending sorted order, 
// and false otherwise
bool is_sorted(const vector<int>& v) 
{
   // note i starts at 1
   for(int i = 1; i < v.size(); i++)
   {
      if (!(v[i-1] <= v[i])) 
      {
        return false;
      }
   }
   return true;
}
```
Here is a test function:
```cpp
bool insertion_sort_ok(vector<int> v)
{
    insertion_sort(v);
    return is_sorted(v);
}

void test_insertion_sort()
{
    cout << "Calling test_insertion_sort ...\n";
    vector<int> empty = {};
    vector<int> one = {5};
    vector<int> two_a = {2, 7};
    vector<int> two_b = {4, 1};
    vector<int> two_c = {3, 3};
    vector<int> same = {4, 4, 4, 4, 4, 4};
    vector<int> ordered = {-1, 0, 5, 9, 10};
    vector<int> rev = {8, 7, 3, 1, 0, -5};

    assert(insertion_sort_ok(empty));
    assert(insertion_sort_ok(one));
    assert(insertion_sort_ok(two_a));
    assert(insertion_sort_ok(two_b));
    assert(insertion_sort_ok(two_c));
    assert(insertion_sort_ok(same));
    assert(insertion_sort_ok(ordered));
    assert(insertion_sort_ok(rev));
    cout << " ... test_insertion_sort done: all tests passed\n";
}
```

## The Performance of Linear Insertion Sort
How fast is insertion sort? Not very, it turns out. 

To estimate it's performance, note that it will do at most $n-1$ insertions since each insertion removes one item from the sorted. Each insertion also requires doing a [[linear search]] to find out where it is inserted. 

How many comparisons does insertion sort do in the *worst case*? We consider the worst case because it is both useful in practice, and the math is not too complicated.

Suppose that the [[linear search]] part of insertion sort always does the worst-case number of comparisons, i.e. it always searches to the end of the sorted part of the list. If we are sorting 5 numbers, it would go like this:
```
a | b c d e     the 1st element, a, is already in correct position
a b | c d e     1 comparison  to determine where to insert b
a b c | d e     2 comparisons to determine where to insert c
a b c d | e     3 comparisons to determine where to insert d
a b c d e |     4 comparisons to determine where to insert e
```
In total, $0 + 1 + 2 + 3 + 4 = 10$ comparisons are needed in the worst case (in some cases fewer comparisons might be necessary). In general, in the worst case insertion sort does $0 + 1 + 2 + ... + n - 1 = \frac{n(n-1)}{2}$ comparisons to sort $n$ objects. The expression $\frac{n(n-1)}{2} = \frac{1}{2}n^2 - \frac{1}{2}n$ is *quadratic*. When $n$ is big, the low-order term $\frac{1}{2}n$ doesn't make much difference and so we'll ignore it. Thus, when $n$ is big, insertion sort does on the order of $n^2$ comparisons.

This analysis only considers *comparisons*: it ignores the work done when inserting new elements. So lets consider how many numbers are *moved* by insertion sort. Again, to make the analysis easier, we consider the worst case when all of the sorted part of the vector moves up one position. When there are $k$ numbers in the sorted part, the next insertion must move all $k$ of those numbers. As shown above, the sorted part of the vector increases by 1 after every insertion, so the total number of data moves is $1+2+3+\ldots +(n-1) = \frac{n(n-1)}{2}$, which is approximately $n^2$. So, when $n$ is big, insertion sort does about $n^2$ data moves in the worst case.

Whether you count comparisons or data moves (or both), the result is the same: in the worst case, linear insertion sort does about $n^2$ work to sort $n$ items. In practice, this turns out to be quite slow when $n$ is large, and so insertion sort should only be used for sorting a small number of items (maybe a few thousand, depending upon the speed of your computer).

## Faster Sorting: Mergesort
[[mergesort]] is a sorting algorithm that is much more efficient than [[insertion sort]], and variants of it are often used in practice as good general-purposes sorting algorithm.

Suppose you want to sort these 8 elements using [[mergesort]]:
```
4 8 2 1 3 7 6 5
```
You first divide the numbers into a left part and a right part, where the parts are equal in size (or as close to equal in size as possible):
```
        |
  left  |  right
4 8 2 1 | 3 7 6 5        split data into equals halves
        |
```
Second, *recursively* sort the left part and then *recursively* sort the right part to get this:
```
        |
  left  |  right
1 2 4 8 | 3 5 6 7      recursivel sort each half
        |
```
The two parts are sorted, but the entire vector is not sorted. So now we [[Merging|merge]] the parts into a single sorted vector.

[[Merging|merging]] is the process of combining two sorted vectors into one sorted vector. Importantly, it can be done more efficiently then sorting. The basic technique is as follows. Create two pointers, `a` and `b`, initialized to point to the beginning of each half like this:
```
        |
  left  |  right
1 2 4 8 | 3 5 6 7
^       | ^
|         |
a         b
```
Also, create a result vector big enough to hold both halves:
```
        |
  left  |  right
1 2 4 8 | 3 5 6 7
^       | ^
|         |
a         b

result: { }
```
To merge `left` and `right`, compare the elements that `a` and `b` point to, and append a copy of the *smaller* to the end of `result`. Then, increment the pointer to point to the next element. For example, in the above diagram 1 is less than 3, so 1 is appended to `result` and `a` is incremented:
```
  left  |  right
1 2 4 8 | 3 5 6 7
  ^     | ^
  |       |
  a       b

result: { 1 }
```
Next, 2 is smaller than 3, so 2 is appended to `result` and `a` is incremented:
```
  left  |  right
1 2 4 8 | 3 5 6 7
    ^   | ^
    |     |
    a     b
result: { 1, 2 }
```
Next, 3 is less than 4, so 3 is appended to `result` and `b` is incremented:
```
  left  |  right
1 2 4 8 | 3 5 6 7
    ^   |   ^
    |       |
    a       b

result: { 1, 2, 3 }
```
The merge continues in the same way until all the elements in left and right have been appended to `result`:
```
  left  |  right
1 2 4 8 | 3 5 6 7
      ^ |   ^
      |     |
      a     b

result: { 1, 2, 3, 4 }


  left  |  right
1 2 4 8 | 3 5 6 7
      ^ |     ^
      |       |
      a       b

result: { 1, 2, 3, 4, 5 }


  left  |  right
1 2 4 8 | 3 5 6 7
      ^ |       ^
      |         |
      a         b

result: { 1, 2, 3, 4, 5, 6 }


  left  |  right
1 2 4 8 | 3 5 6 7
      ^ |        ^
      |          |
      a          b

result: { 1, 2, 3, 4, 5, 6, 7 }


  left  |  right
1 2 4 8 | 3 5 6 7
       ^|        ^
       |         |
       a         b

result: { 1, 2, 3, 4, 5, 6, 7, 9 }
```
Now the entire vector is sorted.

Here's [[pseudocode]] for [[mergesort]]:
```
mergesort(v)    // v has n elements
   if v is size 0 or 1, then return // base case

   
   h = n / 2                        // split v into 2 equal parts
   left = { v[0], v[1], ..., v[h-1] }
   right = { v[h], v[h+1], ..., v[n-1] }

   left = mergesort(left)           // recursively sort the 2 parts
   right = mergesort(right)
   
   v = merge(left, right)           // combine the 2 parts
```

Here is a C++ implementation of mergesort. It uses a helper function called `slice` to get copies of the left and right part of the vector:
```cpp
// Pre-condition:
//    is_sorted(v)
//    is_sorted(w)
// Post-condition:
//    returned vector is v and w merged, i.e. it is in 
//    ascending sorted order and contains all strings in v and w
vector<int> merge(const vector<int> &v, 
				  const vector<int> &w)
{
    assert(is_sorted(v));
    assert(is_sorted(w));
    vector<int> result(v.size() + w.size(), 0);
    int a = 0;
    int b = 0;
    for (int i = 0; i < result.size(); i++)
    {
        if (a >= v.size())
        {
            result[i] = w[b];
            b++;
        }
        else if (b >= w.size())
        {
            result[i] = v[a];
            a++;
        }
        else if (v[a] < w[b])
        {
            result[i] = v[a];
            a++;
        }
        else
        {
            result[i] = w[b];
            b++;
        }
    }
    assert(is_sorted(result));
    return result;
}

// Returns a new vector<int> containing a copy of the elements of v 
// from v[begin] to v[end - 1].
vector<int> slice(const vector<int> &v, 
				  int begin, int end)
{
    vector<int> result(end - begin, 0);
    for (int i = begin; i < end; i++)
    {
        result[i - begin] = v[i];
    }
    return result;
}

// Pre-condition:
//    none
// Post-condition:
//    v has been sorted into ascending order using mergesort
void mergesort(vector<int> &v)
{
    if (v.size() <= 1)
        return; // base case

    int h = v.size() / 2;
    vector<int> left = slice(v, 0, h);
    vector<int> right = slice(v, h, v.size());
    mergesort(left);
    mergesort(right);
    v = merge(left, right);
}
```

> **Note** This version is not as efficient as it could be: it makes many extra copies of the vector being sorted. But even with all this extra work it still runs quite quickly, usually *much* faster than insertion sort.

In the worst case, [[mergesort]] does about $n \log n$ comparisons, which makes it very efficient. This table shows the expected number of comparisons done by [[mergesort]] and [[insertion sort]]: 

| $n$    | $n\log n$ (mergesort) | $n^2$ (insertion sort) |
|--------|-----------------------|------------------------|
| 10     | 33                    | 100                    |
| 100    | 64                    | 10 000                  |
| 1000   | 9966                  | 1 000 000                |
| 10000  | 132877                | 100 000 000              |
| 100000 | 1660964               | 10 000 000 000            |

For example, to sort one hundred thousand items, [[mergesort]] does about 1.6 million comparisons, while insertion sort does about 10 *billion* comparisons. In other words, insertion sort does *6000 times more work* than [[mergesort]] to sort one hundred thousand items.

In general, to sort a list of $n$ items, mergesort does about $n\log n$ comparisons. In contrast, insertion sort would do about $n^2$ comparisons.

[[Mergesort]] is often used as the starting point for more sophisticated sorting algorithms. For example, [timsort](http://en.wikipedia.org/wiki/Timsort) is a popular a variation of [[mergesort]] that uses various tricks to run faster on partially sorted data. [Timsort](http://en.wikipedia.org/wiki/Timsort) is remarkably intricate (see [the source code](http://svn.python.org/projects/python/trunk/Objects/listobject.c)) and consists of hundreds of lines of carefully crafted code.

## Optional Extra: Quicksort
Another very popular divide-and-conquer sorting algorithm is [[quicksort]]. In practice, it can be more efficient and use less memory than [[mergesort]], although occasionally its performance can degrade if you're unlucky.

Here is a C++ implementation of [[quicksort]]:

```cpp
void swap(int& x, int& y) 
{
    int temp = x;
    x = y;
    y = temp;
}

// returns index of the final location of pivot value
int partition(vector<int>& v, int begin, int end) 
{
    int p = begin;
    for (int i = begin + 1; i < end; ++i) 
    {            
        if (v[i] <= v[p]) 
        {
            swap(v[i], v[p + 1]);
            swap(v[p], v[p + 1]);
            ++p;
        }
    }
    return p;
}

// re-arranges the elements from v[begin] to v[end - 1] such that
// v[begin] <= v[begin + 1] <= ... <= v[end - 1]
void quicksort(vector<int>& v, int begin, int end) 
{
    const int n = end - begin;
    if (n <= 1) return;
    int p = partition(v, begin, end);
    quicksort(v, begin, p);
    quicksort(v, p + 1, end);
}

void quicksort(vector<int>& v) 
{
    quicksort(v, 0, v.size());
}
```

Like [[mergesort]], [[quicksort]] splits the vector it's sorting into two parts, and then recursively sorts them. But, instead of merging the results, [[quicksort]] splits the vector using *partitioning*, which moves all the "small" elements to the left, and all the "big" elements to the right. So once the two halves of the vector are sorted, the entire vector is sorted! If the results of the partitioning are two nearly-equal halves, then [[quicksort]] runs extremely quickly --- typically faster than [[mergesort]]. However, in rare cases when multiple bad partitions (where one side is much bigger than the other) occur, it can slow to a crawl, running at about the same speed as [[insertion sort]].
## Binary Search
Sorted data is extremely valuable. A good demonstration of this is the amazing performance of [[binary search]], an [[algorithm]] that finds the location of an element in a sorted vector:
```cpp
// Pre-condition: 
//    v is in ascending sorted order, i.e.
//    v[0] <= v[1] <= ... <= v[n-1]
// Post-condition: 
//    returns an index i such that v[i] == x
int binary_search(int x, const vector<int>& v)
```
The [[pre-condition]] is essential: binary search only works on data that is in ascending [[sorted order]].

When searching for an element `x` in vector `v`, binary search first looks at the *middle-most* element of the vector. There are three possible cases:

1. **`x` equals the middle-most element**. In this case `x` has been found and binary search immediately returns the position of `x`.
2. **`x` is smaller than the middle-most element**. In this case, *if* `x` is in the vector it must be among the values to the *left* of the middle element, and so binary search is run on this *left* half.
3. **`x` is bigger than the middle-most element**. In this case, *if* `x` is in the vector it's among the values to the *right* of the middle element, and so binary search is run on this *right* half.

What makes this so efficient is that each time a middle-most element is checked,  *half* of the remaining elements are discarded. In contrast, each comparison step in linear search discards only 1 element.

For example, suppose we're searching this sorted vector:
```
4, 5, 8, 11, 15, 20, 21
```
Does it contain 6? Binary search proceeds like this:
```
4, 5, 8, 11, 15, 20, 21
          ^
          |
      check the middle-most element
```
Since 11 is not 6, we know that *if* 6 is in the vector, it must be to the left of 11. Thus we can discard all the elements from 11 to 21:
```
4, 5, 8
   ^
   |
 check the middle-most element
```
Since 5 is not 11, we know that *if* 6 is among these numbers it must be to the right of 5. Thus we can discard 4 and 5:
```
8
^
|
check the middle-most element
```
After checking that 8 is not equal to 6, we are done: we've proven that 6 is *not* in the list of numbers. And it only took *3* comparisons to do this. In contrast, [[linear search]] would have checked that *all* the numbers are not equal to 3, and so would have done *7* comparisons.

Here's an implementation:
```cpp
// Pre-condition:
//    v is in ascending sorted order
// Post-condition:
//    returns an index i such that v[i] == x; if x is
//    not in v, -1 is returned
int binary_search(int x, const vector<int> &v)
{
    int begin = 0;
    int end = v.size();

    while (begin < end)
    {
        int mid = (begin + end) / 2;
        if (v[mid] == x)
        {
            return mid;
        }
        else if (v[mid] < x)
        {
            begin = mid + 1;
        }
        else // v[mid] > x
        {
            end = mid;
        }
    }

    return -1;  // x not found
}
```
The [[algorithm]] is notoriously easy to code incorrectly. For example, this line is easy to get wrong:
```cpp
int mid = (begin + end) / 2;
```
It calculates the mid-point of a range. You can derive it as follows. The length of the range is $end - begin$, and half of that is $\frac{end - begin}{2}$. Since the range starts at $begin$, the mid-point is $begin + \frac{end - begin}{2}$, which simplifies to $\frac{end + begin}{2}$.

If $end - begin$ happens to be odd, then $\frac{end + begin}{2}$ ends with .5, and we simply chop that off (e.g. 34.5 becomes 34). This is not obviously the right thing to do, but if you test it with a few actual values by hand, and write some good tests, you can be pretty confident that it's correct.

Here's a recursive version of [[binary search]]:
```cpp
int binary_search_rec(int x, const vector<int> &v,
                      int begin, int end)
{
    int n = end - begin;

    // if the sub-vector being searched is empty,
    // then x is not in it
    if (n <= 0)
        return -1; // x not found

    int mid = (begin + end) / 2;
    if (x == v[mid])
    {
        return mid;
    }
    else if (x < v[mid])
    {
        return binary_search_rec(x, v, begin, mid);
    }
    else
    {
        return binary_search_rec(x, v, mid + 1, end);
    }
}

// Pre-condition:
//    v is in ascending sorted order
// Post-condition:
//    returns an index i such that v[i] == x; 
//    if x is not in v, -1 is returned
int binary_search_rec(int x, const vector<int>& v) 
{
  return binary_search_rec(x, v, 0, v.size());
}
```
The code is similar in length and complexity to the non-recursive version, and is quite efficient (especially if [[tail call elimination]] is used).

Binary search has a lot of little details that are easier to get wrong, and so it is important to test it carefully:
```cpp
void binary_search_test() 
{
   vector<int> empty;
   vector<int> one = {5};
   vector<int> two = {2, 7};

   assert(binary_search(2, empty) == -1);
   assert(binary_search(2, one) == -1);
   assert(binary_search(5, one) == 0);
   assert(binary_search(0, two) == -1);
   assert(binary_search(2, two) == 0);
   assert(binary_search(4, two) == -1);
   assert(binary_search(7, two) == 1);
   assert(binary_search(10, two) == -1);

   vector<int> v = {1, 5, 7, 8, 10, 13, 14, 20, 25};
   assert(binary_search(8, v) == 3);
   assert(binary_search(10, v) == 4);
   assert(binary_search(13, v) == 5);

   assert(binary_search(2, v) == -1);
   assert(binary_search(9, v) == -1);
   assert(binary_search(21, v) == -1);

   cout << "all binary_search tests passed\n";
}
```
How fast is [[binary search]]? Blazingly fast, as it turns out: for an n-element vector, it needs to check, at most, $\log_2 n$ different values. So, for instance, on a million-element vector [[binary search]] will never do *at most* 20 comparisons (because $\log_2 1000000 \approx 20$).

While [[binary search]] is extremely efficient for searching large amounts of data, it comes with a high price: the vector must be in [[sorted order]]. The problem with sorting is that the fastest general-purpose sorting algorithms are slower than *linear* search. Thus sorting a vector and then calling [[binary search]] is usually slower than just calling [[linear search]]. However, sorting the data once followed by *multiple* binary searches may be faster than lots of linear searches.

> **Did you know that you can drive your car a mile without using only a drop of gas?** Just start at the top of a mile-long hill and roll down. Of course, the hard part is getting your car up there in the first place! Binary search suffers from a similar problem.
## Why is Binary Search so Fast?
Every time [[binary search]] iterates once through its loop, it discards *half* of all the elements of `v`. So if `v` initially has n elements, the number of possible elements that could be equal to `x` decreases in size like this: $n$, $\frac{n}{2}$, $\frac{n}{4}$, $\frac{n}{8}$, ..., $\frac{n}{2^i}$.

Eventually, $2^i$ is bigger than $n$, meaning there are no more elements to consider. We want to know the *first* value of $i$ that makes $\frac{n}{2^i} < 1$. That is, we want to solve for $i$ in this inequality:

$\frac{n}{2^i} < 1 \leq \frac{n}{2^{i-1}}$

Multiplying everything by $2^i$ gives this:

$n < 2^i \leq 2n$

And taking the base-2 logarithm:

$\log_2 n < i \leq \log_2 2n$

Since $\log_2 2n = \log_2 2 + \log_2 n = 1 + \log_2 n$, it further simplifies to:

$\log_2 n < i \leq 1 + \log_2 n$

Thus, `i` is approximately equal to $\log_2 n$.

This result shows that [[binary search]] does about $\log_2 n$ comparisons *in the worst case*. Sometimes it might do fewer, of course, but $\log_2 n$ is small for even big values of $n$. For instance, $\log_2 10^9 \approx 30$, meaning that[[ binary search]] does *at most* 30 comparisons to find a given number in a vector with a *billion* elements.

| $n$     | $\log n$ (approx) |
| ------- | ----------------- |
| 10      | 3                 |
| 100     | 7                 |
| 1000    | 10                |
| 10000   | 13                |
| 100000  | 17                |
| 1000000 | 20                |

> **Fact** The base-2 logarithm $\log_2 n$ of a positive integer $n$ is the least number of bits needed to represent $n$ in binary.
## Practice Questions
1. Given an example of a vector with 5 elements that is in [[sorted order]], and after you reverse it is still in [[sorted order]].
2. State the basic [[pre-condition]] and [[post-condition]] for sorting.
3. Why is the following [[pre-condition]] and [[post-condition]] for sorting *incorrect*?
   ```cpp
   // Pre-condition:
   //     none
   // Post-condition:
   //     v[0] <= v[1] <= ... <= v[n-1].
   void sort(vector<int>& v)
   ```
4. In your own words, describe the basic method that insertion sort uses to sort a list.
5. Implement a variation of `is_sorted` that test if a `vector<int>` is in reverse [[sorted order]].
6. About how many comparisons does insertion do, in the worst-case, to sort $n$ items?
7. Suppose an implementation of insertion sort takes 1 second to sort 5000 items. About how long would you expect it to take to sort 10,000 items? **Hint**: 2 seconds is not the answer!
8. In your own words, describe the basic method that [[mergesort]] sort uses to sort a list.
9. In your own words, describe how two already-sorted lists can be efficiently merged into a single sorted list.
10. In your own words, describe the basic method that [[binary search]] uses to find an element in a sorted list.
11. Suppose `v` is a `vector<int>` with $n$ elements, and we know for a fact that the number 5 is *not* in `v`. How many comparisons must [[binary search]] do to prove that 5 is not in `v`?
12. Suppose [[binary search]] takes 5 seconds in the worst-case to find a target value in a list of $n$ elements. About how many seconds would you expect it to take in the worst case to find a target value in a list with $n^2$ elements?
13. The loop-based and recursive implementations of [[binary search]] have some potential problems.
	1. The statement `int mid = (begin + end) / 2` could fail in some cases. How?
	2. On each iteration or recursive call, *two* comparisons are usually done: `x == v[mid]` and also `x < v[mid]`. How could you get rid of one of these comparisons?
	3. If the `x` occurs more than once in `v`, our [[binary search]] makes no promises about which `x` index it returns. 
