int: n_elements;
int: n_sets;

array[1..n_sets] of int: costs;
  
array[1..n_sets] of set of 0..n_elements-1: sets;

array[1..n_sets] of var float: chosen;

constraint forall(i in 1..n_sets) (
    chosen[i] >= 0 /\ chosen[i] <= 1
);

constraint forall(i in 0..n_elements-1) (
    sum(j in 1..n_sets)((i in sets[j]) * chosen[j]) >= 1
);

solve minimize sum(i in 1..n_sets) (costs[i] * chosen[i]);

output ["\(chosen[i]) " | i in 1..n_sets];
