#pragma once

#include <assert.h>
#include <list>
#include "core.h"

namespace cyclone
{
	class PathNode
	{
	public:
		PathNode();
		PathNode(const Vector3 p) : pos(p) { parent = nullptr; }
		~PathNode();

		void setParent(PathNode* p) { parent = p; }
		PathNode* getParent() { return parent; }
		void setPosition(Vector3 p) { pos = p; }
		Vector3 getPosition() { return pos; }
		
		void setCost(float gv, float hv, float fv) { g = gv; h = hv; f = fv; }
		void setCost(float gv, float hv) { g = gv; h = hv; f = gv+hv; }
		void setCost(float fv) { f = fv; }

		void getCost(float& fr, float& gr, float& hr) { fr = f; gr = g; hr = h; }
		void getCost(float& fr) { fr = f; }
		float getCost() { return f; }

		void setAdjacentList(std::list<PathNode*> adj) { adjacentList = adj; }
		std::list<PathNode*> getAdjacentList() { return adjacentList; }

	private:
		Vector3 pos;
		PathNode* parent;
		std::list<PathNode*> adjacentList;
		float f;
		float g;
		float h;
	};

}