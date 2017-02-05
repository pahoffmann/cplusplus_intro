#include "GraphicsTileItem.hpp"

GraphicsTileItem::GraphicsTileItem(QPixmap *tileset, const QRect &rect, int index){
	
	setPixmap(tileset->copy(rect));
	
}

GraphicsTileItem::GraphicsTileItem(QColor *color, int w, int h){

}

void GraphicsTileItem::mousePressEvent(QGraphicsSceneMouseEvent * event){

}


GraphicsTileItem::~GraphicsTileItem(){
	//TODO
}
