########## Easy ##########  ##########  ##########  ##########

class lc463 : #E, island-perimeter
    def islandPerimeter(self, grid: List[List[int]]) -> int:


##########  ##########  ##########  ##########  ##########


########## Medium ##########  ##########  ##########  ##########

root_node = {'$id': '1',
             'neighbors': [{'$id': '2',
                            'neighbors': [{'$ref': '1'},
                                          {'$id': '3',
                                           'neighbors': [{'$ref': '2'},
                                                         {'$id': '4',
                                                          'neighbors': [{'$ref': '3'},
                                                                        {'$ref': '1'}],
                                                          'val': 4}],
                                           'val': 3}],
                            'val': 2},
                           {'$ref': '4'}],
             'val': 1}

class Node:
    def __init__(self, val, neighbors):
        self.val = val
        self.neighbors = neighbors

node = Node(1, [Node(2, [Node(3, [Node(4,[])])])])

node1, node2, node3, node4 = Node(1,[]), Node(2,[]), Node(3,[]), Node(4,[])
node1.neighbors = [node2, node4]
node2.neighbors = [node1, node3]
node3.neighbors = [node2, node4]
node4.neighbors = [node1, node3]

class lc133:  # M, Clone Graph
    def cloneGraph(self, node: 'Node') -> 'Node':
        graph = {}
        visited = set()

        def _dfs(node, visited, graph):
            if not node or node.val in visited:
                return
            visited |= {node.val}
            if node.val not in graph:
                graph[node.val] = Node(node.val)
            newNode = graph[node.val]

            for nbr in node.neighbors:
                if nbr.val not in graph:
                    graph[nbr.val] = Node(nbr.val)
                newNode.neighbors.append(graph[nbr.val])
                _dfs(nbr, visited, graph)
            return newNode

        return _dfs(node, visited, graph)

##########  ##########  ##########  ##########  ##########
