# rc
Repository for the Complex Networks 2016/2017 course at IST, University of Lisbon.

## Metrics
Pick a metric and implement it. Try to find the original source for the
algorithms you choose. That would be good great to put in the report.

### Graph metrics

- [ ] **Degree distribution** [#1](https://github.com/rodamber/rc/issues/1)
- [ ] **Average path length** [#2](https://github.com/rodamber/rc/issues/2)
  - Note: path lengths from a node can be computed using a BFS if the graph is
    unweighted.
- [ ] **Clustering coefficient** [#3](https://github.com/rodamber/rc/issues/3)

### Vertex centrality metrics

- [ ] **Closeness centrality** [#4](https://github.com/rodamber/rc/issues/4)
- [ ] **Betweeness centrality** [#5](https://github.com/rodamber/rc/issues/5)
- [ ] **PageRank** [#6](https://github.com/rodamber/rc/issues/6)
- [ ] Eigenvector centrality
- [ ] Katz centrality
- [ ] Harmonic centrality

## Models
After implementing some metrics we can apply them to some graphs following some
specific models and verify that the results are consistent with what we learnt
in the lectures (like the degree distribution is binomial or follows a power
law, the model follows an ultra-small world regime, etc).

This section could enrich the report with a lot of data and insights.

Some example models,

- Erdos-Renyi model (random model)
- Watts-Strogatz small world model
- Barabasi-Albert model
- ...
