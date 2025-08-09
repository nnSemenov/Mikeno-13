#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge


= Phase Graph of this case

#diagram(
	node-stroke: 1pt,
	node((0,1),[fluid]),
	edge("-"),
	node((0,0), [inert]),
	node((1,0.5),[catA]),
	edge((0,1),(1,0.5),"--"),

	node((2,0),[H2]),
	edge("-"),
	node((2,1),[MCH]),
	edge("-"),
	node((2,2),[TOL]),

	edge((1,0.5),(2,0),"-"),

	node((0,2), [Al2O3]),
	edge("-"),
	node((0,3),[ZrO2]),
	edge("-"),
	node((1,2.5), [Pt]),

	edge((0,1),(0,2),"--")

)