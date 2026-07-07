# Fixed Size Sliding Window Documentation

This note explains the different **window manipulation techniques** used inside:

- `find_all_anagram.cpp`
- `premutaion_in_string.cpp`
- `Subarray_equal_to_threshold.cpp`
- `substring_of_size_3.cpp`
- `Vowel_substring_of_given_lengh.cpp`
- `max_point_can_obtain.cpp`

---

## 1. What is a fixed size sliding window?

A fixed size sliding window means:

- we always keep a window of length `k`
- we move that window one step at a time
- when one new element enters from the right, one old element leaves from the left

General idea:

```cpp
add incoming element
if (window size becomes k) {
    process current window
    remove outgoing element
    move left
}
```

or sometimes:

```cpp
build first window of size k
for every next step:
    remove old element
    add new element
    process current window
```

Even though all these are fixed-size windows, the **thing that changes from problem to problem** is:

- what data we maintain inside the window
- when we shrink
- how we check whether the current window is valid or optimal

---

## 2. Main types of window manipulation in this folder

There are 6 main patterns in this folder.

### Type 1: Grow window, and when size becomes more than `k`, shrink from left

Files:

- `find_all_anagram.cpp`
- `premutaion_in_string.cpp` (Approach 1)

### How it works

- Keep two pointers `l` and `r`
- Expand by moving `r`
- Add `s[r]` into the window data
- If window size becomes more than `k`, remove `s[l]` and move `l`
- When window size is exactly `k`, check answer

Template:

```cpp
while (r < n) {
    add(arr[r]);

    if (r - l + 1 > k) {
        remove(arr[l]);
        l++;
    }

    if (r - l + 1 == k) {
        process current window;
    }

    r++;
}
```

### Why use this version?

- It is the most natural sliding window template
- Good for beginners
- Easy to extend later to variable-size window problems

### In these files

#### `find_all_anagram.cpp`

Window data:

- `check[26]` = frequency of current window
- `freq[26]` = frequency of pattern

Window check:

- if `check == freq`, then current substring is an anagram

Shrink meaning:

- remove the leftmost character count

#### `premutaion_in_string.cpp` Approach 1

Exactly same style as anagram problem.

Difference:

- instead of collecting all valid starting indices, it returns `true` as soon as one valid window is found

---

### Type 2: Process the window exactly when size becomes `k`, then immediately slide it

Files:

- `Subarray_equal_to_threshold.cpp`
- `Vowel_substring_of_given_lengh.cpp`

### How it works

- Expand using right pointer
- Keep adding current element
- As soon as size becomes exactly `k`, process answer
- Immediately remove left element and move left
- So the next iteration naturally forms the next window

Template:

```cpp
for (int r = 0; r < n; r++) {
    add(arr[r]);

    if (r - l + 1 == k) {
        process current window;
        remove(arr[l]);
        l++;
    }
}
```

### Why this version is nice

- No separate `> k` case
- Very clean for fixed-size window problems
- Easy when every valid window must be processed once

### In these files

#### `Subarray_equal_to_threshold.cpp`

Window data:

- current sum of the window

Window check:

- if `sum >= k * threshold`, then average is at least threshold

Shrink meaning:

- subtract `arr[left]` from sum

Main insight:

- average condition is converted into a sum condition
- this makes updates easy during sliding

#### `Vowel_substring_of_given_lengh.cpp`

Window data:

- count of vowels inside current window

Window check:

- update `maxcnt = max(maxcnt, cnt)` when size reaches `k`

Shrink meaning:

- if `s[left]` is a vowel, decrement vowel count

Main insight:

- we do not care about exact characters, only about how many vowels are inside the window

---

### Type 3: Pre-build the first full window, then slide by one step using incoming and outgoing elements

Files:

- `premutaion_in_string.cpp` (Approach 2 and Approach 3)

### How it works

- First create the first valid window of size `k`
- Compare or process it
- Then for every next step:
  - add incoming element
  - remove outgoing element
  - compare again

Template:

```cpp
build first window
process first window

for (int i = k; i < n; i++) {
    add(arr[i]);
    remove(arr[i - k]);
    process current window;
}
```

### Why use this version?

- Best when the window size is always fixed and known
- Often shorter than the classic `l, r` version
- Makes the incoming/outgoing transition very explicit

### Difference between Approach 2 and Approach 3 in that file

#### Approach 2

- Uses a `for` loop
- outgoing element is written as `i - k`
- compact and formula-based

#### Approach 3

- Uses two explicit indices
- one pointer says which element leaves
- one pointer says which element enters
- easier to visualize for some learners

Both are doing the same window movement:

- one character leaves
- one character enters
- window length remains fixed

---

### Type 4: Fixed window with frequency map comparison

Files:

- `find_all_anagram.cpp`
- `premutaion_in_string.cpp`

This is not about pointer movement only, but about **what the window stores**.

### Window data

- a frequency array of size 26 for lowercase letters

### Why frequency array is enough

For anagrams/permutations:

- order does not matter
- only count of each letter matters

So if current window frequency equals pattern frequency, then:

- same letters are present
- same number of times
- therefore current window is a valid permutation/anagram

### Manipulation when window slides

