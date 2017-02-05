#include "GraphicsTileItem.hpp"
#include <QPointF>
#include <iostream>

GraphicsTileItem::GraphicsTileItem(QPixmap *tileset, const QRect &rect, int index){
	
	setPixmap(tileset->copy(rect));
    setIndex(index);
	
}

GraphicsTileItem::GraphicsTileItem(QColor *color, int w, int h){

}


/*void GraphicsTileItem::mouseClicked(int index){



}*/

void GraphicsTileItem::mousePressEvent(QGraphicsSceneMouseEvent * event){
    //emit mouseClicked(getIndex());
    QPointF p= event->scenePos();
    std::cout <<"Coords: " << p.x() << " | " << p.y() <<  " Index : " << getIndex() << std::endl;
}


GraphicsTileItem::~GraphicsTileItem(){
	//TODO
}
