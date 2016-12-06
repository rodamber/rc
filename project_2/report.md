# Layered Label Propagation: Coordinate-free Node Ordering Method for Graph Compression

**Professor**: Francisco João Duarte Cordeiro Correia dos Santos

**Group**: 10

**Students**:

  - Gonçalo Cardoso Gaspar (58803)
  - João Nuno Estevão Fidalgo Ferreira Alves (79155)
  - Rodrigo André Moreira Bernardo (78942)

## Abstract

We present a summary of how Layered Label Propagation (LLP), a highly scalable,
coordinate-free, graph reordering algorithm, uses community finding techniques
to permute very large immutable graphs, with applications to graph compression.

## Introduction

Real-world networks are rich with information that can be gathered through graph
mining techniques. Cases of study are friendship relations or community finding
in social networks, cooperation networks in scientific co-authorships or
protein-protein interactions.

Obtaining this kind of informations becomes a real implementation problem when
the subjacent graph has millions or billions of nodes, since most of the
standard graph mining algorithms assume that the graph is stored in main memory,
which may not be the case. This can be witnessed, for example, in the web graph
which describes the directed links between pages of the addressable World Wide
Web, or when regarding the most used social networks, like Facebook or Twitter.

Therefore, techniques for efficient storage and fast access/traversal of large
graphs are needed in order to become feasible to analyze not only web graphs,
but large graphs of any kind.

While several approaches have been taken regarding graph compression, we chose
to analyze how LLP uses community finding techniques to reorder the nodes of a
graph in order to exploit its inner structure and obtain, in combination with
the Boldi and Vigna (BV) compression method (which we do not explore here),
superior compression products than current alternatives.

<!-- *FIXME* Put the reference to the llp paper. -->

LLP was first mentioned in *FIXME*. The objective was to find effective general
techniques to store and access graphs. Moreover, the resulting compressed data
structure must provide fast amortised random access to an edge. The authors
address this problem by applying *intrinsic* heuristics (i.e., ones that depend
only on the inner structure of the network), in contrast to *extrinsic*
heuristics (which are features of each specific kind of network). For instance,
in a web graph one can find an extrinsic permutation of the nodes in the
URL-based lexicographic order which, in practice, can be shown to produce
impressive compression ratios. However, this ordering isn't applicable to all
sorts of networks.

<!-- Maybe stretches the idea a little bit too far... -->
Nonetheless, the ordering of the nodes becomes important once we consider that,
in order to achieve good compression performances, compression algorithms
usually exploit two properties:
(1) *similarity*: nodes tend to have resembling sets of neighbours if they're
close to each other in the ordering;
(2) *locality*: most of the edges are shared between nodes close to each other
in the ordering.
Furthermore, most current algorithms are sensitive to the initial ordering of
the graphs, generating different compression ratios depending on how the dataset
is originally presented. LLP, on the other hand, is *coordinate-free*, i.e.,
attains similar results independently of the original ordering.

## Problem Definition

Given an input graph, devise an ordering $\pi : V_G \rightarrow |V_G|$
that minimizes the number of bits per edge needed to store the graph, while
providing fast amortised random access to its edges.

Obviously, the algorithm must be parameterised by a compression method. The
authors of LLP chose to combine it with the BV compression algorithm, as they
regard it as the "*de facto* standard for handling large web-like graphs". The
procedure relies heavily on similarity and locality to manage its good results,
which are exactly the properties what LLP tries to maximise.

It is also worth noting that this problem is NP-hard. Therefore, it is
appropriate to try to craft heuristics that work well in most practical cases.
In this case we are only interested in intrinsic heuristics.

## Label Propagation

As said before, LLP exploits the inner structure of the network to devise
intrinsic orderings of its nodes, so it may be appropriate to approach the issue
of graph reordering as a community finding problem. However, the size of the
graphs we are handling demand the usage of highly efficient algorithms.

Label propagation algorithms seem fit to address this problem because, not only
no *a priori* information is needed regarding the structure of the network, they
are also efficient, requiring only a few passes through the network and are
linear in the number of edges.

<!-- *FIXME* Put the reference to the original label propagation paper. -->

 What the authors of LLP call the (*standard*) label propagation algorithm is
described in *FIXME* and works as follows: at the beginning each node is
assigned a unique label. At each iteration, in random order each node takes up
the label that most of its neighbours have, with ties resolved uniformly
randomly. As the labels propagate through the graph, densely connected groups of
nodes form an agreement over their labels. This iterative process goes on until
every node in the graph is assigned a label equal to most of its neightbours. At
the end, nodes with the same labels are grouped together as communities.

However, the authors found that the algorithm just described, tends to produce
one giant cluster containing the bulk of the nodes when applied to social
networks, which is due to the very nature of the topology of this kind of
networks.

<!-- *FIXME* Put the reference to the original APM paper. -->

