* Use C++17 or later standards to compile.

* Meeting 1 with (b1,e1) and meeting 2 with (b2,e2) overlap if:
  * Meeting 1 starts before meeting 2 ends (b1<e2), and
  * Meeting 2 starts before meeting 1 ends (b2<e1)

* One way to find schedule conflicts is to check the above two conditions for any two meetings. This approach is O(N^2) in time.

* Another approach that is O(NlogN) in time is implemented in this repository.
  * Enumerate all end points of all intervals in an array.
  * Sort the array in order of increasing time. This is the O(NlogN) operation.
  * Sweep through the sorted array and check, when a new meeting starts, if there is another meeting that has started but not yet ended. In such a case, the two meetings overlap. This is O(N) operation.
