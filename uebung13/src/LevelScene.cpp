#include "LevelScene.hpp"
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QPixmap>
#include "GraphicsTileItem.hpp"

LevelScene::LevelScene(QString filename, MainWindow* window){
	

	m_mainWindow = window;

    //void mousePressEvent(QGraphicsSceneMouseEvent * event);

	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	else{
		QTextStream in(&file);
		QString tmp;
		QString pixname = 0;;
		in >> pixname; m_texFileName = pixname.toStdString(); std::cout << pixname.toStdString()<< " ";

		in >> tmp; m_tileWidth = tmp.toInt(); std::cout << tmp.toInt() << " ";
		in >> tmp; m_tileHeight = tmp.toInt(); std::cout << tmp.toInt() << " ";
		in >> tmp; m_tilesPerRow = tmp.toInt(); std::cout << tmp.toInt() << " ";
		in >> tmp; m_numRows = tmp.toInt(); std::cout << tmp.toInt()<< " ";
		in >> tmp; m_tileOffset = tmp.toInt(); std::cout << tmp.toInt()<< " ";
		in >> tmp; m_keyR = tmp.toInt(); std::cout << tmp.toInt()<< " ";
		in >> tmp; m_keyG = tmp.toInt(); std::cout << tmp.toInt()<< " ";
		in >> tmp; m_keyG = tmp.toInt(); std::cout << tmp.toInt()<< " ";
		in >> tmp; m_levelWidth = tmp.toInt(); std::cout << tmp.toInt()<< " ";
		in >> tmp; m_levelHeight = tmp.toInt(); std::cout << tmp.toInt() << std::endl;

		m_pixmap = new QPixmap(pixname);


   		window->label_4->setText("Level Width:  "+QString::number(m_levelWidth));
		window->label_3->setText("Level Height:  "+ QString::number(m_levelHeight));
		window->label_5->setText("Tile Width:  "+QString::number(m_tileWidth));
		window->label_2->setText("Tile Height:  "+ QString::number(m_tileHeight));
        window->label->setText("Bitmap-Name:  "+ pixname);
		


		m_tiles = new int*[m_levelHeight];
        for(int i = 0; i < m_levelHeight; i++)
        {
                m_tiles[i] = new int[m_levelWidth];
        }

        // Read tile numbers in grid
        for(int i = 0; i < m_levelHeight; i++)
        {
                for(int j = 0; j < m_levelWidth; j++)
                {
                        in >> tmp; m_tiles[i][j] = tmp.toInt();
                        std::cout << m_tiles[i][j] << " ";
                }
        }

        std::cout << " ENDEEEEEEEEEEEEEEEEEEEEEEEEEEEEE " << std::endl;

	}

	file.close();

	//GraphicTiles erzeugen

	GraphicsTileItem* item;
	QRect rect;
	int index;
	int col; //helpers
	int row; 
	int x1; //upper left of rect
	int y1;

	for(int i = 0; i < m_levelHeight ; i++){
		for(int j = 0; j< m_levelWidth ; j++){
			index = m_tiles[i][j] -1;
			if(index >=0){
				std::cout << index  << " " ;

				row = index / m_tilesPerRow;
                col = index % m_tilesPerRow;
				
				x1 = col*(m_tileWidth);
				if(col > 0)
                {
                    x1 += col * m_tileOffset;
                }
				
				y1 = row*(m_tileHeight);
				if(row > 0)
                {
                    y1 += row * m_tileOffset;
                
                }
                //soruce-rectangle coords
				rect.setCoords(x1,y1,x1+m_tileWidth,y1+m_tileHeight);
				//
				item = new GraphicsTileItem(m_pixmap, rect, index);
				//target on screen
				item->setX(j*m_tileWidth);
				item->setY(i*m_tileHeight);
				addItem(item);
			}
		
		}
	}
	std::cout << std::endl;

	


}


void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent * event){
    //connect(event, )
}
