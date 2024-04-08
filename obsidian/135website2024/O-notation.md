
**O-notation**, also known as **asymptotic notation**, or **order notation**, is a mathematical notation for discussing [[algorithm]] performance. It is commonly used both in the theoretical analysis of [[algorithm|algorithms]], and in practical programming for estimating running-times.
## Algorithms and Input
To analyze [[algorithm|algorithms]] mathematically, we usually make simplifying assumptions. First, we assume that we are considering an [[algorithm]] $A$ takes input of size $n$. Typically, this input is a sequence, such as an array or vector or string, with $n$ elements. We assume $A$ runs for a *finite* amount of time, i.e. that it eventually stops and returns a result.

For example, [[linear search]] is an algorithm that takes $n$ elements and a target value $x$ as input, and returns the index location of an element that equals $x$. If $x$ is not in the list, -1 is returned. We might write in [[pseudocode]] like this:

1. linear_search({$a_1$, $a_2$, $\ldots$, $a_n$}, $x$)
2. $i \leftarrow 1$
3. if $a_i = x$ then return $i$
4. if $i = n$ then return $-1$
5. $i \leftarrow i + 1$
6. go to step 3

It's usually more readable to use [[pseudocode]] instead of C++. The line numbers make it easy to refer to specific lines.
## Measuring Running Time
Since we are interested in how quickly [[algorithm|algorithms]] run, you might think that we would use real time --- such as seconds or microseconds --- to measure performance. We certainly judge real-world software as being fast or slow by how much time it takes.

But real time is difficult to measure for programs because different computers run at different speeds. They may have different CPUs, different amounts of memory, or just be doing other things at the same time (e.g. playing a video, receiving email, etc). To fairly compare programs, we'd have to make sure they are run in the same conditions, on *exactly* the same computer, with *exactly* the same software, etc. That is easier said than done.
## Key Operations
So, to avoid these problems, computer scientists will often estimate an [[algorithm]]'s running time by measuring the *work* it does. And this work is estimated by *counting* how many times it executes a chosen [[key operation]]. A [[key operation]] is typically the most frequently executed instruction in an [[algorithm]]. The main advantage of this approach is that it is independent of hardware and software details, and it can even be applied to [[algorithm|algorithms]] written in [[pseudocode]].

It's important to choose a sensible [[key operation]] that reflects the work the algorithm does. It should give us a good estimate of the algorithms running time. For example, in [[linear search]] above, there are a couple of reasonable choices for the [[key operation]]:

- item comparison using $=$
- item accesses, i.e. a call to $a_i$ corresponds accessing an element of an array or vector
- variable assignments using $\leftarrow$

Usually, item **comparisons**, i.e. calls to $=$ or $\leq$, are the [[key operation]] for sorting and searching algorithms.

An example of a **bad** choice of [[key operation]] for linear search would be the number of times `return` is called. `return` is called exactly once, no matter how big $n$ is. This is not helpful because the running-time of linear search gets longer when $n$ is big, but the number of times `return` is called never changes.
## Algorithm Running Time
We will refer to the key instruction count in an [[algorithm]] as its **running time**. Keep in mind that even though we call this *time*, it is not actual time --- it is just a count of how many times the key instruction is executed.

Care must be taken when comparing the running times of [[algorithm|algorithms]] with different key operations. For example, comparing two strings may take longer than comparing two integers, and so 1000 string comparisons may take longer than 1000 integer comparisons. 

> It's bit like comparing money: if you have $1000 Canadian and $1000 American, it's incorrect to say that you have $2000 in total.

We should also be clear if we are talking about the **best case**, **average case**, or **worst case** running time. In practice, the average case and worst case running times are usually the most useful.
## O-Notation
Getting precise instruction counts of even simple [[algorithm|algorithms]] is often difficult, and the mathematical expressions can be complicated. Further, simple [[key operation|key operations]], such as comparisons or additions, can be done so quickly on most computers that there is often little practical difference between [[algorithm|algorithms]] that do, say, $5n + 1000$ or $n$ operations.

