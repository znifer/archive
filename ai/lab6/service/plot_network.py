import graphviz
import re


def plot_network(knowledge, dictionary):
    nodes = []
    graph = graphviz.Digraph(engine='fdp')
    graph.attr(overlap='scale')
    pattern = r'(part_of|is_a)\((".*"), (".*")\).'
    pattern = re.compile(pattern)
    with open(knowledge) as file:
        for line in file:
            result = pattern.match(line.strip())
            if result:
                command = result.group(1)
                a = result.group(2)
                b = result.group(3)
                if a not in nodes:
                    nodes.append(a)
                    graph.node(a, label=dictionary[a[1:-1]])
                if b not in nodes:
                    nodes.append(b)
                    graph.node(b, label=dictionary[b[1:-1]])
                if command == 'is_a':
                    graph.edge(a, b, label="IS-A")
                else:
                    graph.edge(b, a, label="PART-OF")
    return graph


def render(knowledge, dictionary, output):
    plot_network(knowledge, dictionary).render(output)
