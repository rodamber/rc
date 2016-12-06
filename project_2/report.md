# Abstract

We present a summary of how Layered Label Propagation (LLP), a highly scalable,
coordinate-free, graph reordering algorithm, uses community finding techniques
to permute very large immutable graphs, with applications to graph compression.

# Introduction

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

## Layered Label Propagation 

LLP was first mentioned in *FIXME*. The objective was to find effective general
techniques to store and access graphs. Moreover, the resulting compressed data
structure must provide fast amortised random access to an edge. The authors
address this problem by applying *intrinsic* heuristics (i.e., ones that depend
only on the inner structure of the network), in contrast to *extrinsic*
heuristics (which are features of each specific kind of network). For instance,
in a web graph one can find a permutation of the nodes in the URL-based
lexicographic order which, in practice, can be shown to produce impressive
compression ratios. However, this ordering isn't applicable to all sorts of
networks.

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

# Problem Definition

Given an input graph, devise an ordering $\pi : V_G \rightarrow |V_G|$
that minimizes the number of bits per edge needed to store the graph, while
providing fast amortised random access to its edges.

Obviously, the algorithm must be parameterised by a compression method. The
authors of LLP chose to combine it the BV compression algorithm, as they regard
it as the "*de facto* standard for handling large web-like graphs". The
procedure relies heavily on similarity and locality to manage its good results,
which are exactly the properties what LLP tries to maximise.

It is also worth noticing that this problem is NP-hard. Therefore, it is
appropriate to craft heuristics that work well in most practical cases. In this
case we are only interested in intrinsic heuristics.

# General Label Propagation

As said before, LLP exploits the inner structure of the network to devise
intrinsic orderings of its nodes, so it may be appropriate to approach the issue
of graph reordering as a community finding problem. However, the size of the
graphs we are handling demand the usage of highly efficient algorithms.

Label propagation algorithms seem fit to address this problem because, not only
no *a priori* information is needed regarding the structure of the network, they
are also efficient, requiring only a few passes through the network and are
linear in the number of edges.

The usual procedure for label propagation algorithms is presented:

```
Label Propagation




```

<!-- -------------------- -->

Simply, this type of algorithms start by giving every node a different label.

At each iteration, every node update it's label (that represents the cluster it
currently belongs to) according to some update rule.

Algorithm terminates as soon as no more updates take place. What differs from
the various label propagation algorithms is the rule applied when updating a
node's label.

The updating rule in the referred as the standard label propagation algorithm,
is for every node to take the label that occurs more frequently on its
neighborhood, being another way to view this rule, as every node in the network
chooses to join the largest neighboring community.

This updating rule make that dense consensus groups are created throughout the
network.

What tends to happen, when applying this rule, is to observe the production of
one giant cluster containing the majority of nodes, due to the topology of
social networks.

To overcome this problem, it is used a variant called Absolute Pott Model (APM),
that makes part of the \textit{Layered Label Propagation} algorithm.

This algorithm introduces a non local weight discount term when considering
weight preferences for choosing a node label.

Previously (in standard label propagation) the label chosen by a node
\textit{x}, was the one that maximized $k_i$, being $k_i$ the number of
neighbors having given label.

In APM, this value is subtracted by the referenced discount term $\gamma (v_i -
k_i)$, with $v_i$ being the overall number of nodes in the given label.

This way, the value is the one that maximizes\newline $$k_i - \gamma (v_i -
k_i)$$ Note that, if $\gamma$=0, we have a standard label propagation choosing
method, and also for low $\gamma$ values, outer and further nodes tend to have
more weight at the time of label choosing, resulting in large and sparse
clusters, and for higher $\gamma$ values, local nodes have more weight at label
choosing time, resulting in denser and smaller clusters.

# The Algorithm

# Analysis

<!-- quality measures, reconstructing host structure, blah, blah, blah... -->

## Quality measures

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

# Performance Results
