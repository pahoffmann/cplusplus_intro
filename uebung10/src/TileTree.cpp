/*
 * TileTree.tcc
 *
 *  Created on: Dec 27, 2016
 *      Author: twiemann
 */


#include <iostream>
#include <cassert>
#include <cmath>
#include "JumperTypes.hpp"
#include <functional>

using std::cout;
using std::endl;

namespace jumper
{

template<typename T>
T TileTree<T>::TileWidth = -1;

template<typename T>
T TileTree<T>::TileHeight = -1;

template<typename T>
T TileTree<T>::IndexHelper::operator[](int x)
{
    return m_parent->get(x, m_y);
}

template<typename T>
TileTree<T>::TileTree(int x, int y, int w, int h, SplitAxis axis) :
    m_x(x), m_y(y), m_w(w), m_h(h), m_axis(axis), m_sub1(0), m_sub2(0)
{
    m_tiles = 0;
    m_numTiles = 0;
}

template<typename T>
SDL_Rect TileTree<T>::getRect() const
{
	SDL_Rect r;
        r.x = m_x * TileWidth;
        r.y = m_y * TileHeight;
        r.w = m_w * TileWidth;
        r.h = m_h * TileHeight;

	return r;
}

template<typename T>
int TileTree<T>::getSplitPosition(const SplitAxis& axis) const
{
    float globalSplitPosition;
    if(axis == VERTICAL)
    {
        globalSplitPosition = m_x + (float) m_w / 2.0f;
        return round(globalSplitPosition);
    }
    else
    {
        globalSplitPosition = m_y + (float) m_h / 2.0f;
        return round(globalSplitPosition);
    }
}

template<typename T>
T TileTree<T>::get(int x, int y) const
{
    // Reference point in tile coordinates that is
    // compared to the split axis position.
    int ref;

    // Position of the searched point in the index
    // array
    int pos;

    // Calculate reference point, index position and
    // split axis position
    if(m_axis == VERTICAL)
    {
        ref = x;
        pos = y - m_y;
    }
    else
    {
        ref = y;
        pos = x - m_x;
    }
    int	splitPosition = getSplitPosition(m_axis);

    // Search recursively in the two sub trees
    // if they exist. If a leaf is found, check
    // if an index value was saved and return
    // it if so. If the leaf is empty return 0.
    if(ref < splitPosition)
    {
        if(m_sub1)
        {
            return m_sub1->get(x, y);
        }
        else
        {
            if(m_tiles != 0)
            {
                return m_tiles[pos];
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        if(m_sub2)
        {
            return m_sub2->get(x, y);
        }
        else
        {
            if(m_tiles != 0)
            {
                return m_tiles[pos];
            }
            else
            {
                return 0;
            }
        }
    }
}

template<typename T>
void TileTree<T>::clip(const Camera& cam, TileList& list)
{
    const SDL_Rect camRect = cam.getRect();
    Tile tile;

    if(m_sub1 || m_sub2){
        if(m_sub1){
            const SDL_Rect lhs=m_sub1->getRect();
            if(SDL_HasIntersection(&lhs,&camRect)){
             m_sub1->clip(cam, list);
            }
        }
        if(m_sub2){
            const SDL_Rect rhs=m_sub2->getRect();
            if(SDL_HasIntersection(&rhs,&camRect)){
                m_sub2->clip(cam, list);
            }
        } 
    } else{
        const SDL_Rect tmp = this->getRect();
        if(SDL_HasIntersection(&tmp,&camRect)){
            for(int i = 0; i< m_numTiles; i++){
                std::get<0>(tile) = m_tiles[i];
                if(m_axis == VERTICAL){
                    std::get<1>(tile) = m_x;
                    std::get<2>(tile) = m_y+i;   
                } else{
                    std::get<1>(tile) = m_x+i;
                    std::get<2>(tile) = m_y;
                }
                
                //std::cout << "Index: " <<std::get<0>(tile) << " " << std::get<1>(tile) << std::endl;
                if(std::get<0>(tile)!=0){
                    list.push_back(tile);      
                }
              
            }
        }
    }



    

}

template<typename T>
void TileTree<T>::insert(int x, int y, T index)
{
    // Do not insert empty tiles
    if(index == 0)
    {
        // Note: This means that tiles cannot be cleared, but we won't change
        // the level after it's loaded anyways.
        return;
    }

    // Determine sub tree for current tile
    if(m_axis == VERTICAL)
    {
        // Determine horizontal split position, i.e., the
        // sub tree position plus half the with of the sub tree.
        // Make sure, that the position is a multiple of the
        // tile width
        int splitPosition = getSplitPosition(VERTICAL);

        // Determine in which sub tree the tile belongs
        if(x < splitPosition)
        {
            if(m_sub1)
            {
                m_sub1->insert(x, y, index);
            }
            else
            {
                // Check if we have to subdivide
                if(m_w > 1)
                {
                    int newWidth = splitPosition - m_x;
                    m_sub1 = new TileTree<T>(m_x, m_y, newWidth, m_h, HORIZONTAL);
                    m_sub1->insert(x, y, index);
                }
                else
                {
                    m_numTiles = m_h;
                    if(m_tiles == 0)
                    {
                        m_tiles = new T[m_numTiles];
                        for(int a = 0; a < m_numTiles; a++)
                        {
                            m_tiles[a] = 0;
                        }
                    }

                    // Determine entry and save tile index
                    int pos = y - m_y;
                    m_tiles[pos] = index;

                }
            }
        }
        else
        {
            if(m_sub2)
            {
                m_sub2->insert(x, y, index);
            }
            else
            {
                // Check if we have to subdivide
                if(m_w > 1)
                {
                    m_sub2 = new TileTree<T>(splitPosition, m_y, m_x + m_w - splitPosition, m_h, HORIZONTAL);
                    m_sub2->insert(x, y, index);
                }
                else
                {
                    m_numTiles = m_h;
                    if(m_tiles == 0)
                    {
                        m_tiles = new T[m_numTiles];
                        for(int a = 0; a < m_numTiles; a++)
                        {
                            m_tiles[a] = 0;
                        }
                    }

                    // Determine entry
                    int pos = y - m_y;
                    m_tiles[pos] = index;
                }
            }
        }
    }
    else
    {
        // Determine horizontal split position, i.e., the
        // sub tree position plus half the with of the sub tree.
        // Make sure, that the position is a multiple of the
        // tile width
        int splitPosition = getSplitPosition(HORIZONTAL);
        // Determine in which sub tree the tile belongs
        if(y < splitPosition)
        {
            if(m_sub1)
            {
                m_sub1->insert(x, y, index);
            }
            else
            {
                // Check if we have to subdivide
                if(m_h > 1)
                {
                    int newHeight = splitPosition - m_y;
                    m_sub1 = new TileTree<T>(m_x, m_y, m_w, newHeight, VERTICAL);
                    m_sub1->insert(x, y, index);
                }
                else
                {

                    m_numTiles = m_w;
                    if(m_tiles == 0)
                    {
                        m_tiles = new int[m_numTiles];
                        for(int a = 0; a < m_numTiles; a++)
                        {
                            m_tiles[a] = 0;
                        }
                    }

                    // Determine entry
                    int pos = x - m_x;
                    m_tiles[pos] = index;
                }
            }
        }
        else
        {
            if(m_sub2)
            {
                m_sub2->insert(x, y, index);
            }
            else
            {
                // Check if we have to subdivide
                if(m_h > 1)
                {
                    m_sub2 = new TileTree<T>(m_x, splitPosition, m_w, splitPosition - m_y, VERTICAL);
                    m_sub2->insert(x, y, index);
                }
                else
                {
                    m_numTiles = m_w;
                    if(m_tiles == 0)
                    {
                        m_tiles = new int[m_numTiles];
                        for(int a = 0; a < m_numTiles; a++)
                        {
                            m_tiles[a] = 0;
                        }
                    }

                    // Determine entry save index
                    int pos = x - m_x;
                    m_tiles[pos] = index;
                }
            }
        }
    }
}

template<typename T>
TileTree<T>::~TileTree()
{
    if(m_sub1)
    {
        delete m_sub1;
    }

    if(m_sub2)
    {
        delete m_sub2;
    }

    if(m_tiles)
    {
        delete[] m_tiles;
    }

}

}
