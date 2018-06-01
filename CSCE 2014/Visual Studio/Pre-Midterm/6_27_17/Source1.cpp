
//SMALL
// 1) Bubble Sort
// Repeatedly swap adjacent elements if they are out of order
// O(N^2) - worst case
// O(N) - best case (array is already sorted)

// 2) Selection SOrt (The Claw)
// pick largest and swap in last position
// O(N^2) - worst case
// 0(N^2) - best case
// use when data is small and random

// 3) Insertion Sort (Poker)
// Start with one card, when new card arrives, swap with adjacent
// elements until its in the correct posisiton
// O(N^2) - worst case
// O(N) - best case (data is already sorted)

//MEDIUM
// 4) Quick Sort (N/A)
// Partition O(N)
// O(N * log(N)) - average
// O(N^2) - worst case

// 5) Merge Sort (ZIPPER)
// DOES REQUIRE AN EXTRA ARRAY
// Divide your array into atomic pieces (size 1, 2), MERGE, 
// O(N * log(N)) - worst case
// O(N * log(N)) - bast case

//FAST
// 6) Radix Sort (GRANDPA)
// Sort based on MSD -> LSD. One pass for each digit
// O(N)
//

// 7) Bucket Sort
// O(N)

// 8) Counting Sort
// O(N)
// 4 4 3 2 6 7 8 9 1