For these reasons we often *approximate* algorithm instruction counts by ignoring everything except their high-order term.

Roughly speaking, **O-notation** says that the **order** of a mathematical expression is its biggest term, with constants and low-order terms ignored. For example, we say that the expression $2n-5$ is in $O(n)$, and that $25n^7 -4n^3 + 20$ is in $O(n^7)$.

When adding O-notation expressions, the result is, intuitively-speaking, the *max* of the expressions. For example, $O(\log n) + O(n)$ is $O(n)$, and $O(n) + O(n^2) + O(n^3)$ is $O(n^3)$.

It's easy to determine the high-order term of polynomials. For example, all of these expressions are in $O(n^2)$:
- $n^2$
- $n^2+100$
- $n^2-100$
- $n + 2n^2$
- $\frac{1}{2}n^2 - 500n + 700$

If you say that a particular [[algorithm]] runs in $O(n^2)$ time, then that means the [[key operation]] count can be described by some expression from $O(n^2)$ (but we don't know which one).

Intuitively, $O(n)$ is the *set* of all mathematical expressions of a single variable $n$ whose highest-order term is $n$, or lower. Similarly, $O(n^3)$ is the set of all expressions whose highest order term is $n^3$, or lower; thus $O(n)$ is a *subset* of $O(n^3)$.

The expression $45n - 80$ is in both $O(n)$ and in $O(n^3)$. We say that $O(n)$ is **tighter** than $O(n^3)$.  In practice, we usually want to know the *tightest* O-notation description for an expression since saying something like "$2n$ is $O(n^{3})$" is true but not as informative as saying "$2n$ is $O(n)$".

Here's one more intuitive way for think about O-notation: it is like *less than or equal* but for functions. For instance, if you say $f(n)$ is $O(g(n))$, it is, intuitively, like saying "$f(n)$ if less than, or equal to, $g(n)$ for the key instruction". Or: "$f(n)$ is, at most, $g(n)$".

Here is a more precise definition of O-notation:

> **Definition of O-notation.** [[Algorithm]] $A$ is order $f(n)$, written $O(f(n))$, if there exist fixed constants $k$ and $n_0$ such that $A$ requires no more than $kf(n)$ key operations to process an input of size $n \geq n_0$.

This definition lets us rigorously prove all the basic facts about O-notation alluded to above. We won't go into the proofs in this course.
## O-notation Applied to Algorithms
In practice, these are the most common O-notation expressions that you should know:

| O-expression  | Name         | Example                   |
|---------------|--------------|---------------------------|
| $O(1)$        | constant     | $1, 10, 34, 3538, \ldots$ |
| $O(\log n)$   | logarithmic  | $8\,\log_2 n + 5$         |
| $O(n)$        | linear       | $29n+5, n-9000$           |
| $O(n \log n)$ | linearithmic | $n\,\log_3 n + 23n - 4$   |
| $O(n^2)$      | quadratic    | $7n^2 - 4n + 22$          |
| $O(n^3)$      | cubic        | $n^3 + 2n^2 + 22n + 1$    |
| $O(2^n)$      | exponential  | $3^n + n^4 - 2n^2 + 80$   |
For example:

- Finding the minimum value in an *unordered* vector of $n$ elements using the standard algorithm always does $n-1$ comparisons, and $n-1$ is in $O(n)$. So we say that the standard min-finding algorithm does $O(n)$ comparisons, or just that it is $O(n)$.
- Finding the minimum value in a *sorted* vector is easy: it is the first element of  the list. No matter how big $n$ is, returning the first element takes a fixed amount of work. So we say that finding the min of a sorted $n$-element vector requires at most $O(1)$ work, i.e. it is a *constant  time* algorithm whose performance doesn't depend on $n$.
- [[linear search]] does $O(n)$ comparisons in the average/worst case, and so we say it is a **linear**-time [[algorithm]]. In the best case, linear search does only 1 comparison, and so in that case, it is $O(1)$, i.e. constant time.
- [[Insertion sort]] does $O(n^2)$ comparisons in the worst-case and average-case, and so it is a **quadratic**-time [[algorithm]]. In the best case (e.g. when the data is already sorted), [[insertion sort]] only does $O(n)$ comparisons, and so it is linear, i.e. $O(n)$ in that case.
- [[Quicksort]] does $O(n \log n)$ comparisons in the average case, but degrades to $O(n^2)$ in the worst case. The worst-case occurs very rarely, and so many programmers --- perhaps unwisely --- treat it as if it did $O(n\log n)$ comparisons in all cases.
 - Another important sorting algorithm is [[mergesort]] is also $O(n \log n)$ comparisons in *all* cases, even the worst case. However, compared to [[quicksort]], [[mergesort]] uses about twice as much memory, and is usually a little slower on average.
- [[Binary search]] does $O(\log\,n)$ comparisons in the worst-case and average-case (in the best case it does only 1 comparison). Thus it is a **logarithmic** [[algorithm]]. This is not quite as good as $O(1)$, but in practice logarithmic algorithms are often extremely fast.

  > **Note** The base of a logarithm doesn't matter when we describe it with O-notation: $\log_a x$ and $\log_b x$ differ only by a constant factor, and so they are both $O(\log n)$.

## Two or More Algorithms in a Row
Real-world programs often do multiple functions calls in a row. For example, if `f(n)` does $O(n^3)$ operations in the worst case, and `g(n)` does $O(n\log n)$ operations in its worst case, then how many operations does calling `f(n)` followed immediately by `g(n)` do in the worst case?

Since `f(n)` is $O(n^3)$, that means there is a polynomial with a highest-order term of $n^3$ that describes the running time of `f(n)`. Since O-notation lets us ignore constants and low-order terms, we can assume `f(n)` does $n^3$ operations. Similarly, since `g(n)` does $O(n\log n)$ comparisons, we can treat it as if it does $n \log n$ operations.

So if we run `f(n)` and then `g(n)`, that's about $n^3 + n \log n$ operations in total. Since $n^3$ is the high-order term of *that* expression, and O-notation lets us ignore constants and lower-order terms, we can say the sequence of two function calls does $O(n^3)$ [[key operation|key operations]] in total.

In general, when we run two [[algorithm|algorithms]] in a row one after the other, the total running-time equals the running time of the individual [[algorithm]] with the highest-order running time. So, for example, suppose you sort an n-element list using [[insertion sort]] and then search it using [[binary search]]. [[Insertion sort]] does $O(n^2)$ comparisons, and [[binary search]] does $O(\log n)$ comparisons, and so in total both operations together do $O(n^2)$ operations, i.e. the higher-order of the two terms.

So, overall, from the point of view of O-notation, a sequence of operations is only as fast as its slowest individual operation.

## Examples
**Example 1.** Suppose `v` is a vector of `n` items, and you sort it and then reverse it:

```
sort(v)
reverse(v)
```
In O-notation, what is the worst-case performance of this code?

If `sort(v)` is, say, insertion sort, then the total work is $O(n^2)$ , then the code does $O(n^2) + O(n)$ work in total (reversing `v` can be done in worst-case $O(n)$ time). When adding O-notation expressions, the intuitive idea is to "take the biggest". So $O(n^2) + O(n)$ is $O(n^2)$.

If `sort(v)` is instead mergesort, then it does $O(n \log n)$ comparisons. The overall code than does $O(n \log n) + O(n)$ work, or $O(n \log n)$ work.

This shows that the two lines of code is dominated by the run-time of `sort`. So if you want to make this code faster when `n` is big, improving the speed of `sort` is probably your best bet.

**Example 2.** Assuming `v` is a vector of `n` items, how much work does this code do?

```
mergesort(v)
for i = 1 to 1000 do
	x = some target value
	binary_search(v, x)  // look for x in v
end
```
Mergesort does $O(n \log n)$ work, and binary search does $O(\log n)$ work (we assume getting the target value `x` is insignificant). But binary search is done 1000 times, and so the overall work is $O(n \log n) + 1000 \cdot O(\log n)$. So, in terms of O-notation, the overall work done can be written $O(n \log n)$. O-notation throws away constant like 1000.

Of course, in practice, a piece of code that runs 1000 times faster or slower than another one could be a big deal and make all the difference in practice. But O-notation is a theoretical tool, and it is only accurate when $n$ is big enough. If a piece of code is $O(n \log n)$, then that means that, when $n$ is big enough, the code runs in no more than about $n \log n$ time. The "when $n$ is big enough" is essential: it is what lets O-notation throw away constants. Since $n$ can be arbitrarily large, it will eventually get bigger than any constant value.

**Example 3**. Algorithm A takes 3 seconds in the worst case to process 5000 items. How long will it take, in the worst case, for A to process 10,000 items?

- If A is $O(n)$, then processing 10,000 items will take about $2 \cdot 3 = 6$ seconds. That's because when you double $n$, the running time doubles because it is linear.
- If A is $O(n^2)$, then processing 10,000 items will take about $4 \cdot 3 = 12$ seconds. When you double `n`, then running time becomes $(2n)^2 = 4n^2$, i.e. 4 times as much as for $n$. items.
- If A is $O(n^3)$, then processing 10,000 items will take about $8 \cdot 3 = 12$ seconds. When you double `n`, then running time becomes $(2n)^3 = 8n^2$, i.e. 8 times as much as for $n$. items.
- If A is $O(2^n)$, then processing 10,000 items will take about $3^2 = 9$ seconds. When you double `n`, then running time becomes $2^{2n} = (2^n)^2$, i.e. square of the time it takes for $n$. items.
- If A is $O(1)$, then processing 10,000 items will take about 3 seconds. Since A is $O(1)$, that means its running time does *not* depend on $n$, and we can assume that it is the same for any value of $n$. For instance, if A finds the min of an already-sorted array, then it will do this the same amount of time no matter how many elements are in the array.

## Practice Questions
1. Besides run-time performance, what are three other kinds of questions that computer scientists may be interested in asking about an [[algorithm]]?
2. When analyzing [[algorithm|algorithms]], why do we usually write them in [[pseudocode]] instead of an actual programming language?
3. What are three reasons why it can be difficult to measure the real-time performance of an [[algorithm]]?
4. What is a [[key operation]]?
5. What is the usual [[key operation]] for searching and sorting algorithms?
6. Give an example of an [[algorithm]] whose [[key operation]] is addition.
7. What are the three main running-time cases in [[algorithm]] analysis? Which is usually the *least* important in practice?
8. Why is it often difficult to compare the running-times of [[algorithm|algorithms]] that have different [[key operation|key operations]]?
9. Write the simplest and tightest O-notation expression for each of the following:

   1. 25
   2. $n - 100$
   3. $500n + 3000$
   4. $4n^2 - 8000n - 5000$
   5. $n^2 + 1$
   6. $n^3 + n^2 + n + 1$
   7. $n^4 - 5000n^3 + 20n^2 + \log_4\,n - 143$
   8. $2^{n} + n^{10} - 25n^2$

10. For each of the following, name, or briefly describe, an [[algorithm]] that has the given performance characteristics; give a different [[algorithm]] for each question:
     1. $O(1)$ in its worst case
     2. $O(1)$ in its best case, but $O(n)$ in its worst case
     3. $O(n \log\,n)$ in the average case, but $O(n^2)$ in its worst case
     4. $O(n^2)$ in all cases (best, average, and worst)
     5. $O(n \log n)$ in its best case
     6. $O(2^n)$ in its worst case

11. Name two different sorting [[algorithm|algorithms]] that do $O(n \log\,n)$ comparisons in the average case.
12. Suppose `f(n)` has a worst-case running time of $O(n^2)$, and `g(n)` has a worst case running time of $O(500n+2000)$. What is the tightest O-expression that describes the worst-case running time of calling `f(n)` and then `f(n)`?

[[O-notation practice question solutions]].
