#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <limits>

#define NL std::cout << '\n';
#define WATCH(x) std::cout << (#x) << ": " << (x) << '\n';
#define PRINT(s, x) std::cout << s << ": " << x << '\n';
#define FOR_PRINT(s, items) for (auto x : items) { PRINT(s, x) }
#define FOR_DICT_PRINT(s, items) for (auto x : items) { PRINT(x.first, x.second) }

using Edge = std::pair<size_t, size_t>;
using Edges = std::vector<Edge>;

struct Input
{
	Input(Edges&& vec, std::pair<size_t, size_t> p) : edges(std::move(vec)), descr(p){}
	Edges edges;
	std::pair<size_t, size_t> descr;
};

static std::pair<bool, Input> read_input()
{
	size_t i, j;
	std::cin >> i >> j;
	std::pair<size_t, size_t> descr { i, j };

	Edges edges;
	edges.reserve(j);
	if (!i && !j) { return std::make_pair<bool, Input>(true, Input({}, descr)); }

	bool truly_stop = false;
	while ( !0 )
	{
		std::cin >> i >> j;
		std::cin.get();
		if (!i && !j) { truly_stop = true; break; } // FIXME
		edges.push_back({i , j});
		if (std::cin.peek() == '\n') { break; }
	}

	return { truly_stop, Input(std::move(edges), descr) };
}

template <typename T>
struct Graph
{
	Graph(Edges edges, std::pair<size_t, size_t> descr)
	{
		for (const auto& [v1, v2] : edges)
		{
			if (m_vertexMap.find(v1) == m_vertexMap.end())
			{
				auto vertex1 = new Vertex(v1, 0);
				m_vertexMap.insert(std::make_pair(v1, vertex1));
			}
			if (m_vertexMap.find(v2) == m_vertexMap.end())
			{
				auto vertex2 = new Vertex(v2, 0);
				m_vertexMap.insert(std::make_pair(v2, vertex2));
			}
		
			m_vertexMap[v1]->v_neighbors.insert(m_vertexMap[v2]);
			m_vertexMap[v1]->v_value++;
			m_vertexMap[v2]->v_neighbors.insert(m_vertexMap[v1]);
			m_vertexMap[v2]->v_value++;
		}

		std::vector<size_t> supplement (descr.first - m_vertexMap.size());
		std::iota(supplement.begin(), supplement.end(), 1 + m_vertexMap.size());
		for (auto key : supplement)
		{
			m_vertexMap.insert(std::make_pair(key, new Vertex(key, 0)));
		}

		m_sorted_keys.reserve(m_vertexMap.size());

		std::vector<Vertex*> m_sorted_keys_tmp;
		m_sorted_keys_tmp.reserve(m_vertexMap.size());

		std::transform(m_vertexMap.begin(), m_vertexMap.end(),
			std::back_inserter(m_sorted_keys_tmp), [](auto a){ return a.second; });

		std::sort(
			m_sorted_keys_tmp.begin(), m_sorted_keys_tmp.end(),
			[](auto v1, auto v2) -> bool {
				return v1->v_value > v2->v_value;
		});

		std::transform(m_sorted_keys_tmp.begin(), m_sorted_keys_tmp.end(),
			std::back_inserter(m_sorted_keys), [](auto a){ return a->v_index; });
	}

	//Graph (const Graph&) = delete;
	//Graph& operator= (const Graph&) = delete;
	
	// ~Graph() { for (auto [_, vertex] : m_vertexMap) { delete vertex; }} 

	struct Vertex
	{
		Vertex(const size_t index, const T val) : v_index(index), v_value(val), 
			v_exploration(Explore::UNSEEN), v_serviced(false) {}

		enum class Explore { UNSEEN, OPEN, CLOSED };

		size_t v_index;
		T v_value;
		Explore v_exploration;
		std::set<Vertex*> v_neighbors;
		bool v_serviced;
	};
	
	std::map<size_t, Vertex*> m_vertexMap;
	std::vector<size_t> m_sorted_keys;

	T BFS_stationning_internal(size_t start)
	{
		T count_stations = 0;
		Vertex* currentVertex = m_vertexMap[m_sorted_keys[start]];

		auto comparator = [](const auto a, const auto b) -> bool {
			return a->v_value < b->v_value;
		};

		std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(comparator)> que {
			comparator
		};
		que.push(currentVertex);

		while (!que.empty())
		{
			currentVertex = que.top();
			que.pop();

			currentVertex->v_exploration = Vertex::Explore::OPEN;
			
			if (std::all_of(m_vertexMap.begin(), m_vertexMap.end(), [](auto c){
				return c.second->v_serviced == true;
			}))
			{
				return count_stations;
			}
			//if (currentVertex->v_value > 0)
			//{
				currentVertex->v_value = 0;
				//if (!currentVertex->v_serviced)
				{
					currentVertex->v_serviced = true;
					++count_stations;

					for (auto& neighbor : currentVertex->v_neighbors)
					{
						--neighbor->v_value;
						neighbor->v_serviced = true;
					}
				}
				
				//for (auto& neighbor : currentVertex->v_neighbors)
				{
					//--neighbor->v_value;
				}
			//}
			//WATCH(currentVertex->v_index)
			//WATCH(count_stations)
			for (auto& neighbor : currentVertex->v_neighbors)
			{
				if (neighbor->v_exploration == Vertex::Explore::UNSEEN)
				{
					neighbor->v_exploration = Vertex::Explore::OPEN;
					que.push(neighbor);
				}
			}
			currentVertex->v_exploration = Vertex::Explore::CLOSED;
		}

		return count_stations;
	}

