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
	m_tiles1 = 0;
	m_numTiles = 0;
	m_numTiles1 = 0;
}



int TileTree::get(int i, int j)
{

	/*if(i*m_tileWidth > m_w || j*m_tileHeight > m_h){
		cout << "TileTree : index values too high!" << endl;
		exit(1);
	}*/

	int tmp;
	int splitXV;


	splitXV= m_x + m_w/2;
	if(splitXV % m_tileWidth != 0){
		tmp = splitXV % m_tileWidth;
		if(tmp < m_tileWidth - tmp){
			splitXV -= tmp;
		} else splitXV += (m_tileWidth - tmp);
	}

	int splitYH;
	splitYH = m_y + m_h/2;

	if(splitYH % m_tileHeight != 0){
		tmp = splitYH % m_tileHeight;
		if(tmp < m_tileHeight - tmp){
			splitYH -= tmp;
		} else splitYH += (m_tileHeight - tmp);
	}

	if(m_sub1 || m_sub2){
		if(m_axis == VERTICAL){

			if(i*m_tileWidth < splitXV  && m_sub1){
				return m_sub1->get(i,j);

			} else if(m_sub2){
				return m_sub2->get(i,j);
			}
		} else{

			if(j*m_tileHeight < splitYH  && m_sub1){
				return m_sub1->get(i,j);
			} else if(m_sub2){
				return m_sub2->get(i,j);
			}
		}
	} else{
		if(m_axis == VERTICAL){

			//cout << " length: " << m_numTiles << "  " << m_numTiles1 << endl;
			if(i*m_tileWidth < splitXV)
				return m_numTiles;//m_tiles[j-(m_y/m_tileHeight)];
			else return m_numTiles1;//m_tiles1[j-(m_y/m_tileHeight)];


		} else{
			//cout << " length: " << m_numTiles << "  " << m_numTiles1 << endl;
			if(j*m_tileHeight < splitYH)
				return m_numTiles;//m_tiles[i-(m_x/m_tileWidth)];
			else
				return m_numTiles1;//m_tiles1[i-(m_x/m_tileWidth)];
		}
	}


	return 0;
}

void TileTree::insert(int i, int j,int index){

	int splitX;
	int splitY;
	int tileX = m_tileWidth  * i;
	int tileY = m_tileHeight * j;
	int subW;
	int subH;
	int tmp;

	if(index > 0){
		if(m_axis == VERTICAL){                   /* VERTICAL STARTS HERE */
			splitX = m_x + m_w/2;
			splitY = m_y;

			if(splitX % m_tileWidth != 0){
				tmp = splitX % m_tileWidth;
				if(tmp < m_tileWidth - tmp){
					splitX -= tmp;
				} else splitX += (m_tileWidth - tmp);
			}

			if(tileX < splitX){					  /* LEFT SUB TREE HERE */
				if(m_sub1) m_sub1 -> insert(i,j,index);
				else{
					subW = splitX - m_x;
					subH = m_h;
					if(subW > m_tileWidth) m_sub1 = new TileTree(m_x,m_y,subW,subH,HORIZONTAL);
					else{
						if(m_numTiles == 0){
							tmp = m_h/m_tileHeight;
							m_tiles = new int[tmp];
							m_numTiles = tmp;
						}

						m_tiles[j-(m_y/m_tileHeight)] = index;


					}
				}
			} else {                              /* RIGHT SUB TREE HERE */
				if(m_sub2){cout << "test" <<endl; m_sub2 -> insert(i,j,index); }
				else{
					subW = m_x + m_w - splitX;
					subH = m_h;
					if(subW > m_tileWidth) m_sub2 = new TileTree(splitX,m_y,subW,subH,HORIZONTAL);
					else{
						if(m_numTiles1 == 0){
							tmp = m_h/m_tileHeight;
							m_tiles1 = new int[tmp];
							m_numTiles1 = tmp;
						}

						m_tiles1[j-(m_y/m_tileHeight)] = index;
					}
				}
			}


		} else{									  /* HORIZONTAL STARTS HERE */
			splitX = m_x;
			splitY = m_y + m_h/2;

			if(splitY % m_tileHeight != 0){
				tmp = splitY % m_tileHeight;
				if(tmp < m_tileHeight - tmp){
					splitY -= tmp;
				} else splitY += (m_tileHeight - tmp);
			}

			if(tileY < splitY){					  /* LEFT SUB TREE HERE */
				if(m_sub1) m_sub1 -> insert(i,j,index);
				else{
					subW = m_w;
					subH = splitY - m_y;
					if(subH > m_tileHeight) m_sub1 = new TileTree(m_x,m_y,subW,subH,VERTICAL);
					else{
						if(m_numTiles == 0){
							tmp = m_w/m_tileWidth;
							m_tiles = new int[tmp];
							m_numTiles = tmp;
						}

						m_tiles[i-(m_x/m_tileWidth)] = index;


					}
				}
			} else {                              /* RIGHT SUB TREE HERE */
				if(m_sub2) m_sub2 -> insert(i,j,index);
				else{
					subW = m_w;
					subH = m_y + m_h - splitY;
					if(subW > m_tileWidth) m_sub2 = new TileTree(m_x,splitY,subW,subH,VERTICAL);
					else{
						if(m_numTiles1 == 0){
							tmp = m_w/m_tileWidth;
							m_tiles1 = new int[tmp];
							m_numTiles1 = tmp;
						}


						m_tiles1[i-(m_x/m_tileWidth)] = index;
					}
				}
			}
		}
	}
}
/*void TileTree::insert(int i, int j, int index)
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
		 //Split position
		splitx = m_x + m_w/2;
		splity = m_y;
		if(!(splitx % m_tileWidth == 0)){
			tmp = splitx % m_tileWidth;
			if(tmp < m_tileWidth-tmp){
				splitx = splitx - tmp;
			} else splitx+=(m_tileWidth - tmp);
		}
		// end of split position

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
		// Split position
		splitx = m_x;
		splity = m_y + m_h/2;

		if(!(splity % m_tileHeight == 0)){
			tmp = splity % m_tileHeight;
			if(tmp < m_tileHeight-tmp){
				splity-=tmp;
			} else splity+=(m_tileHeight - tmp);
		}
		// end of split position

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
					m_tiles[j-tmp] = index;
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
					m_tiles[j-tmp] = index;
				}
			}
		}

	}

}*/

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


