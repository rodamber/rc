# Abstract

Regarding the subject of graph compression, we make an analysis on it's
cornerstones, considering the importance and value on the correlation between a
graph's ordering and it's subsequent compression. We take on this issue by
analyzing how Layered Label Propagation (LLP), a coordinate-free ordering
method, uses intrisinc heuristics to produce an ordering to improve over current
graph compression methods.

*?* and also, even though webgraphs and social networks have different inherent
characteristics, how can a webgraph compression algorithm be adapted to process
a social network.

# Introduction

Modeling real-world relations through graphs is a very widely used way to gather
information between constituents of a given network.
In such a way, a lot of information can be mined from this given structure, e.g.,
detecting node relationships, like friendship relations in social networks,
finding communities between users, and other statistical information obtained by
graph metrics.

This becomes a real implementation problem when the graph has millions or
billions of nodes, since much of the standard graph mining algorithms assume
that the graph is stored in main memory.
This can be witnessed, for example, in the web graph, which describes the
directed links between pages of the addressable World Wide Web, or when
regarding commonly used social networks, like Facebook or Twitter.

<!-- Bullshit Paragraph -->
So, we can agree that effective techniques to store and access large graphs are
needed in order to be possible to realize and analyze, not only web graphs, but
also social networks. We will be addressing how this techniques can be
implemented, why they are effective, and also an optimization variant that
relies on a specific node ordering technique called Layered Label Propagation.


<!-- I guess what we need to say here is that we're looking for intrisinc -->
<!-- characteristics instead of extrinsic ones. -->
<!-- Also, that the objective is a compressed data structure for immutable graphs -->
<!-- that provides fast edge access and does not need to be decompressed. -->

Taking this in consideration, it is vital to have an accurate understanding of
the characteristics and inner structure of such networks, so one can improve the
compression performance on this networks. 

What is desired is to be possible to develop structures that propitiate a very
fast amortized random access to an edge.

This idea has already been explored with success with application to web graphs,
showing that is possible to use 3 bits/link.
To achieve this kind of ratio, it is needed to make good use of two properties:

- *similarity*: nodes that are close to each other in the order tend to have
similar sets of neighbours;

- *locality*: most links are between nodes that are close to each other in the
order.

<!-- also tell that because most algorithms exploit these properties, they become -->
<!-- sensible to the way nodes are ordered -->

<!-- extrinsic properties are characteristic of each kind of graph, while intrinsic -->
<!-- properties can be generally applied. -->

<!-- Bullshit Paragraph -->
This way, we can develop a model that facilitates efficient adjacency queries
and we can, for example: exploit lexicographic locality: ordering URLs naturally
(Web Graphs), or ordering Facebook users through the amount of shared friendship
relationships (social networks). This properties show the importance of node
ordering for compressing algorithms achieving better compression ratios. From
here, we can develop different ordering heuristics based on the provenance of
the information that allowed us the given ordering, and the type on network
itself:

<!-- What were they thinking? Probably forgot about this here. -->
- *intrinsic heuristics*: nodes that are close to each other in the order tend
to have similar sets of neighbours;

- *extrinsic heuristics*: most links are between nodes that are close to each
other in the order.

# Problem

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