One interesting variant of label propagation is the Absolute Pott Model (APM)
*FIXME*. This algorithm addresses the resolution limit problem in community
detection by introducing nonlocal weight discount parameter when considering
weight preferences for assigning node labels. In standard label propagation, the
label $\lambda_i$ assigned to a node $x$, was the one that maximized $k_i$,
being $k_i$, the number of neighbours having the given label $\lambda_i$. In
APM, the value to maximize becomes $k_i - \gamma(v_i - k_i)$, where $v_i$ is the
number of nodes in the network with label $\lambda_i$. Note that, if $\gamma$ is
fixed to zero, we get the standard label propagation method.

However, the APM algorithms suffers from some shortcomings. First, there is no
known way to predetermine an "optimal" value for $\gamma$: every value of this
parameter accounts for a different resolution of the analyzed graph. Second, the
sizes of the produced clusters lean towards a heavy-tailed decreasing
distribution, yielding an enormous amount of huge-sized clusters.

## Layered Label Propagation

For low values of the resolution parameter $\gamma$ of the APM algorithm, outer
and further nodes tend to have more weight at the time of updating the labels,
highlighting fewer, larger and sparser clusters, while higher values of $\gamma$
result in denser and smaller clusters, reveiling a finer structure of the
network. This idea motivates the definition of *Layered Label Propagation*. 

The algorithm starts with any initial ordering of the nodes. The APM algorithm
is then iterated through different values of $\gamma$ and at each iteration the
produced labelling is converted into an ordering that keeps nodes with the same
label close to each other; nodes within the same community are left in the same
order they had before. Regarding nodes from different communities, their
relative order is determined by the labels themselves.

LLP becomes parameter-free once the initial ordering and the sequence of
resolution terms are defined. For that matter, the initial ordering is defined
to be the original ordering of the input graph (any ordering will suffice
because LLP is coordinate-free). Regarding the choice of resolution parameters,
they are picked uniformly randomly from the set $\{0\} \cup \{2^{-i}, i=0,...,K\}$
where $K$ is *FIXME*.
<!-- *FIXME* what is K ? -->

It's worth noting that the algorithm as described lends itself naturally to a
parallel implementation. It is shown to be possible to obtain performance
improvements linear in the number of cores.

## Analysis

<!-- basically, why it is good -->
<!-- quality measures, reconstructing host structure, blah, blah, blah... -->

### Quality measures

In this paper were presented two measures to prove empiricaly that existing
aproaches compress well web graphs. The first measure exposed in this paper is
the probability of changing host given a partion $\mathcal{H}$, representing one
partition where any node that has the same host belongs to the same class of
equivalence of another node that has the same host as the previous node, and a
certain permutation $\pi$ $$HT(\mathcal{H},\pi)=\dfrac{\sum_{i=1}^{|V_G|-1}
\delta(\mathcal{H}[\pi^{-1}(i)],\mathcal{H}[\pi^{-1}(i - 1)])}{|V_G|-1} $$

In this formula $\delta$, represents the usual Kronecker's Delta, as stated in
the paper. As a group we've reached the conclusion that this formula is plain
wrong, since it does not represent the fraction of times there is an host
transition, but instead represents its complement, since while transversing
$\pi$ as a list, HT($\mathcal{H},\pi$) will only increment for each contiguos
pair of $\pi$ where both elements have the same host. We state the correct
formula as: $$HT(\mathcal{H},\pi)= 1 -\dfrac{\sum_{i=1}^{|V_G|-1}
\delta(\mathcal{H}[\pi^{-1}(i)],\mathcal{H}[\pi^{-1}(i - 1)])}{|V_G|-1} $$ If
$HT(\mathcal{H},\pi)$ is minimun then we have find permutation $\pi$ which
maximizes the compression ratio.

Let $\mathcal{H}_{|\pi}$, be defined as the the reflexive and transitive closure
of relation $\rho$:
$${x}\rho{y}\iff\pi({x})=\pi({y})\frown\mathcal{H}[{x}]=\mathcal{H}[{y}]$$

i.e. $$\mathcal{H} = \{\{0\},\{1,2,3\},\{4,6\},\{5\}\}$$ $\hspace{3.5cm}and$
$$\pi = (0,1,4,3,2,5,4,6)$$ $\hspace{3.4cm}then$
$$\mathcal{H}_{|\pi}=\{\{0\},\{1\},\{2,3\},\{4,6\},\{5\}\} $$

With $\mathcal{H}_{|\pi}$ defined we can now expose the second measure,
Variation of Information:

The expected value of information contained by a partition $\mathcal{U}$ is
defined by its entropy value $H(\mathcal{U})$, the amount of information
contained by the conjunction of two partition is called Mutual Information and
its defined by $I(\mathcal{U},\mathcal{V})$, finally the difference of
information expected to be obtained when comparing two partitions is called
Variation of Information. Throught simple algebrics it is trivial to prove that:
$$I(\mathcal{H}_{|\pi},\mathcal{H})=\mathcal{H}$$ $\hspace{3cm}implying$
$$VI(\mathcal{H}_{|\pi},\mathcal{H})=H(\mathcal{H}_{|\pi})-H(\mathcal{H})$$
Since $$ \leq VI(\mathcal{H}_{|\pi},\mathcal{H})\leq VI(\mathcal{H}_{|\pi} +
\mathcal{H}) $$