- add new character count
- remove old character count
- compare arrays

This pattern appears often in string fixed-window problems.

---

### Type 5: Fixed window with duplicate tracking instead of full rechecking

File:

- `substring_of_size_3.cpp`

### Problem idea

We need to count substrings of size 3 with all distinct characters.

### How this window is manipulated

- add `s[r]`
- if a character count becomes 2, increase duplicate counter `dup`
- once window size reaches 3, check whether `dup == 0`
- then remove `s[l]`
- if its count changes from 2 to 1, duplicate problem is gone, so decrease `dup`

### Why this is different

In anagram problems we compare two full frequency arrays.
Here we do not need that.

We only need one yes/no property:

- does the current window contain any duplicate character?

So instead of checking the whole map every time, we maintain a smarter summary value:

- `dup = number of characters currently causing duplication`

### Main learning

Sometimes the window should not store the whole answer.
It should store just enough information to test the condition quickly.

---

### Type 6: Fixed window on a transformed view of the problem

File:

- `max_point_can_obtain.cpp`

This is the most different one in the folder.

### Original problem

Pick exactly `k` cards from either:

- the front
- or the back

At first this does not look like a normal sliding window over one contiguous subarray.

### Hidden sliding-window idea

If you take some cards from the left and the rest from the right,
then the chosen cards always form a combination like:

- first `x` cards from front
- last `k - x` cards from back

So instead of checking every pick from scratch, we do this:

1. start with taking all `k` cards from the front
2. one by one:
   - remove one card from the left-picked part
   - add one card from the right-picked part
3. keep the best total

### Window manipulation here

This is not a normal contiguous window inside the array.
It is more like a **choice window exchange**:

- one chosen front card leaves
- one chosen back card enters
- total chosen count remains `k`

### Why this still belongs to sliding window thinking

Because the update rule is still local:

- subtract one outgoing value
- add one incoming value
- recompute answer in O(1)

### Main learning

Sliding window is not only about contiguous middle subarrays.
Sometimes the trick is to transform the problem into:

- keep a fixed-size chosen set
- replace one element at a time

---

## 3. Quick comparison of all window styles in this folder

### Pattern A: `> k` then shrink

Used in:

- `find_all_anagram.cpp`
- `premutaion_in_string.cpp` Approach 1

Best when:

- you want a universal left-right template
- you are comfortable checking window size dynamically

---

### Pattern B: `== k` then process and immediately remove left

Used in:

- `Subarray_equal_to_threshold.cpp`
- `Vowel_substring_of_given_lengh.cpp`

Best when:

- every valid window of exact size `k` must be processed once
- you want a very clean fixed-window loop

---

### Pattern C: build first window, then incoming/outgoing swap

Used in:

- `premutaion_in_string.cpp` Approach 2
- `premutaion_in_string.cpp` Approach 3

Best when:

- window size is fixed from the start
- you want to think in terms of one element entering and one leaving

---

### Pattern D: maintain summary state instead of rechecking full window

Used in:

- `substring_of_size_3.cpp`
- `Vowel_substring_of_given_lengh.cpp`
- `Subarray_equal_to_threshold.cpp`

Examples of summary state:

- sum of window
- count of vowels
- duplicate counter

Best when:

- you can compress the condition into one running value
- full recheck would be wasteful

---

### Pattern E: transformed fixed choice window

Used in:

- `max_point_can_obtain.cpp`

Best when:

- the problem does not look like a standard sliding window at first
- but answer can be updated by removing one chosen value and adding one new chosen value

---

## 4. How to decide what to store inside a fixed window

Whenever you see a fixed-window problem, ask these questions:

### 1. What makes a window valid or good?

Examples:

- average >= threshold
- all characters distinct
- same frequency as pattern
- maximum number of vowels

### 2. What is the smallest information needed to test that condition quickly?

Examples:

- just the sum
- just vowel count
- full frequency array
- duplicate counter

### 3. When the window moves by one step, how can I update that information in O(1)?

Usually:

- add effect of incoming element
- remove effect of outgoing element

That is the heart of sliding window.

---

## 5. Master template for fixed-size window

```cpp
int l = 0;
for (int r = 0; r < n; r++) {
    add(arr[r]);

    if (r - l + 1 == k) {
        process current window;
        remove(arr[l]);
        l++;
    }
}
```

For strings with frequency arrays:

```cpp
vector<int> need(26, 0), window(26, 0);

for (char ch : pattern) need[ch - 'a']++;

int l = 0;
for (int r = 0; r < s.size(); r++) {
    window[s[r] - 'a']++;

    if (r - l + 1 == pattern.size()) {
        if (window == need) {
            // valid window
        }
        window[s[l] - 'a']--;
        l++;
    }
}
```

---

## 6. Final takeaway

All fixed-size sliding window problems in this folder follow the same base rule:

- one element enters
- one element leaves
- the window length stays constant

The real difference is not the pointers.
The real difference is **what information you maintain while the window moves**.

In this folder, that maintained information is:

- character frequency array
- sum
- vowel count
- duplicate count
- exchanged front/back score

If you understand that part, then most fixed window problems start feeling like the same technique in different clothes.
