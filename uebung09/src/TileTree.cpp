/*
 * TileTree.cpp
 *
 *  Created on: Dec 27, 2016
 *      Author: twiemann
 */

#include "TileTree.hpp"

#include <iostream>
#include <cassert>
#include <cmath>
#include <stdlib.h>

using namespace std;



int TileTree::m_tileWidth = -1;
int TileTree::m_tileHeight = -1;


TileTree::TileTree(int x, int y, int w, int h, SplitAxis axis)
{
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;

	m_axis = axis;
	m_sub1 = 0;
	m_sub2 = 0;

	m_tiles = 0;
	m_numTiles = 0;

}



int TileTree::get(int i, int j)
{

	if(i*m_tileWidth > m_w || j*m_tileHeight > m_h){
		cout << "TileTree : index values too high!" << endl;
		exit(1);
	}

	if(m_sub1 || m_sub2){
		if(m_axis == VERTICAL){
			if(i*m_tileWidth < m_w/2 - ((m_w/2)%m_tileWidth)  && m_sub1){
				return m_sub1->get(i,j);
			} else{
				return m_sub2->get(i,j);
			}
		} else{
			if(j*m_tileHeight < m_h/2 - ((m_h/2)%m_tileHeight)  && m_sub1){
				return m_sub1->get(i,j);
			} else{
				return m_sub2->get(i,j);
			}
		}
	} else{
		if(m_axis == VERTICAL){
			return m_tiles[i-(m_x/m_tileWidth)];
		} else{
			return m_tiles[j-(m_y/m_tileHeight)];
		}
	}


	return 0;
}


void TileTree::insert(int i, int j, int index)
{
	if(m_tileWidth <0 || m_tileHeight <0){
		cout << "TileTree : wrong tileheight/width!" << endl;
		exit(1);
	}
	int x = m_tileWidth * i;
	int y = m_tileHeight * j;
	int splitx;
	int splity;
	int w;
	int h;
	int tmp;

	if(m_axis == VERTICAL){
		/* Split position */
		splitx = m_x + m_w/2;
		splity = m_y;
		if(!(splitx % m_tileWidth == 0)){
			tmp = splitx % m_tileWidth;
			if(tmp < m_tileWidth-tmp){
				splitx = splitx - tmp;
			} else splitx+=(m_tileWidth - tmp);
		}

		/*if(!(splity % m_tileHeight == 0)){
			tmp = splity % m_tileHeight;
			splity = splity - tmp;
		}*/
		/* end of split position */

		if(x < splitx){
			if(m_sub1){
				m_sub1 -> insert(i,j,index);
			} else{
				w = splitx-m_x;
				h = m_h;
				if(w > m_tileWidth){
					m_sub1 = new TileTree(splitx-(splitx - m_x),splity,w,h,HORIZONTAL);
				} else {
					tmp = (w/m_tileWidth);
					if(m_numTiles == 0){
						m_tiles = new int[10000];
					}
					m_numTiles++;
					tmp = m_x / m_tileWidth;
					m_tiles[i-tmp] = index;
				}
			}
		} else{
			if(m_sub2){
				m_sub2 -> insert(i,j,index);
			} else{
				w = m_w-(splitx-m_x);
				h = m_h;
				if(w > m_tileWidth){
					m_sub1 = new TileTree(splitx,splity,w,h,HORIZONTAL);
				} else {
					tmp = (w/m_tileWidth);
					if(m_numTiles == 0){
						m_tiles = new int[10000];
					}
					m_numTiles++;
					tmp = m_x / m_tileWidth;
					m_tiles[i-tmp] = index;
				}
			}
		}
	} else{
		/* Split position */
		splitx = m_x;
		splity = m_y + m_h/2;
		/*if(!(splitx % m_tileWidth == 0)){
			tmp = splitx % m_tileWidth;
			splitx = splitx - tmp;
		}*/

		if(!(splity % m_tileHeight == 0)){
			tmp = splity % m_tileHeight;
			if(tmp < m_tileHeight-tmp){
				splity-=tmp;
			} else splity+=(m_tileHeight - tmp);
		}
		/* end of split position */

		if(y < splity){
			if(m_sub1){
				m_sub1 -> insert(i,j,index);
			} else{
				w = m_w;
				h = splity - m_y;
				if(h > m_tileHeight){
					m_sub1 = new TileTree(splitx,splity-(splity - m_h),w,h,VERTICAL);
				} else {
					tmp = (h/m_tileHeight);
					if(m_numTiles == 0){
						m_tiles = new int[10000];
					}
					m_numTiles++;

					tmp = m_y / m_tileHeight;
					m_tiles[j-tmp] = index;    /* insert to array */
				}
			}
		} else{
			if(m_sub2){
				m_sub2 -> insert(i,j,index);
			} else{
				w = m_w;
				h = m_h - (splity- m_y);
				if(h > m_tileHeight){
					m_sub1 = new TileTree(splitx,splity,w,h,VERTICAL);
				} else {
					tmp = (h/m_tileHeight);
					if(m_numTiles == 0){
						m_tiles = new int[10000];
					}
					m_numTiles++;
					tmp = m_y / m_tileHeight;
					m_tiles[j-tmp] = index;   /* insert to array */
				}
			}
		}

	}

}

void TileTree::clear(){
	if(m_sub1){
		m_sub1->clear();
	}
	if(m_sub2){
		m_sub2->clear();
	}

	delete []m_tiles;
}


TileTree::~TileTree()
{
	clear();
}


