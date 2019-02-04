% run with gecode -O1

include "globals.mzn";

int: n = 20;

array[1..n, 1..n] of var {-1, 1}: matrix;

function var int: dot_product_row(int: i, int: j) =
    sum(x in 1..n) (matrix[i, x] * matrix[j, x]);

function var int: dot_product_col(int: i, int: j) =
    sum(x in 1..n) (matrix[x, i] * matrix[x, j]);

constraint forall(i, j in 1..n where i < j) ( % dot product of each row should be zero
    dot_product_row(i, j) = 0
);

constraint forall(i, j in 1..n where i < j) ( % dot product of each column should be zero
    dot_product_col(i, j) = 0
);

% breaking the symmetry

% we can fix the top row to be all ones, and the rest of the matrix can be changed accordingly
% cause inverting all column does not change anything
constraint forall(i in 1..n) (
    matrix[1, i] = 1
);

% changing the order of columns does not change anything
% so we can say that the second row is non-increasing
constraint forall(i in 1..n-1) (
    matrix[2, i] >= matrix[2, i+1]
);


% changing the order of rows does not change anything
% so we can say that the first column is non-increasing
constraint forall(i in 1..n-1) (
    matrix[i, 1] >= matrix[i+1, 1]
);

solve satisfy;

output [
    show(matrix[i, j]) ++
    if j = n then
        "\n"
    else
        "\t"
    endif
    | i, j in 1..n
];
