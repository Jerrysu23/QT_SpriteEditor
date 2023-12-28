#include "view.h"
#include "ui_view.h"
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <tuple>
#include <QAction>

/**
 * @brief View::View
 * @param spriteLayout
 * @param colorPalette
 * @param fileHandler
 * @param parent
 */
View::View(SpriteLayout& spriteLayout, ColorPalette& colorPalette, FileHandler& fileHandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

    spriteLayoutPtr = &spriteLayout;
    colorPalettePtr = &colorPalette;
    fileHandlerPtr = &fileHandler;

    ui->gridToggleButton->setVisible(false);
    ui->colorButton1->setVisible(false);
    ui->colorButton2->setVisible(false);
    ui->colorButton3->setVisible(false);
    ui->colorButton4->setVisible(false);
    ui->colorButton5->setVisible(false);
    ui->colorButton6->setVisible(false);
    ui->colorButton7->setVisible(false);
    ui->colorButton8->setVisible(false);
    ui->colorButton9->setVisible(false);
    ui->changeColorButton->setVisible(false);
    ui->addNewFrame_Button->setVisible(false);
    ui->removeFrame_button->setVisible(false);
    ui->framescomboBox->setVisible(false);
    ui->eraserButton->setVisible(false);
    ui->penSizeLabel->setVisible(false);
    ui->penSizeBox->setVisible(false);
    ui->penButton->setVisible(false);
    ui->selectFrameLabel->setVisible(false);

    ui->spriteSizeComboBox->addItem("Size of sprite");
    ui->spriteSizeComboBox->addItem("4");
    ui->spriteSizeComboBox->addItem("8");
    ui->spriteSizeComboBox->addItem("16");
    ui->spriteSizeComboBox->addItem("32");
    ui->spriteSizeComboBox->addItem("64");
    ui->spriteSizeComboBox->addItem("128");
    ui->selectFrameLabel->setStyleSheet("QLabel {color : white;}");
    ui->penSizeLabel->setStyleSheet("QLabel {color : white;}");
    ui->fpsLabel->setStyleSheet("QLabel {color : white;}");

    connect(ui->spriteSizeComboBox, &QComboBox::currentIndexChanged, this, &View::startSpriteEditor_slot);
    connect(this, &View::setSpriteSize_signal, &spriteLayout, &SpriteLayout::setGridSize_slot);
    connect(&spriteLayout, &SpriteLayout::drawGrid_signal, this, &View::drawGrid_slot);
    connect(ui->gridToggleButton, &QPushButton::clicked, this, &View::toggleGridLines_slot);
    connect(ui->penButton, &QPushButton::clicked, this, &View::selectPen_slot);
    connect(ui->eraserButton, &QPushButton::clicked, this, &View::selectEraser_slot);
    connect(ui->penSizeBox, &QSpinBox::valueChanged, this, &View::changePenSize_slot);

    // Color Palette Connections
    connect(ui->colorButton1,&QPushButton::clicked, &colorPalette, &ColorPalette::setColor1_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor1_signal, ui->colorButton1, &QPushButton::setStyleSheet);
    connect(ui->colorButton2, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor2_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor2_signal, ui->colorButton2, &QPushButton::setStyleSheet);
    connect(ui->colorButton3, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor3_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor3_signal, ui->colorButton3, &QPushButton::setStyleSheet);
    connect(ui->colorButton4, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor4_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor4_signal, ui->colorButton4, &QPushButton::setStyleSheet);
    connect(ui->colorButton5, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor5_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor5_signal, ui->colorButton5, &QPushButton::setStyleSheet);
    connect(ui->colorButton6, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor6_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor6_signal, ui->colorButton6, &QPushButton::setStyleSheet);
    connect(ui->colorButton7, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor7_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor7_signal, ui->colorButton7, &QPushButton::setStyleSheet);
    connect(ui->colorButton8, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor8_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor8_signal, ui->colorButton8, &QPushButton::setStyleSheet);
    connect(ui->colorButton9, &QPushButton::clicked, &colorPalette, &ColorPalette::setColor9_slot);
    connect(&colorPalette, &ColorPalette::setButtonColor9_signal, ui->colorButton9, &QPushButton::setStyleSheet);
    connect(ui->changeColorButton, &QPushButton::clicked, &colorPalette, &ColorPalette::changeColor_slot);

    //Add new frame
    connect(ui->addNewFrame_Button, &QPushButton::clicked, this, &View::addNewFrameButtonClicked_slot);
    connect(ui->addNewFrame_Button, &QPushButton::clicked, &spriteLayout, &SpriteLayout::updateNumberOfFrames_slot);
    connect(ui->framescomboBox, &QComboBox::currentIndexChanged, &spriteLayout, &SpriteLayout::updateCurrFrame_slot);
    connect(&spriteLayout, &SpriteLayout::currFramesChange_signal, this, &View::currFramesChange_slot);
    connect(ui->removeFrame_button, &QPushButton::clicked, &spriteLayout, &SpriteLayout::removeFrames_slot);
    connect(&spriteLayout, &SpriteLayout::removeFrameButtonClicked_signal, this, &View::removeFrameButtonClicked_slot);

    /* The purpose of mouseTimer is to solve the "click and drag" problem with drawing. We can just update a pixel
    when we click on it, me must update pixels as we drag across them with the mouse held down, and for this we need
    to check many times a second if we are still holding down our mouse button and if our mouse comes across a new
    pixel that we need to modify. */
    mouseTimer = new QTimer(this);
    connect(mouseTimer, &QTimer::timeout, this, &View::mousePress_slot);

    QAction *open = new QAction("&Open", this);
    QAction *saveAs = new QAction("&Save As", this);
    QAction *save = new QAction("&Save", this);
    QAction *exportSprite = new QAction("&Export Sprite Image", this);
    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(open);
    file->addAction(saveAs);
    file->addAction(save);
    file->addAction(exportSprite);

    connect(saveAs, &QAction::triggered, this, &View::getFileName_slot);
    connect(this, &View::saveNewFile_signal, &fileHandler, &FileHandler::saveNewFile_slot);
    connect(&fileHandler, &FileHandler::getFileName_signal, this, &View::getFileName_slot);
    connect(open, &QAction::triggered, this, &View::getExistingFile_slot);
    connect(save, &QAction::triggered, &fileHandler, &FileHandler::saveExistingFile_slot);
    connect(this, &View::openExistingFile_signal, &fileHandler, &FileHandler::openExistingFile_slot);
    connect(exportSprite, &QAction::triggered, this, &View::exportFrameImage);
    connect(ui->fpsSlider, &QSlider::sliderMoved, this, &View::displayFps_slot);
    connect(ui->animationSizeCheckBox, &QCheckBox::toggled, this, &View::animationCheckboxToggled_slot);
    connect(ui->exportSizeCheckBox, &QCheckBox::toggled, this, &View::setExportSize_slot);
    connect(ui->playAnimationButton, &QPushButton::clicked, this, &View::paintAnimationFrames_slot);

    ui->fpsSlider->setValue(5);
    ui->currentFpsLabel->setText(QString::number(5));
    ui->fpsSlider->setMinimum(1);
    ui->animationSizeCheckBox->setVisible(false);
    showRealAnimationSize = false;
    setExportSize = false;
    ui->exportSizeCheckBox->setVisible(false);
    ui->playAnimationButton->setVisible(false);
    ui->fpsSlider->setVisible(false);
    ui->fpsLabel->setVisible(false);
    ui->currentFpsLabel->setVisible(false);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVisible(false);
}

