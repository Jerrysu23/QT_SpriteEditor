#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QPainter>
#include "spritelayout.h"
#include "colorpalette.h"
#include "filehandler.h"
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT
private:
    Ui::View* ui;
    SpriteLayout* spriteLayoutPtr;
    ColorPalette* colorPalettePtr;
    FileHandler* fileHandlerPtr;
    QTimer *mouseTimer;
    pair<int, int> getMousePositionInPixelCanvas();
    QGraphicsScene *scene;
    QVector<QPixmap> animationFrames;
    int mousePosX;
    int mousePosY;
    int canvasWindowSize = 512;
    int currentAnimationFrame;
    double canvasWindowStartingPointX;
    double canvasWindowStartingPointY;
    bool inStartScreen = true;
    bool gridEnabled = true;
    bool stopAnimation;
    bool showRealAnimationSize;
    bool setExportSize;
    void mousePressEvent(QMouseEvent *eventPress); // TODO: Should these be virutal like paintEvent?
    void mouseReleaseEvent(QMouseEvent *eventRelease);
    void exportFrameImage();
    void showPlaybackAnimation();
    void startAnimation();
    enum Tool{pen = 0, eraser = 1};
    Tool selectedTool = pen;
    int penSize = 1;
public:
    View(SpriteLayout& spriteLayout, ColorPalette& colorPalette, FileHandler& fileHandler, QWidget *parent = nullptr);
    ~View();
    virtual void paintEvent(QPaintEvent *event);///Basic painEvent for painting out drawing panel
public slots:
    void startSpriteEditor_slot();
    void drawGrid_slot();
    void mousePress_slot();
    void toggleGridLines_slot();
    void getFileName_slot();
    void getExistingFile_slot();
    void paintAnimationFrames_slot();
    void displayFps_slot();
    void addNewFrameButtonClicked_slot();
    void currFramesChange_slot();
    void removeFrameButtonClicked_slot();
    void advanceFrames_slot();
    void selectPen_slot();
    void selectEraser_slot();
    void changePenSize_slot(int size);
    void animationCheckboxToggled_slot();
    void setExportSize_slot();
signals:
    void setSpriteSize_signal(int);
    void saveNewFile_signal(QString);
    void openExistingFile_signal(QString, QByteArray);
};
#endif // VIEW_H
