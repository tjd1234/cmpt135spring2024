## Sending Information Securely
Imagine logging into an online bank. You type your password into a box, press "Submit", your password is sent to the bank across the Internet, and then the bank sends back access to your account.

As your password travels through the Internet to your bank, it passes through various unknown computers along the way. This is normal: any time you send information  the Internet it is handled by computers you personally know nothing about.

So what stops an evil hacker from copying your password as it travels across the internet? If they get your password they can then login to your bank account.

To protect sensitive information like passwords, we **encrypt** it. That means scrambling it in such a way that only someone with the **key** for **decrypting** it can read it. If a bad guy gets a copy of the encrypted password, then they will likely have a hard time figuring the actual unencrypted password.

These days web pages that use `https` automatically encrypt and decrypt information. But is instructive to see how it could be done by hand. For example, suppose `password.txt` contains your bank account password. Before sending it, you can encrypt it using the Linux program `ccencrypt`:

```shell
❯ cat password.txt 
swordfish

❯ ccencrypt password.txt 
Enter encryption key: honeybee
Enter encryption key: (repeat) 

❯ cat password.txt.cpt 
��[��d�d#���3�;4�g�⏎   

❯ ccdecrypt password.txt.cpt 
Enter decryption key: honey

❯ cat password.txt
swordfish
```

> If you want to try `ccencrypt`/`ccdecrypt` yourself, install them in Ubuntu Linux with this shell command: `sudo apt install ccrypt`

Modern encryption tools like `ccencrypt` are pretty good: unless you have the encryption key (i.e. the password string `honeybee`), it's practically impossible to determine the encrypted password. So if an evil hacker gets a copy of your encrypted password, you are probably safe.

> **Careful** If you use an easy-to-guess, or very short, encryption key, then a hacker might be able to figure it out. For instance, if your key is a single English word, then it is relatively easy to guess: a hacker could use a dictionary of all English words to see if any work.
> 
> This is why many websites insist that passwords include special characters, like digits or punctuations. Such passwords are much harder to guess.

### Getting the Key
But there is a problem: how do you communicate the *encryption key* to a site so it can decrypt your password? If you send `password.txt` to your bank, how does it get the encryption key `honeybee`? You have to send them the key somehow, and if you send it unencrypted over the web then hackers could copy it. But if you encrypt the key, then that encryption needs its own key: how do you send *that* key securely? There is no immediately obvious way around this problem.

> One way to get the key to the bank is for you to physically deliver it to them, making sure no one sees it as you go to the bank. While that works, it can be slow, and you can only do it if the bank is geographically near you. Plus changing a password requires going back to the bank.

