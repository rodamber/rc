# Abstract

We present a summary of how Layered Label Propagation (LLP), a highly scalable,
coordinate-free, graph reordering algorithm, uses community finding techniques
to permute very large (immutable) graphs (possibly billions of nodes), with
applications to graph compression.

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
the Boldi and Vigna (BV) compression method (which we do not explore here), a
better compression than current alternatives.

# Problem Definition

# Layered Label Propagation

LLP was first mentioned in *FIXME*. The objective was to find effective general
(i.e. suitable to several types of graphs) techniques to store and access
graphs. Moreover, the resulting compressed data structure must provide fast
amortised random access to an edge. The authors address this problem by trying
to apply *intrinsic* heuristics (i.e., ones that depend only on the inner
structure of the network), in contrast to *extrinsic* heuristics (which are
features of each specific kind of network). For instance, in a web graph one can
find a permutation of the nodes in the URL-based lexicographic order which, in
practice, can be shown to produce impressive compression ratios. However, this
ordering isn't applicable to all sorts of networks.

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

The general problem of a graph-compression algorithm can be defined as a
function which receives a graph $G$ as input and stores it in a compressed data
structure; the output of this algorithm will depend on a node ordering
$\pi : V_G \rightarrow |V_G|$, an application that for any given node it will
return its index within this list, in such a way that the compression-ratio is
highly correlated with a specific numbering. This optimization problem has as
objective to find such an order $\pi$ that minimizes the amount of memory
required to store this graph. In this analyze we shall assume that a graph $G$
with $n$ nodes has $V_G = n$, so a node order is actually a permutation $\pi : n
\rightarrow n$.

<!-- is this english? -->
The graph-compression scheme, used to obtain the results present in this report,
is BV compression-scheme used within the WebGraph framework, used for handling
large web-like graphs, but in social networks there are no natural ordering,
since node names in this genre of network, have no prefix or it has no meaning,
lexicographical ordering is no longer viable.

<!-- incomplete -->
It is quite relevant that this algorithm is coordinate-free,

# Ordering Considerations

As mentioned previously there are various different ordering techniques that
derive from the origin of the information available from the graph. What we just
want to remark is that, most intrinsic techniques while attaining different
results and consequently different compression ratios, all depend on the initial
numbering of the nodes, since they work on the adjacency matrix $A_G$. This
overlooked situation turns out to be very relevant as it was noted that applying
this intrinsic ordering techniques to randomly numbered graphs produces worse
compression ratios than started from, for example, a URL-ordered web graph.
\newline Also, we previously mentioned the term \textit{coordinate-free}
algorithms. This term refers to those algorithms that achieve almost the same
compression performances when initialized from any initial ordering. This is
desired since it avoids dependency on the way in which the graph is presented
initially, and also on \textit{Layered Label Propagation} all the tests
regarding it's implementation presupposes starting from a random permutation of
the original graph. This way we have a strong validation of the importance of
coordinate-free algorithms.

# Quality measures

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

# Label Propagation Algorithms

As stated before, most of intrinsic ordering analyzed fail to produce
satisfactory compression ratios when applied to a randomly perpetuated graph.
This is attributed to the fact they fail in reconstructing host information as
we discussed previously. So in order to surpass this situation, this was
addressed as a clustering problem. Label propagation algorithms address this
type of problem and present a wanted solution, in terms that they use the
network structure alone as their guide, don't require external information about
communities in the graph and are linear in the number of edges.\newline Simply,
this type of algorithms start by giving every node a different label. At each
iteration, every node update it's label (that represents the cluster it
currently belongs to) according to some update rule. Algorithm terminates as
soon as no more updates take place. What differs from the various label
propagation algorithms is the rule applied when updating a node's label.\newline
The updating rule in the referred as the standard label propagation algorithm,
is for every node to take the label that occurs more frequently on its
neighborhood, being another way to view this rule, as every node in the network
chooses to join the largest neighboring community. This updating rule make that
dense consensus groups are created throughout the network. What tends to happen,
when applying this rule, is to observe the production of one giant cluster
containing the majority of nodes, due to the topology of social networks. To
overcome this problem, it is used a variant called Absolute Pott Model (APM),
that makes part of the \textit{Layered Label Propagation} algorithm. This
algorithm introduces a non local weight discount term when considering weight
preferences for choosing a node label. Previously (in standard label
propagation) the label chosen by a node \textit{x}, was the one that maximized
$k_i$, being $k_i$ the number of neighbors having given label. In APM, this
value is subtracted by the referenced discount term $\gamma (v_i - k_i)$, with
$v_i$ being the overall number of nodes in the given label. This way, the value
is the one that maximizes\newline $$k_i - \gamma (v_i - k_i)$$ Note that, if
$\gamma$=0, we have a standard label propagation choosing method, and also for
low $\gamma$ values, outer and further nodes tend to have more weight at the
time of label choosing, resulting in large and sparse clusters, and for higher
$\gamma$ values, local nodes have more weight at label choosing time, resulting
in denser and smaller clusters.

# Layered Label Propagation

# Comparisons

# Conclusion
