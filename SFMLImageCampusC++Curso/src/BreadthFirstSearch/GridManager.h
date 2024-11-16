#pragma once

#include "../Utilities/Vector2fHash.h"
#include <unordered_map>
#include "Node.h"


class GridManager
{
private:
	std::unordered_map<sf::Vector2f, Node*, Vector2fHash, Vector2fEqual> nodesGrid;

public:
	GridManager();
	std::unordered_map<sf::Vector2f, Node*, Vector2fHash, Vector2fEqual>& GetNodesGrid() { return nodesGrid; }
	Node* GetNode(sf::Vector2f coordinates);
	void ResetNodes();
	
	//CREAR ACA LA GRILLA DE NODOS.
	//SE PERSEGUIRA A LOS NODOS OBJETIVO. ESTO SE DETERMINA A PARTIR DE LOS NODOS QUE PISA EL JUGADOR.
	//GUARDAMOS NODOS OBJETIVO EN UN ARREGLO?
	//HACER GETTER PARA DIBUJAR


};