The [RSA Cryptosystem](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) solves this problem using an idea called [public key cryptography](https://en.wikipedia.org/wiki/Public-key_cryptography). Basically, the *bank* provides a special **public key** that anyone can use to *encrypt* a message. But only the bank is able to decrypt it. The bank does the decryption using a **private key** that they don’t share with anyone else.

We won’t go into the details of how [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) works other than to highlight an intriguing fact: one step of the [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) algorithms requires calculating a large integer power, such as $a^{65537}$. For [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) to be practical, this large power must be calculated quickly.
## Calculating Large Integer Powers
How can you calculate $a^{65537}$ *efficiently*? For our purposes, we define efficiency to be the number of multiplications needed to calculate the answer.
### Some Special Cases
There are a few cases that can be handled individually:

- $a^0$ is 1 if $a \neq 0$
- $0^n$ is 0 if $n \neq 0$
- $1^n$ is 1 if $n \neq 0$
- $0^0 = 1$ ([although sometimes it is said to be undefined](https://en.wikipedia.org/wiki/Exponentiation#Zero_to_the_power_of_zero))

In the following discussing we assume these cases are taken care of, and so won't worry about them any more.
### The Basic Approach (Iterative)
The "basic" way to calculate $a^n$ is to multiple $a$ by itself $n-1$ times. For example, $a^4=a \cdot a \cdot a \cdot a$, a total of *three* multiplications.

Here's an implementation:

```cpp
// Pre-condition: 
//    n >= 0
// Post-condition: 
//    returns a to the power of n, i.e. a^n
int power_iter(int a, int n) 
{
    // check pre-condition
    if (n < 0) cmpt::error("exponent must be non-negative");

    if (a == 0 && n == 0) return 1;
    if (a == 0 && n != 0) return 0;
    if (a != 0 && n == 0) return 1;
    if (a == 1) return 1;
    
    int pow = 1;
    for(int i = 0; i < n; i++) 
    {
        pow *= a;
    }
    return pow;
}
```

Note the use of [[contract|contracts]] to specify what the function ought to do.

> Note that `power_iter` actually does $n$ multiplications. Where does this extra multiplication from from? It's due to the fact that `pow` is initialized to 1, and to get $a^1$ it multiplies this initial 1 by $a$. So the algorithm calculates $1 \cdot a \cdot a \cdot \ldots \cdot a$. In practice, one extra multiplication doesn't make much difference in performance, so we will not worry about here.

Here's the same [[algorithm]] implemented using [[recursion]]:

```cpp
int power_recur(int a, int n) {
    // check pre-condition
    if (n < 0) cmpt::error("exponent must be non-negative");

    if (a == 0 && n == 0) return 1;
    if (a == 0 && n != 0) return 0;
    if (a != 0 && n == 0) return 1;
    if (a == 1) return 1;
    
    return a * power_recur(a, n - 1);
}
```

While the source code is shorter than `power_iter`, it's probably a little less efficient since each call to `power_recur` is pushed onto [[stack memory|call stack]] memory.
### Performance of the Basic Approach
For both the iterative and recursive versions of the basic approach, we can estimate the efficiency as follows: 

- $a^2 = a \cdot a$ does 1 multiplication
- $a^3 = a \cdot a \cdot a$ does 2 multiplications
- $a^4 = a \cdot a \cdot a \cdot a$ does 3 multiplications
- ...
- $a^n = a \cdot a \cdot \ldots \cdot a \cdot a$ does $n-1$ multiplications (for $n > 1$).

In general, the basic approach does $n - 1$ multiplications to calculate $a^n$. 

The *time* it takes to do the calculation is *proportional* to the number of multiplications. For instance, calculating $a^{2n}$ does $2n-1$ multiplications, and so takes about twice the time as $a^n$.

To calculate $a^{65537}$ from above, 65536 multiplications are needed.
## A Faster Algorithm: Repeated Squaring
The basic algorithm calculate $a^n$ in about $n$ multiplications. Can we do better? Is there an algorithm that does fewer multiplications in general?

It turns out there is. Take a look at these calculations:

$a \cdot a = a^2$
$a^2 \cdot a^2 = a^4$

In only 2 multiplications we calculated $a^4$. That's one less than the number of multiplications done by the basic algorithm.

It gets better. For example, $a^4 \cdot a^4 = a^8$, and so to get $a^8$ only 1 more multiplication is needed, for a total of 3 (instead of 7 for the basic algorithm). Similarly, to get $a^{16}$ we can do $a^8 \cdot a^8 = a^{16}$. This calculates $a^{16}$ in only 4 multiplications (instead of 15 for the basic algorithm).

These examples show that **repeated squaring** can, at least when $n$ is a power of 2, calculate $a^n$ using fewer multiplications than the basic algorithm.

But what if $n$ is *not* a power of 2?

There's a trick to make this work with any positive $n$. The idea is distinguish between even and odd values of $n$. When $n$ is *even*, we use the squaring trick; when it's *odd*, we do one extra multiplication, and then a squaring.

More precisely, when $n$ is even we can write it like $n=2k$ (for some positive integer $k$). To calculate $a^{2k}$ we just square $a^k$ (and recursively calculate $a^k$). When $n$ is odd it has the form $n=2k+1$. To calculate $a^{2k+1}$ we re-arrange it like this: $a^{2k+1} = a \cdot a^{2k}$. So to get $a^{2k+1}$ we calculate $a$^{2k}$ as in the previous, and multiply the result by $a$.

Mathematically, the formula can be written like this (assuming $a$ and $n$ are both non-negative integers):

$$
a^n = 
\begin{cases}
0 & \text{if $a = 0$ and $n \neq 0$} \\
1 & \text{if $n = 0$} \\
a^{n/2} \cdot a^{n/2}  & \text{if $n$ is even} \\
a \cdot a^{n/2} \cdot a^{n/2} & \text{if $n$ is odd}
\end{cases}
$$
We can also write this as recursive rules closer in style to programming. To calculate `pow(a, n)`:
1. If $a=0$ and $n \neq 0$, then return 0 (base case)
2. If $n = 0$, return 1 (base case)
3. else if $n$ is even, return `h * h`, where `h` is `pow(a, n/2)`
4. else if $n$ is odd, return `a * h * h` where `h` is `pow(a, (n-1)/2)`

For rules 3 and 4, only one recursive is made in each. It would be mistake to call `pow` twice in these rules, as that would take much more time and memory.

Here's a recursive implementation in C++:
```cpp
int power_recur_fast(int a, int n) 
{
    // check pre-condition
    if (n < 0) cmpt::error("exponent must be non-negative");

    if (a == 0 && n == 0) return 1;
    if (a == 0 && n != 0) return 0;
    if (a != 0 && n == 0) return 1;
    if (a == 1) return 1;

    
    if (n % 2 == 0) 
    {
        int half = power_recur_fast(a, n / 2);
        return half * half;
    } 
    else 
    {
        int half = power_recur_fast(a, (n - 1) / 2);
        return a * half * half;
    }
}
```
### Counting Multiplications
How many multiplications does `power_recur_fast` do? The answer is not immediately obvious from looking at the algorithm. So lets add some code to count multiplications:

```cpp
int mult_count = 0;

int power_recur_fast(int a, int n) 
{
    // check pre-condition
    if (n < 0) cmpt::error("exponent must be non-negative"); 

    if (a == 0 && n == 0) return 1;
    if (a == 0 && n != 0) return 0;
    if (a != 0 && n == 0) return 1;
    if (a == 1) return 1;

    if (n % 2 == 0) 
    {
        int half = power_recur_fast(a, n / 2);
        mult_count += 1;
        return half * half;
    } 
    else 
    {
        int half = power_recur_fast(a, (n - 1) / 2);
        mult_count += 2;
        return a * half * half;
    }
}

void power_test(int a, int n) 
{
    mult_count = 0;
    power_recur_fast(a, n);
	cout << " " << a << "^" << n << ", " 
         << mult_count << " multiplications\n";
}
```

Here's some test code:

```cpp
for(int i = 0; i <= 20; ++i) 
{
    power_test(2, i);
}
```

And its output:

```
2^0, 0 multiplications
2^1, 2 multiplications
2^2, 3 multiplications
2^3, 4 multiplications
2^4, 4 multiplications
2^5, 5 multiplications
2^6, 5 multiplications
2^7, 6 multiplications
2^8, 5 multiplications
2^9, 6 multiplications
2^10, 6 multiplications
2^11, 7 multiplications
2^12, 6 multiplications
2^13, 7 multiplications
2^14, 7 multiplications
2^15, 8 multiplications
2^16, 6 multiplications
2^17, 7 multiplications
2^18, 7 multiplications
2^19, 8 multiplications
2^20, 7 multiplications
```

When $n$ is big, the number of multiplications being done is less then for the basic algorithm.

Look at the sequence of multiplications: 0, 2, 3, 4, 4, 5, 5, 6, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, .... Is there a pattern? Notice that the numbers don't always increase --- sometimes they go down! The numbers don't seem random (they can't be!), but it is tricky to see what pattern the follow.

It turns out to be useful to print a message when each part of the if-statement is called:

```cpp
int power_recur_fast(int a, int n) {
    // check pre-condition
    if (n < 0) cmpt::error("exponent must be non-negative");

    if (a == 0 && n == 0) return 1;
    if (a == 0 && n != 0) return 0;
    if (a != 0 && n == 0) return 1;
    if (a == 1) return 1;

    if (n % 2 == 0) 
    {
       int half = power_recur_fast(a, n / 2);
       mult_count += 1;
       cout << 1;           // print 1
       return half * half;
    }
    else 
    {
       int half = power_recur_fast(a, (n - 1) / 2);
       mult_count += 2;
       cout << 2;          // print 2
       return a * half * half;
    }
}

void power_test(int a, int n) 
{
    mult_count = 0;
    power_recur_fast(a, n);
	cout << " " << a << "^" << n << ", " 
         << mult_count << " multiplications\n";
}
```

The output is:

```
2
21
22
211
212
221
222
2111
2112
2121
2122
2211
2212
2221
2222
21111
21112
21121
21122
21211
 ```

Can you see a pattern in these values?

It might be easier to see if you change 1s to 0s and 2s to 1s:

```
1
10
11
100
101
110
111
1000
1001
1010
1011
1100
1101
1110
1111
10000
10001
10010
10011
10100
```

These are the [[binary number|binary numbers]] from 1 to 20 (!). In addition to (quickly) calculating powers, we've also created an algorithm that generates the [[binary number|binary numbers]].

This observation is the key to counting the total number of multiplications. First note that a 0 means the algorithm does 1 multiplication, and a 1 means it does two. If we know the number of bits in the binary representation of $n$, then we can estimate the number of multiplications done when `power_recur_fast` calculates $a^n$.

When you represent a positive integer $n$ in binary, you need about $\log_2 n$ bits. So, *at worst*, if every bit were a 1, then $2\log_2 n$ multiplications are done. This is *much* smaller than the $n - 1$ multiplications done by the basic algorithm.

 > More precisely, to represent the base-10 number $n$ as an unsigned binary number you need at least $1 + \lfloor \log_2 n \rfloor$ bits. For example, to represent 20 in binary you need at least $1 + \lfloor \log_2 20 \rfloor= 1 + \lfloor 4.32 \rfloor = 1+ 4 = 5$ bits. Indeed, 20 in binary is 5 bits: 10100.
 
So, *in the worst case*, the number of multiplications done by `power_recur_fast` is proportional to $\log_2 n$. This makes it fast enough in practice to calculate large exponents like those needed by the [RSA cryptosystem](http://en.wikipedia.org/wiki/65537_(number)) example at the beginning, e.g. it can calculate $a^{65537}$ using approximately $\log_2 65536 \approx 16$ multiplications. This is more than 4000 times faster than the 65536 multiplications done by the basic algorithm!
## Note
This is an interesting algorithm! The performance is not at all obvious at first, nor is the connection to binary numbers.

You may wonder if this is the fastest way to calculate exponents. And the answer is ... no! For *some* exponents even fewer multiplications are possible. For example, consider $2^{15}$:

- you get $2^{3}$ in 2 multiplications
- then square it to get $2^{6}$ (1 more multiplication)
- then square it to get $2^{12}$ (1 more multiplication)
- then multiply by $2^{3}$ from the first step to get $2^{15}$ (1 more multiplication)

This uses *5 multiplications* in total to calculate $2^{15}$. But the fast recursive algorithm takes 8 multiplications.
## Practice Questions
1. If you were using the basic algorithm in a program, which implementation would you prefer: the iterative (loop) one, or the recursive one? Explain your answer.
2. In the *worst case*, how many multiplications will the basic algorithm and the fast algorithm do to calculate $a^{1000000}$, i.e. $a$ to the power of one million?
3. For `power_recur_fast(a, n)`, it was shown in the notes that in the worst case about $2\log_2 n$ multiplications are needed. But what about the *best* case, when the binary representation of $n$ has just one 1-bit? About how many multiplications are done? And how often does this best case occur for an $n$-bit number?
4. Using the fast power function as a starting point, write a function called `to_binary_string(int n)` that returns the binary representation of `n` as a string of `0`s and `1`s.
