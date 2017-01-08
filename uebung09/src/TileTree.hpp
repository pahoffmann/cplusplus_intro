/*
 * TileTree.hpp
 *
 *  Created on: Dec 27, 2016
 *      Author: twiemann
 */

#ifndef KD_KDTREE_TILETREE_HPP_
#define KD_KDTREE_TILETREE_HPP_

enum SplitAxis
{
	HORIZONTAL,
	VERTICAL
};

class TileTree
{
public:

	/***
	 * @brief 	Creates a new tile tree at position \ref x, ref y with width \ref w
	 * 			and height \ref h. \ref Split axis defines the axis on which the
	 * 			first split is performed. The position and bounding box information
	 * 			is given in global pixel space.
	 */
	TileTree(int x, int y, int w, int h, SplitAxis axis);

	/**
	 * @brief	Inserts a \ref element at the given *grid* position, hence \ref i
	 * 			and \ref j reference indices in the tile grid
	 */
	void insert(int i, int j, int tileIndex);

	/**
	 * @brief	Returns the tile at the given position
	 */
	int get(int i, int j);

	void clear();

	/// Destrcutor
	virtual ~TileTree();




	/// Width of the tiles in the tree
	static int		m_tileWidth;

	/// Height of the tiles in the tree
	static int		m_tileHeight;

protected:

	/// x position
	int 			m_x;

	/// y position
	int 			m_y;

	/// Width
	int 			m_w;

	/// Height
	int 			m_h;

	/// Split axis orientation
	SplitAxis 		m_axis;

	/// Upper / left sub tree (depending on split orientation)
	TileTree* 		m_sub1;

	/// Lower / right sub tree (depending on split orientation)
	TileTree* 		m_sub2;

	/// Array of tiles stored in the leafs
	int* 			m_tiles;

	/// Number of tiles on the tile leaf array
	int				m_numTiles;


};

#endif /* KD_KDTREE_TILETREE_HPP_ */