/**
 * @brief View::~View deconstrutor for view
 */
View::~View()
{
    delete ui;
}

/**
 * @brief View::startSpriteEditor_slot gets called when a user chooses a frame size. It then sets the visibility to UI components to ready the UI for the user
 */
void View::startSpriteEditor_slot()
{
    inStartScreen = false;
    ui->fpsLabel->setVisible(true);
    ui->fpsSlider->setVisible(true);
    ui->currentFpsLabel->setVisible(true);
    ui->graphicsView->setVisible(true);
    ui->colorButton1->setVisible(true);
    ui->colorButton2->setVisible(true);
    ui->colorButton3->setVisible(true);
    ui->colorButton4->setVisible(true);
    ui->colorButton5->setVisible(true);
    ui->colorButton6->setVisible(true);
    ui->colorButton7->setVisible(true);
    ui->colorButton8->setVisible(true);
    ui->colorButton9->setVisible(true);
    ui->gridToggleButton->setVisible(true);
    ui->changeColorButton->setVisible(true);
    ui->spriteSizeComboBox->setVisible(false);
    ui->playAnimationButton->setVisible(true);
    ui->penSizeLabel->setVisible(true);
    ui->eraserButton->setVisible(true);
    ui->penSizeBox->setVisible(true);
    ui->penButton->setVisible(true);
    ui->selectFrameLabel->setVisible(true);
    ui->animationSizeCheckBox->setVisible(true);
    ui->exportSizeCheckBox->setVisible(true);

    emit setSpriteSize_signal(ui->spriteSizeComboBox->itemText(ui->spriteSizeComboBox->currentIndex()).toInt());

    // Add new frame.
    ui->framescomboBox->addItem("1");
    ui->addNewFrame_Button->setVisible(true);
    ui->addNewFrame_Button->setEnabled(true);
    ui->framescomboBox->setVisible(true);
    ui->removeFrame_button->setVisible(true);
}

