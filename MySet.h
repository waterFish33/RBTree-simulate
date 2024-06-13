#pragma once
#include "RBTree.hpp"

namespace wxj {
	template <class T>
	class set {
		struct setkot {
			const T& operator()(const T& tmp){
				return tmp;
			}
		};
		typedef typename RBTree<T, T, setkot>::iterator iterater;
		
		
	public:
		iterater begin() {
			return _t.begin();
		}
		iterater end() {
			return _t.end();
		}
		
		pair<iterater, bool> insert(const T& key)
		{
			return _t.Insert(key);
		}
	private:
		RBTree<T, T, setkot> _t;
	};



}