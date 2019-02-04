% run with gecode -O1

include "globals.mzn";

int: n = 3;

array[-1..n+2, -1..n+2] of var 0..1: board; % adding a zero border of size two

constraint forall(i in -1..n+2) ( % making sure they're zero
        board[-1, i] = 0
    /\  board[i, -1] = 0
    /\  board[i, n+2] = 0
    /\  board[n+2, i] = 0

    /\  board[0, i] = 0
    /\  board[i, 0] = 0
    /\  board[i, n+1] = 0
    /\  board[n+1, i] = 0
);

function var int: alive_neighbors(int: i, int: j) = 
    sum(dx, dy in -1..1 where dx != 0 \/ dy != 0) (board[i + dx, j + dy]);

constraint forall(i, j in 0..n+1) ( % 3 alive neighbors forces the cell to be alive too
    alive_neighbors(i, j) = 3 -> board[i, j] = 1
);

constraint forall(i, j in 0..n+1) ( % less than 2 or more than 3 alive neighbors forces the cell to be dead
        alive_neighbors(i, j) < 2
    \/  alive_neighbors(i, j) > 3
    ->  board[i, j] = 0
);

constraint forall(i, j in 0..n+1) ( % if the cell is alive then it must stay alive
    board[i, j] = 1
    ->  alive_neighbors(i, j) = 2
    \/  alive_neighbors(i, j) = 3
);

constraint forall(i, j in 0..n+1) ( % if the cell is dead then it must stay dead
    board[i, j] = 0
    -> alive_neighbors(i, j) != 3
);

% breaking the symmetry
constraint board[1, 1] <= board[n, n];
constraint board[1, n] <= board[n, 1];

solve maximize sum(i, j in 1..n) (board[i, j]);

output ["sum: \(sum(i, j in 1..n) (board[i, j]))\n"] ++ [
    show(board[i, j]) ++
    if j = n then
        "\n"
    else
        " "
    endif
    | i, j in 1..n
];