/**
 * @brief View::drawGrid_slot calls repaint, shows or removes the grid from the frame view
 */
void View::drawGrid_slot()
{
    View::repaint();
}

/**
 * @brief View::paintEvent sets corresponding pixel data on the screen
 * @param event
 */
void View::paintEvent(QPaintEvent *event)
{
    if (inStartScreen)
        return;

    canvasWindowStartingPointX = (this->size().width() / 2) - (canvasWindowSize / 2);
    canvasWindowStartingPointY = (this->size().height() / 2) - (canvasWindowSize / 2);

    QPainter painter(this);
    QBrush brush;
    QPen pen;

    // Paint white background for pixel canvas.
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(QRect(canvasWindowStartingPointX, canvasWindowStartingPointY, canvasWindowSize, canvasWindowSize));

    // Paint diagonal over white background.
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::BDiagPattern);
    painter.setBrush(brush);
    painter.drawRect(QRect(canvasWindowStartingPointX, canvasWindowStartingPointY, canvasWindowSize, canvasWindowSize));

    // Paint every pixel in the frame.
    vector<vector<tuple<int, int, int, int>>> data = spriteLayoutPtr->getFrameData();
    for (int i = 0; i < (int)data.size(); i++)
    {
       for (int j = 0; j < (int)data.size(); j++)
       {
           tuple<int, int, int, int> colorData = data[i][j];
           brush.setColor(QColor(get<0>(colorData), get<1>(colorData), get<2>(colorData), get<3>(colorData)));
           brush.setStyle(Qt::SolidPattern);
           painter.setBrush(brush);
           if (!gridEnabled)
           {
               painter.setPen(Qt::NoPen);
           }
           double pixelSize = canvasWindowSize / data.size();
           painter.drawRect(QRect(canvasWindowStartingPointX + (j * pixelSize), canvasWindowStartingPointY + (i * pixelSize), pixelSize, pixelSize));
       }
    }
}

/**
 * @brief View::mousePressEvent
 * @param eventPress
 */
void View::mousePressEvent(QMouseEvent *eventPress)
{
    //Trigger when mouse clicked
    if (inStartScreen)
        return;

    // While holding down mouse, check for pixel edits 1000 times a second.
    mouseTimer->start(5);
}

/**
 * @brief View::mouseReleaseEvent
 * @param eventRelease
 */
void View::mouseReleaseEvent(QMouseEvent *eventRelease)
{
    mouseTimer->stop();
}

/**
 * @brief View::mousePress_slot checks if the click is a valid action to change any UI components and then updates the frame data if necessary
 */