	void reset_state(Component comp)
	{
		for (auto& item : comp)
		{
			item->v_exploration = Vertex::Explore::UNSEEN;
			item->v_serviced = false;
		}
	}

	void reset_state_map(std::map<size_t, Vertex*> map)
	{
		for (auto& [_, item] : map)
		{
			item->v_exploration = Vertex::Explore::UNSEEN;
			item->v_serviced = false;
		}
	}

	using Component = std::vector<Vertex*>;

	Component get_component(size_t start)
	{
		Component cs;

		Vertex* currentVertex = m_vertexMap[m_sorted_keys[start]];
		std::queue que;
		que.push(currentVertex);

		while (!que.empty())
		{
			currentVertex = que.top();
			que.pop();

			currentVertex->v_exploration = Vertex::Explore::OPEN;
			cs.push_back(currentVertex);

			for (auto& neighbor : currentVertex->v_neighbors)
			{
				if (neighbor->v_exploration == Vertex::Explore::UNSEEN)
				{
					neighbor->v_exploration = Vertex::Explore::OPEN;
					que.push(neighbor);
				}
			}
			currentVertex->v_exploration = Vertex::Explore::CLOSED;
		}

		return cs;
	}

	T BFS_stationning_bactracking(size_t start)
	{
		T count_stations = std::numeric_limits<T>::max();
		// std::vector<bool> to_restore_is_servicing();
		// to_restore_is_servicing.reserve(m_sorted_keys.size());
		// std::vector<size_t> to_restore_value;
		// to_restore_value.reserve(m_sorted_keys.size());

		std::vector<Component> components;
		for (size_t idx = 0; idx < m_sorted_keys.size(); idx++)
		{
			auto vertex = m_vertexMap[m_sorted_keys[jdx]];
			if (vertex->v_exploration == Vertex::Explore::UNSEEN)
			{
				components.push_back(get_component(idx));
			}
		}
		
		reset_state_map(m_vertexMap);

		for (auto& component : components)
		{

		}
		
		for (size_t idx = 0; idx < m_sorted_keys.size(); idx++)
		{
			T acc = 0;

			for (size_t jdx = 0; jdx < m_sorted_keys.size(); jdx++)
			{
				//std::copy_if(m_vertexMap.begin(), m_vertexMap.end(), std::back_inserter(to_restore), [](auto v) -> bool { return vertex->v_exploration == Vertex::Explore::UNSEEN; });
				auto vertex = m_vertexMap[m_sorted_keys[jdx]];
				if (vertex->v_exploration == Vertex::Explore::UNSEEN)
				{
					acc += BFS_stationning_internal(idx);
					//PRINT("global count stations", acc)
				}
			}
			//WATCH(count_stations)
			//WATCH(acc)
			count_stations = std::min(count_stations, acc);
		}
		return count_stations;
	}

	T BFS_stationning()
	{
		T count_stations = std::numeric_limits<T>::max();
		for (size_t idx = 0; idx < m_sorted_keys.size(); idx++)
		{
			count_stations = std::min(BFS_stationning_bactracking(idx), count_stations); 
		}

		return count_stations;
	}
};

template <typename T> using InputGraphs = std::vector<Graph<T>>;

template <typename T>
InputGraphs<T> read_inputs()
{
	InputGraphs<T> graphs;

	auto input = read_input();
	if (input.first) { return std::move(graphs); }
	graphs.emplace_back(Graph<T>(std::move(input.second.edges), input.second.descr));
	
	while ( std::cin.peek() == '\n') //  input.edges.empty())
	{
		std::cin.get();
		input = read_input();
		if (!input.second.descr.first && !input.second.descr.second) { return std::move(graphs); }

		graphs.emplace_back(Graph<T>(std::move(input.second.edges), input.second.descr));
		if (input.first) { return std::move(graphs); }
	}
	return std::move(graphs);
}

int main()
{
	InputGraphs<size_t> graphs = read_inputs<size_t>();
	for (auto& graph : graphs)
	{
		std::cout << std::to_string(graph.BFS_stationning()) << '\n';
	}
	return 0;
}

