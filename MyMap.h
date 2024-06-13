#pragma once
#include "RBTree.hpp"
using namespace std;
namespace wxj {
	template <class K,class V>
	class mapkot {
		struct setkot {
			const K& operator()(const pair<K,V>& tmp){
				return tmp.first;
			}
		};
		typedef typename RBTree<K,V, setkot>::iterator iterater;
		
	public:
		iterater begin() {
			return _t.begin();
		}
		iterater end() {
			return _t.end();
		}
		pair<iterater, bool> insert(const pair<K, V> tmp)
		{
			return _t.Insert(tmp);
		}
	private:
		RBTree<K, std::pair<K,V>, setkot> _t;
	};

}