void View::mousePress_slot()
{
    if (inStartScreen)
        return;

    stopAnimation = true;
    pair<int, int> mousePosXY = View::getMousePositionInPixelCanvas();

    // If our mouse is in the canvas display, modify pixels.
    if ((mousePosXY.first > 0) && (mousePosXY.first < canvasWindowSize) && (mousePosXY.second > 0) && (mousePosXY.second < canvasWindowSize))
    {
        int pixelX = mousePosXY.first / (canvasWindowSize / spriteLayoutPtr->getFrameSize());
        int pixelY = mousePosXY.second / (canvasWindowSize / spriteLayoutPtr->getFrameSize());

        QColor qColor = colorPalettePtr->getSelectedColor();
        tuple<int, int, int, int> pixelPen;
        if (selectedTool == pen)
            pixelPen = {qColor.red(), qColor.green(), qColor.blue(), qColor.alpha()};
        else if (selectedTool == eraser)
            pixelPen = {0, 0, 0, 0};

        int startingPixelOffset;
        if (penSize % 2 == 0)
            startingPixelOffset = (penSize / 2) - 1;
        else
            startingPixelOffset = penSize / 2;
        for (int i = 0; i < penSize; i++)
            for (int j = 0; j < penSize; j++)
                if ((pixelY - i + startingPixelOffset) >= 0
                        && (pixelY - i + startingPixelOffset) <= (spriteLayoutPtr->getFrameSize() - 1)
                        && (pixelX - j + startingPixelOffset) >= 0
                        && (pixelX - j + startingPixelOffset) <= (spriteLayoutPtr->getFrameSize() - 1))
                    spriteLayoutPtr->setFrameData(spriteLayoutPtr->getCurrentFrame(), pixelY - i + startingPixelOffset, pixelX - j + startingPixelOffset, pixelPen);
        update();
    }
}

/**
 * @brief View::getMousePositionInPixelCanvas converts mouse click coordinates to frame coordinates to set the data in the spriteLayout frames
 * @return
 */
pair<int, int> View::getMousePositionInPixelCanvas()
{
    double frameWindowStartingPointX = (this->size().width() / 2) - (canvasWindowSize / 2);
    double frameWindowStartingPointY = (this->size().height() / 2) - (canvasWindowSize / 2);

    int mousePosX = QCursor::pos().x();
    int mousePosY = QCursor::pos().y();

    int windowPosX = this->pos().x();
    int windowPosY = this->pos().y();

    int mouseWindowPosX = mousePosX - windowPosX;
    int mouseWindowPosY = mousePosY - windowPosY - 30;

    int mouseFramePosX = mouseWindowPosX - frameWindowStartingPointX;
    int mouseFramePosY = mouseWindowPosY - frameWindowStartingPointY;

    return {mouseFramePosX, mouseFramePosY};
}

/**
 * @brief View::toggleGridLines_slot enables or disables gridLines
 */
void View::toggleGridLines_slot()
{
    gridEnabled = !gridEnabled;
    update();
}

/**
 * @brief View::getFileName_slot retrieves the file name for saving a file then calls the fileHandler to actually produce JSON file
 */
void View::getFileName_slot(){
    if (inStartScreen)
        return;

    QString fileName = QFileDialog::getSaveFileName(this, "Save As", "savedSprite", tr("Sprite JSON (*.spp)"));
    if (fileName.isEmpty())
    {
        QMessageBox::information(this, tr("No File Name"), tr("We were unable to save your sprite because there was no file name entered. Please try again."), QMessageBox::Ok);
        return;
    }

    emit saveNewFile_signal(fileName);
}

/**
 * @brief View::getExistingFile_slot if file exists then the user can contuously save their sprite to the existing save
 */
void View::getExistingFile_slot()
{
    function fileContentReady = [this](const QString &fileName, const QByteArray &fileContent)
    {
        if (fileName.isEmpty())
        {
            QMessageBox::information(this, tr("Error Opening File"), tr("There was an error opening your file. Please try again or choose a different file."), QMessageBox::Ok);
            return;
        }
        else
        {
            emit openExistingFile_signal(fileName, fileContent);
        }
    };
    QFileDialog::getOpenFileContent("Sprite JSON (*.spp)", fileContentReady);
}

