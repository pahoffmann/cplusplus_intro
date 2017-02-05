#ifndef LEVEL_SCENE_HPP
#define LEVEL_SCENE_HPP

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "MainWindow.hpp"

class LevelScene : public QGraphicsScene
{
	Q_OBJECT;
public:
    /// Loads des Level with the given filenale nad
    /// Stores a pointer to it's main window in a
    /// class valiable.
	LevelScene(QString filename, MainWindow* window);
protected:
    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

/*public slots:
    void levelClicked(int index);*/
private:  
  int** m_tiles;        // The 2D tile array
  QPixmap* m_pixmap;    // A QPixmap to store the tile bitmap
	int m_tileWidth;      // Width of the tiles
	int m_tileHeight;     // Height of the tiles
	int m_tilesPerRow;    // Tiles per row in the tile bitmap
	int m_numRows;        // Number of rows in the tile bitmap
	int m_tileOffset;     // Offset between the tiles
	int m_levelWidth;     // Level width (in tiles)
	int m_levelHeight;    // Level height in tiles
	int m_keyR;           // Key color r component
	int m_keyG;           // Key color g component
	int m_keyB;           // Key color b component
	std::string m_texFileName; // File name of the tile bitmap
	MainWindow* m_mainWindow; // Pointer to a main window
};

#endif
