
#pragma once

#include <utility>
#include <set>
#include <map>
#include <optional>
#include <iostream>

namespace CXXGRAPH
{
	template <typename T>
	class Node;
	template <typename T>
	class Edge;
	template <typename T>
	class DirectedEdge;
	template <typename T>
	class UndirectedEdge;
	template <typename T>
	class Graph;

	template <typename T>
	using AdjacencyMatrix = std::map<const Node<T>,std::vector<std::pair<const Node<T>, const Edge<T>>>>;

	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Node<T> &node);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Edge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const DirectedEdge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const UndirectedEdge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Graph<T> &graph);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const AdjacencyMatrix<T> &adj);

	template <typename T>
	class Node
	{
	private:
		unsigned long id;
		T data;

	public:
		Node(const unsigned long id, const T &data);
		~Node() = default;
		const unsigned long &getId() const;
		const T &getData() const;
		//operator
		bool operator==(const Node<T> &b) const;
		bool operator<(const Node<T> &b) const;
		friend std::ostream &operator<<<>(std::ostream &os, const Node<T> &node);
	};

	template <typename T>
	Node<T>::Node(const unsigned long id, const T &data)
	{
		this->id = id;
		this->data = data;
	}

	template <typename T>
	const unsigned long &Node<T>::getId() const
	{
		return id;
	}

	template <typename T>
	const T &Node<T>::getData() const
	{
		return data;
	}

	template <typename T>
	bool Node<T>::operator==(const Node<T> &b) const
	{
		return (this->id == b.id && this->data == b.data);
	}
	
	template<typename T>
	bool Node<T>::operator<(const Node<T> &b) const
	{
		return (this->id < b.id);
	}

	template <typename T>
	class Edge
	{
	private:
		unsigned long id;
		std::pair<const Node<T>*,const Node<T>*> nodePair;

	public:
		Edge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		Edge(const unsigned long id, const std::pair<const Node<T>*,const Node<T>*> &nodepair);
		virtual ~Edge() = default;
		const unsigned long &getId() const;
		const std::pair<const Node<T>*, const Node<T>*> &getNodePair() const;
		virtual const std::optional<bool> isDirected() const;
		virtual const std::optional<bool> isWeighted() const;
		//operator
		virtual bool operator==(const Edge<T> &b) const;
		bool operator<(const Edge<T> &b) const;
		//operator DirectedEdge<T>() const { return DirectedEdge<T>(id, nodePair); }
		//operator UndirectedEdge<T>() const { return UndirectedEdge<T>(id, nodePair); }

		friend std::ostream &operator<<<>(std::ostream &os, const Edge<T> &edge);
	};

	template <typename T>
	Edge<T>::Edge(const unsigned long id, const Node<T> &node1, const Node<T> &node2) : nodePair(&node1, &node2)
	{
		this->id = id;
	}

	template <typename T>
	Edge<T>::Edge(const unsigned long id, const std::pair<const Node<T>*,const Node<T>*> &nodepair) : nodePair(nodepair)
	{
		this->id = id;
	}

	template <typename T>
	const unsigned long &Edge<T>::getId() const
	{
		return id;
	}

	template <typename T>
	const std::pair<const Node<T>*, const Node<T>*> &Edge<T>::getNodePair() const
	{
		return nodePair;
	}

	template <typename T>
	const std::optional<bool> Edge<T>::isDirected() const
	{
		return std::nullopt;
	}

	template <typename T>
	const std::optional<bool> Edge<T>::isWeighted() const
	{
		return std::nullopt;
	}

	template <typename T>
	bool Edge<T>::operator==(const Edge<T> &b) const
	{
		return (this->id == b.id && this->nodePair == b.nodePair);
	}

	template <typename T>
	bool Edge<T>::operator<(const Edge<T> &b) const
	{
		return (this->id < b.id);
	}

	template <typename T>
	class DirectedEdge : public Edge<T>
	{
	public:
		DirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		DirectedEdge(const unsigned long id, const std::pair<const Node<T>*, const Node<T>*> &nodepair);
		DirectedEdge(const Edge<T> &edge);
		virtual ~DirectedEdge() = default;
		const Node<T> &getFrom() const;
		const Node<T> &getTo() const;
		const std::optional<bool> isDirected() const override;
		virtual const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator UndirectedEdge<T>() const { return UndirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair()); }

		friend std::ostream &operator<<<>(std::ostream &os, const DirectedEdge<T> &edge);
	};

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2) : Edge<T>(id, node1, node2)
	{
	}

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const unsigned long id, const std::pair<const Node<T>*,const Node<T>*> &nodepair) : Edge<T>(id, nodepair)
	{
	}

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const Edge<T> &edge) : DirectedEdge(edge.getId(), *(edge.getNodePair().first), *(edge.getNodePair().second))
	{
	}

	template <typename T>
	const Node<T> &DirectedEdge<T>::getFrom() const
	{
		return *(Edge<T>::getNodePair().first);
	}

	template <typename T>
	const Node<T> &DirectedEdge<T>::getTo() const
	{
		return *(Edge<T>::getNodePair().second);
	}

	template <typename T>
	const std::optional<bool> DirectedEdge<T>::isDirected() const
	{
		return true;
	}

	template <typename T>
	const std::optional<bool> DirectedEdge<T>::isWeighted() const
	{
		return false;
	}

	template <typename T>
	class UndirectedEdge : public Edge<T>
	{
	public:
		UndirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		UndirectedEdge(const unsigned long id, const std::pair<const Node<T>*,const Node<T>*> &nodepair);
		UndirectedEdge(const Edge<T> &edge);
		virtual ~UndirectedEdge() = default;
		const Node<T> &getNode1() const;
		const Node<T> &getNode2() const;
		const std::optional<bool> isDirected() const override;
		const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator DirectedEdge<T>() const { return DirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair()); }

		friend std::ostream &operator<<<>(std::ostream &os, const UndirectedEdge<T> &edge);
	};

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2) : Edge<T>(id, node1, node2)
	{
	}

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const unsigned long id, const std::pair<const Node<T>*,const Node<T>*> &nodepair) : Edge<T>(id, nodepair)
	{
	}

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const Edge<T> &edge) : UndirectedEdge(edge.getId(), *(edge.getNodePair().first), *(edge.getNodePair().second))
	{
	}

	template <typename T>
	const Node<T> &UndirectedEdge<T>::getNode1() const
	{
		return *(Edge<T>::getNodePair().first);
	}

	template <typename T>
	const Node<T> &UndirectedEdge<T>::getNode2() const
	{
		return *(Edge<T>::getNodePair().second);
	}

	template <typename T>
	const std::optional<bool> UndirectedEdge<T>::isDirected() const
	{
		return false;
	}

	template <typename T>
	const std::optional<bool> UndirectedEdge<T>::isWeighted() const
	{
		return false;
	}

	template <typename T>
	class Graph
	{
	private:
		std::set<const Edge<T>*> edgeSet;
		void addElementToAdjMatrix(AdjacencyMatrix<T> &adjMatrix, const Node<T> &nodeFrom, const Node<T> &nodeTo, const Edge<T> &edge) const;

	public:
		Graph() = default;
		Graph(const std::set<const Edge<T>*> &edgeSet);
		~Graph() = default;
		const std::set<const Edge<T>*> &getEdgeSet() const;
		void setEdgeSet(std::set<const Edge<T>*> &edgeSet);
		void addEdge(const Edge<T> &edge);
		void removeEdge(unsigned long edgeId);
		const std::optional<const Edge<T>*> getEdge(unsigned long edgeId) const;
		/*This function generate a list of adjacency matrix with every element of the matrix 
		***contain the node where is directed the link and the Edge corrispondent to the link
		*/
		const AdjacencyMatrix<T> getAdjMatrix() const;

		friend std::ostream &operator<<<>(std::ostream &os, const Graph<T> &graph);
		friend std::ostream &operator<<<>(std::ostream &os, const AdjacencyMatrix<T> &adj);
	};

	template <typename T>
	Graph<T>::Graph(const std::set<const Edge<T>*> &edgeSet)
	{
		this->edgeSet = edgeSet;
	}

	template <typename T>
	const std::set<const Edge<T>*> &Graph<T>::getEdgeSet() const
	{
		return edgeSet;
	}

	template <typename T>
	void Graph<T>::setEdgeSet(std::set<const Edge<T>*> &edgeSet)
	{
		this->edgeSet = edgeSet;
	}

	template <typename T>
	void Graph<T>::addEdge(const Edge<T> &edge)
	{
		edgeSet.insert(&edge);
	}

	template <typename T>
	void Graph<T>::removeEdge(unsigned long edgeId)
	{
		auto edgeOpt = getEdge(edgeId);
		if (edgeOpt.has_value())
		{
			edgeSet.erase(edgeSet.find(edgeOpt.value()));
		}
	}

	template <typename T>
	const std::optional<const Edge<T>*> Graph<T>::getEdge(unsigned long edgeId) const
	{

		auto it = edgeSet.begin();
		for (it; it != edgeSet.end(); ++it)
		{
			if ((*it)->getId() == edgeId)
			{
				return *it;
			}
		}

		return std::nullopt;
	}

	template <typename T>
	void Graph<T>::addElementToAdjMatrix(AdjacencyMatrix<T> &adjMatrix, const Node<T> &nodeFrom, const Node<T> &nodeTo, const Edge<T> &edge) const
	{
		std::cout << "add element START " << std::endl;
		std::pair<const Node<T>, const Edge<T>> elem = {nodeTo, edge};
		std::cout << "add element insert " << std::endl;
		adjMatrix[nodeFrom].push_back(elem);
		
		//adjMatrix[nodeFrom.getId()].push_back(std::make_pair<const Node<T>,const Edge<T>>(nodeTo, edge));
		std::cout << "add element END " << std::endl;
	}

	template <typename T>
	const AdjacencyMatrix<T> Graph<T>::getAdjMatrix() const
	{
		AdjacencyMatrix<T> adj;
		auto edgeSetIt = edgeSet.begin();
		for (edgeSetIt; edgeSetIt != edgeSet.end(); ++edgeSetIt)
		{
			std::cout << "Has Value: " << (*edgeSetIt)->isDirected().has_value() << std::endl;
			if ((*edgeSetIt)->isDirected().has_value() && (*edgeSetIt)->isDirected().value())
			{
				std::cout << "is directed edge" << std::endl;
				DirectedEdge d_edge = **edgeSetIt;
				addElementToAdjMatrix(adj, d_edge.getFrom(), d_edge.getTo(), d_edge);
			}
			else if ((*edgeSetIt)->isDirected().has_value() && !(*edgeSetIt)->isDirected().value())
			{
				std::cout << "is undirected edge" << std::endl;
				UndirectedEdge ud_edge = **edgeSetIt;
				addElementToAdjMatrix(adj, ud_edge.getNode1(), ud_edge.getNode2(), ud_edge);
				addElementToAdjMatrix(adj, ud_edge.getNode2(), ud_edge.getNode1(), ud_edge);
			}
			else
			{ //is a simple edge we cannot create adj matrix
				return adj;
			}
		}
		return adj;
	}
	//ostream overload
	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Node<T> &node)
	{
		os << "Node: {\n"
		   << "  Id:\t" << node.id << "\n  Data:\t" << node.data << "\n}";
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Edge<T> &edge)
	{
		os << "((Node: " << edge.nodePair.first->getId() << ")) ?----- |Edge: " << edge.id << "|-----? ((Node: " << edge.nodePair.second->getId() << "))";
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const DirectedEdge<T> &edge)
	{
		os << "((Node: " << edge.getFrom().getId() << ")) +----- |Edge: " << edge.getId() << "|-----> ((Node: " << edge.getTo().getId() << "))";
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const UndirectedEdge<T> &edge)
	{
		os << "((Node: " << edge.getNode1().getId() << ")) <----- |Edge: " << edge.getId() << "|-----> ((Node: " << edge.getNode2().getId() << "))";
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const AdjacencyMatrix<T> &adj)
	{
		os << "Adjacency Matrix:\n";
		auto it = adj.begin();
		unsigned long max_column = 0;
		for (it; it != adj.end(); ++it)
		{
			if (it->second.size() > max_column)
			{
				max_column = it->second.size();
			}
		}
		if (max_column == 0)
		{
			os << "ERROR in Print\n";
			return os;
		}
		else
		{
			it = adj.begin();
			os << "|--|";
			for (int i = 0; i < max_column; i++)
			{
				os << "-----|";
			}
			os << "\n";
			for (it; it != adj.end(); ++it)
			{
				os << "|N" << it->first.getId() << "|";
				auto it2 = it->second.begin();
				for (it2; it2 != it->second.end(); ++it2)
				{
					os << "N"<<it2->first.getId() << ",E" << it2->second.getId() << "|";
				}
				os << "\n|--|";
				for (int i = 0; i < max_column; i++)
				{
					os << "-----|";
				}
				os << "\n";
			}
		}
		return os;
	}

} // namespace CXXGRAPH