/**
 * @brief View::setExportSize_slot changes the current value to setExport size so the user can determine what size the frame exports as
 */
void View::setExportSize_slot(){
    setExportSize = !setExportSize;
}

/**
 * @brief View::exportFrameImage exporting the current frame to a PNG, asks user what they would like to name their file and then saves to their computer
 */
void View::exportFrameImage()
{
    if (inStartScreen)
        return;

    int exportPixmapSize;
    if (setExportSize)
    {
        exportPixmapSize = spriteLayoutPtr->getFrameSize();
    } else
    {
        exportPixmapSize = 512;
    }

    // Get file name from user to save image
    QString fileName = QFileDialog::getSaveFileName(this, "Save Frame Image", "spriteFrame", tr("Images (*.png)"));

    // Initialize pixmap and necessary painting objects to create image data
    QPixmap pixmap(exportPixmapSize, exportPixmapSize);
    QPainter painter(&pixmap);
    QBrush brush;

    // Set white background for sprite
    pixmap.fill(Qt::white);

    // Paint every pixel in the frame.
    vector<vector<tuple<int, int, int, int>>> data = spriteLayoutPtr->getFrameData();
    for (int i = 0; i < (int)data.size(); i++)
    {
       for (int j = 0; j < (int)data.size(); j++)
       {
           tuple<int, int, int, int> colorData = data[i][j];
           brush.setColor(QColor(get<0>(colorData), get<1>(colorData), get<2>(colorData), get<3>(colorData)));
           brush.setStyle(Qt::SolidPattern);
           painter.setBrush(brush);
           painter.setPen(Qt::NoPen);

           double pixelSize = exportPixmapSize / data.size();
           painter.drawRect(QRect((j * pixelSize), (i * pixelSize), pixelSize, pixelSize));
       }
    }
    pixmap.save(fileName + ".png");
}

/**
 * @brief View::animationCheckboxToggled_slot change the current state of the showRealAnimationSize variable
 */
void View::animationCheckboxToggled_slot(){
    showRealAnimationSize = !showRealAnimationSize;
    stopAnimation = true;
}

/**
 * @brief View::paintAnimationFrames_slot paints the current frames to a vector of pixmaps. This is used for the animation and is called when the refresh animation button is pressed
 */
void View::paintAnimationFrames_slot()
{
    if (!stopAnimation)
    {
        stopAnimation = !stopAnimation;
        return;
    }
    stopAnimation = !stopAnimation;

    int animationFrameSize;
    if (showRealAnimationSize)
    {
        animationFrameSize = spriteLayoutPtr->getFrameSize();
    }
    else
    {
        animationFrameSize = 128;
    }

    scene->clear();
    animationFrames.clear();
    for (int i = 0; i < spriteLayoutPtr->getNumberOfFrames(); i++)
    {
        QPixmap pixmap(animationFrameSize, animationFrameSize);
        QPainter painter(&pixmap);
        QBrush brush;
        // Set white background for sprite
        pixmap.fill(Qt::white);

        brush.setColor(Qt::gray);
        brush.setStyle(Qt::BDiagPattern);
        painter.setBrush(brush);
        painter.drawRect(QRect(0, 0, animationFrameSize, animationFrameSize));

        // Paint every pixel in the frame.
        vector<vector<tuple<int, int, int, int>>> data = spriteLayoutPtr->getFrameData(i); // need to add index so we get the right frame
        for (int i = 0; i < (int)data.size(); i++)
        {
            for (int j = 0; j < (int)data.size(); j++)
            {
                tuple<int, int, int, int> colorData = data[i][j];
                brush.setColor(QColor(get<0>(colorData), get<1>(colorData), get<2>(colorData), get<3>(colorData)));
                brush.setStyle(Qt::SolidPattern);
                painter.setBrush(brush);
                painter.setPen(Qt::NoPen);

                double pixelSize = animationFrameSize / data.size();
                painter.drawRect(QRect((j * pixelSize), (i * pixelSize), pixelSize, pixelSize));
            }
        }
        animationFrames.push_back(pixmap);
    }
    startAnimation();
}

