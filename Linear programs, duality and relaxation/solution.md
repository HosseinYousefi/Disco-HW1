# Linear programs, duality and relaxation

## 1

Given a bipartite graph $G = (V, E)$. For each edge $e \in E$ we define $x_{e}$ to be whether or not we include this edge in the matching so we have:

$x_{e} \in \{0, 1\} \;(\forall e \in E)$

$\sum_{e \text{ incident to } v}{x_{e}} \leq 1\;(\forall v \in V)$

$\sum_{e \in E}{x_e} \rightarrow \max$

## 2

$y_v \ge 0$

$y_u + y_v \ge 1 \; (\forall uv \in E)$

$\sum_{v \in V}{y_v} \rightarrow \min$

## 3

`set-cover.mzn` and `set-cover-float.mzn` are included. Rounding files are available in `Rounding` directory.