/**
 * @brief View::startAnimation gets called after frames are painted for animation, start the recursive timer
 */
void View::startAnimation()
{
    stopAnimation = false;
    currentAnimationFrame = 0;
    advanceFrames_slot();
}

/**
 * @brief View::advanceFrames_slot calls itself repeatedly if the animation has not been stopped. Iterates through the pixmap array to show next frame on QGraphicsScene
 */
void View::advanceFrames_slot()
{
    if (stopAnimation)
        return;

    if (animationFrames.size() == 1)
    {
        scene->addPixmap(animationFrames[0]);
        currentAnimationFrame = 0;
        return;
    }
    else if (currentAnimationFrame == animationFrames.size())
    {
        currentAnimationFrame = 0;
        scene->clear();
        scene->addPixmap(animationFrames[currentAnimationFrame]);
        currentAnimationFrame++;
        QTimer::singleShot(1000/ui->fpsSlider->value(), this, &View::advanceFrames_slot);
        return;
    }
    else if (currentAnimationFrame != animationFrames.size())
    {
        scene->clear();
        scene->addPixmap(animationFrames[currentAnimationFrame]);
        currentAnimationFrame++;
        QTimer::singleShot(1000/ui->fpsSlider->value(), this, &View::advanceFrames_slot);
        return;
    }
}

/**
 * @brief View::displayFps_slot displays the current fps value in a label
 */
void View::displayFps_slot()
{
    ui->currentFpsLabel->setText(QString::number(ui->fpsSlider->value()));
}

/**
 * @brief View::addNewFrameButtonClicked_slot adds new frame to spriteLayout and UI
 */
void View::addNewFrameButtonClicked_slot()
{
    stopAnimation = true;
    currentAnimationFrame = 0;
    if (ui->addNewFrame_Button)
    {
       int currFrames = spriteLayoutPtr->getNumberOfFrames();
       currFrames += 1;
       QString s = QString::number(currFrames);
        ui->framescomboBox->addItem(s);
    }
}

/**
 * @brief View::currFramesChange_slot repaints UI when create a new frames and it repaint the drawing gird
 */
void View::currFramesChange_slot()
{
    View::repaint();
}

/**
 * @brief View::removeFrameButtonClicked_slot removes and modify a frame from spriteLayout and UI
 */
void View::removeFrameButtonClicked_slot(){
    stopAnimation = true;
    currentAnimationFrame = 0;
    int currIndex = ui->framescomboBox->currentIndex();
    //If we at the initial frame and there are more than 1 frams has been created
    //We will remove the first frame and we remove it and re-arrange the dropdown meue's text.
    if (currIndex == 0 && ui->framescomboBox->count() > 1 )
    {
         ui->framescomboBox->removeItem(currIndex);
         for (int var = 0; var < ui->framescomboBox->count(); var++)
         {
             QString newIndex = QString::number(var + 1);
             ui -> framescomboBox->setItemText(var, newIndex);
         }
    }
    else
    {   //If we at the random # of frams, we will delete it and iterate all the frames we have and re-arrange
        //the dropdown meue's text
        if (currIndex > 0)
        {
            ui->framescomboBox->removeItem(currIndex);
            for (int var = currIndex; var < ui->framescomboBox->count(); var++)
            {
                QString newIndex = QString::number(var + 1);
                ui -> framescomboBox->setItemText(var, newIndex);
            }
        }
    }

}

/**
 * @brief View::selectPen_slot gets called when the pen brush is selected, sets pen to current color
 */
void View::selectPen_slot()
{
    selectedTool = pen;
    ui->penButton->setChecked(true);
    ui->eraserButton->setChecked(false);
}

/**
 * @brief View::selectEraser_slot gets called when eraser brush is selected, erases pixels if used on a frame
 */
void View::selectEraser_slot()
{
    selectedTool = eraser;
    ui->eraserButton->setChecked(true);
    ui->penButton->setChecked(false);
}

/**
 * @brief View::changePenSize_slot adjusts pensize when the value changes on the scroll box
 * @param size
 */
void View::changePenSize_slot(int size)
{
    penSize = size;
}
